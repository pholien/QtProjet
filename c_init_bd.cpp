#include "c_init_bd.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

C_INIT_BD::C_INIT_BD()
{

}

C_INIT_BD::~C_INIT_BD()
{

}

bool C_INIT_BD::Creation_BD()
{
    bool b_test;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if(db.isValid())
    {
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("password");

        if(QFile::exists("base_tmp.sqli"))
            QFile::remove("base_tmp.sqli");

        db.setDatabaseName("base_tmp.sqli");
        db.open();

        QSqlQuery query(db);
        if(!db.isOpen())
        {
            qDebug() << db.lastError().text();
            qDebug() << "Erreur à louverture de la base !\n";
            return false;
        }

        b_test=query.exec("create table TCompte "
                          "(Id integer primary key, "
                          "IdRessource integer, "
                          "Login varchar(50), "
                          "MdP varchar(50))");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Table TCompte non crée !\n";
            return false;
        }

        b_test=query.exec("create table TConsult "
                          "(Id integer primary key, "
                          "IdPatient integer, "
                          "IdRessource integer)");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Table TConsult non crée !\n";
            return false;
        }

        b_test=query.exec("create table TPatient "
                          "(Id integer primary key, "
                          "Nom varchar(50), "
                          "Prenom varchar(50), "
                          "Adresse varchar(50), "
                          "Ville varchar(50), "
                          "CP integer, "
                          "Commentaire varchar(50), "
                          "Tel integer, "
                          "DateConsultation date, "
                          "DureeConsultation integer, "
                          "Priorite integer)");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Table TPatient non crée !\n";
            return false;
        }

        b_test=query.exec("create table TRessource "
                          "(Id integer primary key, "
                          "Nom varchar(50), "
                          "Prenom varchar(50), "
                          "IdType integer)");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Table TRessource non crée !\n";
            return false;
        }

        b_test=query.exec("create table TType "
                          "(Id integer primary key, "
                          "Label varchar(50))");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Table TType non crée !\n";
            return false;
        }

        b_test=query.exec("INSERT INTO TCompte (Id, IdRessource, Login, MdP) VALUES "
                          "(1, 1, 'Admin', 'Password')");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TCompte impossible !\n";
            return false;
        }

        b_test=query.exec("INSERT INTO TConsult "
                          "SELECT '1' AS 'Id', '1' AS 'IdPatient', '11' AS 'IdRessource'"
                                  "UNION SELECT 2, 1, 3 "
                                  "UNION SELECT 3, 1, 5 "
                                  "UNION SELECT 4, 2, 6 "
                                  "UNION SELECT 5, 3, 2 "
                                  "UNION SELECT 6, 3, 4 "
                                  "UNION SELECT 7, 4, 12 "
                                  "UNION SELECT 8, 4, 8 "
                                  "UNION SELECT 9, 5, 9 "
                                  "UNION SELECT 10, 6, 8");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TConsult impossible !\n";
            return false;
        }


        b_test=query.exec("INSERT INTO TPatient "
                          "SELECT '1' AS 'Id', 'Ricardo' AS 'Nom', 'Jacques' AS 'Prenom', '3 rue des justices' AS 'Adresse', 'Tours' AS 'Ville', '37200' AS 'CP', 'Dépressif' AS 'Commentaire', '247558963' AS 'Commentaire', '2013-06-01' AS 'DateConsultation', '90' AS 'DureeConsultation', '2' AS 'Priorite'"
                                  "UNION SELECT 2, 'Pirouette', 'Stéphanie', '15 rue des dames', 'Chanceaux', 37390, 'Rien à dire.', 247542942, '2013-06-01', 50, 2 "
                                  "UNION SELECT 3, 'Puisser', 'Albert', '15 rue des chevaux', 'Verigné', 37250, 'Asthmatique.', 247642892, '2013-06-01', 45, 3 "
                                  "UNION SELECT 4, 'Tujais', 'Téo', '15 rue de l''arbre', 'Monts', 37450, '', 247845889, '2013-06-01', 20, 4 "
                                  "UNION SELECT 5, 'Kistran', 'Flavien', '89 impasse des rangs', 'Mettray', 37620, 'En forme.', 247895623, '2013-06-01', 80, 1 "
                                  "UNION SELECT 6, 'Qing', 'Xue', '14 rue Jean Jaures', 'Tours', 37200, 'Aucun.', 247555588, '2013-06-01', 60, 3 ");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TPatient impossible !\n";
            return false;
        }

        b_test=query.exec("INSERT INTO TRessource "
                          "SELECT '1' AS 'Id', 'Admin' AS 'Nom', 'Admin' AS 'Prenom', '7' AS 'IdType'"
                                  "UNION SELECT 2, 'Dubois', 'Jean', 1 "
                                  "UNION SELECT 3, 'De La Roche', 'Julie', 1 "
                                  "UNION SELECT 4, 'Ducroix', 'Lisa', 2 "
                                  "UNION SELECT 5, 'Boulanger', 'Stéphane', 3 "
                                  "UNION SELECT 6, 'Bijet', 'Paul', 3 "
                                  "UNION SELECT 7, 'durant', 'Mélanie', 4 "
                                  "UNION SELECT 8, 'Tortue', 'Adeline', 4 "
                                  "UNION SELECT 9, 'guillet', 'Sonia', 4 "
                                  "UNION SELECT 10, 'Boulot', 'Marie', 4 "
                                  "UNION SELECT 11, 'Titan', 'Geoffrey', 5 "
                                  "UNION SELECT 12, 'Dupont', 'Christophe', 6");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TRessource impossible !\n";
            return false;
        }

        b_test=query.exec("INSERT INTO TType "
                          "SELECT '1' AS 'Id', 'Médecin A' AS 'Label'"
                                  "UNION SELECT 2, 'Médecin B' "
                                  "UNION SELECT 3, 'Radiologue' "
                                  "UNION SELECT 4, 'Infirmière' "
                                  "UNION SELECT 5, 'Kinésithérapeute' "
                                  "UNION SELECT 6, 'Psychologue' "
                                  "UNION SELECT 7, 'Informaticien'");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TType impossible !\n";
            return false;
        }

        db.close();
        db.removeDatabase("QSQLITE");
        return true;

    }
    else
    {
        qDebug() << db.lastError().text();
        qDebug() << "Erreur à création de la base !\n";
        return false;
    }
