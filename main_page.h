#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "base_page.h"

class MainPage : public BasePage {
    Q_OBJECT
public:
    MainPage(QQmlEngine *engine, QQuickItem *container);
};

#endif // MAIN_PAGE_H
