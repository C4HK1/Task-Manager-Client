#include "received_invites.h"

//Object part
ReceivedInvites::ReceivedInvites(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        InvitesList(engine, container, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileReceivedInvitesResponseHandling, this, &InvitesList::receivedInvitesInitialization);

    netManager->sendGetProfileReceivedInvitesRequest();
}

ReceivedInvites::~ReceivedInvites() {}

//Methods
void ReceivedInvites::createInviteItem(Models::Invite &invite) {
    auto item = qobject_cast<QQuickItem*>(receivedItemComponent->create(engine->rootContext()));

    item->setProperty("senderName", invite.senderName);
    item->setProperty("roomName", invite.roomName);
    item->setProperty("senderID", QString::number(invite.senderID));
    item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

    invite.inviteItem = item;
    item->setParentItem(listContainer);
}
