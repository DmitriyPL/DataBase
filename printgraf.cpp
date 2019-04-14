#include "printgraf.h"
#include "ui_printgraf.h"

printgraf::printgraf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printgraf)
{
    ui->setupUi(this);

    QCPDocumentObject *poHeandler = new QCPDocumentObject(this);
    ui->textEdit->document()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, poHeandler);
    ui->textEdit->setVisible(false);

    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0,0, new QCPPlotTitle(ui->widget, "График выручки"));

    QVector<double> dx, dy;

    double minX, minY, maxX, maxY;
    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;

    QSqlQuery *query = new QSqlQuery();

    if ( query->exec( " SELECT * FROM profitability " ) )
    {
        while (query->next())
        {
            if (minX >= query->value(0).toDouble() ) minX = query->value(0).toDouble();
            if (minY >= query->value(1).toDouble() ) minY = query->value(1).toDouble();
            if (maxX <= query->value(0).toDouble() ) maxX = query->value(0).toDouble();
            if (maxY <= query->value(1).toDouble() ) maxY = query->value(1).toDouble();

            dx << query->value(0).toDouble();
            dy << query->value(1).toDouble();

            QCPBars *bar = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
            bar->setName("Значение");
            bar->setBrush(QColor(255, 0, 0, 255));
            bar->setData(dx, dy);
            bar->setWidth(0.20);

            ui->widget->xAxis->setLabel("Месяц");
            ui->widget->yAxis->setLabel("Выручка (млн.)");

            ui->widget->xAxis->setRange(minX, maxX+0.20);
            ui->widget->yAxis->setRange(minY-0.5, maxY+1);

            ui->widget->xAxis->setAutoTickStep(false);
            ui->widget->yAxis->setAutoTickStep(false);
            ui->widget->xAxis->setTickStep(1);
            ui->widget->yAxis->setTickStep(1);

            ui->widget->replot();
        }
    }


    QTextCursor cur = ui->textEdit->textCursor();
    cur.insertText(QString(QChar::ObjectReplacementCharacter), QCPDocumentObject::generatePlotFormat(ui->widget, 480, 340));
}

printgraf::~printgraf()
{
    delete ui;
}

void printgraf::on_pushButton_clicked()
{
    QString savePath;
    savePath = QFileDialog::getSaveFileName(this, tr("Сохранить в PDF"), "./", tr("PDF (*.pdf)"));

    if(!savePath.isEmpty())
    {
        QPrinter pdfPrint;
        pdfPrint.setFullPage(true);
        pdfPrint.setOrientation(QPrinter::Portrait);
        pdfPrint.setOutputFormat(QPrinter::PdfFormat);
        pdfPrint.setPaperSize(QPrinter::A4);

        pdfPrint.setOutputFileName(savePath);
        ui->textEdit->document()->print(&pdfPrint);
    };
}
