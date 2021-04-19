
#include <QWidget>

namespace Ui {
    class PathWidget;
}

class PathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PathWidget(QWidget *parent = 0);
    ~PathWidget();
private slots:
void on_lineEdit_textEdited(const QString &arg1);

void on_lineEdit_4_textEdited(const QString &arg1);

void on_lineEdit_2_textEdited(const QString &arg1);

void on_lineEdit_3_textEdited(const QString &arg1);

void on_lineEdit_5_textEdited(const QString &arg1);

void on_lineEdit_6_textEdited(const QString &arg1);

void on_pushButton_released();

private:
    Ui::PathWidget *ui;
    QString Floor1, Floor2, X1, X2, Y1, Y2;
};
