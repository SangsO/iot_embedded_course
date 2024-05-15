//=================================
// 관리자가 충전구역에 차량 입출차 상태 및 충전량 확인, 긴급충전정지 제어 화면
// 긴급충전정지시 충전기 해제 명령 전송 및 버튼이 충전기연결해제 이미지로 변경
// 충전구역에 차량유무를 이미지로 표현
//=================================

#include "tab4onoff.h"
#include "ui_tab4onoff.h"

Tab4OnOff::Tab4OnOff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab4OnOff)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);

    connect(ui->pPBLamp1,SIGNAL(clicked(bool)),this,SLOT(slotOneOnOff(bool)));
    connect(ui->pPBLamp2,SIGNAL(clicked(bool)),this,SLOT(slotTwoOnOff(bool)));

    m_img[0].load(":/IotQtClient/img/areaemp.png");
    m_img[1].load(":/IotQtClient/img/areacar.png");
    m_img[2].load(":/IotQtClient/img/plugIn.png");
    m_img[3].load(":/IotQtClient/img/plugOut.png");

    ui->progressBar->setValue(0);

   // db = QSqlDatabase::addDatabase("QMYSQL");
   // db.setHostName("10.10.141.188");
   // db.setUserName("iot");
    //db.setPassword("kcci");
    //db.setDatabaseName("vehicle_info");
   // bool ok =db.open();
    //if(ok)
    //{
     //   qDebug() << "Database open\n";
    //}
    //else
     //   qDebug() << "Database not open\n" ;

    //model = new QSqlTableModel(this);
    //model->setTable("now_stat");
}

Tab4OnOff::~Tab4OnOff()
{
    delete ui;
}
void Tab4OnOff::slotOneOnOff(bool check)  //관리자가 긴급충전정지시 버튼이미지 변경 및 해제 명령 전송
{
    if(check)
    {
        ui->pPBLamp1->setChecked(true);
        emit sigSocketSendData("[Jets1]6@");
        ui->pPBLamp1->setIcon(QIcon(":/IotQtClient/img/plugOut.png"));
        ui->pPBLamp1->setIconSize(QSize(60,60));

    }
    else
    {
        ui->pPBLamp1->setChecked(false);
        emit sigSocketSendData("[SPOT1]ONL");
        ui->pPBLamp1->setIcon(QIcon(":/IotQtClient/img/plugIn.png"));
        ui->pPBLamp1->setIconSize(QSize(60,60));
    }
}
void Tab4OnOff::slotTwoOnOff(bool check)
{
    if(check)
    {
        ui->pPBLamp2->setChecked(true);
        emit sigSocketSendData("[SPOT2]ON");
    }
    else
    {
        ui->pPBLamp2->setChecked(false);
        emit sigSocketSendData("[SPOT2]OFF");
    }
}
void Tab4OnOff::slotTab4RecvData(QString strRecvData)  //충전 시작시 차량의 배터리량을 pregressBar로 현재 배터리량 표시
{
    //qDebug() << strRecvData;
    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList qlist = strRecvData.split("@");
    QString batt = qlist[2];
    int bat = batt.toInt();
    ui->progressBar->setValue(bat);

}
void Tab4OnOff::slotTab4InOutData(QString strInOutData)  //차량 충전구역 입출차시 차량의 유무를 차량이미지로 표시
{
    //qDebug() << strInOutData;

    if(strInOutData.indexOf("1") != -1)
    {
        ui->pcar1->setPixmap(m_img[1].scaled(200,268,Qt::KeepAspectRatio));
        //ui->pPBLamp1->setIcon(m_img[2].scaled(w,h,Qt::KeepAspectRatio));
/*
        QString query;
        QSqlQuery qry;
        query = "UPDATE now_stat SET STATUS = '1' WHERE SPOT = 'SPOT1'";
        if(!qry.exec(query))
        {
            qDebug() << qry.lastError().text();
            qDebug() << "Database not update\n" ;
        }
        else
        {
            qDebug() << "Database update\n" ;
        }
*/
    }
    if(strInOutData.indexOf("0") != -1)
    {
        ui->pcar1->setPixmap(m_img[0].scaled(200,268,Qt::KeepAspectRatio));
        //ui->pPBLamp1->setIcon(m_img[3].scaled(w,h,Qt::KeepAspectRatio));
        ui->progressBar->setValue(0);
/*
       QString query;
       QSqlQuery qry;
       query = "UPDATE now_stat SET STATUS = '0' WHERE SPOT = 'SPOT1'";
       if(!qry.exec(query))
       {
           qDebug() << qry.lastError().text();
           qDebug() << "Database not update\n" ;
       }
       else
       {
           qDebug() << "Database update\n" ;
       }
*/


    }
}
void Tab4OnOff::slotTab4Rechage(QString strRechageData)  //Jetson에게 충전시작 데이터를 받으면 버튼의 이미지를 충전된 이미지로 변경
{
    if(strRechageData.indexOf("5") != -1)
    {
        ui->pPBLamp1->setIcon(QIcon(":/IotQtClient/img/plugIn.png"));
        ui->pPBLamp1->setIconSize(QSize(60,60));

    }
}
