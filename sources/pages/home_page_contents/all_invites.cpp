#include "all_invites.h"
#include "received_invites.h"
#include "sended_invites.h"

AllInvites::AllInvites(QQmlEngine *engine, HomePage *homePage) :
        InvitesList(engine, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileReceivedInvitesResponseHandling, this, &InvitesList::receivedInvitesInitialization);
    connect(netManager, &NetworkManager::finishGetProfileSendedInvitesResponseHandling, this, &InvitesList::sendedInvitesInitialization);

    netManager->sendGetProfileReceivedInvitesRequest();
    netManager->sendGetProfileSendedInvitesRequest();
}

AllInvites::~AllInvites() {
    this->receivedItemComponent->deleteLater();
    this->sendedItemComponent->deleteLater();
}

void AllInvites::createInviteItem(Models::Invite &invite) {
    if (invite.type == Models::RECEIVED) {
        auto item = qobject_cast<QQuickItem*>(receivedItemComponent->create(engine->rootContext()));

        item->setProperty("senderName", invite.senderName);
        item->setProperty("roomName", invite.roomName);
        item->setProperty("senderID", QString::number(invite.senderID));
        item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

        invite.inviteItem = item;
        item->setParentItem(listContainer);
    } else {
        auto item = qobject_cast<QQuickItem*>(sendedItemComponent->create(engine->rootContext()));

        item->setProperty("receiverName", invite.receiverName);
        item->setProperty("roomName", invite.roomName);
        item->setProperty("receiverID", QString::number(invite.receiverID));
        item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

        invite.inviteItem = item;
        item->setParentItem(listContainer);
    }
}
