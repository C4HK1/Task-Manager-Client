#ifndef RECEIVED_INVITES_H
#define RECEIVED_INVITES_H

#include "invites_list.h"

class HomePage;

class ReceivedInvites : public InvitesList {
    Q_OBJECT
public:
    ReceivedInvites(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~ReceivedInvites() override;

    void createInviteItem(Models::Invite &invite, InviteType inviteType = RECEIVED) override;
signals:
public slots:
protected:
private:
};

#endif // RECEIVED_INVITES_H
