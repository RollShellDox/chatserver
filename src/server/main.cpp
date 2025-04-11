#include <iostream>
#include "chatserver.hpp"
using namespace std;

int main()
{
    InetAddress addr("127.0.0.1", 6000);
    EventLoop loop;
    ChatServer server(&loop, addr, "Chatserver");
    server.start();
    loop.loop();
}