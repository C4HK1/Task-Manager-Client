#include <base_page.h>
#include <main_application.h>

BasePage::BasePage(QQmlEngine *engine, QQuickItem *container, QString moduleName) :
    engine(engine), object(qobject_cast<QQuickItem*>(loadQmlFrame(moduleName)))
{
    object->setParentItem(container);
}

QQuickItem* BasePage::loadQmlFrame(QString moduleName) {
    QQmlComponent *component = new QQmlComponent(engine, QUrl::fromLocalFile(moduleName));
    qInfo() << component->errors();
    QQuickItem *new_frame = qobject_cast<QQuickItem*>(component->create(engine->rootContext()));
    component->deleteLater();

    return new_frame;
}

BasePage::~BasePage() {
    object->deleteLater();
}
