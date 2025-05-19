#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include <string>
#include <vector>

// 维护群组信息的操作接口方法
class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);

    // 加入群组
    void addGroup(int userid, int groupid, string role);

    // 查询用户所在群组消息
    vector<Group> queryGroups(int userid);

    // 根据指定的groupid查询用户id列表，除了userid自己，主要用户群聊业务给群组其他成员 群发 消息
    // 其实意思是：用户在群里发消息， 其他群成员需要接收这些消息
    // 具体为： unordered_map<int, TcpConnectionPtr> _userConnMap;存储了用户的链接信息，
    // 通过groupid找到组内userid，再在_userConnMap找到建立的服务器连接，实现消息的转发
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif