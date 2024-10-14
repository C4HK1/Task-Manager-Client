#include "rooms_page.h"

RoomsPage::RoomsPage(QQmlEngine *engine, QQuickItem *container, QString moduleName, QString itemName)
    : BasePage(engine, container, moduleName), item_component(new QQmlComponent(engine, QUrl::fromLocalFile(itemName))) {}

RoomsPage::~RoomsPage(){
    for(auto &item : rooms_items) {
        item->deleteLater();
    }

    item_component->deleteLater();
}
