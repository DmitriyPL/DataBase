#ifndef CMCHANGEDATA_H
#define CMCHANGEDATA_H

#include <QWidget>
#include <QCloseEvent>
#include <QSqlQuery>

namespace Ui {
class cmchangedata;
}

class cmchangedata : public QWidget
{
    Q_OBJECT

public:
    explicit cmchangedata(QWidget *parent = nullptr);
    ~cmchangedata();

protected:

    void closeEvent(QCloseEvent *e);

signals:
    void refresh_table();
    void cmChangeData_close();

private slots:
    void on_pushButton_addDataInTable_clicked();
    void on_sendContextMenuItem_ID(QString &ContextMenuItem_ID);

private:
    Ui::cmchangedata *ui;

};

#endif // CMCHANGEDATA_H
