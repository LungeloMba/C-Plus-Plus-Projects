#include "client.h"
#include "../Q1/rainrecord.h"
#include "../Q2/rainxml.h"
#include "../Q3/stationthread.h"
#include "../Q3/mytablewidgetmemento.h"

#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QComboBox>

Client::Client(QWidget *parent)
    : QMainWindow(parent),
      stationEdit(nullptr), dateEdit(nullptr), mmEdit(nullptr), searchEdit(nullptr),
      addButton(nullptr), xmlButton(nullptr), searchButton(nullptr), backupButton(nullptr),
      restoreButton(nullptr), tableWidget(nullptr), xmlOutput(nullptr), statusLabel(nullptr),
      thread(nullptr), memento(nullptr), searchRow(0)
{
    setupUi();
}

Client::~Client()
{
    if (thread) {
        thread->wait();
        delete thread;
    }
    qDeleteAll(records);
    delete memento;
}

void Client::setupUi()
{
    setWindowTitle("Rainfall Tracker");
    resize(900, 650);

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QFormLayout *form = new QFormLayout;
    stationEdit = new QLineEdit;
    stationEdit->setPlaceholderText("AagA100");
    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    mmEdit = new QDoubleSpinBox;
    mmEdit->setRange(0.0, 1000000.0);
    mmEdit->setDecimals(2);
    form->addRow("Station code:", stationEdit);
    form->addRow("Date:", dateEdit);
    form->addRow("Rainfall (mm):", mmEdit);
    mainLayout->addLayout(form);

    QHBoxLayout *buttons = new QHBoxLayout;
    addButton = new QPushButton("Add Record");
    xmlButton = new QPushButton("Generate XML");
    backupButton = new QPushButton("Backup Table");
    restoreButton = new QPushButton("Restore Table");
    buttons->addWidget(addButton);
    buttons->addWidget(xmlButton);
    buttons->addWidget(backupButton);
    buttons->addWidget(restoreButton);
    mainLayout->addLayout(buttons);

    QHBoxLayout *search = new QHBoxLayout;
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Station to search, e.g. AagA100");
    searchButton = new QPushButton("Search in Thread");
    search->addWidget(searchEdit);
    search->addWidget(searchButton);
    mainLayout->addLayout(search);

    statusLabel = new QLabel("Ready.");
    mainLayout->addWidget(statusLabel);

    tableWidget = new MyTableWidget;
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Station" << "Date" << "Rainfall (mm)");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableWidget);

    xmlOutput = new QPlainTextEdit;
    xmlOutput->setReadOnly(true);
    xmlOutput->setPlaceholderText("Generated XML appears here.");
    mainLayout->addWidget(xmlOutput);

    setCentralWidget(central);

    connect(addButton, &QPushButton::clicked, this, &Client::addRecord);
    connect(xmlButton, &QPushButton::clicked, this, &Client::generateXml);
    connect(searchButton, &QPushButton::clicked, this, &Client::searchStation);
    connect(backupButton, &QPushButton::clicked, this, &Client::backupTable);
    connect(restoreButton, &QPushButton::clicked, this, &Client::restoreTable);
}

void Client::setStatus(const QString &text)
{
    statusLabel->setText(text);
}

void Client::addRecord()
{
    const QString station = stationEdit->text().trimmed();
    const QRegularExpression re("^([A-Z])[a-z]{2}\\1[1-9][0-9]{2}$");

    if (!re.match(station).hasMatch()) {
        QMessageBox::warning(this, "Invalid station", "Use one capital letter, two lowercase letters, the same capital letter, and three digits with the first digit non-zero.");
        return;
    }

    records.append(new RainRecord(station, dateEdit->date(), mmEdit->value()));
    refreshTable();
    setStatus("Rain record added.");
}

void Client::refreshTable()
{
    tableWidget->setRowCount(records.size());
    for (int row = 0; row < records.size(); ++row) {
        RainRecord *r = records.at(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(r->station()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(r->date().toString("yyyy/MM/dd")));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(r->mm(), 'g', 15)));
    }
}

void Client::generateXml()
{
    xmlOutput->setPlainText(RainXml::getInstance().writeToXml(records));
    setStatus("XML generated.");
}

void Client::searchStation()
{
    if (thread && thread->isRunning()) {
        setStatus("A search is already running.");
        return;
    }

    const QString station = searchEdit->text().trimmed();
    if (!RainXml::getInstance().checkStationCode(station)) {
        QMessageBox::warning(this, "Invalid station", "Enter a valid station code.");
        return;
    }

    tableWidget->setRowCount(0);
    searchRow = 0;
    thread = new StationThread(records, station, this);
    connect(thread, &StationThread::foundStation, this, &Client::handleFound, Qt::QueuedConnection);
    connect(thread, &StationThread::searchFinished, this, &Client::searchFinished, Qt::QueuedConnection);
    thread->start();
    setStatus("Searching in a thread...");
}

void Client::handleFound(const QString &date, const QString &mm)
{
    tableWidget->insertRow(searchRow);
    tableWidget->setItem(searchRow, 0, new QTableWidgetItem(searchEdit->text().trimmed()));
    tableWidget->setItem(searchRow, 1, new QTableWidgetItem(date));
    tableWidget->setItem(searchRow, 2, new QTableWidgetItem(mm));
    ++searchRow;
}

void Client::searchFinished()
{
    setStatus(QString("Search finished. %1 matching record(s).").arg(searchRow));
    if (thread) {
        thread->deleteLater();
        thread = nullptr;
    }
}

void Client::backupTable()
{
    delete memento;
    memento = tableWidget->createMemento();
    setStatus("Table backup created.");
}

void Client::restoreTable()
{
    if (!memento) {
        setStatus("No table backup exists.");
        return;
    }
    tableWidget->setMemento(memento);
    setStatus("Table restored from backup.");
}
