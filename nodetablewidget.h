#ifndef NODETABLEWIDGET_H
#define NODETABLEWIDGET_H

#include <QTableWidget>
#include <QDomNode>
#include <QModelIndex>

class NodeTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit NodeTableWidget(QWidget *parent = 0);
    explicit NodeTableWidget(int rows, int columns, QWidget *parent = 0);
    void setNode(QDomNode);
    void setModelIndex(QModelIndex);
    QModelIndex getModelIndex();

signals:
    void nodeCellChanged(QModelIndex,int,int);

public slots:
    void onCellChanged(int,int);

private:
    QDomNode node;
    QModelIndex index;
};

#endif // NODETABLEWIDGET_H
