#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include "muduo/net/TcpConnection.h"
#include <functional>
#include <unordered_map>
#include <mutex>

using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
#include "usermodel.hpp"
using json = nlohmann::json;

using MsgHandler = function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例服务类对象的接口
    static ChatService *instance();

    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);

private:
    // 单例模式，隐藏构造函数 //注册消息以及对应的Handler回调函数
    ChatService();

    // 存储消息id和业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
};

#endif