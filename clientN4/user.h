#ifndef USER_H
#define USER_H

#include <QString>

// 用户类
class User
{
public:
    User(int id = -1, QString name = "", QString password = "", QString state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = password;
        this->state = state;
    }

    void setId(int id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setPassword(QString password) { this->password = password; }
    void setState(QString state) { this->state = state; }

    int getId() { return id; }
    QString getName() { return name; }
    QString getPassword() { return password; }
    QString getState() { return state; }

private:
    int id;
    QString name;
    QString password;
    QString state;
};

#endif // USER_H
