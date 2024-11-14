#include "settings.h"

//Object part
Settings::Settings(QQmlEngine *engine, HomePage *homePage) :
        BasePage(engine, "qml/Settings.qml"),
        homePage(homePage) {
}

Settings::~Settings() {
}


void Settings::update() {}
void Settings::leave() {}
