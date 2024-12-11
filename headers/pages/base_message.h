#ifndef BASE_MESSAGE_H
#define BASE_MESSAGE_H

#include "base_element.h"

class BaseMessage : public BaseElement {
    Q_OBJECT
public:
    BaseMessage(QQmlEngine *engine, QQuickItem *parent, QString moduleName);
    virtual ~BaseMessage();
};

template <typename T>
concept IsMessage = std::is_base_of<BaseMessage, T>::value;


#endif // BASE_MESSAGE_H
