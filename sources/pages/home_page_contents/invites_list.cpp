#include "invites_list.h"
#include "network_manager.h"
#include "home_page.h"

//Object part
InvitesList::InvitesList(QQmlEngine *engine, HomePage *homePage) :
        BasePage(engine, "qml/Invites.qml"),
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
    clearContents();
    sendedItemComponent->deleteLater();
    receivedItemComponent->deleteLater();
}

void InvitesList::clearContents() {
    for(auto &invite : invites) {
        invitesItems[invite.localID]->deleteLater();
    }

    invitesItems.clear();
}

//Slots
void InvitesList::sortBy(QString by, bool ascending) {
    for (auto &invite : invites) {
        invitesItems[invite.localID]->setParentItem(nullptr);
    }

    auto get_str = [&by](Models::Invite invite) { return (invite.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::stable_sort(invites.begin(), invites.end(),
              [&ascending, &by, &get_str](const Models::Invite t1, const Models::Invite t2) { return (get_str(t1) < get_str(t2)) ^ !ascending; });

    for(auto &invite : invites) {
        invitesItems[invite.localID]->setParentItem(listContainer);
    }
}

void InvitesList::receivedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites) {
    if (!serverStatus.status) {
        this->invites.append(invites);

        for(auto &invite : this->invites){
            if (this->find(invite, invites) == -1)
                continue;

            this->createInviteItem(invite);
            connect(invitesItems[invite.localID], SIGNAL(acceptInvite(int, QString)), this, SLOT(acceptInvite(int, QString)));
            connect(invitesItems[invite.localID], SIGNAL(deleteReceivedInvite(int, int, QString)), this, SLOT(deleteReceivedInvite(int, int, QString)));
        }

        this->sortBy("roomName", true);
    } else {
        qInfo() << "get profile room error status: " << serverStatus.status;
    }
}

void InvitesList::sendedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites) {
    if (!serverStatus.status) {
        this->invites.append(invites);

        for(auto &invite : this->invites){
            if (this->find(invite, invites) == -1)
                continue;

            this->createInviteItem(invite);
            connect(invitesItems[invite.localID], SIGNAL(deleteSendedInvite(int, int, QString)), this, SLOT(deleteSendedInvite(int, int, QString)));
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

void InvitesList::finishAcceptInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite) {
    if (!serverStatus.status) {
        auto item = this->getInviteItem(invite);

        if (!item) {
            qInfo() << "there is no inivte with such parameters";
            return;
        }

        item->deleteLater();
        this->invites.removeAcceptedInvites(invite);
    } else {
        qInfo() << "accept invite failed with status: " << serverStatus.status;
    }
}

void InvitesList::finishDeleteReceivedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite) {
    if (!serverStatus.status) {
        auto item = this->getInviteItem(invite);

        if (!item) {
            qInfo() << "there is no inivte with such parameters";
            return;
        }

        item->deleteLater();
        this->invites.remove(invite);
    } else {
        qInfo() << "delete received invite failed with status: " << serverStatus.status;
    }
}

void InvitesList::finishDeleteSendedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite) {
    if (!serverStatus.status) {
        auto item = this->getInviteItem(invite);

        if (!item) {
            qInfo() << "there is no inivte with such parameters";
            return;
        }

        item->deleteLater();
        this->invites.remove(invite);
    } else {
        qInfo() << "delete sended invite failed with status: " << serverStatus.status;
    }
}

//Methods

QQuickItem *InvitesList::getInviteItem(Models::Invite invite) {
    auto senderID = invite.senderID;
    auto receiverID = invite.receiverID;
    auto roomCreatorID = invite.roomCreatorID;
    auto roomName = invite.roomName;

    for (auto &invite : this->invites) {
        if     (invite.senderID == senderID &&
                invite.receiverID == receiverID &&
                invite.roomCreatorID == roomCreatorID &&
                invite.roomName == roomName) {
            return invitesItems[invite.localID];
        }
    }

    return nullptr;
}

int InvitesList::find(Models::Invite invite, Models::Invites invites) {
    auto senderID = invite.senderID;
    auto receiverID = invite.receiverID;
    auto roomCreatorID = invite.roomCreatorID;
    auto roomName = invite.roomName;
    auto invites_count = invites.size();

    int i = 0;
    for (auto invite : invites) {
        if (invite.senderID == senderID &&
            invite.receiverID == receiverID &&
            invite.roomCreatorID == roomCreatorID &&
            invite.roomName == roomName) {
            return i;
        }

        ++i;
    }

    return -1;
}
