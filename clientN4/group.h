#ifndef GROUP_H
#define GROUP_H

#include <QList>
#include <QString>
#include "groupuser.h"

// 群组类
class Group
{
public:
    Group(int id = -1, QString name = "", QString desc = "")
    {
        this->id = id;
        this->name = name;
        this->desc = desc;
    }

    void setId(int id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setDesc(QString desc) { this->desc = desc; }

    int getId() { return id; }
    QString getName() { return name; }
    QString getDesc() { return desc; }
    QList<GroupUser>& getUsers() { return users; }

private:
    int id;
    QString name;
    QString desc;
    QList<GroupUser> users;
};

#endif // GROUP_Hs
