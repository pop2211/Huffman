#include <stdlib.h>
#include <stdio.h>


struct Occurence
{
	char c;
	int occ;
	struct Occurence * succ;
};
typedef struct Occurence * Occ;


/* Prototypes des fonctions */
void compte_carac_fichier(char* nom,Occ *liste);
void verif_present (char c, Occ *l);
void incrementEtTrie(Occ *liste);
void ajoutchar(Occ *maliste,char car);
void afficher(Occ p);


void ajoutchar(Occ *maliste,char car)//ajoute le caractere à la liste avec une occurence à 1
{
	Occ tmp;
	tmp = (Occ)malloc(sizeof(struct Occurence));
	tmp->c = car;
	tmp->occ = 1;
	
	if(*maliste == NULL)//si la liste est vide
	{
		tmp->succ = NULL;
		*maliste=tmp;
	}
	else//si elle n'est pas vide
	{
		tmp->succ = (*maliste);
		*maliste=tmp;
	}
	
}


void incrementEtTrie(Occ *liste)
{
	(*liste)->occ++;//incrementation
	
	Occ tmp=(*liste);
	int tmpOcc;
	char tmpC;
	
	//il faut retrier les listes
	
	while((tmp->succ != NULL) && ((*liste)->occ > tmp->succ->occ))
	{
		tmp=tmp->succ;//on cherche l'element à partir du quel l'occurence est plus élevé 
	}
	tmpOcc=tmp->occ;
	tmpC=tmp->c;
	
	tmp->occ=(*liste)->occ;			//on utilise des variables tanpons pour interchanger les variables des listes.
	tmp->c=(*liste)->c;
	
	(*liste)->occ=tmpOcc;
	(*liste)->c=tmpC;
}


void verif_present (char c, Occ *l)//fonction qui verifie si le char est present ou non dans la liste et effectue l'action nécessaire.
{
	Occ tmp = *l;
	while (tmp != NULL && tmp->c != c)
	{
		tmp = tmp->succ;
	}
	
	if (tmp == NULL)//si le caractere n'existe pas dans la liste, on l'ajoute
	{
		ajoutchar(&(*l),c);
	}
	else// le caractere existe, il faut l'incrementer
	{
		incrementEtTrie(&tmp);
	}
}


void compte_carac_fichier(char* nom,Occ *liste) //fonction permettant de parcourir les caracteres des fichiers et les envoient au traitement
{
	FILE* fichier = NULL;
	char caractereActuel = ' ';
	fichier = fopen(nom, "r");

	if (fichier != NULL)
	{	// Boucle de lecture des caractères un à un
		while (caractereActuel != EOF)  // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
		{
			caractereActuel = fgetc(fichier);
			
			if(caractereActuel != EOF)// On lit les caractères sauf le EOF
				verif_present(caractereActuel,&(*liste));
		}
		fclose(fichier);
	}
}


void afficher(Occ p) //fonction pour vérifier la liste (DEBUGGAGE)
{
	int i=1;
	while(p!=NULL)
		{
			if(p->c != '\n')
				printf("%d : |%c| -> %d\n",i,p->c,p->occ);
			else
				printf("%d : |/n| -> %d\n",i,p->occ); //pour afficher les sauts de lignes
						
			p=p->succ;
			i++;
		}
	printf("\n");
}


int main(int argc, char *argv[1])
{
	char* nom = "txt.txt";
	Occ liste = NULL;
	
	compte_carac_fichier(nom,&liste); //ou argv[0] à la place de nom si on entre le nom du fichier après l'exe
	
	afficher(liste);// pour debuggage
	
return 0;
}
