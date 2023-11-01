#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_buttonBox_accepted()
{
QString login = ui->loginEdit->text();
QString password = ui->passwordEdit->text();
//if (login=="1" && password=="1"){
 // ui->statusbar
    // emit registrationRequested();
}



void LoginForm::on_buttonBox_rejected()
{

}

void LoginForm::on_registrationButton_clicked()
{
emit registrationRequested();
}
