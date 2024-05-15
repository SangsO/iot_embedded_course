//=====================================
// 서버를 통해 들어온 데이터를 client별로 구별
// 서버 연결시 pSocketClient을 통해 서버에서 보낼 데이터 함수
//=====================================


#include "tab1socketclient.h"
#include "ui_tab1socketclient.h"

Tab1SocketClient::Tab1SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab1SocketClient)
{
    ui->setupUi(this);

    pSocketClient = new SocketClient(this);
    connect(ui->pPbServerConnect,SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer(bool)));
    connect(pSocketClient, SIGNAL(sigSocketRecv(QString)), this, SLOT(slotSocketRecvUpdate(QString)));
    connect(ui->pPbRecvDataClear, SIGNAL(clicked()), ui->pTeRecvData1, SLOT(clear()));
    connect(ui->pPbRecvDataClear, SIGNAL(clicked()), ui->pTeRecvData2, SLOT(clear()));

}

Tab1SocketClient::~Tab1SocketClient()
{
    delete ui;
}
void Tab1SocketClient :: slotConnectToServer(bool check)  //connect버튼을 눌러 서버와 연결 및 연결 해제
{
    bool bOK;
    if(check){
        pSocketClient->slotConnectToServer(bOK);

        if(bOK)
        {
            ui->pPbServerConnect->setText("disconnect");
        }
    }
    else
    {
        pSocketClient->slotClosedByServer();
        ui->pPbServerConnect->setText("connect");
    }
}
void Tab1SocketClient :: slotSocketRecvUpdate(QString strRecvData) //서버를 통해 받은 메시지 client 구별 및 데이터내용별로 signal 구별
{
    //qDebug() << strRecvData;

    QTime time = QTime::currentTime();
    QString strtime = time.toString();
    //qDebug() << strtime;
    //strRecvData.chop(1);
    //qDebug() << strRecvData.indexOf("0") << strRecvData.indexOf("1") ;

    if((strRecvData.indexOf("SPOT1") != -1)) //client가 SPOT1일 경우
    {
        if((strRecvData.indexOf("@") != -1)) //받은 데이터에 @ 존재시 textview2에 내용 표시
        {
            strRecvData.chop(1);
            emit sigTab4RecvData(strRecvData);
            ui->pTeRecvData2->append(strRecvData);
            ui->pTeRecvData2->moveCursor(QTextCursor::End);
            //qDebug() << strRecvData;
        }
        else if((strRecvData.indexOf("1") != -1)||(strRecvData.indexOf("0") != -1))  //받은 데이터에 1또는0 존재시 textview1에 내용 표시
        {
            strRecvData.chop(1);
            emit sigTab4InOutData(strRecvData);
            ui->pTeRecvData1->append(strRecvData);
            ui->pTeRecvData1->moveCursor(QTextCursor::End);

        }
    }
    else if ((strRecvData.indexOf("Jets1") != -1)) //client가 Jetson1일 경우
    {
        if((strRecvData.indexOf("L") != -1))  //받은 데이터에 L 존재시 2번째 탭(충천 GUI화면) signal을 통해 데이터 내용 전송
        {
            strRecvData.chop(1);
            emit sigTab4Rechage(strRecvData);
            qDebug() << strRecvData;
        }
    }
}

void Tab1SocketClient :: slotSocketSendData(QString strData)  //server에게 보낼 데이터 함수
{
    if(ui->pPbServerConnect->isChecked())
    {
        pSocketClient->slotSocketSendData(strData);
    }
    else
        QMessageBox::information(this,"socket", "need server connection");

}
