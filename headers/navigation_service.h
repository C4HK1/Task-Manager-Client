#ifndef NAVIGATION_SERVICE_H
#define NAVIGATION_SERVICE_H

#include "base_page.h"

class NavigationService final : public QObject {
    Q_OBJECT
public:
    NavigationService(QQuickItem *container, int bufferSize = 1);
    ~NavigationService();
    void switchTo(BasePage *newElement);
    void switchBackward();
    void switchForward();
    void clear(QList<BasePage*>::iterator begin, QList<BasePage*>::iterator end);
    void clearMemory(QList<BasePage*>::iterator begin, QList<BasePage*>::iterator end);

    bool isFirst();
    bool isLast();

private:
    QQuickItem *container;
    QList<BasePage*> elements;
    QList<BasePage*>::iterator current;
    int bufferSize{};
};

#endif // NAVIGATION_SERVICE_H
