#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QInputDialog>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socketReadyRead);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::socketError);
    // 新增信号连接 ======================
    connect(this, &MainWindow::friendsUpdated, this, &MainWindow::updateFriendList);
    connect(this, &MainWindow::groupsUpdated, this, &MainWindow::updateGroupList);
    isLoggedIn = false;
    showLoginPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    QString ip = ui->serverIpEdit->text();
    int port = ui->serverPortEdit->text().toInt();

    socket->connectToHost(ip, port);
}

void MainWindow::on_loginButton_clicked()
{
    if(!socket->isOpen()) {
        QMessageBox::warning(this, "错误", "请先连接服务器");
        return;
    }

    int id = ui->userIdEdit->text().toInt();
    QString pwd = ui->passwordEdit->text();

    QJsonObject json;
    json["msgid"] = LOGIN_MSG;
    json["id"] = id;
    json["password"] = pwd;

    QJsonDocument doc(json);
    socket->write(doc.toJson());
}

void MainWindow::on_registerButton_clicked()
{
    if(!socket->isOpen()) {
        QMessageBox::warning(this, "错误", "请先连接服务器");
        return;
    }

    QString name = ui->regNameEdit->text();
    QString pwd = ui->regPwdEdit->text();

    QJsonObject json;
    json["msgid"] = REG_MSG;
    json["name"] = name;
    json["password"] = pwd;

    QJsonDocument doc(json);
    socket->write(doc.toJson());
}

void MainWindow::on_sendButton_clicked()
{
    if(!isLoggedIn || currentChatId == -1 || isGroupChat) {
        QMessageBox::warning(this, "错误", "请先选择好友");
        return;
    }

    QString msg = ui->messageEdit->toPlainText();
    if(msg.isEmpty()) return;

    QJsonObject json;
    json["msgid"] = ONE_CHAT_MSG;
    json["id"] = currentUser.getId();
    json["name"] = currentUser.getName();
    json["to"] = currentChatId;
    json["msg"] = msg;
    json["time"] = getCurrentTime();

    QJsonDocument doc(json);
    socket->write(doc.toJson());

    // 显示自己发送的消息
    ui->chatTextEdit->append(QString("[%1] %2: %3")
                                 .arg(getCurrentTime())
                                 .arg("我")
                                 .arg(msg));

    ui->messageEdit->clear();
}

void MainWindow::on_addFriendButton_clicked()
{
    bool ok;
    int friendId = QInputDialog::getInt(this, "添加好友", "请输入好友ID:", 0, 1, 2147483647, 1, &ok);

    if(ok) {
        QJsonObject json;
        json["msgid"] = ADD_FRIEND_MSG;
        json["id"] = currentUser.getId();
        json["friendid"] = friendId;

        QJsonDocument doc(json);
        socket->write(doc.toJson());
    }
}

void MainWindow::on_createGroupButton_clicked()
{
    bool ok;
    QString groupName = QInputDialog::getText(this, "创建群组", "请输入群组名称:", QLineEdit::Normal, "", &ok);

    if(ok && !groupName.isEmpty()) {
        QString groupDesc = QInputDialog::getText(this, "创建群组", "请输入群组描述:", QLineEdit::Normal, "", &ok);

        QJsonObject json;
        json["msgid"] = CREATE_GROUP_MSG;
        json["id"] = currentUser.getId();
        json["groupname"] = groupName;
        json["groupdesc"] = groupDesc;

        QJsonDocument doc(json);
        socket->write(doc.toJson());
    }
}

void MainWindow::on_joinGroupButton_clicked()
{
    bool ok;
    int groupId = QInputDialog::getInt(this, "加入群组", "请输入群组ID:", 0, 1, 2147483647, 1, &ok);

    if(ok) {
        QJsonObject json;
        json["msgid"] = ADD_GROUP_MSG;
        json["id"] = currentUser.getId();
        json["groupid"] = groupId;

        QJsonDocument doc(json);
        socket->write(doc.toJson());
    }
}

