#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QList>
#include <QDate>

class QLineEdit;
class QDateEdit;
class QDoubleSpinBox;
class QPushButton;
class QPlainTextEdit;
class QLabel;
class QComboBox;
class RainRecord;
class StationThread;
class MyTableWidget;
class MyTableWidgetMemento;

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client() override;

private slots:
    void addRecord();
    void generateXml();
    void searchStation();
    void handleFound(const QString &date, const QString &mm);
    void searchFinished();
    void backupTable();
    void restoreTable();

private:
    void setupUi();
    void refreshTable();
    void setStatus(const QString &text);

    QLineEdit *stationEdit;
    QDateEdit *dateEdit;
    QDoubleSpinBox *mmEdit;
    QLineEdit *searchEdit;
    QPushButton *addButton;
    QPushButton *xmlButton;
    QPushButton *searchButton;
    QPushButton *backupButton;
    QPushButton *restoreButton;
    MyTableWidget *tableWidget;
    QPlainTextEdit *xmlOutput;
    QLabel *statusLabel;

    QList<RainRecord *> records;
    StationThread *thread;
    MyTableWidgetMemento *memento;
    int searchRow;
};

#endif
