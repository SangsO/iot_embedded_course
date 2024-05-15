#include "mainwidget.h"
#include "ui_mainwidget.h"

mainwidget::mainwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainwidget)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    pTab1SocketClient = new Tab1SocketClient(ui->pTab1);
    ui->pTab1->setLayout(pTab1SocketClient->layout());

    pTab4OnOff = new Tab4OnOff(ui->pTab4);
    ui->pTab4->setLayout(pTab4OnOff->layout());

    pTab5Mysql=new Tab5Mysql(ui->pTab5);
    ui->pTab5->setLayout(pTab5Mysql->layout());

    pTab6ParkinglotLog = new Tab6ParkinglotLog(ui->pTab6);
    ui->pTab6->setLayout(pTab6ParkinglotLog->layout());


    connect(pTab1SocketClient, SIGNAL(sigTab4RecvData(QString)), pTab4OnOff, SLOT(slotTab4RecvData(QString)));
    connect(pTab1SocketClient, SIGNAL(sigTab4InOutData(QString)), pTab4OnOff, SLOT(slotTab4InOutData(QString)));
    connect(pTab1SocketClient, SIGNAL(sigTab4Rechage(QString)), pTab4OnOff, SLOT(slotTab4Rechage(QString)));
    connect(pTab4OnOff, SIGNAL(sigSocketSendData(QString)), pTab1SocketClient, SLOT(slotSocketSendData(QString)));

}

mainwidget::~mainwidget()
{
    delete ui;
}

