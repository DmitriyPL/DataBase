#include "addrecord.h"
#include "ui_addrecord.h"

addrecord::addrecord(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::addrecord)



{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT name FROM suppliers");

    while(query->next())
    {
       ui->comboBox_suppliers->addItem(query->value(0).toString());
    }

    suppliersID = 0;
}

addrecord::~addrecord()
{
    delete ui;
}

void addrecord::closeEvent(QCloseEvent *e)
{
    emit addrec_close();
    e->accept();
}

void addrecord::on_pushButton_addDataInTable_clicked()
{
    try {


    if ( ui->lineEdit_productName->displayText() == QString("") ) throw CustomException();

     QSqlQuery *query = new QSqlQuery();
     query->prepare("INSERT INTO table1(name,post,picture,date) VALUES(:name, :post, :picture, :date)");
     query->bindValue(":name", ui->lineEdit_productName->text());
     query->bindValue(":post", ui->comboBox_suppliers->itemText(suppliersID) );
     query->bindValue(":picture", imageAdress);
     query->bindValue(":date", ui->dateEdit->date().toString(Qt::ISODate));

     auto *mess = new QMessageBox();

     if (!query->exec())
     {
         mess->setText("Запрос составлен не верно");
         mess->show();
     }

        emit refresh_table();

    } catch ( CustomException ) {

        auto *mess = new QMessageBox();
        mess->setText("Пустые поля");
        mess->show();
    }
}

void addrecord::on_toolButton_clicked()
{
    imageAdress = QFileDialog::getOpenFileName(nullptr, "Открыть изображение", R"(D:\Qt\C++\QtDB2019)", "*.jpg");
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(imageAdress));
}

void addrecord::on_comboBox_suppliers_currentIndexChanged(int index)
{
    suppliersID = index;
}
