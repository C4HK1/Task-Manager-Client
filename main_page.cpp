#include "main_page.h"
#include "main_application.h"

MainPage::MainPage(MainApplication *app) : BasePage(app, "MainWorkspace.qml") {}

void MainPage::loadPage(MainApplication *app) {
    auto page = new MainPage(app);
    app->SetCurrentPage(page);
}
