#include <nlohmann/json.hpp>

#include "loggout_form.h"
#include "main_page.h"

LoggoutForm::LoggoutForm(QQmlEngine *engine, QQuickItem *container, MainPage *mainPage) :
        BasePage(engine, container, "qml/Loggout.qml"),
        mainPage(mainPage) {
    connect(this->getObject(), SIGNAL(loggout()), this, SLOT(loggout()));
    connect(this->getObject(), SIGNAL(closeLoggoutForm()), this, SLOT(closeLoggoutForm()));
}

void LoggoutForm::loggout() {
    std::remove("data/authentication_key.organizer");
    this->mainPage->mainApp->switchToLogginingPage();
}

void LoggoutForm::closeLoggoutForm() {
    this->mainPage->closeForm();
}

LoggoutForm::~LoggoutForm() {}
