#ifndef INVITE_MESSAGE_H
#define INVITE_MESSAGE_H

#include <QObject>
#include <QQuickItem>
#include <nlohmann/json.hpp>

#include "base_message.h"

class HomePage;

class InviteMessage : public  BaseMessage {
    Q_OBJECT
public:
    HomePage *homePage;

    //Object part
    InviteMessage(QQmlEngine *engine, QQuickItem *parent, HomePage *homePage, nlohmann::json &messageValue);
    ~InviteMessage();

public slots:
    void switchToInvitesPage();
    void closeInviteMessage();
};

#endif // INVITE_MESSAGE_H