/*
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("tp");
    db.setDatabaseName("customdb");
    db.setUserName("tp");
    db.setPassword("tp");
    db.setDatabaseName("PATIENT.db");     //创建数据库
    if(!db.open())
    {
        qDebug()<< "database is error";
        //return;
    }
    else
    {
        qDebug()<<"database is ok";
        //return;
    }

    QSqlQuery query(db);
    //------------------------------------------------------创建一个表------------------------------------------------------
    bool bsuccess = query.exec("create table TPatient ("
                               "IdPatient int primary key, Nom varchar(20), Prenom varchar(20), Adress varchar(100), "
                               "Ville varchar(20), CP varchar(20), Commentaire varchar(200), Tel int, "
                               "DateConsultation date, DureeConsultation date, Priorite int )");
    if(!bsuccess)
    {
        qDebug()<< "create table TPatient is error";
    }

    //------------------------------------------------------创建一个表------------------------------------------------------
    bsuccess = query.exec("create table TType (IdType int primary key, Label varchar(40)");
    if(!bsuccess)
    {
        qDebug()<< "create table TPatient is error";
    }

    //------------------------------------------------------创建一个表------------------------------------------------------
    bsuccess = query.exec("create table TRessource ("
                          "IdRessource int primary key, Nom varchar(20), Prenom varchar(20), IdType int,"
                          "foreign key(IdType) references TType(IdType))");
    if(!bsuccess)
    {
        qDebug()<< "create table TRessource is error";
    }

    //------------------------------------------------------创建一个表------------------------------------------------------
    bsuccess = query.exec("create table TConsult ("
                          "IdConsult int primary key,IdPatient int, IdRessource int, "
                          "foreign key(IdPatient)references TPatient(IdPatient), "
                          "foreign key(IdRessource)references TRessource(IdRessource))");
    if(!bsuccess)
    {
        qDebug()<< "create table TConsult is error";
    }

    //------------------------------------------------------创建一个表------------------------------------------------------
    bsuccess = query.exec("create table TCompte ("
                          "IdCompte int primary key, IdRessource int, Login varchar(20), MdP varchar(20),"
                          "foreign key(IdRessource)references TRessource(IdRessource))");
    if(!bsuccess)
    {
        qDebug()<< "create table TCompte is error";
    }else{
        qDebug()<<"table is created";
    }


//    query.exec("insert into person values(101, 'Danny', 'Young')");
//    query.exec("insert into person values(102, 'Christine', 'Holand')");
//    query.exec("insert into person values(103, 'Lars', 'Gordon')");
//    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
//    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");
//    query.exec("INSERT INTO persons VALUES ('xue','chao','langfang')");*/
}


