#ifndef TAB4ONOFF_H
#define TAB4ONOFF_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "socketclient.h"

namespace Ui {
class Tab4OnOff;
}

class Tab4OnOff : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4OnOff(QWidget *parent = nullptr);
    ~Tab4OnOff();

private:
    Ui::Tab4OnOff *ui;
    SocketClient* pSocketClient;
    QPixmap m_img[5];
    QSqlDatabase db;
    QSqlTableModel *model;


private slots:
    void slotOneOnOff(bool);
    void slotTwoOnOff(bool);
    void slotTab4RecvData(QString);
    void slotTab4InOutData(QString);
    void slotTab4Rechage(QString);

signals:
    void sigSocketSendData(QString);


};

#endif // TAB4ONOFF_H
