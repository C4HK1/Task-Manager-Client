#include "settings_page.h"

SettingsPage::SettingsPage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/Settings.qml"),
        mainPage(mainPage) {

}
