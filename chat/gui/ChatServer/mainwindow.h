#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QDebug>
#include <QSqlDatabase>
//#include <QSqlError>
#include <QModelIndexList>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QString>
#include <QAbstractItemView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_updateUserPushButton_clicked();
    void on_updateMessagePushButton_clicked();
    void on_pushButtonBan_clicked();
    void on_pushButtonUnban_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    void message();
    void user();
};
#endif // MAINWINDOW_H
