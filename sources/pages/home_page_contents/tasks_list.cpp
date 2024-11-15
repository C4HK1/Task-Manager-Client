#include "tasks_list.h"
#include "network_manager.h"
#include "home_page.h"

//Object part
TasksList::TasksList(QQmlEngine *engine, HomePage *homePage) :
        BasePage(engine, "qml/Tasks.qml"),
        itemComponent(new QQmlComponent(engine, QUrl::fromLocalFile("qml/MainWorkspaceElements/TaskListItem.qml"))),
        listContainer(object->findChild<QQuickItem*>("flickable")->findChild<QQuickItem*>("listContainer")),
        homePage(homePage) {
    connect(object, SIGNAL(sortBy(QString,bool)), this, SLOT(sortBy(QString,bool)));
}

TasksList::~TasksList(){
    clearContents();
    itemComponent->deleteLater();
}


//Slots
void TasksList::sortBy(QString by, bool ascending) {
    for (auto &task : tasks) {
        tasksItems[task.localID]->setParentItem(nullptr);
    }

    auto get_str = [&by](Models::Task task) { return (task.property(by.toStdString().c_str())).toString().toLower().trimmed(); };

    std::stable_sort(tasks.begin(), tasks.end(),
              [&ascending, &by, &get_str](const Models::Task t1, const Models::Task t2) {
        QString s1 = get_str(t1), s2 = get_str(t2);
        return (ascending && s1 < s2) || (!ascending && s1 > s2);
    });

    for(auto &task : tasks) {
        tasksItems[task.localID]->setParentItem(listContainer);
    }
}

void TasksList::tasksInitialization(Models::ServerStatus serverStatus, Models::Tasks tasks) {
    if (!serverStatus.status) {
        this->tasks = tasks;

        for(auto &task : this->tasks){
            this->createTaskItem(task);
            connect(tasksItems[task.localID], SIGNAL(openRoom(int,QString)), this, SLOT(openRoom(int,QString)));
        }

        this->sortBy("taskName", true);
    } else {
        qInfo() << "get profile room error status: " << serverStatus.status;
    }
}

void TasksList::clearContents() {
    for(auto &task : tasks) {
        tasksItems[task.localID]->deleteLater();
    }

    tasks.clear();
    tasksItems.clear();
}

void TasksList::openRoom(int roomCreatorID, QString roomName) {
    for (auto &task : this->tasks) {    // REIMPLEMENTATION REQUIRED
        if (task.parent.creatorID == roomCreatorID && task.parent.name == roomName) {
            this->homePage->switchToRoom(task.parent);
            break;
        }
    }
}

// color help functions

struct Rgb {
    u_int8_t r{}, g{}, b{};
};

u_int8_t componentCast(u_int8_t c) {    // component from ['a', 'z'] to [100, 230]
    double norm = (double) (c - 'a') / ('z' - 'a');
    return (u_int8_t) (norm * 130 + 100);
}

Rgb stringToRgb(QString str) {
    Rgb rgb;

    if (str.length()) {
        rgb.r = componentCast(str[0].unicode());
    }

    if (str.length() >= 2) {
        rgb.g = componentCast(str[1].unicode());
    }

    if (str.length() >= 3) {
        rgb.b = componentCast(str[2].unicode());
    }

    return rgb;
}

Rgb rgbToDarkerRgb(Rgb rgb) {
    static const double perc = 0.6;

    rgb.r *= perc;
    rgb.g *= perc;
    rgb.b *= perc;

    return rgb;
}

QString rgbToHex(Rgb rgb) {
    QString r = ((rgb.r < 16) ? "0" : "") + QString::number(rgb.r, 16);
    QString g = ((rgb.g < 16) ? "0" : "") + QString::number(rgb.g, 16);
    QString b = ((rgb.b < 16) ? "0" : "") + QString::number(rgb.b, 16);
    return "#" + r + g + b;
}

//Methods
void TasksList::createTaskItem(Models::Task &task){
    auto item = qobject_cast<QQuickItem*>(itemComponent->create(engine->rootContext()));

    item->setProperty("roomCreatorID", QString::number(task.parent.creatorID));
    item->setProperty("roomName", task.parent.name);
    item->setProperty("taskName", task.name);
    item->setProperty("creatorName", task.creatorName);
    item->setProperty("label", task.label);

    Rgb rgb = stringToRgb(task.label);
    qInfo() << rgbToHex(rgb);
    item->setProperty("labelColor", rgbToHex(rgb));
    item->setProperty("labelBorderColor", rgbToHex(rgbToDarkerRgb(rgb)));

    item->setParentItem(listContainer);
    tasksItems[task.localID] = item;
}
