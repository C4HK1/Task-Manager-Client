#ifndef NAVIGATION_SERVICE_H
#define NAVIGATION_SERVICE_H

#include "base_page.h"

class NavigationService final {
public:
    NavigationService(QQmlEngine *engine, QQuickItem *container);
    ~NavigationService();
    void switchTo(BasePage *newElement);
    void switchBackward();
    void switchForward();
    void clear(QList<BasePage*>::iterator begin, QList<BasePage*>::iterator end);
    void clearMemory(QList<BasePage*>::iterator begin, QList<BasePage*>::iterator end);

    bool isFirst();
    bool isLast();

    static constexpr int BUFFER_SIZE = 20;

private:
    QQmlEngine *engine;
    QQuickItem *container;
    QList<BasePage*> elements;
    QList<BasePage*>::iterator current;
};

#endif // NAVIGATION_SERVICE_H
