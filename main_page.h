#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(MainApplication *app);
    static void loadPage(MainApplication *app);
};

#endif // MAIN_PAGE_H
