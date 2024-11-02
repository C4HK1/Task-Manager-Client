#include "settings.h"

//Object part
Settings::Settings(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        BaseElement(engine, container, "qml/Settings.qml"),
        homePage(homePage) {
}

Settings::~Settings() {
}
