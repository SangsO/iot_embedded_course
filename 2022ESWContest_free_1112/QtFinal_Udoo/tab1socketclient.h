#ifndef TAB1SOCKETCLIENT_H
#define TAB1SOCKETCLIENT_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include "socketclient.h"


namespace Ui {
class Tab1SocketClient;
}

class Tab1SocketClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1SocketClient(QWidget *parent = nullptr);
    ~Tab1SocketClient();

private:
    Ui::Tab1SocketClient *ui;
    SocketClient *pSocketClient;
    QString dlgLineStr;


private slots:
    void slotConnectToServer(bool);
    void slotSocketRecvUpdate(QString);
    void slotSocketSendData(QString);

signals:
    void sigTab4RecvData(QString);
    void sigTab4InOutData(QString);
    void sigTab4Rechage(QString);

};

#endif // TAB1SOCKETCLIENT_H
