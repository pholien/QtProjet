#include "controleur_patient.h"
#include <QSqlQuery>
#include<QDebug>
#include <QDate>
#include <QSqlError>
#include <QVariant>


bool AddPatient(Patient p)
{
    QSqlQuery query;
    query.exec("select * from TPatient");
    query.last();
    int id=query.value(0).toInt()+1;
    QString sql="insert into TPatient values("
            +QString::number(id)+","+"'"
            +p.getNom()+"' , '"
            +p.getPrenom() +"' , '"
            +p.getAdresse() +"' , '"
            +p.getVille()+"' , '"
            +QString::number(p.getCP())+"' , '"
            +p.getCommentaire()+"' , '"
            +p.getTelephone()+"' , '"
            +p.getDateDebut().toString("yyyy-MM-dd")+"' , '"
            +QString::number(p.getDuree())+"' , '"
            +QString::number(p.getPriorite())+"')";
    bool b_test=query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Insertion de données dans TPatient impossible !\n";
        return false;
    }
    query.exec("select Id from TConsult");
    query.last();
    int idc=query.value(0).toInt()+1;
    for(int n=0; n<p.vIdRessource.size(); n++,idc++){
         b_test=query.exec("insert into TConsult values("
                           +QString::number(idc)+","
                           +QString::number(id)+","
                           +QString::number(p.vIdRessource.at(n))
                           +")");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TConsult impossible !\n";
            return false;
        }
    }
    return true;
}

bool ModifierPatient(Patient p,QString id)
{
    QSqlQuery query;
    QString sql="update TPatient set Nom='"+p.getNom()+"' , "
            +"Prenom='"+p.getPrenom() +"' , "
            +"Adresse='"+p.getAdresse() +"' , "
            +"Ville='"+p.getVille()+"' , "
            +"CP='"+QString::number(p.getCP())+"' , "
            +"Commentaire='"+p.getCommentaire()+"' , "
            +"Tel='"+p.getTelephone()+"' , "
            +"DateConsultation='"+p.getDateDebut().toString("yyyy-MM-dd")+"' , "
            +"DureeConsultation="+QString::number(p.getDuree())+" , "
            +"Priorite="+QString::number(p.getPriorite())
            +" where id="+id;
    bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Modifier de données dans TPatient impossible !\n";
        return false;
    }

    query.exec("delete from TConsult where IdPatient="+id);

    query.exec("select Id from TConsult");
    query.last();
    int idc=query.value(0).toInt()+1;
    for(int n=0; n<p.vIdRessource.size(); n++,idc++){
         b_test=query.exec("insert into TConsult values("
                           +QString::number(idc)+","
                           +id+","
                           +QString::number(p.vIdRessource.at(n))
                           +")");
        if(!b_test)
        {
            qDebug() << query.lastError().text();
            qDebug() << "Insertion de données dans TConsult impossible !\n";
            return false;
        }
    }
    return true;
}

bool DeletePatient(QString id)
{
    QSqlQuery query;
    bool boo;
    boo=query.exec("delete from TPatient where id='"+id+"'");
    if(!boo)
    {
        qDebug() << query.lastError().text();
        qDebug() << "record in TPatient non delete !\n";
        return false;
    }
    boo=query.exec("delete from TConsult where IdPatient='"+id+"'");
    if(!boo)
    {
        qDebug() << query.lastError().text();
        qDebug() << "record in TConsult non delete !\n";
        return false;
    }
    return true;
}

Patient *SearchPatient(QString id)
{
    if(id=="")
        return NULL;
    QSqlQuery query;
    QString sql="select * from TPatient where Id='"+id+"'";
    bool boo=query.exec(sql);
    if(!boo || query.size()==0)
        return NULL;
    query.first();
    Patient *p=new Patient();
    p->setNom(query.value(1).toString());
    p->setPrenom(query.value(2).toString());
    p->setAdresse(query.value(3).toString());
    p->setVille(query.value(4).toString());
    p->setCP(query.value(5).toInt());
    p->setCommentaire(query.value(6).toString());
    p->setTelephone(query.value(7).toString());
    p->setDateDebut(query.value(8).toDate());
    p->setDuree(query.value(9).toInt());
    p->setPriorite(query.value(10).toInt());

    query.exec("select IdRessource from TConsult where IdPatient="+id);
    while(query.next())
    {
        p->vIdRessource.push_back(query.value(0).toInt());
    }
    return p;
}
