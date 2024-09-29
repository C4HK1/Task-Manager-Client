#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
    void setCurrentPage(BasePage *page);
    void switchToSettings();
    void switchToProfile();
    void switchToRooms();

private:
    QQuickItem *workspace = nullptr;
    BasePage *cur_page = nullptr;
};

#endif // MAIN_PAGE_H
