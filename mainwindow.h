#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QtDebug>

#include <QSqlQueryModel>

#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

#include "login.h"
#include "ui_login.h"

#include "addrecord.h"
#include "ui_addrecord.h"

#include "cmchangedata.h"
#include "ui_cmchangedata.h"

#include "printreport.h"
#include "ui_printreport.h"

#include "printgraf.h"
#include "ui_printgraf.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int GetIdFromTable(const QModelIndex &index);
    void deleteData(QString &index);
    QString& GetContextMenuItem_ID();

    login        *logwin;
    addrecord    *addrec;
    cmchangedata *cmChangeData;
    printreport  *report;
    printgraf    *pg;


private slots:
    void on_action_triggered();

    void on_pushButton_showData_clicked();

    void on_pushButton_addDataWinOpen_clicked();

    void on_refresh_table();

    void on_addrec_close();

    void on_login_close();

    void on_cmChangeData_close();

    void on_report_close();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_changeData_clicked();

    void on_pushButton_deleteData_clicked();

    void on_customContextMenuRequested(const QPoint &pos);

    void on_tableView_del();

    void on_tableView_change();

    void on_pushButton_printReport_clicked();

    void on_pushButton_clicked();

    void on_pushButton_printToPDF_clicked();

    void on_action_2_triggered();

signals:
    void sendContextMenuItem_ID(QString&);

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;

    QString ContextMenuItem_ID;

    bool addrecIsShow;
    bool loginIsShow;
    bool cmChangeDataIsShow;
    bool reportIsShow;

    bool flag_showData;
};

#endif // MAINWINDOW_H
