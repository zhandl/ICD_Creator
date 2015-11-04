#include "nodetablewidget.h"

NodeTableWidget::NodeTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChanged(int,int)), Qt::UniqueConnection);
}

NodeTableWidget::NodeTableWidget(int rows, int columns, QWidget *parent) :
    QTableWidget(rows, columns, parent)
{
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChanged(int,int)), Qt::UniqueConnection);
}

void NodeTableWidget::setNode(QDomNode newNode)
{
    node = newNode;
}

void NodeTableWidget::setModelIndex(QModelIndex newIndex)
{
    index = newIndex;
}

QModelIndex NodeTableWidget::getModelIndex()
{
    return index;
}

void NodeTableWidget::onCellChanged(int row, int column)
{
    emit nodeCellChanged(index, row, column);
}
