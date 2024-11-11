#ifndef SENDED_INVITES_H
#define SENDED_INVITES_H

#include "invites_list.h"

class HomePage;

class SendedInvites : public InvitesList {
    Q_OBJECT
public:
    SendedInvites(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    ~SendedInvites() override;

    void createInviteItem(Models::Invite &invite) override;
signals:
public slots:
protected:
private:
};

#endif // SENDED_INVITES_H
