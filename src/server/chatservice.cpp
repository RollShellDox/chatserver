#include "chatservice.hpp"
#include "public.hpp"
#include "muduo/base/Logging.h"

using namespace muduo;

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

// 单例模式，隐藏构造函数 //注册消息以及对应的Handler回调函数
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
    _msgHandlerMap.insert({ONE_CHAR_MSG, std::bind(&ChatService::oneChat, this, _1, _2, _3)});
}

// 获取消息对应的处理器
MsgHandler ChatService::getHandler(int msgid)
{
    auto it = _msgHandlerMap.find(msgid);
    // 记录错误日志，msgid没有对应的事件回调
    if (it == _msgHandlerMap.end())
    {
        // 返回一个默认的处理器，空操作
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time)
        {
            LOG_ERROR << "msgid:" << msgid << "can not find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}

// 处理登录业务 id pwd
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int id = js["id"];
    string pwd = js["password"];

    User user = _userModel.query(id);

    if (user.getId() == id && user.getPassword() == pwd)
    {
        if (user.getState() == "online")
        {
            // 该用户已经登录，不允许重复登录
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "该账号已经登录，请重新输入新账号";
            conn->send(response.dump());
        }
        else
        {
            // 登录成功，记录用户连接信息
            {
                lock_guard<mutex> lock(_connMutex);
                _userConnMap.insert({id, conn});
            }

            // 登录成功，更新用户信息 state offline->online
            user.setState("online");
            _userModel.updateState(user);

            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();
            conn->send(response.dump());
        }
    }
    else
    {
        // 该用户不存在,登录失败/用户存在，但是密码错误
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "用户名或密码错误";
        conn->send(response.dump());
    }
}

// 处理注册业务 name password
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    string name = js["name"];
    string pwd = js["password"];

    User user;
    user.setName(name);
    user.setPassword(pwd);
    bool state = _userModel.insert(user);
    if (state)
    {
        // 注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.getId();
        conn->send(response.dump());
    }
    else
    {
        // 注册失败
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}

// 处理客户端异常退出
void ChatService::clientCloseException(const TcpConnectionPtr &conn)
{
    User user;
    {
        lock_guard<mutex> lock(_connMutex);
        for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it)
        {
            if (it->second == conn)
            {
                // 从map表删除用户的连接信息
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }

    // 更新用户的状态信息
    if (user.getId() != -1)
    {
        user.setState("offline");
        _userModel.updateState(user);
    }
}

// 一对一聊天业务
void ChatService::oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int toid = js["to"].get<int>();
    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _userConnMap.find(toid);
        if (it != _userConnMap.end())
        {
            // toid在线，转发消息 服务器主动推送消息给toid用户
            it->second->send(js.dump());
            return;
        }
    }

    // toid 不在线，存储消息
}