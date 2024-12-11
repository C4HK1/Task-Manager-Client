#include <QSignalMapper>

#include "invite_message.h"
#include "home_page.h"
#include "base_message.h"
#include "kafka/consumer.h"

//Object part
InviteMessage::InviteMessage(QQmlEngine *engine, QQuickItem *parent, HomePage *homePage, nlohmann::json &messageValue) :
        BaseMessage(engine, parent, "qml/MainWorkspaceElements/InviteMessage.qml"),
        homePage(homePage) {
    object->setProperty("inviteSenderName", messageValue.at("invite sender name").dump().c_str());
    object->setProperty("roomName", messageValue.at("room name").dump().c_str());

    connect(this->getObject(), SIGNAL(switchToInvitesPage()), this, SLOT(switchToInvitesPage()));
    connect(this->getObject(), SIGNAL(closeInviteMessage()), this, SLOT(closeInviteMessage()));
}

InviteMessage::~InviteMessage() {
}

//Slots
void InviteMessage::switchToInvitesPage() {
    this->homePage->switchToReceivedInvites();
}

void InviteMessage::closeInviteMessage() {
    this->homePage->closeMessage();
}
