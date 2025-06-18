#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QListWidgetItem>
#include "user.h"
#include "group.h"
#include "groupuser.h"
#include "public.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_sendButton_clicked();
    void on_addFriendButton_clicked();
    void on_createGroupButton_clicked();
    void on_joinGroupButton_clicked();
    void on_groupSendButton_clicked();
    void on_logoutButton_clicked();
    void on_friendList_itemClicked(QListWidgetItem *item);
    void on_groupList_itemClicked(QListWidgetItem *item);

    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void socketError(QAbstractSocket::SocketError error);

signals:  // 新增信号
    void friendsUpdated();
    void groupsUpdated();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    User currentUser;
    QList<User> friendList;
    QList<Group> groupList;
    bool isLoggedIn;
    int currentChatId; // 当前聊天对象ID（好友或群组）
    bool isGroupChat;  // 当前是否为群聊
    QMap<int, QList<QJsonObject>> pendingPrivateMsgs;
    QMap<int, QList<QJsonObject>> pendingGroupMsgs;

    void showLoginPage();
    void showMainPage();
    void updateFriendList();
    void updateGroupList();
    void showChatHistory(int id, bool isGroup);
    QString getCurrentTime();
    void processServerResponse(const QJsonObject &json);
    void showPrivateMessage(const QJsonObject &json);
    void showGroupMessage(const QJsonObject &json);
};

#endif // MAINWINDOW_H
