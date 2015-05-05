#include "qitemaction.h"

QItemAction::QItemAction(QObject *parent) :
    QAction(parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onTrigger()), Qt::UniqueConnection);
}

QItemAction::QItemAction(const QString &text, QObject *parent) :
    QAction(text, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onTrigger()), Qt::UniqueConnection);
}

void QItemAction::setNode(QDomNode newNode)
{
    node = newNode;
}

void QItemAction::setIndex(QModelIndex newIndex)
{
    index = newIndex;
}

void QItemAction::setCP(QPoint newCP)
{
    cp = newCP;
}

void QItemAction::onTrigger()
{
//    emit clicked(node);
//    emit clicked(index);
    emit clicked(cp);
}
