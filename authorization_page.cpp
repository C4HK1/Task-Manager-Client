#include "authorization_page.h"
#include "main_application.h"

AuthorizationPage::AuthorizationPage(MainApplication *app) : BasePage(app, "Authorization.qml") {}

void AuthorizationPage::loadPage(MainApplication *app) {
    auto page = new AuthorizationPage(app);
    app->SetCurrentPage(page);
}
