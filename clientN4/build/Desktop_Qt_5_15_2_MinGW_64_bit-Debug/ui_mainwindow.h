/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serverIpEdit;
    QLabel *label_2;
    QLineEdit *serverPortEdit;
    QPushButton *connectButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *userIdEdit;
    QLabel *label_4;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLineEdit *regNameEdit;
    QLabel *label_6;
    QLineEdit *regPwdEdit;
    QPushButton *registerButton;
    QWidget *mainPage;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QListWidget *friendList;
    QLabel *label_8;
    QListWidget *groupList;
    QPushButton *addFriendButton;
    QPushButton *createGroupButton;
    QPushButton *joinGroupButton;
    QPushButton *logoutButton;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *chatTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *messageEdit;
    QPushButton *sendButton;
    QPushButton *groupSendButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(loginPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        serverIpEdit = new QLineEdit(groupBox);
        serverIpEdit->setObjectName(QString::fromUtf8("serverIpEdit"));

        horizontalLayout->addWidget(serverIpEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serverPortEdit = new QLineEdit(groupBox);
        serverPortEdit->setObjectName(QString::fromUtf8("serverPortEdit"));

        horizontalLayout->addWidget(serverPortEdit);

        connectButton = new QPushButton(groupBox);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout->addWidget(connectButton);


        verticalLayout_2->addWidget(groupBox);

        tabWidget = new QTabWidget(loginPage);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        userIdEdit = new QLineEdit(tab);
        userIdEdit->setObjectName(QString::fromUtf8("userIdEdit"));

        verticalLayout_3->addWidget(userIdEdit);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        passwordEdit = new QLineEdit(tab);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(passwordEdit);

        loginButton = new QPushButton(tab);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout_3->addWidget(loginButton);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        regNameEdit = new QLineEdit(tab_2);
        regNameEdit->setObjectName(QString::fromUtf8("regNameEdit"));

        verticalLayout_4->addWidget(regNameEdit);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_4->addWidget(label_6);

        regPwdEdit = new QLineEdit(tab_2);
        regPwdEdit->setObjectName(QString::fromUtf8("regPwdEdit"));
        regPwdEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_4->addWidget(regPwdEdit);

        registerButton = new QPushButton(tab_2);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));

        verticalLayout_4->addWidget(registerButton);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        stackedWidget->addWidget(loginPage);
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        horizontalLayout_2 = new QHBoxLayout(mainPage);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QWidget(mainPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_5->addWidget(label_7);

        friendList = new QListWidget(widget);
        friendList->setObjectName(QString::fromUtf8("friendList"));

        verticalLayout_5->addWidget(friendList);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_5->addWidget(label_8);

        groupList = new QListWidget(widget);
        groupList->setObjectName(QString::fromUtf8("groupList"));

        verticalLayout_5->addWidget(groupList);

        addFriendButton = new QPushButton(widget);
        addFriendButton->setObjectName(QString::fromUtf8("addFriendButton"));

        verticalLayout_5->addWidget(addFriendButton);

        createGroupButton = new QPushButton(widget);
        createGroupButton->setObjectName(QString::fromUtf8("createGroupButton"));

        verticalLayout_5->addWidget(createGroupButton);

        joinGroupButton = new QPushButton(widget);
        joinGroupButton->setObjectName(QString::fromUtf8("joinGroupButton"));

        verticalLayout_5->addWidget(joinGroupButton);

        logoutButton = new QPushButton(widget);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        verticalLayout_5->addWidget(logoutButton);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(mainPage);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_6 = new QVBoxLayout(widget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        chatTextEdit = new QTextEdit(widget_2);
        chatTextEdit->setObjectName(QString::fromUtf8("chatTextEdit"));
        chatTextEdit->setReadOnly(true);

        verticalLayout_6->addWidget(chatTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        messageEdit = new QTextEdit(widget_2);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));

        horizontalLayout_3->addWidget(messageEdit);

        sendButton = new QPushButton(widget_2);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout_3->addWidget(sendButton);

        groupSendButton = new QPushButton(widget_2);
        groupSendButton->setObjectName(QString::fromUtf8("groupSendButton"));

        horizontalLayout_3->addWidget(groupSendButton);


        verticalLayout_6->addLayout(horizontalLayout_3);


        horizontalLayout_2->addWidget(widget_2);

        stackedWidget->addWidget(mainPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\242\346\210\267\347\253\257", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\350\277\236\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250IP:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243:", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267ID:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201:", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\347\276\244\347\273\204\345\210\227\350\241\250", nullptr));
        addFriendButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        createGroupButton->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\347\276\244\347\273\204", nullptr));
        joinGroupButton->setText(QCoreApplication::translate("MainWindow", "\345\212\240\345\205\245\347\276\244\347\273\204", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\346\263\250\351\224\200", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        groupSendButton->setText(QCoreApplication::translate("MainWindow", "\347\276\244\345\217\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
