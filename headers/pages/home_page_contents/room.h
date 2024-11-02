#ifndef ROOM_PAGE_H
#define ROOM_PAGE_H

#include "base_element.h"

class HomePage;

class Room : public BaseElement {
    Q_OBJECT
public:
    //Fields
    HomePage *homePage;

    //Object part
    Room(QQmlEngine *engine, QQuickItem *container, HomePage *homePage, Models::Room room);
    ~Room();

    //Methods
    void addTask(Models::Task task);

    //Form part
    void setCurrentForm(BaseElement *form);

    template <typename FormType, typename ...Args> requires IsElement<FormType>
    void switchForm(Args... args);
signals:
public slots:
    void roomInitialization(Models::ServerStatus serverStatus, Models::Tasks tasks);

    void switchToTaskCreationForm();
    void closeForm();
protected:
private:
    QQmlComponent *taskComponent;
    QQuickItem *tasksContainer;

    BaseElement *curForm = nullptr;

    Models::Room room;
    Models::Tasks tasks;
};

#endif // ROOM__PAGE_H
