#include <iostream>
#include "chatserver.hpp"
#include "chatservice.hpp"
#include <signal.h>
using namespace std;

void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main()
{
    signal(SIGINT, resetHandler);

    InetAddress addr("127.0.0.1", 6000);
    EventLoop loop;
    ChatServer server(&loop, addr, "Chatserver");
    server.start();
    loop.loop();
}