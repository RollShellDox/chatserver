#include "json.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

using namespace std;
using json = nlohmann::json;

#include "user.hpp"
#include "group.hpp"
#include "public.hpp"

#define DEBUG_A

// 记录当前系统登录的用户信息
User g_currentUser;
// 记录当前登录用户的好友列表信息
vector<User> g_currentUserFriendList;
// 记录当前登录用户的群组列表信息
vector<Group> g_currentUserGroupList;

// 显示当前登录成功用户的基本信息
void showCurrentUserData();
// 接受线程
void readTaskHandler(int clientfd);
// 获取系统时间（聊天信息需要添加时间信息）
string getCurrentTime();
// 主聊天页面程序
void mainManu(int clientfd);

// 聊天客户端程序实现，main线程用作发送线程，子线程用作接受线程
int main(int argc, char **argv)
{
    // 提示输入参数连接客户端
    if (argc < 3)
    {
        cerr << "command invalid! example: ./ChatClient 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 创建client端的socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientfd)
    {
        cerr << "socket create error" << endl;
        exit(-1);
    }

    // 填写client需要连接的server信息 ip+port
    sockaddr_in server;
    memset(&server, 0, sizeof(sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // client和server进行连接
    if (-1 == connect(clientfd, (sockaddr *)&server, sizeof(sockaddr_in)))
    {
        cerr << "connect server error" << endl;
        close(clientfd);
        exit(-1);
    }

    // main线程用于接收用户输入，负责发送数据
    for (;;)
    {
        // 显示首页面菜单 登录、注册、退出
        cout << "========================" << endl;
        cout << "1.login" << endl;
        cout << "2.register" << endl;
        cout << "3.quit" << endl;
        cout << "========================" << endl;
        cout << "choice:";
        int choice = 0;
        cin >> choice;
        cin.get(); // 读掉缓冲区残留的回车

        switch (choice)
        {
        case 1: // login业务
        {
            int id = 0;
            char pwd[50] = {0};
            cout << "userid:";
            cin >> id;
            cin.get(); // 读掉缓冲区残留的回车
            cout << "userpassword:";
            cin.getline(pwd, 50);

            json js;
            js["msgid"] = LOGIN_MSG;
            js["id"] = id;
            js["password"] = pwd;
            string request = js.dump();

            int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
            if (len == -1)
            {
                cerr << "send login msg error" << request << endl;
            }
            else
            {
                char buffer[1024] = {0};
                len = recv(clientfd, buffer, 1024, 0);
                if (len == -1)
                {
                    cerr << "recv login response error" << request << endl;
                }
                else
                {
                    json responsejs = json::parse(buffer);
                    if (0 != responsejs["errno"].get<int>()) // 登录失败
                    {
                        cerr << responsejs["errmsg"] << endl;
                    }
                    else // 登录成功
                    {
                        // 记录当前用户的id和name
                        g_currentUser.setId(responsejs["id"].get<int>());
                        g_currentUser.setName(responsejs["name"]);
                        // 记录当前用户的好友列表信息
                        if (responsejs.contains("friends"))
                        {
                            vector<string> vec = responsejs["friends"];
                            for (string &str : vec)
                            {
                                json js = json::parse(str);
                                User user;
                                user.setId(js["id"].get<int>());
                                user.setName(js["name"]);
                                user.setState(js["state"]);
                                g_currentUserFriendList.push_back(user);
                            }
                        }

                        // 记录当前用户的群组列表信息
                        if (responsejs.contains("groups"))
                        {
                            vector<string> vec1 = responsejs["groups"];
                            for (string &groupstr : vec1)
                            {
                                json grpjs = json::parse(groupstr);
                                Group group;
                                group.setId(grpjs["id"].get<int>());
                                group.setName(grpjs["groupname"]);
                                group.setDesc(grpjs["groupdesc"]);

                                vector<string> vec2 = grpjs["users"];
                                for (string &userstr : vec2)
                                {
                                    GroupUser user;
                                    json js = json::parse(userstr);
                                    user.setId(js["id"].get<int>());
                                    user.setName(js["name"]);
                                    user.setRole(js["role"]);
                                    group.getUsers().push_back(user);
                                }

                                g_currentUserGroupList.push_back(group);
                            }
                        }

                        // 显示登录用户的基本信息；
                        showCurrentUserData();

                        // 显示当前用户的离线消息 个人聊天消息或者群组消息
                        if (responsejs.contains("offlinemsg"))
                        {
                            vector<string> vec = responsejs["offlinemsg"];
                            for (string &str : vec)
                            {
                                json js = json::parse(str);
                                // time + [id] + name + "said" + xxx;
                                cout << js["time"] << "[" << js["id"] << "]" << js["name"] << ":" << js["msg"] << endl;
                            }
                        }

                        // 登陆成功，启动接收线程负责接收数据；
                        std::thread readTask(readTaskHandler, clientfd); // pthread_create
                        readTask.detach();                               // pthread_detach

                        // 进入聊天主菜单界面
                        mainManu(clientfd);
                    }
                }
            }
            break;
        }

        case 2: // register业务
        {
            char name[50] = {0};
            char pwd[50] = {0};
            cout << "username:";
            cin.getline(name, 50); // 不使用cin >> ,因为非法字符都会终止
            cout << "userpassword:";
            cin.getline(pwd, 50);

            json js;
            js["msgid"] = REG_MSG;
            js["name"] = name;
            js["password"] = pwd;
            string request = js.dump();

            int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
            if (len == -1)
            {
                cerr << "send reg msg error" << request << endl;
            }
            else
            {
                char buffer[1024] = {0};
                len = recv(clientfd, buffer, 1024, 0);
                if (len == -1)
                {
                    cerr << "recv reg response error" << request << endl;
                }
                else
                {
                    json responsejs = json ::parse(buffer);
                    if (0 != responsejs["errno"].get<int>()) // 注册失败
                    {
                        cerr << name << "is already exist,register error" << endl;
                    }
                    else // 注册成功
                    {
                        cout << name << "register success,userid is " << responsejs["id"] << ",do not forget it!" << endl;
                    }
                }
            }
            break;
        }

        case 3: // quit 业务
        {
            close(clientfd);
            exit(0);
            break;
        }
        default:
        {
            cerr << "invalid input!" << endl;
            break;
        }
        }
    }
}

// 显示当前登录成功用户的基本信息
void showCurrentUserData()
{
    cout << "====================login user=======================" << endl;
    cout << "current id login user => id:" << g_currentUser.getId() << " " << "name:" << g_currentUser.getName() << endl;
    cout << "--------------------friend list----------------------" << endl;
    if (!g_currentUserFriendList.empty())
    {
        for (User &user : g_currentUserFriendList)
        {
            cout << user.getId() << " " << user.getName() << " " << user.getState() << endl;
        }
    }
    cout << "--------------------group list-----------------------" << endl;
    if (!g_currentUserGroupList.empty())
    {
        for (Group &group : g_currentUserGroupList)
        {
            cout << group.getId() << " " << group.getName() << " " << group.getDesc() << endl;
            for (GroupUser &user : group.getUsers())
            {
                cout << user.getId() << " " << user.getName() << " " << user.getState() << " " << user.getRole() << endl;
            }
        }
    }
    cout << "=====================================================" << endl;
}

/*
void readTaskHandler(int clientfd)
{
    for (;;)
    {
        char buffer[1024] = {0};
        int len = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0)
        {
            cerr << "Connection closed or error" << endl;
            close(clientfd);
            exit(-1);
        }

        try
        {
            json js = json::parse(buffer);
            cout << "Received raw JSON: " << js.dump() << endl; // 调试：打印原始 JSON

            // 检查必需字段是否存在且不为 null
            if (!js.contains("msgid") || js["msgid"].is_null())
            {
                cerr << "Invalid message: missing or null msgid" << endl;
                continue;
            }

            int msgid = js["msgid"].get<int>(); // 现在确保 msgid 是数字

            if (ONE_CHAT_MSG == msgid)
            {
                // 检查聊天消息的必需字段
                if (!js.contains("id") || js["id"].is_null() ||
                    !js.contains("name") || js["name"].is_null() ||
                    !js.contains("msg") || js["msg"].is_null() ||
                    !js.contains("time") || js["time"].is_null())
                {
                    cerr << "Invalid chat message: missing required fields" << endl;
                    continue;
                }

                // 现在可以安全地调用 get<int>() 和 get<string>()
                cout << js["time"].get<string>() << " ["
                     << js["id"].get<int>() << "] "
                     << js["name"].get<string>() << ": "
                     << js["msg"].get<string>() << endl;
            }
            // 可以添加其他消息类型的处理...
        }
        catch (const json::exception &e)
        {
            cerr << "JSON parse error: " << e.what() << endl;
            cerr << "Received data: " << buffer << endl; // 打印原始数据以便调试
        }
    }
}
*/

// 接受线程
void readTaskHandler(int clientfd)
{
    for (;;)
    {
        char buffer[4096] = {0};
        int len = recv(clientfd, buffer, 4096, 0);
        if (len == -1 || len == 0)
        {
            close(clientfd);
            exit(-1);
        }
        // 接收chatserver转发的数据，反序列化为json对象
        json js = json::parse(buffer);
        // cout << "Received: " << js.dump() << endl; // 在 readTaskHandler 中
        if (ONE_CHAT_MSG == js["msgid"].get<int>())
        {
            cout << js["time"].get<string>() << "[" << js["id"] << "]" << js["name"].get<string>()
                 << ":" << js["msg"].get<string>() << endl;
            continue;
        }
    }
}

// 获取系统时间（聊天信息需要添加时间信息）
string getCurrentTime()
{
    // 获取当前时间点
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // 将时间点转换为本地时间结构体
    struct tm *ptm = localtime(&tt);

    // 准备一个字符数组来存储格式化后的时间字符串
    char date[60] = {0};

    // 使用sprintf将时间结构体中的信息格式化为指定的字符串格式
    sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
            (int)ptm->tm_year + 1900, // 年份，tm_year是从1900年开始的年数
            (int)ptm->tm_mon + 1,     // 月份，tm_mon是从0开始的，所以需要加1
            (int)ptm->tm_mday,        // 日
            (int)ptm->tm_hour,        // 小时
            (int)ptm->tm_min,         // 分钟
            (int)ptm->tm_sec);        // 秒

    // 返回格式化后的时间字符串
    return std::string(date);
}

// Command handler function declarations
void help(int, string);        // "help" command handler
void chat(int, string);        // "chat" command handler (private message)
void addfriend(int, string);   // "addfriend" command handler
void creategroup(int, string); // "creategroup" command handler
void addgroup(int, string);    // "addgroup" command handler
void groupchat(int, string);   // "groupchat" command handler
void loginout(int, string);    // "loginout" command handler

// 系统支持的客户端命令列表
unordered_map<string, string> commandMap = {
    {"help", "显示所有支持的命令，格式help"},
    {"chat", "一对一聊天，格式chat:friendid:message"},
    {"addfriend", "添加好友，格式addfriend:friendid"},
    {"creategroup", "创建群组，格式creategroup:groupname:groupdesc"},
    {"addgroup", "加入群组，格式addgroup:groupid"},
    {"groupchat", "群聊，格式groupchat:groupid:message"},
    {"loginout", "注销，格式loginout"}};

// 注册系统支持的客户端命令处理
unordered_map<string, function<void(int, string)>> commandHandlerMap = {
    {"help", help},
    {"chat", chat},
    {"addfriend", addfriend},
    {"creategroup", creategroup},
    {"addgroup", addgroup},
    {"groupchat", groupchat},
    {"loginout", loginout}};

// 主聊天页面程序
void mainManu(int clientfd)
{
    help(clientfd, "");
    char buffer[1024] = {0};
    for (;;)
    {
        cin.getline(buffer, 1024);
        string commandbuf(buffer);
        string command; // 存储命令
        int idx = commandbuf.find(":");
        if (-1 == idx)
        {
            command = commandbuf; // help、loginout存进去，不合法命令也没问题---因为它不在表内;
        }
        else
        {
            command = commandbuf.substr(0, idx);
        }
        auto it = commandHandlerMap.find(command);
        if (commandHandlerMap.end() == it)
        {
            cerr << "invalid input commmand!" << endl;
            continue;
        }
        // 调用相应命令的事件处理回调，mainManu对修改封闭，添加新功能不需要修改该函数
        it->second(clientfd, commandbuf.substr(idx + 1, commandbuf.size() - idx));
    }
}

// Command handler function declarations
void help(int clientfd, string str = "") // "help" command handler
{
    cout << "show command list >>>" << endl;
    for (auto &p : commandMap)
    {
        cout << p.first << " : " << p.second << endl;
    }
    cout << endl;
}

void chat(int clientfd, string str) // "chat" command handler (private message)
{
    int idx = str.find(":");
    if (-1 == idx)
    {
        cerr << "Chat command invalid " << endl;
    }
    int friendid = atoi(str.substr(0, idx).c_str());
    string message = str.substr(idx + 1, str.size() - idx);

    json js;
    js["msgid"] = ONE_CHAT_MSG;
    js["id"] = g_currentUser.getId();
    js["name"] = g_currentUser.getName();
    js["to"] = friendid;
    js["msg"] = message;
    js["time"] = getCurrentTime();
    string buffer = js.dump();

    cout << "Sending: " << js.dump() << endl; // 在 chat() 中

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "send one_chat msg error ->" << buffer << endl;
    }
}

void addfriend(int clientfd, string str) // "addfriend" command handler
{
    int friendid = atoi(str.c_str());
    json js;
    js["msgid"] = ADD_FRIEND_MSG;
    js["id"] = g_currentUser.getId();
    js["friendid"] = friendid;
    string buffer = js.dump();

    // ！！！！！！！！strlen部分可能有边界问题，需要注意
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    {
        if (-1 == len)
        {
            cerr << "send addfriend msg error ->" << buffer << endl;
        }
    }
}

void creategroup(int fd, string str) // "creategroup" command handler
{
}
void addgroup(int clientfd, string str) // "addgroup" command handler
{
}
void groupchat(int fd, string str) // "groupchat" command handler
{
}
void loginout(int fd, string str) // "loginout" command handler
{
}

// void creategroup(int clientfd, string str) // "creategroup" command handler
// {
//     int idx = str.find(":");
//     if (-1 == idx)
//     {
//         cerr << "creategroup command invalid " << endl;
//     }
//     string groupname = str.substr(0, idx);
//     string groupdesc = str.substr(idx + 1, str.size() - idx);

//     json js;
//     js["msgid"] = CREATE_GROUP_MSG;
//     js["groupname"] = groupname;
//     js["groupdesc"] = groupdesc;

//     string buffer = js.dump();
//     int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
//     {
//         if (-1 == len)
//         {
//             cerr << "send creategroup msg error ->" << buffer << endl;
//         }
//     }
// }

// void addgroup(int clientfd, string str)  // "addgroup" command handler
// {
//     int groupid = atoi(str.c_str());

//     json js;
//     js["msgid"] = ADD_GROUP_MSG;
//     js["groupid"] = groupid;

//     string buffer = js.dump();
//     int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
//     {
//         if (-1 == len)
//         {
//             cerr << "send addgroup msg error ->" << buffer << endl;
//         }
//     }

// }

// void groupchat(int clientfd, string str) // "groupchat" command handler
// {
//     int idx = str.find(":");
//     if(-1 == idx)
//     {
//         cerr << "groupchat command invalid" << endl;
//     }

//     int groupid = atoi(str.substr(0,idx).c_str());
//     string message = str.substr(idx+1,str.size()-idx);

//     json js;
//     js["msgid"] = GROUP_CHAT_MSG;
//     js["userid"] = g_currentUser.getId();
//     js["groupid"] = groupid;
//     js["message"] = message;
//     string buffer = js.dump();

//     int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
//     {
//         if (-1 == len)
//         {
//             cerr << "send groupchat msg error ->" << buffer << endl;
//         }
//     }
// }

// void loginout(int clientfd, string)  // "loginout" command handler
// {
//     close(clientfd);
// }