//============================
// 서버 mariaDB에 있는 데이터베이스를 연동
// 데이터베이스안에 차량의 입차시간, 충전구역 및 주차된 장소를 표로 확인
//============================
#include "tab6parkinglotlog.h"
#include "ui_tab6parkinglotlog.h"

Tab6ParkinglotLog::Tab6ParkinglotLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6ParkinglotLog)
{
    ui->setupUi(this);
    qDebug() << "devices" <<QSqlDatabase::drivers();
    qDebug() << QCoreApplication::libraryPaths();

    connect(ui->pPbReport,SIGNAL(clicked()),this,SLOT(slottab6database()));
}

Tab6ParkinglotLog::~Tab6ParkinglotLog()
{
    delete ui;
}
void Tab6ParkinglotLog::slottab6database()
{
    ui->pTvParkingLogDb->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.141.188");
    db.setUserName("iot");
    db.setPassword("kcci");
    db.setDatabaseName("vehicle_info");
    bool ok =db.open();
    if(ok)
    {
        qDebug() << "Database open\n";
    }
    else
        qDebug() << "Database not open\n" ;

    model1 = new QSqlTableModel(this);
    model1->setTable("parkinglot_log");  //MariaDB의 테이블 정보를 model1에 저장
    ui->pTvParkingLogDb->setModel(model1);
    model1->select();
}
