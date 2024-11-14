#include "base_form.h"

BaseForm::BaseForm(QQmlEngine *engine, QQuickItem *parent, QString moduleName) : BaseElement(engine, moduleName) {
    object->setParentItem(parent);
}

BaseForm::~BaseForm() {}
