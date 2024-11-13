#ifndef ALL_INVITES_H
#define ALL_INVITES_H

#include "invites_list.h"

class HomePage;

class AllInvites : public InvitesList {
    Q_OBJECT
public:
    AllInvites(QQmlEngine *engine, HomePage *homePage);
    ~AllInvites() override;

    void createInviteItem(Models::Invite &invite) override;
signals:
public slots:
protected:
private:
};

#endif // ALL_INVITES_H
