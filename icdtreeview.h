#ifndef ICDTREEVIEW_H
#define ICDTREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QModelIndex>

#include <QDebug>
#include <QPoint>

class ICDTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit ICDTreeView(QWidget *parent = 0);

signals:
    void LeftClicked(QModelIndex);
    void RightClicked(QModelIndex);

public slots:

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QModelIndex index;
    void setIndex(QModelIndex);
    QModelIndex getIndex(QPoint pos);

};

#endif // ICDTREEVIEW_H
