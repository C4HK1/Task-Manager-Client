#include "received_invites.h"

//Object part
ReceivedInvites::ReceivedInvites(QQmlEngine *engine, HomePage *homePage) :
        InvitesList(engine, homePage) {}

ReceivedInvites::~ReceivedInvites() {}

void ReceivedInvites::update() {
    connect(netManager, &NetworkManager::finishGetProfileReceivedInvitesResponseHandling, this, &InvitesList::receivedInvitesInitialization);
    netManager->sendGetProfileReceivedInvitesRequest();
}

void ReceivedInvites::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileReceivedInvitesResponseHandling, this, &InvitesList::receivedInvitesInitialization);
    clearContents();
}

//Methods
void ReceivedInvites::createInviteItem(Models::Invite &invite) {
    auto item = qobject_cast<QQuickItem*>(receivedItemComponent->create(engine->rootContext()));

    item->setProperty("senderName", invite.senderName);
    item->setProperty("roomName", invite.roomName);
    item->setProperty("senderID", QString::number(invite.senderID));
    item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

    invitesItems[invite.localID] = item;
    item->setParentItem(listContainer);
}