void MainWindow::on_groupSendButton_clicked()
{
    if(!isLoggedIn || currentChatId == -1 || !isGroupChat) {
        QMessageBox::warning(this, "错误", "请先选择群组");
        return;
    }

    QString msg = ui->messageEdit->toPlainText();
    if(msg.isEmpty()) return;

    QJsonObject json;
    json["msgid"] = GROUP_CHAT_MSG;
    json["id"] = currentUser.getId();
    json["name"] = currentUser.getName();
    json["groupid"] = currentChatId;
    json["msg"] = msg;
    json["time"] = getCurrentTime();

    QJsonDocument doc(json);
    socket->write(doc.toJson());

    // 显示自己发送的消息
    ui->chatTextEdit->append(QString("群[%1] [%2] 我: %3")
                                 .arg(currentChatId)
                                 .arg(getCurrentTime())
                                 .arg(msg));

    ui->messageEdit->clear();
}

void MainWindow::on_logoutButton_clicked()
{
    QJsonObject json;
    json["msgid"] = LOGIN_OUT_MSG;
    json["id"] = currentUser.getId();

    QJsonDocument doc(json);
    socket->write(doc.toJson());

    isLoggedIn = false;
    showLoginPage();
}

void MainWindow::on_friendList_itemClicked(QListWidgetItem *item)
{
    int friendId = item->data(Qt::UserRole).toInt();
    currentChatId = friendId;
    isGroupChat = false;

    ui->chatTextEdit->clear();
    showChatHistory(friendId, false);

    for (auto &msg : pendingPrivateMsgs.value(currentChatId)) {
        showPrivateMessage(msg);
    }
    pendingPrivateMsgs.remove(currentChatId);
}

void MainWindow::on_groupList_itemClicked(QListWidgetItem *item)
{
    int groupId = item->data(Qt::UserRole).toInt();
    currentChatId = groupId;
    isGroupChat = true;

    ui->chatTextEdit->clear();
    showChatHistory(groupId, true);
    for (auto &msg : pendingGroupMsgs.value(currentChatId)) {
        showPrivateMessage(msg);
    }
    pendingGroupMsgs.remove(currentChatId);
}

void MainWindow::socketConnected()
{
    ui->statusBar->showMessage("已连接到服务器", 3000);
}

void MainWindow::socketDisconnected()
{
    ui->statusBar->showMessage("与服务器断开连接", 3000);
    isLoggedIn = false;
    showLoginPage();
}

void MainWindow::socketReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(doc.isNull()) return;

    QJsonObject json = doc.object();
    processServerResponse(json);
}

void MainWindow::socketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    ui->statusBar->showMessage("连接错误: " + socket->errorString(), 3000);
}

void MainWindow::showLoginPage()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->userIdEdit->clear();
    ui->passwordEdit->clear();
    ui->regNameEdit->clear();
    ui->regPwdEdit->clear();
    ui->serverIpEdit->setText("192.168.88.128");
    ui->serverPortEdit->setText("6000");
}

void MainWindow::showMainPage()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->friendList->clear();
    ui->groupList->clear();
    ui->chatTextEdit->clear();
    ui->messageEdit->clear();

    updateFriendList();
    updateGroupList();
}

void MainWindow::updateFriendList()
{
    // ui->friendList->clear();
    // for(User &user : friendList) {
    //     QString itemText = QString("%1 (%2)").arg(user.getName()).arg(user.getId());
    //     if(user.getState() == "online") {
    //         itemText += " [在线]";
    //     } else {
    //         itemText += " [离线]";
    //     }

    //     QListWidgetItem *item = new QListWidgetItem(itemText);
    //     item->setData(Qt::UserRole, user.getId());
    //     ui->friendList->addItem(item);
    // }
    ui->friendList->clear();
    for(User &user : friendList) {
        QString state = (user.getState() == "online") ? "[在线]" : "[离线]";
        QString itemText = QString("%1 %2 (ID: %3)")
                               .arg(state)
                               .arg(user.getName())
                               .arg(user.getId());

        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, user.getId());
        ui->friendList->addItem(item);
    }
}

