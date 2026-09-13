#include "mytablewidgetmemento.h"

MyTableWidgetMemento::MyTableWidgetMemento(const QVector<QStringList> &stateValue)
    : state(stateValue)
{
}

MyTableWidget::MyTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
}

MyTableWidgetMemento *MyTableWidget::createMemento() const
{
    QVector<QStringList> saved;
    for (int row = 0; row < rowCount(); ++row) {
        QStringList values;
        for (int column = 0; column < columnCount(); ++column) {
            QTableWidgetItem *item = this->item(row, column);
            values.append(item ? item->text() : QString());
        }
        saved.append(values);
    }
    return new MyTableWidgetMemento(saved);
}

void MyTableWidget::setMemento(const MyTableWidgetMemento *m)
{
    if (!m)
        return;

    clearContents();
    setRowCount(m->state.size());
    for (int row = 0; row < m->state.size(); ++row) {
        for (int column = 0; column < m->state.at(row).size() && column < columnCount(); ++column)
            setItem(row, column, new QTableWidgetItem(m->state.at(row).at(column)));
    }
}
