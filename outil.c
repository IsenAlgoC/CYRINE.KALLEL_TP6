#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom :  KALLEL                       Prénom :   CYRINE                            */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		idx = rep->nb_elts;
		modif = true; // Si on a modification,
		rep->tab[idx] = enr; // on enregistre le contact dans le tableau
		rep->nb_elts++; //On augmente le nombre de valeur
		return (OK);
		

	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;

	if (rep->nb_elts == 0)
	{
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0)
		{
			rep->nb_elts = rep->nb_elts + 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}
	}
	else if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) 
	{
		rep->nb_elts++;						// Element ahjoutée a queue de la liste
		modif = true;
		rep->est_trie = false;
		return(OK);
	}
		


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		if (indice <= rep->nb_elts || indice > 0)
		{

			for (int i = indice; i <rep->nb_elts; i++)
			{

				rep->tab[i] = rep->tab[i + 1];
			}
			rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
			modif = true;
		}
	}

		

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) 
	{
		int ret=DeleteLinkedListElem(rep->liste, elem);
		if (ret == 1) 
		{
			rep->nb_elts--;
			modif = true;
		}
		return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%s,%s                  %s", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// On realise la meme chose que fonction affichage_enreg, mais avec présentation alignées des infos

	int alphanom = strlen(enr.nom);
	int alphaprenom = strlen(enr.prenom);
	int numtel = strlen(enr.tel);

	printf("\n|%s", enr.nom);
	if (alphanom < MAX_NOM) 
	{
		for (int i = alphanom; i <= MAX_NOM; i++)
		{
			printf(" ");
		}
	}

	printf("|%s", enr.prenom);
	if (alphaprenom < MAX_NOM) 
	{
		for (int j = alphaprenom; j <= MAX_NOM; j++) 
		{
			printf(" ");
		}
	}

	printf("|%s", enr.tel);
	if (numtel < MAX_TEL) 
	{
		for (int j = alphaprenom; j <= MAX_TEL; j++) 
		{
			printf(" ");
		}
	}



} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	
	_strupr_s (enr1.nom, MAX_NOM); //POUR METTRE LE NOM DE L'ENRG1 EN MAJUSCULE
	_strupr_s (enr1.prenom, MAX_NOM); //POUR METTRE LE PRENOM DE L'ENRG1 EN MAJUSCULE
	_strupr_s(enr2.nom, MAX_NOM); //POUR METTRE LE NOM DE L'ENRG2 EN MAJUSCULE
	_strupr_s(enr2.prenom, MAX_NOM); //POUR METTRE LE PRENOM DE L'ENRG2 EN MAJUSCULE


	int test_nom = strcmp(enr1.nom , enr2.nom); //compare les 2 NOM 
	int test_prenom = strcmp(enr1.prenom, enr2.prenom); //compare les 2 NOM 

	if (test_nom < 0) //nom de enr1 est avant nom de enr2 
	{
		return (true);
	}
	if (test_nom > 0) //nom de enr1 est apres nom de enr2 
	{
		return (false);
	}
	 
	if (test_nom == 0 && test_prenom < 0) //si les noms sont les memes mais que prenom 1 avant prenom 2
	{
		return(true); 
	}     
	if (test_nom == 0 && test_prenom > 0) //si les noms sont les memes mais que prenom 1 apres prenom 2
	{ 
		return(false); 
	}
	else 
	{
		return (true); //Si les noms et prénoms sont exactement les mêmes alors on dit qu'ils sont triés.     
	}

	

}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	
	for (int i = 0; i < rep->nb_elts; i++) //on utilise un tri a bulle grace a un double for 
	{
		for (int j = 0; j < rep->nb_elts; j++)
		{
			if (est_sup(rep->tab[i], rep->tab[j]) == false) //Appel a la fonction est_sup, si les elements compares au dessus ne sont pas dans ordre alphebatique
			{
				Enregistrement tmp = rep->tab[i]; //Alors on fait une permutation
				rep->tab[i] = rep->tab[j];
				rep->tab[j] = tmp;

			}
		}
	}
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


	ind_fin = rep->nb_elts - 1; // indice de fin à ne pas dépasser
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	compact(tmp_nom); // nettoyage du numéro


#ifdef IMPL_TAB
	while ((i <= ind_fin) && (!trouve))
	{
		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);
		compact(tmp_nom2);
		if (strcmp(tmp_nom, tmp_nom2) == 0)
		{
			trouve = true;
		}
		else
		{
			// si pas trouvé, on passe au suivant
			i++;
		}						
	}
#else
#ifdef IMPL_LIST 
	
	SingleLinkedListElem* currentElement = GetElementAt(rep->liste, i);
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);    // Le nom va d'abord etre copié dans "tmp_nom", Puis passer en majuscule.
	while ((currentElement != NULL) && (!trouve))
	{
		strncpy_s(tmp_nom2, _countof(tmp_nom2), currentElement->pers.nom, _TRUNCATE);   // IDEM QUE LIGNE AVANT: NOM COPI2 DANS tmp2 PUIS PASSER EN MAJ
		if (_strcmpi(tmp_nom, tmp_nom2) == 0) //CONDITION A SATISFAIre qui permettra de comparer pouvoir comparer la chaine 
		{
			trouve = true; //SI On a la meme chaine de caratere renvoi de true 
		}
		else //sinon on passe a la suivante	
		{
			currentElement = currentElement->next;
			i++;

			_strupr_s(tmp_nom, strlen(tmp_nom) + 1);
		}
	}
	
							
	
#endif
#endif
	
	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i]<48 || s[i]>57)
		{
			for (int j = i; j < strlen(s); j++)
			{
				s[j - 1]  = s[i];
			}
		}

	}

	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	errno_t err;
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) {   // On vérifie que le fichier est ouvert.
		err = ERROR;
		return err;
	}
	for (int i = 0; i < rep->nb_elts; i++) 
	{							 // Pour tous les éléments du tableau...
		fprintf(fic_rep, "%s%c", rep->tab[i].nom, SEPARATEUR);           // On écrit dans le fichier les info du contact !
		fprintf(fic_rep, "%s%c", rep->tab[i].prenom, SEPARATEUR);		 // (nom, prenom, telephone!)
		fprintf(fic_rep, "%s\n", rep->tab[i].tel);

	}
	if (feof(fic_rep)) 
	{
		fclose(fic_rep);
	}
	
#else
#ifdef IMPL_LIST
	
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) //conditions pour verifier que le fichier est bien ouvert
	{
		return (ERROR);
	}
	for (int i = 0; i < rep->nb_elts; i++)  //EN PARCOURANT LES ELEMENTS DU TABLEAUX
	{
		/// On écrit dans le fichier les info du contact
		fputs(GetElementAt(rep->liste, i)->pers.nom, fic_rep);
		fputs("		", fic_rep);
		fputs(GetElementAt(rep->liste, i)->pers.prenom, fic_rep);
		fputs("		", fic_rep);
		fputs(GetElementAt(rep->liste, i)->pers.tel, fic_rep);
		fputs("\n", fic_rep);
	}


#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				SingleLinkedListElem temp;
				if (lire_champ_suivant(buffer, &idx, temp.pers.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							// on saute le separateur 
					if (lire_champ_suivant(buffer, &idx, temp.pers.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, temp.pers.tel, MAX_TEL, SEPARATEUR) == OK)
						{
							InsertElementAt(rep->liste, num_rec, temp.pers);
							num_rec++;		//ELEMENT CORRECT =>BA COMPTER
						}
					}
				}
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */
