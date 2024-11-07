#ifndef INVITATION_FORM_H
#define INVITATION_FORM_H

#include "base_element.h"

class Room;

class InvitationForm : public BaseElement {
    Q_OBJECT
public:
    Room *room;

    InvitationForm(QQmlEngine *engine, QQuickItem *container, Room *room);
    ~InvitationForm();
signals:
public slots:
    void findProfilesWithSuchName(QString name);
    void invite(QVariant recieversID, int roomCreatorID, QString roomName);

    void finishFindProfilesWithSuchName(Models::ServerStatus serverStatus, Models::Profiles profiles);
    void finishInvite(Models::ServerStatus serverStatus);

    void closeInvitationForm();
protected:
private:
};

#endif // INVITATION_FORM_H
