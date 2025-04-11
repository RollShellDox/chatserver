#include "chatservice.hpp"
#include "public.hpp"

ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

// 单例模式，隐藏构造函数 //注册消息以及对应的Handler回调函数
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(ChatService::reg, this, _1, _2, _3)});
}

// 获取消息对应的处理器
MsgHandler ChatService::getHandler(int msgid)
{
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
}
// 处理注册业务
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
}