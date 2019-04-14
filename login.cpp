#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    // Delete befor using
    ui->lineEdit_dataBasePath->setText( R"(D:\Qt\C++\QtDB2019\DB\)" );
    ui->lineEdit_dataBaseName->setText("DB2019");
    // Delete befor using

    mes = new QMessageBox();
}

login::~login()
{
    delete ui;
}

void login::closeEvent(QCloseEvent *e)
{
    emit login_close();
    e->accept();
}

void login::on_pushButton_connectDatabase_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( ui->lineEdit_dataBasePath->text() + ui->lineEdit_dataBaseName->text() + ".db" );

    if (db.open()){
        mes->setText("Connect");
    }
    else {
        mes->setText("Not connect");
    }

    mes->show();
}
