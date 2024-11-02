#include "profile.h"
#include "home_page.h"

//Object part
Profile::Profile(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
        BaseElement(engine, container, "qml/Profile.qml"),
        homePage(homePage) {
}

Profile::~Profile() {
}
