#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "adddatadialog.h"
#include "helpdialog.h"
#include "settingdialog.h"
#include "textconfiguratulatiodialog.h"
#include "emailsenddialog.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAction* pSettingAction;
    QAction* pHelpAction;
    SettingDialog *settingDialog;
    HelpDialog *helpDialog;
    AddDataDialog *hollidayDialog;
    QSqlDatabase db;
    QSqlTableModel *model;
    QModelIndex index;


protected:
    void changeEvent(QEvent *);
private slots:
    void dateProcessing(const QDate & date);
    void pressOnTableRow(QModelIndex index);
    void deleteBPersonFromDB();
public slots:

    void createSettingDialog();
    void createHelpDialog();
    void createAddDataDialog();
    void on_choiceListHolidayDate_activated(const int &arg1);

};

#endif // MAINWINDOW_H
