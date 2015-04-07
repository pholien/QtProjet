#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>
#include <QVector>

class Patient
{
private:
    QString nom;
    QString prenom;
    QString adresse;
    QString ville;
    QString commentaire;
    QString telephone;
    int cp;
    QDate datedebut;
    int duree;
    int priorite;


public:
    QVector<int> vIdRessource;

    Patient();
    ~Patient();
    void setNom(QString n);
    QString getNom();
    void setPrenom(QString pn);
    QString getPrenom();
    void setAdresse(QString adr);
    QString getAdresse();
    void setVille(QString v);
    QString getVille();
    void setCommentaire(QString c);
    QString getCommentaire();

    void setTelephone(QString tel);
    QString getTelephone();
    void setCP(int c);
    int getCP();
    void setDateDebut(QDate d);
    QDate getDateDebut();
    void setDuree(int n);
    int getDuree();
    void setPriorite(int p);
    int getPriorite();
};

#endif // PATIENT_H
