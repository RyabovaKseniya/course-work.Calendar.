#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QPair>


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
    QList < QPair < QString, QPair<int, int> > > getForNotification(int day, int month);
    QString email(int id);
    ///
    //QSqlTableModel* getCurrentModel();
    /// получение самих текcтов для
    QString getTextFor(int idText);
    /// подпиши (получение списка имен текстов для комбобокса)
    QSqlQueryModel* listTextCongr();

    bool addRecordToData(QString lastName, QString firstName, QString patronimicName, QDate date, QString email);
    bool deleteRowFromData(QString lastName, QString firstName, QString patronimicName, int day, int month, int year);

    /// Добавить почту в таблицу почт пользователя
    void addRecordToPersonalEmail( QString email);



    QList<QString> getListOfEmails ();
};

#endif // DBMANAGER_H
