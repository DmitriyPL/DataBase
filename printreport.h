#ifndef PRINTREPORT_H
#define PRINTREPORT_H

#include <QWidget>

#include <QCloseEvent>
#include <QAxObject>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class printreport;
}

class printreport : public QWidget
{
    Q_OBJECT

public:
    explicit printreport(QWidget *parent = nullptr);
    ~printreport();

protected:

    void closeEvent(QCloseEvent *e);

signals:
    void report_close();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_formedReport_clicked();

private:
    Ui::printreport *ui;
};

#endif // PRINTREPORT_H
