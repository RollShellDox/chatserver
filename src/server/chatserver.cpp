#include "chatserver.hpp"
#include <functional>
using namespace std;
using namespace placeholders;

#include "json.hpp"
using json = nlohmann::json;

// 初始化服务器
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
}

// 启动服务
void ChatServer::start()
{
    _server.start();
}

// 上报连接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown();
    }
}

// 上报读写事件的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();

    // 数据的反序列化
    json js = json::parse(buf);

    // 条件判断msg_id？ NO！ -->     js[msg_id]获取业务Handler，从而获取对应的conn js time
}