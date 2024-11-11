#include "sended_invites.h"

//Object part
SendedInvites::SendedInvites(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        InvitesList(engine, container, homePage) {
    connect(netManager, &NetworkManager::finishGetProfileSendedInvitesResponseHandling, this, &InvitesList::sendedInvitesInitialization);

    netManager->sendGetProfileSendedInvitesRequest();
}

SendedInvites::~SendedInvites() {}

//Methods
void SendedInvites::createInviteItem(Models::Invite &invite){
    if (invite.type != Models::SENDED)
        return;

    auto item = qobject_cast<QQuickItem*>(sendedItemComponent->create(engine->rootContext()));

    item->setProperty("receiverName", invite.receiverName);
    item->setProperty("roomName", invite.roomName);
    item->setProperty("receiverID", QString::number(invite.receiverID));
    item->setProperty("roomCreatorID", QString::number(invite.roomCreatorID));

    invite.inviteItem = item;
    item->setParentItem(listContainer);
}
