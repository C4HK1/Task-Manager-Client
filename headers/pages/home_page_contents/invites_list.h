#ifndef INVITES_LIST_H
#define INVITES_LIST_H

#include "base_element.h"
#include "models.h"

enum InviteType {
    RECEIVED,
    SENDED
};

class HomePage;

class InvitesList : public BaseElement
{
    Q_OBJECT
public:
    HomePage *homePage;

    InvitesList(QQmlEngine *engine, QQuickItem *container, HomePage *homePage);
    virtual ~InvitesList();

    virtual void createInviteItem(Models::Invite &invite, InviteType inviteType) = 0;
signals:
public slots:
    void sortBy(QString by, bool ascending = true);
    void receivedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites);
    void sendedInvitesInitialization(Models::ServerStatus serverStatus, Models::Invites invites);

    void acceptInvite(int roomCreatorID, QString roomName);
    void deleteReceivedInvite(int senderID, int roomCreatorID, QString roomName);
    void deleteSendedInvite(int receiverID, int roomCreatorID, QString roomName);

    void finishAcceptInviteResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteReceivedInviteResponseHandling(Models::ServerStatus serverStatus);
    void finishDeleteSendedInviteResponseHandling(Models::ServerStatus serverStatus);
protected:
    QQuickItem *listContainer;
    QQmlComponent *sendedItemComponent;
    QQmlComponent *receivedItemComponent;

    Models::Invites invites;
private:
};

#endif // INVITES_LIST_H
