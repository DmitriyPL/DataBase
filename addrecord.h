#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>

#include <QMessageBox>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDate>
#include <QDateEdit>
#include <exception>

namespace Ui {
class addrecord;
}

class addrecord : public QWidget
{
    Q_OBJECT

public:
    explicit addrecord(QWidget *parent = nullptr);
    ~addrecord();

    struct CustomException : public std::exception {};

protected:

    void closeEvent(QCloseEvent *e);

private slots:
    void on_pushButton_addDataInTable_clicked();

    void on_toolButton_clicked();

    void on_comboBox_suppliers_currentIndexChanged(int index);

signals:
    void refresh_table();
    void addrec_close();

private:
    Ui::addrecord *ui;
    QString imageAdress;
    int suppliersID;
};

#endif // ADDRECORD_H
