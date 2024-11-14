#include <nlohmann/json.hpp>

#include "loggout_form.h"
#include "home_page.h"

//Object part
LoggoutForm::LoggoutForm(QQmlEngine *engine, QQuickItem *container, HomePage *homePage) :
    BaseForm(engine, "qml/Loggout.qml"), container(container),
        homePage(homePage) {
    connect(this->getObject(), SIGNAL(loggout()), this, SLOT(loggout()));
    connect(this->getObject(), SIGNAL(closeLoggoutForm()), this, SLOT(closeLoggoutForm()));
}

LoggoutForm::~LoggoutForm() {
}


//Slots
void LoggoutForm::loggout() {
    std::remove("data/authentication_key.organizer");
    this->homePage->closePage();
    this->homePage->mainApp->switchToLogginingPage();
}

void LoggoutForm::closeLoggoutForm() {
    this->homePage->closeForm();
}
