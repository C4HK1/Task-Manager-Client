#ifndef ROOM_CREATION_PAGE_H
#define ROOM_CREATION_PAGE_H

#include "base_page.h"

class RoomCreationPage : public BasePage {
    Q_OBJECT
public:
    RoomCreationPage(QQmlEngine *engine, QQuickItem *container);
    ~RoomCreationPage();

public slots:
    void loadFailInfo();
};

#endif // ROOM_CREATION_PAGE_H
