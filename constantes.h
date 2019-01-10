#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define BUFLEN 512  //Max length of buffer
#define MAXBUF 1024 // Taille maximum dans le BUFFER
// Exemple ligne : {Paramètre}{DELIM}{Information = {Valeur1}{SEPARINFO}{Valeur2.1}{SEPARVALEUR}{Valeur2.2}}...
#define DELIM "=" // Delimiteur de parametre / valeur
#define SEPARINFO " " // Séparateur d'information
#define SEPARVALEUR "|" // Séprateur de valeur dans l'info
#define MAXARG 15 // Nombre maximum d'argument pour une commande

#define COMMANDE_NOMSERVEUR "TonNom" // command pour recuperer le nom du serveur
#define COMMANDE_RENOMMERSERVEUR "RenommerTonNom" // commande pour changer le nom du serveur
#define COMMANDE_IMAGESERVEUR "TonImage" // commande pour recuper l image representant le serveur
#define COMMANDE_CHANGERIMAGESERVEUR "ChangeTonImage" // commande pour changer l'image du serveur
#define COMMANDE_NOMBREINTERRUPTEUR "CombienIlYEnA" // commande pour recuperer le nombre de prise connecte
#define COMMANDE_CHANGERNOMBREINTERRUPTEUR "ChangeLeNombre" // commande pour modifier le nombre de prises connectées
#define COMMANDE_NOMBOUTON "NomBouton" // prefix de commande pour gerer une prise
#define COMMANDE_RENOMMERNOMBOUTON "RenommerNomBouton" //prefix de commande pour renommer un bouton
#define COMMANDE_IMAGEBOUTON "ImageBouton" // prefix de commande pour gerer l image d une prise
#define COMMANDE_CHANGERIMAGEBOUTON "ChangeImageBouton" // prefix pour changer l'image d'une prise
#define COMMANDE_STATUTBOUTON "EtatBouton" // Commande pour retourner l'etat d'une prise
#define COMMANDE_CHANGESTATUTBOUTON "ChangeEtatBouton" // Commande pour changer l'état d'un bouton
#define COMMANDE_SAUVEGARDERMINUTERIE "SauvegarderMinuterie" // Commande enregistrer les informations d'une minuterie : {index} {seconde} {minutes} {heure} {jour} {etat} {bouton}
#define COMMANDE_PURGERMINUTERIE "PurgerMinuteries" // Commande pour effacer toutes les informations des minuteries
#define COMMANDE_NOMBREMINUTERIE "CombienDeMinuteries" // Commande pour connaitre le nombre de minuteries
#define COMMANDE_DETAILMINUTERIE "DetailMinuterie" // Commande pour récuperer le détail d'une minuterie
#define COMMANDE_AIDE "Aide" // Commande pour afficher toutes les commandes possibles

#define CONFIG_NOMFICHIER "switchmanager.config" // nom du fichier de config
#define LOG_NOMFICHIER "switchmanager" // nom du fichier de config
#define FICHIERTEMPORAIRE "config.tmp" // nom du fichier temporaire
#define CONFIG_ALLUME 1 // etat quand prise allume
#define CONFIG_ETEINT 0 // etat quand prise eteinte
#define CONFIG_ACTIVER "Oui" // etat d un service active
#define CONFIG_DESACTIVER "Non" //etat d un service inactif
#define CONFIG_LOCALPORTSERVEUR "27601" // port de connexion du client UDP

#define PARAMETRE_NIVEAULOG "NiveauLog" // Niveau de Log
#define INITIAL_NIVEAULOG "2" // Niveau par defaut : ALERT
#define PARAMETRE_PORTSERVEUR "Port" // port de connexion au serveur UDP
#define INITIAL_PORTSERVEUR "27600" // port de connexion par defaut au serveur UDP
#define PARAMETRE_NOMSERVEUR "NomServeur" // nom du serveur udp
#define INITIAL_NOMSERVEUR "Interrupteur" // nom par defaut du serveur
#define PARAMETRE_IMAGESERVEUR "ImageServeur" // Image representant le serveur
#define INITIAL_IMAGESERVEUR "ImageServer.png" // Image par defaut representant le serveur
#define PARAMETRE_NOMBOUTON "NomBouton_" // nom du paramtre qui reference le nom de la prise
#define INITIAL_NOMBOUTON "Bouton" // nom par defaut d une prise
#define PARAMETRE_NOMBREINTERRUPTEUR "NombreBouton" // Nombre de prise connecte au serveur
#define INITIAL_NOMBREINTERRUPTEUR "1" // nombre de prise par defaut connecte au serveur
#define PARAMETRE_IMAGEBOUTON "ImageBouton_" // nom du parametre qui reference l image de la prise
#define INITIAL_IMAGEBOUTON "Light-BulbLeaf-icon.png" // image par defaut d une prise
#define PARAMETRE_MINUTERIEACTIVE "MinuterieActive" // nom du parametre pour la minuterie
#define INITIAL_MINUTERIEACTIVE CONFIG_DESACTIVER // valeur par defaut du parametre minuterie
#define PARAMETRE_ETATDEFAUT "EtatDefaut" // nom du parametre d etat d initialisation d une prise au demarrage
#define INITIAL_ETATDEFAUT "0" // etat par defaut d une prise au demarrage
#define PARAMETRE_MINUTERIE "Minuterie" // Information sur une minuterie
#define INITIAL_MINUTERIE "0" // Valeur par defaut d'une minuterie
#endif // CONSTANTES_H_INCLUDED
