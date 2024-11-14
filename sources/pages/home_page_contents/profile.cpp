#include "profile.h"
#include "home_page.h"

//Object part
Profile::Profile(QQmlEngine *engine, HomePage *homePage) :
        BasePage(engine, "qml/Profile.qml"),
        homePage(homePage) {
}

Profile::~Profile() {
}

void Profile::update() {}
