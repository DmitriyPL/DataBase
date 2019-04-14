#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    QMessageBox *mes;

protected:

    void closeEvent(QCloseEvent *e);

private slots:
    void on_pushButton_connectDatabase_clicked();

signals:
    void login_close();

private:
    Ui::login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
