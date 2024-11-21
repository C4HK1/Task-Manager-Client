#ifndef INVITATION_FORM_H
#define INVITATION_FORM_H

#include "base_form.h"

class Room;

class InvitationForm : public BaseForm {
    Q_OBJECT
public:
    Room *room;
    u_int64_t offset{0};


    InvitationForm(QQmlEngine *engine, QQuickItem *parent, Room *room);
    ~InvitationForm();
signals:
public slots:
    void findProfilesWithSuchName(QString name);
    void invite(int receiverID, int roomCreatorID, QString roomName);

    void finishFindProfilesWithSuchName(Models::ServerStatus serverStatus, Models::Profiles profiles);
    void finishInvite(Models::ServerStatus serverStatus, Models::Invite invite);

    void createItem(Models::Profile profile);
    void destroyItems();
protected:
    QList<QQuickItem *> items;
    QQmlComponent *itemComponent;
    QQuickItem *profilesContainer;
private:
};

#endif // INVITATION_FORM_H
