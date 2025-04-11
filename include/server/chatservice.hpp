#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include "muduo/net/TcpConnection.h"
#include <functional>
#include <unordered_map>

using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
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

private:
    // 单例模式，隐藏构造函数
    ChatService();

    // 存储消息id和业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
};

#endif