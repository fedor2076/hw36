#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient();

private slots:
    void on_messageEdit_returnPressed();

    void on_allSendButton_clicked();

    void on_privateSendButton_clicked();

    void on_actionchose_client_triggered();

    void on_actionexit_triggered();
    void showEvent(QShowEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
