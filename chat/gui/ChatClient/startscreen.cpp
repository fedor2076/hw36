#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    connect(ui->pageLogin, &LoginForm::registrationRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->pageRegistration, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);

}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}
