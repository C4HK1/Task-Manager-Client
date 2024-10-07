#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QQuickItem>
#include <QQmlEngine>

class MainApplication;

class BasePage : public QObject {
    Q_OBJECT
public:
    BasePage(QQmlEngine *engine, QQuickItem *container, QString moduleName);
    BasePage(QQmlEngine *engine, BasePage *container, QString moduleName);

    QQuickItem* loadQmlFrame(QString moduleName);

    ~BasePage();

signals:

public slots:

protected:
    QQmlEngine *engine;
    QQuickItem *container;
    QQuickItem *object;
};

#endif // BASE_PAGE_H
