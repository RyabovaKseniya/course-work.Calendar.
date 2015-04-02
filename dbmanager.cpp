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

bool DBManager::deleteRowFromData(QString lastName, QString firstName, QString patronimicName, int day, int month, int year){
    db.open();
    QSqlQuery query;
    query.prepare("DELETE FROM Data WHERE lastName = :lastName and firstName = :firstName and patronimicName = :patronimicName and birthDay = :birthDay  and birthMonth = :birthMonth and birthYear = :birthYear ");
    query.bindValue(":lastName",lastName);
    query.bindValue(":firstName", firstName);
    query.bindValue(":patronimicName",patronimicName);
    query.bindValue(":birthDay", day);
    query.bindValue(":birthMonth",month);
    query.bindValue(":birthYear", year);
    bool execBool = query.exec();
    db.close();
    return execBool;
}


bool DBManager::addRecordToData(QString lastName, QString firstName, QString patronimicName, QDate date, QString email)
{

    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Data ( lastName, firstName, patronimicName, email, birthDay, birthMonth, BirthYear)"
                  "VALUES(?, ?, ?, ?, ?, ?, ? )");
    query.addBindValue(lastName);
    query.addBindValue(firstName);
    query.addBindValue(patronimicName);
    query.addBindValue(email);
    query.addBindValue(date.day());
    query.addBindValue(date.month());
    query.addBindValue(date.year());
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


QSqlQueryModel* DBManager::listTextCongr()
{
    db.open();
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT congratulationFor FROM CongratulationsText ");
    db.close();
    return model;
}


 QList < QPair < QString, QPair<int, int> > > DBManager::getForNotification(int day, int month)
{
    db.open();
    QSqlQuery query;
    query.prepare("SELECT lastName, firstName, patronimicName, birthYear, idData FROM Data WHERE birthMonth = " + QString::number(month) + " and birthDay = " + QString::number(day));
    QList < QPair < QString, QPair<int, int> > > list;

    if (!query.exec())
        return list;

    while(query.next()){
        QString name = query.value(0).toString() + " " + query.value(1).toString() + " " + query.value(2).toString();
        QPair <int, int> pairYearAndId;
        pairYearAndId.first = query.value(3).toInt();
        pairYearAndId.second = query.value(4).toInt();
        QPair <QString, QPair <int, int> > pairNameAndPair;
        pairNameAndPair.first = name;
        pairNameAndPair.second = pairYearAndId;
        list.append(pairNameAndPair);
    }

    db.close();
    return list;
}

 QString DBManager::email(int id)
 {
     std:: cout << "getEmailFromDB "<< std::endl;
     std:: cout << "id "<< id << std::endl;
     db.open();
     QSqlQuery query;
     query.prepare("SELECT email FROM Data WHERE idData = :id");
     query.bindValue(":id", id);

     if (query.exec())
         std:: cout << "succes "<< std::endl;
     if (query.next()){
         return query.value(0).toString();
     }
     std:: cout << "bad request "<< std::endl;
     return "";
 }
