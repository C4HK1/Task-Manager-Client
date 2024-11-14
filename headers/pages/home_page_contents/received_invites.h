#ifndef RECEIVED_INVITES_H
#define RECEIVED_INVITES_H

#include "invites_list.h"

class HomePage;

class ReceivedInvites : public InvitesList {
    Q_OBJECT
public:
    ReceivedInvites(QQmlEngine *engine, HomePage *homePage);
    ~ReceivedInvites() override;
    void update() override;
    void leave() override;

    void createInviteItem(Models::Invite &invite) override;
signals:
public slots:
protected:
private:
};

#endif // RECEIVED_INVITES_H
