#include <nlohmann/json.hpp>

#include "invitation_form.h"
#include "room.h"
#include "models/profile.h"

//Object part
InvitationForm::InvitationForm(QQmlEngine *engine, QQuickItem *container, Room *room) :
        BaseElement(engine, container, "qml/MainWorkspaceElements/Invitation.qml"),
        itemComponent(new QQmlComponent(engine, "qml/ProfileRow.qml")),
        profilesContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("profilesContainer")),
        room(room) {
    connect(this->getObject(), SIGNAL(findProfilesWithSuchName(QString)), this, SLOT(findProfilesWithSuchName(QString)));
    connect(this->getObject(), SIGNAL(invite(int, int, QString)), this, SLOT(invite(int, int, QString)));
    connect(this->getObject(), SIGNAL(closeInvitationForm()), this, SLOT(closeInvitationForm()));

    connect(netManager, &NetworkManager::finishGetProfilesWithSubstrHandling, this, &InvitationForm::finishFindProfilesWithSuchName);
    connect(netManager, &NetworkManager::finishCreateInviteResponseHandling, this, &InvitationForm::finishInvite);
}

InvitationForm::~InvitationForm() {
}


//Slots
void InvitationForm::findProfilesWithSuchName(QString name) {
    this->destroyItems();
    if (!name.size())
        return;
    this->netManager->sendGetProfilesWithSubstrRequest(name, this->offset);
}

void InvitationForm::invite(int receiverID, int roomCreatorID, QString roomName) {
    qInfo() << "invite: " << receiverID << roomCreatorID << roomName;
    this->netManager->sendCreateInviteRequest(receiverID, roomCreatorID, roomName);
}

void InvitationForm::finishFindProfilesWithSuchName(Models::ServerStatus serverStatus, Models::Profiles profiles) {
    if (!serverStatus.status) {
        for (auto profile : profiles) {
            this->createItem(profile);
        }
    } else {
        qInfo() << "error find profile with such name status: " << serverStatus.status;
    }
}

void InvitationForm::finishInvite(Models::ServerStatus serverStatus) {
    qInfo() << "inviting status: " << serverStatus.status;
}

void InvitationForm::closeInvitationForm() {
    this->room->closeForm();
}

void InvitationForm::createItem(Models::Profile profile) {
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));

    item->setProperty("profileID", QString::number(profile.ID));
    item->setProperty("profileName", profile.name);

    item->setParentItem(profilesContainer);

    this->items.append(item);
}

void InvitationForm::destroyItems() {
    for (auto item : this->items) {
        item->deleteLater();
    }
    this->items.clear();
}



