#ifndef QFILESOCKET_H
#define QFILESOCKET_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QDataStream>
#include "socketclient.h"

namespace Ui {
class QfileSocket;
}

class QfileSocket : public QWidget
{
    Q_OBJECT

public:
    explicit QfileSocket(QWidget *parent = nullptr);
    ~QfileSocket();

private:
    Ui::QfileSocket *ui;
    SocketClient *pSocketClient;


private slots :
    void slotQfileRecvData(QString);
    void slotReadLog();
};

#endif // QFILESOCKET_H
