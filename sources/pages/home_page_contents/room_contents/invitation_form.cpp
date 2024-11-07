#include <nlohmann/json.hpp>

#include "invitation_form.h"
#include "room.h"

//Object part
InvitationForm::InvitationForm(QQmlEngine *engine, QQuickItem *container, Room *room) :
        BaseElement(engine, container, "qml/MainWorkspaceElements/Invitation.qml"),
        room(room){
    connect(this->getObject(), SIGNAL(findProfilesWithSuchName(QString)), this, SLOT(findProfilesWithSuchName(QString)));
    connect(this->getObject(), SIGNAL(invite(QVariant, int, QString)), this, SLOT(invite(QVariant, int, QString)));
    connect(this->getObject(), SIGNAL(closeInvitationForm()), this, SLOT(closeInvitationForm()));

    connect(netManager, &NetworkManager::finishGetProfilesWithPrefixHandling, this, &InvitationForm::finishFindProfilesWithSuchName);
    connect(netManager, &NetworkManager::finishAppendMemberToRoomResponseHandling, this, &InvitationForm::finishInvite);
}

InvitationForm::~InvitationForm() {
}


//Slots
void InvitationForm::findProfilesWithSuchName(QString name) {
    this->netManager->sendGetProfilesWithPrefixRequest(name);
}

void InvitationForm::invite(QVariant recieversID, int roomCreatorID, QString roomName) {
    qInfo() << "invite: " << recieversID << roomCreatorID << roomName;
}

void InvitationForm::finishFindProfilesWithSuchName(Models::ServerStatus serverStatus, Models::Profiles profiles) {
    qInfo() << "finding profiles status: " << serverStatus.status;
}

void InvitationForm::finishInvite(Models::ServerStatus serverStatus) {
    qInfo() << "inviting status: " << serverStatus.status;
}

void InvitationForm::closeInvitationForm() {
    this->room->closeForm();
}

