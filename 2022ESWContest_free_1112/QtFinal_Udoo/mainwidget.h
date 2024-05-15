#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <tab1socketclient.h>
#include <tab4onoff.h>
#include <tab5mysql.h>
#include <tab6parkinglotlog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwidget; }
QT_END_NAMESPACE

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    mainwidget(QWidget *parent = nullptr);
    ~mainwidget();

private:
    Ui::mainwidget *ui;
    Tab1SocketClient *pTab1SocketClient;
    Tab4OnOff *pTab4OnOff;
    Tab5Mysql *pTab5Mysql;
    Tab6ParkinglotLog *pTab6ParkinglotLog;
};
#endif // MAINWIDGET_H
