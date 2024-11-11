#ifndef INVITES_LIST_H
#define INVITES_LIST_H

#include "base_element.h"
#include "models.h"

class HomePage;

class InvitesList : public BaseElement
{
    Q_OBJECT
public:
    HomePage *homePage;

    InvitesList(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);    
    virtual ~InvitesList();

    QQuickItem *getInviteItem(Models::Invite invite);

    int find(Models::Invite invite, Models::Invites invites);

    virtual void createInviteItem(Models::Invite &invite) = 0;
signals:
public slots:
    void sortBy(QString by, bool ascending = true);
    void receivedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites);
    void sendedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites);

    void acceptInvite(int roomCreatorID, QString roomName);
    void deleteReceivedInvite(int senderID, int roomCreatorID, QString roomName);
    void deleteSendedInvite(int receiverID, int roomCreatorID, QString roomName);

    void finishAcceptInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
    void finishDeleteReceivedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
    void finishDeleteSendedInviteResponseHandling(Models::ServerStatus serverStatus, Models::Invite invite);
protected:
    QQuickItem *listContainer;
    QQmlComponent *sendedItemComponent;
    QQmlComponent *receivedItemComponent;

    Models::Invites invites;
private:
};

#endif // INVITES_LIST_H
