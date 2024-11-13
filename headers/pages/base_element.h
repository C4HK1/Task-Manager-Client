#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QQuickItem>
#include <QQmlEngine>
#include "network_manager.h"

class BaseElement : public QObject {
    Q_OBJECT
public:
    BaseElement(QQmlEngine *engine, QString moduleName);
    ~BaseElement();

    QQuickItem* loadQmlFrame(QString moduleName);
    QQuickItem* getObject();
signals:
public slots:
protected:
    QQmlEngine *engine;
    QQuickItem *object;
    NetworkManager *netManager;
private:
};

template <typename T>
concept IsElement = std::is_base_of<BaseElement, T>::value;

#endif // BASE_PAGE_H
