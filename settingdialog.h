#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QApplication>
#include <QTranslator>
#include <dbmanager.h>

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    void fillListOfEmails();
    void getCheckedEmails();
    QList<QString> getBPersons();

private slots:
    void okSaveSettingButton();

    void cancelSettingButton();

    void applySettingButton();

    void on_choiceListLanguage_activated(const QString choiceLanguage);

    void on_okSaveEmailButton_clicked();

    void on_tabWidget_tabBarClicked(int index);



protected:
    void changeEvent(QEvent *apcEvt);

private:
    QTranslator translator;
    Ui::SettingDialog *ui;
    QSqlDatabase db;
    QSqlTableModel *model;




};

#endif // SETTINGDIALOG_H
