#include "controleur_login.h"
#include <QSqlQuery>
#include <QVariant>

bool isCorrectCompte(QString login,QString mdp)
{
    QSqlQuery query;
    query.exec("select MdP from TCompte where Login='"+login+"'");
    while(query.next())
    {
        if(mdp.compare(query.value(0).toString())==0){
            return true;
        }
    }
    return false;
}
