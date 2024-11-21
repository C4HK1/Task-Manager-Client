#ifndef ROOM_PAGE_H
#define ROOM_PAGE_H

#include "base_element.h"
#include "base_page.h"

class HomePage;

class Room : public BasePage {
    Q_OBJECT
public:
    //Fields
    HomePage *homePage;

    //Object part
    Room(QQmlEngine *engine, HomePage *homePage, Models::Room room);
    ~Room();

    //Methods
    void addTask(Models::Task task);
    void update() override;
    void leave() override;

    void clearContents();

    //Form part
    void setCurrentForm(BaseElement *form);

    template <typename FormType, typename ...Args> requires IsElement<FormType>
    void switchForm(Args... args);
signals:
public slots:
    void setTasks(Models::ServerStatus serverStatus, Models::Tasks tasks);
    void leaveFormRoom(int roomCreatorID, QString roomName);
    void finishLeaveFromRoom(Models::ServerStatus sreverStatus);

    //Switches
    void switchToTaskCreationForm();
    void switchToInvitationForm();
    void switchToTaskForm(int localID);
    void closeForm();
protected:
private:
    QQmlComponent *taskComponent;
    QQuickItem *tasksContainer;

    BaseElement *curForm = nullptr;

    Models::Room room;
    Models::Tasks tasks;
    QHash<u_int64_t, QQuickItem*> tasksItems;
};

#endif // ROOM__PAGE_H
