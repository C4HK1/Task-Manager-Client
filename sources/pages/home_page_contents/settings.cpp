#include "settings.h"

//Object part
Settings::Settings(QQmlEngine *engine, HomePage *homePage) :
        BaseElement(engine, "qml/Settings.qml"),
        homePage(homePage) {
}

Settings::~Settings() {
}