void MainWindow::updateGroupList()
{
    // ui->groupList->clear();
    // for(Group &group : groupList) {
    //     QString itemText = QString("%1 (%2)").arg(group.getName()).arg(group.getId());
    //     QListWidgetItem *item = new QListWidgetItem(itemText);
    //     item->setData(Qt::UserRole, group.getId());
    //     ui->groupList->addItem(item);
    // }

    ui->groupList->clear();
    for(Group &group : groupList) {
        QString itemText = QString("%1 (ID: %2)")
        .arg(group.getName())
            .arg(group.getId());

        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, group.getId());
        ui->groupList->addItem(item);
    }
}

void MainWindow::showChatHistory(int id, bool isGroup)
{
    // 这里可以添加从本地数据库加载聊天记录的功能
    // 目前只是清空并显示提示信息
    if(isGroup) {
        ui->chatTextEdit->append(QString("--- 群聊 %1 的聊天记录 ---").arg(id));
    } else {
        ui->chatTextEdit->append(QString("--- 与 %1 的聊天记录 ---").arg(id));
    }
}

QString MainWindow::getCurrentTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void MainWindow::processServerResponse(const QJsonObject &json)
{
    qDebug() << "收到服务端响应：" << json;
    int msgType = json["msgid"].toInt();

    switch(msgType) {
    case LOGIN_MSG_ACK:
        qDebug() << "原始好友数据:" << json["friends"].toArray();
        qDebug() << "原始群组数据:" << json["groups"].toArray();
        if(json["errno"].toInt() == 0) {
            // 登录成功
            currentUser.setId(json["id"].toInt());
            currentUser.setName(json["name"].toString());

            // // ===== 修复好友列表处理 =====
            // if(json.contains("friends")) {
            //     friendList.clear();
            //     QJsonArray friends = json["friends"].toArray();
            //     for(const QJsonValue &val : friends) {
            //         QJsonObject obj = val.toObject();
            //         User user;
            //         user.setId(obj["id"].toInt());
            //         user.setName(obj["name"].toString());
            //         user.setState(obj.contains("state") ? obj["state"].toString() : "offline");
            //         friendList.append(user);
            //     }
            //     emit friendsUpdated(); // 触发UI更新
            // }
            // 修改后的好友列表处理
            if(json.contains("friends")) {
                friendList.clear();
                QJsonArray friends = json["friends"].toArray();
                for(const QJsonValue &val : friends) {
                    // 先获取JSON字符串
                    QString friendStr = val.toString();
                    // 转换为JSON对象
                    QJsonDocument doc = QJsonDocument::fromJson(friendStr.toUtf8());
                    if(!doc.isNull()) {
                        QJsonObject obj = doc.object();
                        User user;
                        user.setId(obj["id"].toInt());
                        user.setName(obj["name"].toString());
                        user.setState(obj["state"].toString());
                        friendList.append(user);
                        qDebug() << "解析好友:" << user.getId() << user.getName();
                    }
                }
                emit friendsUpdated();
            }

            // // ===== 修复群组列表处理 =====
            // if(json.contains("groups")) {
            //     groupList.clear();
            //     QJsonArray groups = json["groups"].toArray();
            //     for(const QJsonValue &val : groups) {
            //         QJsonObject obj = val.toObject();
            //         Group group;
            //         group.setId(obj["id"].toInt());
            //         group.setName(obj["groupname"].toString());
            //         group.setDesc(obj["groupdesc"].toString());
            //         groupList.append(group);
            //     }
            //     emit groupsUpdated(); // 触发UI更新
            // }
            // 修改后的群组列表处理
            if(json.contains("groups")) {
                groupList.clear();
                QJsonArray groups = json["groups"].toArray();
                for(const QJsonValue &val : groups) {
                    // 处理第一层JSON字符串
                    QJsonDocument groupDoc = QJsonDocument::fromJson(val.toString().toUtf8());
                    if(!groupDoc.isNull()) {
                        QJsonObject groupObj = groupDoc.object();
                        Group group;
                        group.setId(groupObj["id"].toInt());
                        group.setName(groupObj["groupname"].toString());
                        group.setDesc(groupObj["groupdesc"].toString());

                        // 处理嵌套的users数组
                        QJsonArray users = QJsonDocument::fromJson(
                                               groupObj["users"].toString().toUtf8()
                                               ).array();

                        for(const QJsonValue &uVal : users) {
                            QJsonObject userObj = QJsonDocument::fromJson(
                                                      uVal.toString().toUtf8()
                                                      ).object();
                            GroupUser user;
                            user.setId(userObj["id"].toInt());
                            user.setName(userObj["name"].toString());
                            user.setRole(userObj["role"].toString());
                            user.setState(userObj["state"].toString());
                            group.getUsers().append(user);
                        }

                        groupList.append(group);
                        qDebug() << "解析群组:" << group.getId() << group.getName();
                    }
                }
                emit groupsUpdated();
            }

            // 显示离线消息
            // QJsonArray offlineMsgs = json["offlinemsg"].toArray();
            // for(const QJsonValue &val : offlineMsgs) {
            //     QJsonObject msg = val.toObject();
            //     if(msg["msgid"].toInt() == ONE_CHAT_MSG) {
            //         showPrivateMessage(msg);
            //     } else if(msg["msgid"].toInt() == GROUP_CHAT_MSG) {
            //         showGroupMessage(msg);
            //     }
            // }

            // 显示离线消息-20250609-第一版
            // QJsonArray offlineMsgs = json["offlinemsg"].toArray();
            // for(const QJsonValue &val : offlineMsgs) {
            //     QJsonObject msg = val.toObject();

            //     // 私聊消息处理
            //     if(msg["msgid"].toInt() == ONE_CHAT_MSG) {
            //         // 显示规则：如果消息是发给我的，或当前正在和发送者聊天
            //         if(msg["to"].toInt() == currentUser.getId() ||
            //             msg["id"].toInt() == currentChatId)
            //         {
            //             showPrivateMessage(msg);
            //         }
            //     }
            //     // 群聊消息处理
            //     else if(msg["msgid"].toInt() == GROUP_CHAT_MSG) {
            //         // 显示规则：如果我在该群组中
            //         bool isMyGroup = false;
            //         for(Group &group : groupList) {  // 直接遍历检查
            //             if(group.getId() == msg["groupid"].toInt()) {
            //                 isMyGroup = true;
            //                 break;
            //             }
            //         }
            //         if(isMyGroup) {
            //             showGroupMessage(msg);
            //         }
            //     }
            // }

            if (json.contains("offlinemsg")) {
                QJsonArray msgArray = json["offlinemsg"].toArray();
                qDebug() << "待处理离线消息数：" << msgArray.size();

                for (const QJsonValue &val : msgArray) {
                    // 解析消息（处理双重JSON编码）
                    QJsonObject msg = val.isString()
                                          ? QJsonDocument::fromJson(val.toString().toUtf8()).object()
                                          : val.toObject();

                    qDebug() << "正在处理消息：" << msg;

                    // 私聊消息处理 (msgid 6)
                    if (msg["msgid"].toInt() == ONE_CHAT_MSG) {
                        // 显示规则：消息是发给我的 或 当前正在和发送者聊天
                        if (msg["to"].toInt() == currentUser.getId() ||
                            (!isGroupChat && msg["id"].toInt() == currentChatId))
                        {
                            QString displayMsg = QString("[%1] %2: %3")
                            .arg(msg["time"].toString())
                                .arg(msg["name"].toString())
                                .arg(msg["msg"].toString());

                            ui->chatTextEdit->append(displayMsg);
                            qDebug() << "已显示私聊消息：" << displayMsg;
                        }
                    }
                    // 群聊消息处理 (msgid 10)
                    else if (msg["msgid"].toInt() == GROUP_CHAT_MSG) {
                        // 检查是否在群组中
                        bool inGroup = std::any_of(groupList.begin(), groupList.end(),
                                                   [&msg](Group &g) { return g.getId() == msg["groupid"].toInt(); });

                        if (inGroup) {
                            QString displayMsg = QString("群[%1][%2] %3: %4")
                                                     .arg(msg["groupid"].toInt())
                                                     .arg(msg["time"].toString())
                                                     .arg(msg["name"].toString())
                                                     .arg(msg["msg"].toString());

                            ui->chatTextEdit->append(displayMsg);
                            qDebug() << "已显示群消息：" << displayMsg;
                        }
                    }
                }
            }

            isLoggedIn = true;
            showMainPage();
            QMessageBox::information(this, "成功", "登录成功");
        } else {
            QMessageBox::warning(this, "错误", json["errmsg"].toString());
        }
        break;

    case REG_MSG_ACK:
        if(json["errno"].toInt() == 0) {
            QMessageBox::information(this, "成功",
                                     QString("注册成功，您的ID是 %1").arg(json["id"].toInt()));
        } else {
            QMessageBox::warning(this, "错误", json["errmsg"].toString());
        }
        break;

    case ONE_CHAT_MSG:
        showPrivateMessage(json);
        break;

    case GROUP_CHAT_MSG:
        showGroupMessage(json);
        break;

    case ADD_FRIEND_MSG:
        if(json["errno"].toInt() == 0) {
            QMessageBox::information(this, "成功", "好友添加成功");
            // 更新好友列表
            User newFriend;
            newFriend.setId(json["friendid"].toInt());
            newFriend.setName(json["friendname"].toString());
            newFriend.setState("offline");
            friendList.append(newFriend);
            updateFriendList();
        } else {
            QMessageBox::warning(this, "错误", json["errmsg"].toString());
        }
        break;

    case CREATE_GROUP_MSG:
        if(json["errno"].toInt() == 0) {
            QMessageBox::information(this, "成功",
                                     QString("群组创建成功，群ID是 %1").arg(json["groupid"].toInt()));
            // 更新群组列表
            Group newGroup;
            newGroup.setId(json["groupid"].toInt());
            newGroup.setName(json["groupname"].toString());
            newGroup.setDesc(json["groupdesc"].toString());
            groupList.append(newGroup);
            updateGroupList();
        } else {
            QMessageBox::warning(this, "错误", json["errmsg"].toString());
        }
        break;

    case ADD_GROUP_MSG:
        if(json["errno"].toInt() == 0) {
            QMessageBox::information(this, "成功", "已加入群组");
            // 更新群组列表
            Group newGroup;
            newGroup.setId(json["groupid"].toInt());
            newGroup.setName(json["groupname"].toString());
            newGroup.setDesc(json["groupdesc"].toString());
            groupList.append(newGroup);
            updateGroupList();
        } else {
            QMessageBox::warning(this, "错误", json["errmsg"].toString());
        }
        break;

    case LOGIN_OUT_MSG:
        QMessageBox::information(this, "提示", "已注销");
        isLoggedIn = false;
        showLoginPage();
        break;
    }
}

void MainWindow::showPrivateMessage(const QJsonObject &json)
{
    // 只显示当前选中好友的消息-20250609
    if(json["to"].toInt() != currentChatId && json["id"].toInt() != currentChatId) {
        return;
    }

    QString time = json["time"].toString();
    int id = json["id"].toInt();
    QString name = json["name"].toString();
    QString msg = json["msg"].toString();

    ui->chatTextEdit->append(QString("[%1] %2(%3): %4")
                                 .arg(time)
                                 .arg(name)
                                 .arg(id)
                                 .arg(msg));
}

void MainWindow::showGroupMessage(const QJsonObject &json)
{
    // 只显示当前选中群组的消息-20250609
    if(json["groupid"].toInt() != currentChatId) {
        return;
    }

    QString time = json["time"].toString();
    int groupId = json["groupid"].toInt();
    int id = json["id"].toInt();
    QString name = json["name"].toString();
    QString msg = json["msg"].toString();

    ui->chatTextEdit->append(QString("群[%1] [%2] %3(%4): %5")
                                 .arg(groupId)
                                 .arg(time)
                                 .arg(name)
                                 .arg(id)
                                 .arg(msg));
}
