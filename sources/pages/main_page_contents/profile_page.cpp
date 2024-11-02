#include "profile_page.h"
#include "main_page.h"

ProfilePage::ProfilePage(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/Profile.qml"),
        mainPage(mainPage) {
}
