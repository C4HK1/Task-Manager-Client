#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QQuickItem>
#include <QQmlEngine>
#include "network_manager.h"

class MainApplication;

class BasePage : public QObject {
    Q_OBJECT
public:
    BasePage(QQmlEngine *engine, QQuickItem *container, QString moduleName);
    BasePage(QQmlEngine *engine, BasePage *container, QString moduleName);
    QQuickItem* loadQmlFrame(QString moduleName);
    QQuickItem* getObject();
    ~BasePage();

signals:

public slots:

protected:
    QQmlEngine *engine;
    QQuickItem *container;
    QQuickItem *object;
    NetworkManager *net_manager;
};

template <typename T>
concept IsPage = std::is_base_of<BasePage, T>::value;

#endif // BASE_PAGE_H
