#include "icdtreeview.h"

ICDTreeView::ICDTreeView(QWidget *parent) :
    QTreeView(parent)
{
}

void ICDTreeView::setIndex(QModelIndex newIndex)
{
    index = newIndex;
}

QModelIndex ICDTreeView::getIndex(QPoint pos)
{
    return indexAt(pos);
}

void ICDTreeView::mousePressEvent(QMouseEvent *e)
{
    setIndex(getIndex(e->pos()));
    if(!index.isValid())
        return;

    if(e->button() == Qt::LeftButton)
    {
        qDebug()<<"Here is Left clicked! "<<index;
        qDebug()<<isExpanded(index);
        setExpanded(index,!isExpanded(index));
        qDebug()<<isExpanded(index);
        emit LeftClicked(index);
    }
    else if(e->button() == Qt::RightButton)
    {
        qDebug()<<"Here is Right clicked!";
        emit RightClicked(index);
    }
    else
        mousePressEvent(e);
}
