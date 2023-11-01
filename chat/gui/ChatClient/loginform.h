#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QString>
namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
signals:
    void registrationRequested();

private slots:

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_registrationButton_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
