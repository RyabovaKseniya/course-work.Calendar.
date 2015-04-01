#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>
#include <iostream>

DBManager* DBManager::instance = NULL;

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Calendar/DB.db");
}

DBManager* DBManager::getInstance()
{
    if (instance == NULL)
        instance = new DBManager();
    return instance;
}

QSqlQueryModel* DBManager::getModel(int mode)
{
    db.open();

    QSqlQueryModel* model = new QSqlQueryModel();

    switch (mode)
    {
    case 0:
    {
        QDate data = QDate::currentDate();
        model->setQuery("SELECT lastName, firstName, patronimicName, birthDay, birthMonth, birthYear  FROM Data WHERE birthMonth = " + QString::number(data.month()));
        break;
    }
    case 1:
    {
        model->setQuery("SELECT lastName, firstName, patronimicName, birthDay, birthMonth, birthYear FROM Data ");
        break;
    }
    default:
    {
        break;
    }
    }

    db.close();

    return model;
}

QSqlQueryModel* DBManager::getDate(int day, int month)
{
    db.open();
     std::cout << "getDate" << std::endl;
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT lastName, firstName, patronimicName, birthDay, birthMonth, birthYear  FROM Data WHERE birthMonth = " + QString::number(month) + " and birthDay = " + QString::number(day));

    db.close();

    return model;
}

//QSqlTableModel* DBManager::getCurrentModel()
//{
//    db.open();
//    QSqlTableModel* model;

//    model = new QSqlTableModel(NULL,db);
//    model->setTable("Data");
//    model->setFilter(QString("birthMonth=%1").arg(month));
//    model->select();

//    db.close();
//    return model;
//}

bool DBManager::addRecordToData(QString lastName, QString firstName, QString patronimicName, QString email, QDate date, QTime hoursReminder, QDate userReminderDate, QTime userReminderTime)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Data ( lastName, firstName, patronimicName, email, birthDay, birthMonth, BirthYear, timeSend, userReminderDate, userReminderTime)"
                  "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");
    query.addBindValue(lastName);
    query.addBindValue(firstName);
    query.addBindValue(patronimicName);
    query.addBindValue(email);
    query.addBindValue(date.day());
    query.addBindValue(date.month());
    query.addBindValue(date.year());
    query.addBindValue(hoursReminder);
    query.addBindValue(userReminderDate);
    query.addBindValue(userReminderTime);
    bool execBool = query.exec();
    db.close();
    return execBool;
}

void DBManager::addRecordToPersonalEmail(QString email)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO PersonalEmail (email) VALUES(?)");
    query.addBindValue(email);
    if (query.exec())
        std::cout << "YES" << std::endl;
    db.close();
}

//void DBManager::addRecordToPersonalEmail( QString email)
//{
//    std::cout << "JHWEWJHEGW" << std::endl;
//    db.open();
//    QSqlQueryModel* model = new QSqlQueryModel();
//    const QString query = QString("INSERT INTO PersonalEmail (email) VALUES ('" + email +"')");
//    model->setQuery(query);
//    QMessageBox::information(NULL, "title", QString(" "+ query));

//    db.close();

QList<QString> DBManager:: getListOfEmails (){
    db.open();
    QList<QString> list;
    QSqlQuery query;
    query.prepare("SELECT email FROM PersonalEmail");
    query.exec();
    while(query.next())
    {
       list.append(query.value("email").toString());
    }

    db.close();
    return list;
}



QString DBManager::getTextFor(int idText)
{
    db.open();
    QSqlQuery query;
    query.prepare("SELECT сongratulationsText FROM CongratulationsText "
                  "WHERE idCongratulationsText = :id ");
    query.bindValue(":id", idText);
    query.exec();
    std::cout << "Records: " << query.size() << std::endl;
    query.first();
    QString q = query.value(0).toString();
    db.close();
    return q;
}
///+
QSqlQueryModel* DBManager::listTextCongr()
{
    db.open();

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT idCongratulationsText FROM CongratulationsText ");

    db.close();

    return model;
}
