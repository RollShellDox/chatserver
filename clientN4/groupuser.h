#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.h"

// 群组用户类
class GroupUser : public User
{
public:
    void setRole(QString role) { this->role = role; }
    QString getRole() { return role; }

private:
    QString role;
};

#endif // GROUPUSER_H
