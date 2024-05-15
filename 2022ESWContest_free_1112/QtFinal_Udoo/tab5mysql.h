#ifndef TAB5MYSQL_H
#define TAB5MYSQL_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class Tab5Mysql;
}

class Tab5Mysql : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5Mysql(QWidget *parent = nullptr);
    ~Tab5Mysql();

private:
    Ui::Tab5Mysql *ui;
    QSqlDatabase db;
    QSqlTableModel *model;

private slots:
    void slottab5database();
    void slotDbclear();
};

#endif // TAB5MYSQL_H
