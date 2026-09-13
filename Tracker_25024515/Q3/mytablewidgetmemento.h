#ifndef MYTABLEWIDGETMEMENTO_H
#define MYTABLEWIDGETMEMENTO_H

#include <QTableWidget>
#include <QVector>

class MyTableWidgetMemento
{
    friend class MyTableWidget;

public:
    explicit MyTableWidgetMemento(const QVector<QStringList> &state);

private:
    QVector<QStringList> state;
};

class MyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit MyTableWidget(QWidget *parent = nullptr);
    MyTableWidgetMemento *createMemento() const;
    void setMemento(const MyTableWidgetMemento *m);
};

#endif
