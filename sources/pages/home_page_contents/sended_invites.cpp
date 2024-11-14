#include "sended_invites.h"

//Object part
SendedInvites::SendedInvites(QQmlEngine *engine, HomePage *homePage) :
        InvitesList(engine, homePage) {}

SendedInvites::~SendedInvites() {}

void SendedInvites::update() {
    connect(netManager, &NetworkManager::finishGetProfileSendedInvitesResponseHandling, this, &InvitesList::sendedInvitesInitialization);
    netManager->sendGetProfileSendedInvitesRequest();
}

void SendedInvites::leave() {
    disconnect(netManager, &NetworkManager::finishGetProfileSendedInvitesResponseHandling, this, &InvitesList::sendedInvitesInitialization);
    clearContents();
}

//Methods
void SendedInvites::createInviteItem(Models::Invite &invite){
    if (invite.type != Models::SENDED)
        return;

    auto item = qobject_cast<QQuickItem*>(sendedItemComponent->create(engine->rootContext()));

    item->setProperty("receiverName", invite.receiverName);
    item->setProperty("roomName", invite.roomName);
    item->setProperty("receiverID", QString::number(invite.receiverID));
    item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

    invitesItems[invite.localID] = item;
    item->setParentItem(listContainer);
}
