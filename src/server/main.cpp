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

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "commmand valid! example:./ChatServer 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传进的ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);
    signal(SIGINT, resetHandler);

    InetAddress addr(ip, port);
    EventLoop loop;
    ChatServer server(&loop, addr, "Chatserver");
    server.start();
    loop.loop();
}