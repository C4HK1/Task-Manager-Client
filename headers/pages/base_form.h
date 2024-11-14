#ifndef BASE_FORM_H
#define BASE_FORM_H

#include "base_element.h"

class BaseForm : public BaseElement {
    Q_OBJECT
public:
    BaseForm(QQmlEngine *engine, QString moduleName);
    virtual ~BaseForm();
};

template <typename T>
concept IsForm = std::is_base_of<BaseForm, T>::value;

#endif // BASE_FORM_H
