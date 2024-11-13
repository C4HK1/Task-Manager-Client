#include "navigation_service.h"

NavigationService::NavigationService(QQmlEngine *engine, QQuickItem *container)
    : engine(engine), container(container), current(elements.begin()) {}

NavigationService::~NavigationService() {
    clearMemory(elements.begin(), elements.end());
}

void NavigationService::switchTo(BaseElement *newElement) {
    if(elements.size()) {
        (*current)->getObject()->setParentItem(nullptr);

        if(current != elements.end() - 1) {
            clear(current + 1, elements.end());
        }
    }

    newElement->getObject()->setParentItem(container);

    elements.append(newElement);
    current = elements.end() - 1;

    for (auto &e : elements) {
        qInfo() << e << ' ' << e->getObject()->parentItem();
    }
    qInfo() << '\n';
}

void NavigationService::switchForward() {
    if(!isLast()) {
        (*current)->getObject()->setParentItem(nullptr);
        ++current;
        (*current)->getObject()->setParentItem(container);
    } else {
        qInfo("tried to switch forward while staying on last");
    }
}

void NavigationService::switchBackward() {
    if(!isFirst()) {
        (*current)->getObject()->setParentItem(nullptr);
        --current;
        (*current)->getObject()->setParentItem(container);
    } else {
        qInfo("tried to switch backward while staying on first");
    }
}

void NavigationService::clear(QList<BaseElement*>::iterator begin, QList<BaseElement*>::iterator end) {
    if (begin >= end || !(begin < current && end <= current) || !(begin > current && end > current)) {
        qInfo() << "incorrect iterators on clear";

        for (auto &e : elements) {
            qInfo() << e;
        }

        qInfo() << std::distance(elements.begin(), begin) << ' ' << std::distance(elements.begin(), end) << '\n';

        return;
    }

    size_t dist;

    if(end <= current) {
        dist = std::distance(elements.begin(), current) - std::distance(begin, end);
    } else {
        dist = std::distance(elements.begin(), current);
    }

    clearMemory(begin, end);

    elements.erase(QList<BaseElement*>::const_iterator(begin), QList<BaseElement*>::const_iterator(end));
    current = elements.begin() + dist;
}

void NavigationService::clearMemory(QList<BaseElement*>::iterator begin, QList<BaseElement*>::iterator end) {
    for(auto it = begin; it != end; ++it) {
        (*it)->deleteLater();
    }
}

bool NavigationService::isFirst() {
    return current == elements.begin();
}

bool NavigationService::isLast() {
    return current == elements.end() - 1;
}
