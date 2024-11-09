#include "invites_list.h"
#include "network_manager.h"
#include "home_page.h"

//Object part
InvitesList::InvitesList(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        BaseElement(engine, container, "qml/Invites.qml"),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")),
        receivedItemComponent(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/ReceivedInviteListItem.qml"))),
        sendedItemComponent(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/SendedInviteListItem.qml"))),
        homePage(homePage) {
    connect(object, SIGNAL(sortBy(QString, bool)), this, SLOT(sortBy(QString, bool)));

    connect(netManager, &NetworkManager::finishAcceptInviteResponseHandling, this, &InvitesList::finishAcceptInviteResponseHandling);
    connect(netManager, &NetworkManager::finishDeleteReceivedInviteResponseHandling, this, &InvitesList::finishDeleteReceivedInviteResponseHandling);
    connect(netManager, &NetworkManager::finishDeleteSendedInviteResponseHandling, this, &InvitesList::finishDeleteSendedInviteResponseHandling);
}

InvitesList::~InvitesList(){
    for(auto &invite : invites) {
        invite.inviteItem->deleteLater();
        invite.inviteItem = nullptr;
    }
}


//Slots
void InvitesList::sortBy(QString by, bool ascending) {
    for (auto &invite : invites) {
        invite.inviteItem->setParentItem(nullptr);
    }

    auto get_str = [&by](Models::Invite invite) { return (invite.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::sort(invites.begin(), invites.end(),
              [&ascending, &by, &get_str](Models::Invite t1, Models::Invite t2) { return (get_str(t1) < get_str(t2)) ^ !ascending; });

    for(auto &invite : invites) {
        invite.inviteItem->setParentItem(listContainer);
    }
}

void InvitesList::receivedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites) {
    if (!serverStatus.status) {
        this->invites = invites;

        for(auto &invite : this->invites){
            this->createInviteItem(invite, RECEIVED);
            connect(invite.inviteItem, SIGNAL(acceptInvite(int, QString)), this, SLOT(acceptInvite(int, QString)));
            connect(invite.inviteItem, SIGNAL(deleteReceivedInvite(int, int, QString)), this, SLOT(deleteReceivedInvite(int, int, QString)));
        }

        this->sortBy("roomName", true);
    } else {
        qInfo() << "get profile room error status: " << serverStatus.status;
    }
}

void InvitesList::sendedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites) {
    if (!serverStatus.status) {
        this->invites = invites;

        for(auto &invite : this->invites){
            this->createInviteItem(invite, SENDED);
            connect(invite.inviteItem, SIGNAL(deleteSendedInvite(int, int, QString)), this, SLOT(deleteSendedInvite(int, int, QString)));
        }

        this->sortBy("roomName", true);
    } else {
        qInfo() << "get profile room error status: " << serverStatus.status;
    }
}

void InvitesList::acceptInvite(int roomCreatorID, QString roomName) {
    this->netManager->sendAcceptInviteRequest(roomCreatorID, roomName);
}

void InvitesList::deleteReceivedInvite(int senderID, int roomCreatorID, QString roomName) {
    this->netManager->sendDeleteReceivedInviteRequest(senderID, roomCreatorID, roomName);
}

void InvitesList::deleteSendedInvite(int receiverID, int roomCreatorID, QString roomName) {
    this->netManager->sendDeleteSendedInviteRequest(receiverID, roomCreatorID, roomName);
}

void InvitesList::finishAcceptInviteResponseHandling(Models::ServerStatus serverStatus) {
    if (!serverStatus.status) {

    } else {
        qInfo() << "accept invite failed with status: " << serverStatus.status;
    }
}

void InvitesList::finishDeleteReceivedInviteResponseHandling(Models::ServerStatus serverStatus) {
    if (!serverStatus.status) {

    } else {
        qInfo() << "delete received invite failed with status: " << serverStatus.status;
    }
}

void InvitesList::finishDeleteSendedInviteResponseHandling(Models::ServerStatus serverStatus) {
    if (!serverStatus.status) {

    } else {
        qInfo() << "delete sended invite failed with status: " << serverStatus.status;
    }
}
