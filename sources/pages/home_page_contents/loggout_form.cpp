#include <nlohmann/json.hpp>

#include "loggout_form.h"
#include "home_page.h"

//Object part
LoggoutForm::LoggoutForm(QQmlEngine *engine, QQuickItem *parent, HomePage *homePage) :
    BaseForm(engine, parent, "qml/Loggout.qml"),
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
