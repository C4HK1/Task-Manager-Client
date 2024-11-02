#include <base_element.h>
#include <main_application.h>

//Object part
BaseElement::BaseElement(QQmlEngine *engine, QQuickItem *container, QString moduleName) :
        engine(engine), object(qobject_cast<QQuickItem*>(loadQmlFrame(moduleName))),
        netManager(NetworkManager::getInstance()) {
    object->setParentItem(container);
}

BaseElement::~BaseElement() {
    object->deleteLater();
}


//Methods
QQuickItem* BaseElement::loadQmlFrame(QString moduleName) {
    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(moduleName));

    if (component->errors().size())
        qInfo() << component->errors();

    QQuickItem *newFrame = qobject_cast<QQuickItem*>(component->create(engine->rootContext()));
    component->deleteLater();

    return newFrame;
}

QQuickItem* BaseElement::getObject() {
    return object;
}
