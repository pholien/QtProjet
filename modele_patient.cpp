#include "modele_patient.h"

Patient::Patient()
{

}

Patient::~Patient()
{

}

void Patient::setNom(QString n){this->nom=n;}
QString Patient::getNom(){return this->nom;}

void Patient::setPrenom(QString pn){this->prenom=pn;}
QString Patient::getPrenom(){return this->prenom;}

void Patient::setAdresse(QString adr){this->adresse=adr;}
QString Patient::getAdresse(){return this->adresse;}

void Patient::setVille(QString v){this->ville=v;}
QString Patient::getVille(){return this->ville;}

void Patient::setCommentaire(QString c){ this->commentaire=c;}
QString Patient::getCommentaire(){return this->commentaire;}

void Patient::setTelephone(QString tel){this->telephone=tel;}
QString Patient::getTelephone(){return this->telephone;}

void Patient::setCP(int c){this->cp=c;}
int Patient::getCP(){return this->cp;}

void Patient::setDateDebut(QDate d){this->datedebut=d;}
QDate Patient::getDateDebut(){return this->datedebut;}

void Patient::setDuree(int d){this->duree=d;}
int Patient::getDuree(){return this->duree;}

void Patient::setPriorite(int p){this->priorite=p;}
int Patient::getPriorite(){return this->priorite;}
