#ifndef CONTROLEUR_PATIENTS_H
#define CONTROLEUR_PATIENTS_H
#include "modele_patient.h"

bool AddPatient(Patient p);

bool ModifierPatient(Patient p,QString id);

bool DeletePatient(QString id);

Patient* SearchPatient(QString id);

#endif // CONTROLEUR_PATIENTS_H
