#ifndef GESTIONCOMMANDES_H_INCLUDED
#define GESTIONCOMMANDES_H_INCLUDED

int ExecuterCommande(char* commande, char* resultat);
int RetournerInformationConfig(char* parametreALire, char* valeurDefaut, char* resultat);
int RetournerInformationConfigIndex (char* parametreALire, char* commande, char* valeurDefaut, char* resultat);
int ModifierInformationsConfig (char* parametreAMettreAJour, char* valeurAMettreAJour);

#endif // GESTIONCOMMANDES_H_INCLUDED
