#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logwin(nullptr),
    addrec(nullptr),
    cmChangeData(nullptr),
    report(nullptr),

    ui(new Ui::MainWindow),

    model(nullptr),
    addrecIsShow(false),
    loginIsShow(false),
    cmChangeDataIsShow(false),
    reportIsShow(false),
    flag_showData(false)

{
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect (ui->tableView, SIGNAL( customContextMenuRequested(const QPoint) ), SLOT( on_customContextMenuRequested(const QPoint) ) );

    ui->dateEdit->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::GetIdFromTable(const QModelIndex &index)
{
    return ( ui->tableView->model()->data( ui->tableView->model()->index(index.row(),0) ).toInt() );
}

void MainWindow::deleteData(QString &index)
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM table1 WHERE id = ?");
    query->bindValue(0, index);

    if(query->exec())
    {
      on_pushButton_showData_clicked();
    }
}

QString &MainWindow::GetContextMenuItem_ID()
{
    return ContextMenuItem_ID;
}

void MainWindow::on_action_triggered()
{
    if (!loginIsShow)
    {
        logwin = new login();
        connect(logwin, SIGNAL( login_close() ), this, SLOT( on_login_close() ) );
        loginIsShow = true;
        logwin->show();
    } else {
        logwin->raise();
    }
}

void MainWindow::on_pushButton_showData_clicked()
{
    flag_showData = true;

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM table1");

    model->setHeaderData(0, Qt::Horizontal, "Номер п/п");
    model->setHeaderData(1, Qt::Horizontal, "Название товара");
    model->setHeaderData(2, Qt::Horizontal, "Поставщик");
    model->setHeaderData(3, Qt::Horizontal, "Изображение");
    model->setHeaderData(4, Qt::Horizontal, "Дата поставки");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::on_pushButton_addDataWinOpen_clicked()
{
    if (!addrecIsShow)
    {
        addrec = new addrecord();
        connect(addrec, SIGNAL( refresh_table() ), this, SLOT( on_refresh_table() ) );
        connect(addrec, SIGNAL( addrec_close() ), this, SLOT( on_addrec_close() ) );
        addrecIsShow = true;
        addrec -> show();
    } else {
        addrec->raise();
    }
}

void MainWindow::on_refresh_table()
{
        on_pushButton_showData_clicked();
}

void MainWindow::on_addrec_close()
{
    addrecIsShow = false;
}

void MainWindow::on_login_close()
{
    loginIsShow = false;
}

void MainWindow::on_cmChangeData_close()
{
    cmChangeDataIsShow = false;
}

void MainWindow::on_report_close()
{
    reportIsShow = false;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_value;
    temp_value = GetIdFromTable(index);

    ui->lineEdit_posNumber->setText(QString::number(temp_value));

    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, post, picture, date FROM table1 WHERE id = :id");
    query->bindValue(":id", temp_value);

    if(query->exec())
    {
        query->next();
        ui->lineEdit_productName->setText(query->value(0).toString());
        ui->lineEdit_supplier->setText(query->value(1).toString());

        ui->PictureShow->setScaledContents(true);
        ui->PictureShow->setPixmap( QPixmap(query->value(2).toString()) ) ;

        ui->dateEdit->setDate(QDate::fromString((query->value(3)).toString(), Qt::ISODate));
    }
}

void MainWindow::on_pushButton_changeData_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE table1 SET name = ?, post =  ? WHERE id = ?");
    query->bindValue(0, ui->lineEdit_productName->text());
    query->bindValue(1, ui->lineEdit_supplier->text());
    query->bindValue(2, ui->lineEdit_posNumber->text());

    if(query->exec())
    {
        on_pushButton_showData_clicked();
    }
}

void MainWindow::on_pushButton_deleteData_clicked()
{
   QString index = ui->lineEdit_posNumber->text();
   deleteData(index);
}

void MainWindow::on_customContextMenuRequested(const QPoint &pos)
{
    if (flag_showData)
    {
        QModelIndex Index_tableData = ui->tableView->indexAt(pos);
        ContextMenuItem_ID = QString::number(GetIdFromTable(Index_tableData));

        auto   *context_Menu = new QMenu(this);

        QAction *change       = new QAction("Изменить", this);
        connect( change, SIGNAL(triggered()), this, SLOT( on_tableView_change() ) );

        QAction *del          = new QAction("Удалить", this);
        connect( del, SIGNAL(triggered()), this, SLOT( on_tableView_del() ) );

        context_Menu->addAction(change);
        context_Menu->addAction(del);
        context_Menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::on_tableView_del()
{
    deleteData(ContextMenuItem_ID);
}

void MainWindow::on_tableView_change()
{
    if (!cmChangeDataIsShow)
    {
        cmChangeData = new cmchangedata;
        cmChangeDataIsShow = true;

        connect(cmChangeData, SIGNAL( cmChangeData_close() ), this, SLOT( on_cmChangeData_close() ) );
        connect(this, SIGNAL(sendContextMenuItem_ID(QString&)), cmChangeData, SLOT( on_sendContextMenuItem_ID(QString&)) );
        connect( cmChangeData, SIGNAL( refresh_table() ), this, SLOT( on_refresh_table() ) );

        emit sendContextMenuItem_ID(ContextMenuItem_ID);

        cmChangeData->show();

        disconnect(this, SIGNAL(sendContextMenuItem_ID(QString&)), cmChangeData, SLOT( on_sendContextMenuItem_ID(QString&)) );

    } else {
        cmChangeData->raise();
    }
}

void MainWindow::on_pushButton_printReport_clicked()
{
    if(!reportIsShow)
    {
        report = new printreport();
        reportIsShow = true;
        connect( report, SIGNAL( report_close() ), this, SLOT( on_report_close()) );
        report->show();
    } else {
        report->raise();
    }

}

void MainWindow::on_pushButton_printToPDF_clicked()
{
    qDebug() << "Вошли в форму";

    QString str;

    str.append("<html><head></head><body><center>" + QString("Пример создания отчета"));
    str.append ("<table border=1><tr>");
    str.append ("<td>" + QString("Номер") + "</td>");
    str.append ("<td>" + QString("Название") + "</td>");
    str.append ("<td>" + QString("Поставщик") + "</td></tr>");

    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM table1");

    while(query->next())
    {
        str.append ("<tr><td>");
        str.append (query->value(0).toString());
        str.append ("</td><td>");
        str.append (query->value(1).toString());
        str.append ("</td><td>");
        str.append (query->value(2).toString());
        str.append ("</td></tr>");
    }

    str.append ("</table></center><body></html>");

    QPrinter pdfPrint;
    pdfPrint.setOrientation(QPrinter::Portrait);
    pdfPrint.setOutputFormat(QPrinter::PdfFormat);
    pdfPrint.setPaperSize(QPrinter::A4);

    QString savePath;
    savePath = QFileDialog::getSaveFileName(this, tr("Сохранить в PDF"), "Отчет", tr("PDF (*.pdf)"));

    if(savePath.isEmpty()) return;

    pdfPrint.setOutputFileName(savePath);

    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&pdfPrint);
}

//Не удалять проблемы с /.moc В mainwindow была создана кнопуля, потом удалена, без описания, но успела везде прописаться!!!
void MainWindow::on_pushButton_clicked()
{}

void MainWindow::on_action_2_triggered()
{
    pg = new printgraf();
    pg->show();
}
