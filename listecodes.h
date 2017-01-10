#ifndef LISTECODES_H_INCLUDED
#define LISTECODES_H_INCLUDED

#define MSG_OK 200                      //Requête traitée avec succès
#define MSG_Created 201                 //Requête traitée avec succès avec création d’un document
#define MSG_Accepted 202    		    //Requête traitée mais sans garantie de résultat
#define MSG_NoContent 204	            //Requête traitée avec succès mais pas d’information à renvoyer
#define MSG_ResetContent 205            //Requête traitée avec succès, la page courante peut être effacée
#define MSG_PartialContent 206		    //Une partie seulement de la ressource a été transmise
#define MSG_MultiStatus 207             //Réponse multiple.
#define MSG_BadRequest 400		        //La syntaxe de la requête est erronée
#define MSG_Unauthorized 401		    //Une authentification est nécessaire pour accéder à la ressource
#define MSG_PaymentRequired 402		    //Paiement requis pour accéder à la ressource
#define MSG_Forbidden 403		        //Le serveur a compris la requête, mais refuse de l'exécuter. Contrairement à l'erreur 401, s'authentifier ne fera aucune différence. Sur les serveurs où l'authentification est requise, cela signifie généralement que l'authentification a été acceptée mais que les droits d'accès ne permettent pas au client d'accéder à la ressource
#define MSG_NotFound 404		        //Ressource non trouvée
#define MSG_MethodNotAllowed 405		//Méthode de requête non autorisée
#define MSG_NotAcceptable 406		    //La ressource demandée n'est pas disponible dans un format qui respecterait les en-têtes "Accept" de la requête.
#define MSG_TimeOutServer 408                 //Temps d’attente d’une réponse du serveur écoulé
#define MSG_Conflict 409		        //La requête ne peut être traitée en l’état actuel
#define MSG_Gone 410    		        //La ressource est indisponible et aucune adresse de redirection n’est connue
#define MSG_LengthRequired 411		    //La longueur de la requête n’a pas été précisée
#define MSG_PreconditionFailed 412		//Préconditions envoyées par la requête non vérifiées
#define MSG_TooLarge 413                //Traitement abandonné dû à une requête trop importante
#define MSG_TooLong 414                 //Trop longue
#define MSG_UnsupportedMediaType 415    //Format de requête non supporté pour une méthode et une ressource données
#define MSG_RangeUnsatisfiable 416	    //Champs d’en-tête de requête « range » incorrect.
#define MSG_ExpectationFailed 417		//Comportement attendu et défini dans l’en-tête de la requête insatisfaisable
#define MSG_BadMapping 421              //La requête a été envoyée à un serveur qui n'est pas capable de produire une réponse (par exemple, car une connexion a été réutilisée)
#define MSG_UnprocessableEntity 422		//L’entité fournie avec la requête est incompréhensible ou incomplète.
#define MSG_Locked 423                  //L’opération ne peut avoir lieu car la ressource est verrouillée.
#define MSG_MethodFailure 424		    //Une méthode de la transaction a échoué.
#define MSG_UpgradeRequired 426	        //Le client devrait changer de protocole, par exemple au profit de TLS/1.0
#define MSG_PreconditionRequired 428	//La requête doit être conditionnelle
#define MSG_TooManyReauests 429	        //Le client a émis trop de requêtes dans un délai donné
#define MSG_FieldsTooLarge 431          //Les donnees émises dépassent la taille maximale admise par le serveur
#define MSG_ConnctionClosed 499         //Le client a fermé la connexion avant de recevoir la réponse. Se produit quand le traitement est trop long côté serveur.
#define MSG_InternalServerError 500     //Erreur interne du serveur
#define MSG_NotImplemented 501          //Fonctionnalité réclamée non supportée par le serveur
#define MSG_BadGateway 502              //Mauvaise réponse envoyée à un serveur intermédiaire par un autre serveur.
#define MSG_UnavailableService 503      //Service temporairement indisponible ou en maintenance
#define MSG_TimeOut 504                 //Temps d’attente d’une réponse d’un serveur à un serveur intermédiaire écoulé
#define MSG_VersionNotSpported 505      //Version non gérée par le serveur
#define MSG_NegociateError 506          //Erreur de négociation transparent content negociation
#define MSG_InsufficientStorage 507     //Espace insuffisant pour modifier les propriétés ou construire la collection
#define MSG_LoopDetected 508            //Boucle dans une mise en relation de ressources (RFC 5842)
#define MSG_BandwidthLimit 509          //Utilisé par de nombreux serveurs pour indiquer un dépassement de quota.
#define MSG_NotExtended 510             //la requête ne respecte pas la politique d'accès aux ressources etendues.
#define MSG_AuthenticationRequired 511  // Le client doit s'authentifier pour accéder au réseau. Utilisé par les portails captifs pour rediriger les clients vers la page d'authentification.
#define MSG_Unknow 520                  //Le serveur renvoie une erreur inconnue

#endif // LISTECODES_H_INCLUDED
