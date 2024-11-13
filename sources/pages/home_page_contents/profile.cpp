#include "profile.h"
#include "home_page.h"

//Object part
Profile::Profile(QQmlEngine *engine, HomePage *homePage) :
        BaseElement(engine, "qml/Profile.qml"),
        homePage(homePage) {
}

Profile::~Profile() {
}
