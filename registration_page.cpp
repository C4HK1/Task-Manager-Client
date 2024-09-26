#include "registration_page.h"
#include "main_application.h"

RegistrationPage::RegistrationPage(MainApplication *app) : BasePage(app, "Registration.qml") {}

void RegistrationPage::loadPage(MainApplication *app) {
    auto page = new RegistrationPage(app);
    app->SetCurrentPage(page);
}
