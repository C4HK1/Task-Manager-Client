#include <base_page.h>
#include <main_application.h>

BasePage::BasePage(MainApplication *app, QString moduleName) :
    object(qobject_cast<QQuickItem*>(app->loadQmlFrame(moduleName))), app(app) {}

BasePage::~BasePage() {
    object->deleteLater();
}

void BasePage::SetContainer(QQuickWindow *window){
    object->setParentItem(window->contentItem());
}
