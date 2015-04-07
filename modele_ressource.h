#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QString>

class Ressource
{
private:
    QString nom;
    QString prenom;
    QString login;
    QString mdp;
    int type;

public:
    void setNom(QString n);
    QString getNom();
    void setPrenom(QString pn);
    QString getPrenom();
    void setLogin(QString l);
    QString getLogin();
    void setMdP(QString m);
    QString getMdP();
    void setType(int t);
    int getType();
    Ressource();
    ~Ressource();
};

#endif // RESSOURCE_H
