#include "controleur_ressource.h"
#include <QSqlQuery>
#include<QDebug>
#include <QDate>
#include <QSqlError>
#include <QVariant>

bool AddRessource(Ressource r)
{
    QSqlQuery query;
    QString sql;
    query.exec("select * from TRessource");
    query.last();
    int id=query.value(0).toInt();
    id=id+1;

    sql="insert into TRessource values("
            +QString::number(id)+","+"'"
            +r.getNom() +"' , '"
            +r.getPrenom() +"' , '"
            +QString::number(r.getType())+"')";
    bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Insertion de données dans TRessource impossible !\n";
        return false;
    }
    if(r.getType()==7)
    {
        query.exec("select * from TCompte");
        query.last();
        int id2=query.value(0).toInt();
        id2=id2+1;
        QString sql2="insert into TCompte values("
                +QString::number(id2)+","+QString::number(id)+","+"'"
                +r.getLogin()+"' , '"
                +r.getMdP() +"')";
        b_test=query.exec(sql2);
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TCompte impossible !\n";
            return false;
        }
    }
    return true;
}

bool ModifierRessource(Ressource r, QString id)
{
    QSqlQuery query;
    QString sql="update TRessource set Nom='"+r.getNom()
            +"', Prenom='"+r.getPrenom()
            +"', IdType='"+QString::number(r.getType())
            +"' where id="+id;
    bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Modifier de données dans TRessource impossible !\n";
        return false;
    }
    if(r.getType()==7)
    {
        QString sql2="update TCompte set Login='"+r.getLogin()+"',  MdP='"+r.getMdP()
                +"' where IdRessource='"+id+"'";
        b_test=query.exec(sql2);
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Modifier de données dans TCompte impossible !\n";
            return false;
        }
    }
    return true;
}

bool DeleteRessource(QString id)
{
    QSqlQuery query;
    bool boo;
    boo=query.exec("delete from TRessource where Id='"+id+"'");
    if(!boo)
    {
        qDebug() << query.lastError().text();
        qDebug() << "record in TRessource non delete !\n";
        return false;
    }
    boo=query.exec("delete from TCompte where IdRessource='"+id+"'");
    if(!boo)
    {
        qDebug() << query.lastError().text();
        qDebug() << "record in TCompte non delete !\n";
        return false;
    }
    boo=query.exec("delete from TConsult where IdRessource='"+id+"'");
    if(!boo)
    {
        qDebug() << query.lastError().text();
        qDebug() << "record in TConsult non delete !\n";
        return false;
    }
    return true;
}
