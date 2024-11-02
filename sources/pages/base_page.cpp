#include <base_page.h>
#include <main_application.h>

BasePage::BasePage(QQmlEngine *engine, QQuickItem *container, QString moduleName) :
        engine(engine), object(qobject_cast<QQuickItem*>(loadQmlFrame(moduleName))),
        netManager(NetworkManager::getInstance()) {
    object->setParentItem(container);
}

QQuickItem* BasePage::loadQmlFrame(QString moduleName) {
    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(moduleName));

    if (component->errors().size())
        qInfo() << component->errors();

    QQuickItem *newFrame = qobject_cast<QQuickItem*>(component->create(engine->rootContext()));
    component->deleteLater();

    return newFrame;
}

QQuickItem* BasePage::getObject() {
    return object;
}

BasePage::~BasePage() {
    object->deleteLater();
}
