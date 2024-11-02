#ifndef ROOM_PAGE_H
#define ROOM_PAGE_H

#include "base_page.h"

class MainPage;

class RoomPage : public BasePage {
    Q_OBJECT
public:
    //Fields
    MainPage *mainPage;

    //Object part
    RoomPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage, Room room);
    ~RoomPage();

    //Methods
    void addTask(Task task);

    //Form part
    void setCurrentForm(BasePage *form);

    template <typename FormType, typename ...Args> requires IsPage<FormType>
    void switchForm(Args... args);
signals:
    void switchToTaskCreation();
public slots:
    void roomPageInitialization(ServerStatus serverStatus, Tasks tasks);

    void switchToTaskCreationForm();
    void closeForm();
private:
    Room room;
    Tasks tasks;
    QQmlComponent *taskComponent;
    QQuickItem *tasksContainer;

    BasePage *curForm = nullptr;
};

#endif // ROOM__PAGE_H
