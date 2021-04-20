#include "pathwidget.h"
#include "ui_PathWidget.h"

PathWidget::PathWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathWidget)
{
    setMinimumWidth(250);
    ui->setupUi(this);
}
PathWidget::~PathWidget()
{
    delete ui;
}

void PathWidget::on_lineEdit_textEdited(const QString &arg1)
{
    Floor1 = arg1;
}

void PathWidget::on_lineEdit_4_textEdited(const QString &arg1)
{
    Floor2 = arg1;
}

void PathWidget::on_lineEdit_2_textEdited(const QString &arg1)
{
    X1 = arg1;
}

void PathWidget::on_lineEdit_3_textEdited(const QString &arg1)
{
    Y1 = arg1;
}

void PathWidget::on_lineEdit_5_textEdited(const QString &arg1)
{
    X2 = arg1;
}

void PathWidget::on_lineEdit_6_textEdited(const QString &arg1)
{
    Y2 = arg1;
}

void PathWidget::on_pushButton_released()
{
    int a;
    a++;
    emit ButtonPressed();
}
