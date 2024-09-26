#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <QQuickItem>

class MainApplication;

class BasePage : public QObject {
    Q_OBJECT
public:
    BasePage(MainApplication *app, QString moduleName);
    ~BasePage();
    void SetContainer(QQuickWindow *window);

signals:

public slots:

private:
    MainApplication *app;
    QQuickItem *object;
};

#endif // BASE_PAGE_H
