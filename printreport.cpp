#include "printreport.h"
#include "ui_printreport.h"

printreport::printreport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printreport)
{
    ui->setupUi(this);
}

printreport::~printreport()
{
    delete ui;
}

void printreport::closeEvent(QCloseEvent *e)
{
    emit report_close();
    e->accept();
}

void printreport::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(nullptr, "Выберите файл" , R"(D:\Qt\C++\QtDB2019)" , "*.html"));
}

void printreport::on_pushButton_formedReport_clicked()
{
    auto *file = new QFile();
    file->setFileName(ui->lineEdit->text());
    file->open(QIODevice::WriteOnly);

    QTextStream in(file);

    in << "<html><head></head><body><center>" + QString("Пример создания отчета");
    in << "<table border=1><tr>";
    in << "<td>" + QString("Номер") + "</td>";
    in << "<td>" + QString("Название") + "</td>";
    in << "<td>" + QString("Поставщик") + "</td></tr>";

    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM table1");

    while(query->next())
    {
        in << "<tr><td>";
        in << query->value(0).toString();
        in << "</td><td>";
        in << query->value(1).toString();
        in << "</td><td>";
        in << query->value(2).toString();
        in << "</td></tr>";
    }

    in << "</table></center><body></html>";

    file->close();

    QAxObject *word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);

    QAxObject *doc = word->querySubObject("Documents");
    doc->dynamicCall("Open(QVariant)", ui->lineEdit->text());
}
