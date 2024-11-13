#ifndef NAVIGATION_SERVICE_H
#define NAVIGATION_SERVICE_H

#include "base_element.h"

class NavigationService final {
public:
    NavigationService(QQmlEngine *engine, QQuickItem *container);
    ~NavigationService();
    template<typename T, typename ...Args> requires IsElement<T>
    void switchTo(Args... args);
    void switchBackward();
    void switchForward();
    void clear(QList<BaseElement*>::iterator begin, QList<BaseElement*>::iterator end);
    void clearMemory(QList<BaseElement*>::iterator begin, QList<BaseElement*>::iterator end);

    bool isFirst();
    bool isLast();

    static constexpr int BUFFER_SIZE = 20;

private:
    QQmlEngine *engine;
    QQuickItem *container;
    QList<BaseElement*> elements;
    QList<BaseElement*>::iterator current;
};

#endif // NAVIGATION_SERVICE_H
