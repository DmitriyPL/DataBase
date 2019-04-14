#include "cmchangedata.h"
#include "ui_cmchangedata.h"

cmchangedata::cmchangedata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cmchangedata)
{
    ui->setupUi(this);
}

cmchangedata::~cmchangedata()
{
    delete ui;
}

void cmchangedata::closeEvent(QCloseEvent *e)
{
    emit cmChangeData_close();
    e->accept();
}

void cmchangedata::on_sendContextMenuItem_ID(QString &ContextMenuItem_ID)
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, post FROM table1 WHERE id = ?");
    query->bindValue(0, ContextMenuItem_ID);

    if(query->exec())
    {
        query->next();
        ui->lineEdit_productName->setText(query->value(0).toString());
        ui->lineEdit_supplier->setText(query->value(1).toString());
        ui->lineEdit_posNumber->setText(ContextMenuItem_ID);
    }
}

void cmchangedata::on_pushButton_addDataInTable_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE table1 SET name = ?, post =  ? WHERE id = ?");
    query->bindValue(0, ui->lineEdit_productName->text());
    query->bindValue(1, ui->lineEdit_supplier->text());
    query->bindValue(2, ui->lineEdit_posNumber->text());

    if(query->exec())
    {
        emit refresh_table();
    }

}
