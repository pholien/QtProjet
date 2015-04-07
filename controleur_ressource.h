#ifndef CONTROLEUR_RESSOURCE_H
#define CONTROLEUR_RESSOURCE_H
#include "modele_ressource.h"

bool AddRessource(Ressource r);

bool ModifierRessource(Ressource r, QString id);

bool DeleteRessource(QString id);



#endif // CONTROLEUR_RESSOURCE_H
