#include "mainwindow.h"
#include "ui_mainwindow.h"

//libqt5sql5-mysql драйвер mysql
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("admin");
    //db.setUserName("root");
    db.setPassword("!Patriot1");
    db.setDatabaseName("chatdb");
    if(db.open())
       {
         ui->statusBar->showMessage("Database connection succesful");
         user();
         message();
       }
       else
       {
        ui->statusBar->showMessage("Database connection failed");
       }

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}
void MainWindow::on_updateUserPushButton_clicked()
{
   user();
}
void MainWindow::on_updateMessagePushButton_clicked()
{
   message();
}
void MainWindow::message()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(0,db);
    query->prepare("SELECT `date` as 'дата отправления',user_from.login as 'отправитель', \
           user_to.login as 'получатель', message as 'сообщение' \
           from messages \
           left join users user_from on messages.from_user_id = user_from.id \
           left join  users user_to on messages.to_user_id = user_to.id  order by `date` ;");
    query->exec();
    model->setQuery(*query);
    ui->tableViewMessages->setModel(model);
    ui->tableViewMessages->resizeColumnsToContents();
    ui->tableViewMessages->setColumnWidth(1, 150);
    ui->tableViewMessages->setColumnWidth(2, 150);
    ui->tableViewMessages->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void MainWindow::user()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(0,db);
    query->prepare("SELECT id, login as 'Логин',\
                    date_registration as 'Дата регистрации', \
                    ban_user as 'Доступ' FROM users WHERE id !=0");
    query->exec();
    model->setQuery(*query);
    ui->tableViewUsers->setModel(model);
    ui->tableViewUsers->resizeColumnsToContents();
    ui->tableViewUsers->setColumnWidth(0, 50);
    ui->tableViewUsers->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void MainWindow::on_pushButtonBan_clicked()
{

    if(ui->tableViewUsers->selectionModel()->hasSelection())
     {
      QModelIndex index = ui->tableViewUsers->selectionModel()->selectedIndexes().first();
      if(index.isValid())
          {
            int content;
            content = index.data().toInt();
            QSqlQuery *query = new QSqlQuery(0,db);
            query->prepare("UPDATE users SET ban_user = 1 WHERE id = " + QString::number(content));
            query->exec();
          }
    }
    user();
}

void MainWindow::on_pushButtonUnban_clicked()
{
    if(ui->tableViewUsers->selectionModel()->hasSelection())
    {
        QModelIndex select = ui->tableViewUsers->selectionModel()->selectedIndexes().first();
        if(select.isValid())
        {
        int content;
        content = select.data().toInt();
        QSqlQuery *query = new QSqlQuery(0,db);
        query->prepare("UPDATE users SET ban_user = 0 WHERE id = " + QString::number(content));
        query->exec();
        }
    }
    user();
}

