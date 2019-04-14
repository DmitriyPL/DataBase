#ifndef PRINTGRAF_H
#define PRINTGRAF_H

#include <QWidget>
#include <QSqlQuery>

#include "qcpdocumentobject.h"

namespace Ui {
class printgraf;
}

class printgraf : public QWidget
{
    Q_OBJECT

public:
    explicit printgraf(QWidget *parent = nullptr);
    ~printgraf();

private slots:
    void on_pushButton_clicked();

private:
    Ui::printgraf *ui;
};

#endif // PRINTGRAF_H
