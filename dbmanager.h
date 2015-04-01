#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>


class DBManager
{
private:
    QSqlDatabase db;
    static DBManager* instance;

public:
    DBManager();
    ~DBManager();

    static DBManager*   getInstance();

    /// получение модели для таблицы на главном окне снизу
    QSqlQueryModel* getModel(int mode);
    QSqlQueryModel* getDate(int day,int month);
    ///
    //QSqlTableModel* getCurrentModel();
    /// получение самих тектов для
    QString getTextFor(int idText);
    /// подпиши (получение списка имен текстов для комбобокса)
    QSqlQueryModel* listTextCongr();

    bool addRecordToData(QString lastName, QString firstName, QString patronimicName, QString email, QDate date, QTime hoursReminder, QDate userReminderDate, QTime userReminderTime);

    /// Добавить почту в таблицу почт пользователя
    void addRecordToPersonalEmail( QString email);

    QList<QString> getListOfEmails ();
};

#endif // DBMANAGER_H
