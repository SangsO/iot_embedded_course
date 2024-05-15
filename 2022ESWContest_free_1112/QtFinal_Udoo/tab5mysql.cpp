//============================
// 서버 mariaDB에 있는 데이터베이스를 연동
// 데이터베이스안에 주차장입출차 상태, 번호, 충전 타입 정보를 표로 표시
//============================

#include "tab5mysql.h"
#include "ui_tab5mysql.h"

Tab5Mysql::Tab5Mysql(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab5Mysql)
{
    ui->setupUi(this);

    qDebug() << "devices" <<QSqlDatabase::drivers();
    qDebug() << QCoreApplication::libraryPaths();

    connect(ui->pPbReport,SIGNAL(clicked()),this,SLOT(slottab5database()));
    connect(ui->pPbclear,SIGNAL(clicked()),this,SLOT(slotDbclear()));
}

Tab5Mysql::~Tab5Mysql()
{
    delete ui;
}

void Tab5Mysql::slottab5database()
{
    ui->pTvNowStatDb->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.10.141.188");
    db.setUserName("iot");
    db.setPassword("kcci");
    db.setDatabaseName("vehicle_info");
    //db의 정보를 입력하여 연동

    bool ok =db.open();
    if(ok)
    {
        qDebug() << "Database open\n";
    }
    else
        qDebug() << "Database not open\n" ;

    model = new QSqlTableModel(this);
    model->setTable("now_stat");  //MariaDB의 테이블 정보를 model에 저장
    ui->pTvNowStatDb->setModel(model); //해당 테이블의 데이터를 Tableview에 표시

    model->select();
}

void Tab5Mysql::slotDbclear()
{
    model->deleteLater();
}
