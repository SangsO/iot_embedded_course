#ifndef TAB6PARKINGLOTLOG_H
#define TAB6PARKINGLOTLOG_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class Tab6ParkinglotLog;
}

class Tab6ParkinglotLog : public QWidget
{
    Q_OBJECT

public:
    explicit Tab6ParkinglotLog(QWidget *parent = nullptr);
    ~Tab6ParkinglotLog();

private:
    Ui::Tab6ParkinglotLog *ui;
    QSqlDatabase db;
    QSqlTableModel *model1;

private slots:
    void slottab6database();
};

#endif // TAB6PARKINGLOTLOG_H
