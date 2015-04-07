#include "modele_ressource.h"

Ressource::Ressource()
{

}

Ressource::~Ressource()
{

}

void Ressource::setNom(QString n){this->nom=n;}
QString Ressource::getNom(){return this->nom;}

void Ressource::setPrenom(QString pn){this->prenom=pn;}
QString Ressource::getPrenom(){return this->prenom;}

void Ressource::setLogin(QString l){this->login=l;}
QString Ressource::getLogin(){return this->login;}

void Ressource::setMdP(QString m){this->mdp=m;}
QString Ressource::getMdP(){return this->mdp;}

void Ressource::setType(int t){this->type=t;}
int Ressource::getType(){return this->type;}
