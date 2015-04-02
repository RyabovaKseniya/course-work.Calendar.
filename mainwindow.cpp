#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QApplication>
#include <dbmanager.h>
#include <notificationdialog.h>
#include <iostream>
#include <smtp.h>
#include <QPalette>
#include <QPixmap>
#include <QBrush>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->choiceListHolidayDate->addItem(tr("Дни рождения за текущий месяц"));
    ui->choiceListHolidayDate->addItem(tr("Все дни рождения из БД"));

    QPalette palette = QWidget::palette();
    QPixmap background = QPixmap(":/resources/background.jpg");
    QBrush brush(background);
    palette.setBrush(QPalette::Active,QPalette::Background, brush);
    palette.setBrush(QPalette::Inactive,QPalette::Background, brush);
    setPalette(palette);


    //pToolBar = new ToolBar(this);
    pSettingAction = new QAction (tr("Настройки"), this);
    pHelpAction = new QAction (tr("Помощь"), this);
    settingDialog = NULL;
    helpDialog = NULL;
    hollidayDialog = NULL;

    ui->mainToolBar->addAction(pSettingAction);
    ui->mainToolBar->addAction(pHelpAction);
    ui->mainToolBar->setMovable(false);

    NotificationDialog* nd = new NotificationDialog();

        nd->show();

    connect(pSettingAction, SIGNAL(triggered()), this, SLOT(createSettingDialog()));
    connect(pHelpAction, SIGNAL(triggered()), this , SLOT(createHelpDialog()));
    connect(this->ui->addHolidayButton, SIGNAL(clicked()), this, SLOT(createAddDataDialog()));
    connect(this->ui->choiceListHolidayDate, SIGNAL(activated(int)), this, SLOT(on_choiceListHolidayDate_activated(int)));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(dateProcessing(QDate)));
    connect(ui->displayingComingHolidaysWidget, SIGNAL(clicked(QModelIndex)),this ,SLOT(pressOnTableRow(QModelIndex)));
    connect(ui->editHolidayButton, SIGNAL(clicked()), this, SLOT(deleteBPersonFromDB()));
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::dateProcessing(const QDate & date)
{
    QSqlQueryModel* model = DBManager::getInstance()->getDate(date.day(), date.month());
    ui->holidaysSelectedHolidaysWidget->setModel(model);
}

void MainWindow::pressOnTableRow(QModelIndex in){
    index = in;
    std:: cout << " pressOnTableRow" <<std::endl;
}

void MainWindow::deleteBPersonFromDB(){
    int row = index.row();
    QAbstractItemModel* model = ui->displayingComingHolidaysWidget->model();
    QString lastName = model->data(model->index(row,0)).toString();
    QString firstName = model->data( model->index(row,1)).toString();
    QString patronimicName = model->data( model->index(row,2)).toString();
    int day = model->data( model->index(row,3)).toInt();
    int month = model->data( model->index(row,4)).toInt();
    int year = model->data( model->index(row,5)).toInt();
    DBManager::getInstance()->deleteRowFromData(lastName, firstName, patronimicName, day, month, year);
    model->removeRow(row);
    ui->displayingComingHolidaysWidget->setModel(model);
}

/// метод описывающий открытие окно SettingDialog

void MainWindow::createSettingDialog()
{

    if (settingDialog == NULL)
       settingDialog = new SettingDialog();
    settingDialog->show();
}


/// метод описывающий открытие окно HelpDialog

void MainWindow::createHelpDialog()
{

    if (helpDialog == NULL)
        helpDialog = new HelpDialog();
    helpDialog->show();
}


 ///метод описывающий открытие окно AddDataDialog

void MainWindow ::createAddDataDialog()
{
    if (hollidayDialog != NULL)
        delete hollidayDialog;
    hollidayDialog = new AddDataDialog();
    hollidayDialog->show();
}


void MainWindow::on_choiceListHolidayDate_activated(const int &arg1)
{

    ui->displayingComingHolidaysWidget->setModel(DBManager::getInstance()->getModel(arg1));
}

void MainWindow::changeEvent(QEvent *apcEvt)
{
    if(apcEvt->type()== QEvent::LanguageChange)
    {
        pSettingAction->setText(tr("Настройки"));
        pHelpAction->setText(tr("Помощь"));
        ui->choiceListHolidayDate->clear();
        ui->choiceListHolidayDate->addItem(tr("Дни рождения за текущий месяц"));
        ui->choiceListHolidayDate->addItem(tr("Все дни рождения из БД"));
    }
}



