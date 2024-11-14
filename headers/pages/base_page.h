#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QQuickItem>
#include "base_element.h"

class BasePage : public BaseElement {
    Q_OBJECT
public:
    BasePage(QQmlEngine *engine, QString module_name);
    virtual void update() = 0;
    virtual ~BasePage() = 0;
};

template <typename T>
concept IsPage = std::is_base_of<BasePage, T>::value;

#endif // BASE_PAGE_H
