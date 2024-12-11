#include "base_message.h"

BaseMessage::BaseMessage(QQmlEngine *engine, QQuickItem *parent, QString moduleName) : BaseElement(engine, moduleName) {
    object->setParentItem(parent);
}

BaseMessage::~BaseMessage() {}
