#ifndef GESTIONCOMMANDES_H_INCLUDED
#define GESTIONCOMMANDES_H_INCLUDED

int ExecuterCommande(char* commande, char* resultat);
int RetournerInformationConfig(char* parametreALire, char* valeurDefaut, char* resultat);
int RetournerInformationConfigIndex (char* parametreALire, char* index, char* valeurDefaut, char* resultat);
int ModifierInformationsConfig (char* parametreAMettreAJour, char* valeurAMettreAJour);
int RetournerEtatBouton (int identifiantBouton, char* resultat);
int retournerEtatBouton (int identifiantBouton);
int ChangerStatutBouton (int identifiantBouton, int statutBouton);
int IdentifiantBoutonPlosible (int identifiantBouton);
int StatutBoutonPlosible (int statutBouton);
int PurgerMinuteriesConfig();

#endif // GESTIONCOMMANDES_H_INCLUDED
