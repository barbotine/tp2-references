


#include <iostream>

void afficherGrille(int uneGrilleJoueur[][10], int uneGrilleOrdinateur[][10])
{
	std::cout << std::endl << " Joueur Ordinateur" << std::endl;
	std::cout << "   ";
	for (char leC = 'A'; leC < 'K'; leC++)
	{
		std::cout << leC << ' ';
	}
	std::cout << "     ";
	for (char leC = 'A'; leC < 'K'; leC++)
	{
		std::cout << leC << ' ';
	}
	std::cout << std::endl;
	for (int leI = 0; leI < 10; leI++)
	{
		std::cout << leI + 1 << ' ';
		if (leI < 9)
		{
			std::cout << ' ';
		}
		for (int leJ = 0; leJ < 10; leJ++)
		{
			if (uneGrilleJoueur[leI][leJ] < 0)
			{
				std::cout << "x ";
			}
			else
			{
				if (uneGrilleJoueur[leI][leJ] >= 2 and uneGrilleJoueur[leI][leJ] <= 5)
				{
					std::cout << uneGrilleJoueur[leI][leJ] << ' ';
				}
				else
				{
					if (uneGrilleJoueur[leI][leJ] == 9)
					{
						std::cout << "o ";
					}
					else
					{
						std::cout << "  ";
					}
				}
			}
		}
		std::cout << "  " << leI + 1 << ' ';
		if (leI < 9)
		{
			std::cout << ' ';
		}
		for (int leJ = 0; leJ < 10; leJ++)
		{
			if (uneGrilleOrdinateur[leI][leJ] < 0)
			{
				std::cout << "x ";
			}
			else
			{
				if (uneGrilleOrdinateur[leI][leJ] == 9)
				{
					std::cout << "o ";
				}
				else
				{
					std::cout << ". ";
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
	Fonction enregistrerNavire
	Vérifie si le navire peut-être placé sur la grille
	- possibilité de placer le navire sans sortir de la grille
	- pas de navire déjà présent sur son emplacement
	- pas de navire collé
	Retourne un booléen vrai si le navire a pu être placé
	Paramètres :
		- La grille sur laquelle placer le navire
		- L'orientation du navire,
		- La position (ligne, colonne) de la case du haut ou de gauche (selon l'orientation)
		- La taille du navire
*/
bool enregistrerNavire(int uneGrille[][10], char uneOrientation, int uneLigne, int uneColonne, int uneLongueur)
{
	bool positionValide;
	positionValide = true;
	if (uneOrientation == 'h')
	{
		for (int leI = uneColonne; leI < uneColonne + uneLongueur; leI++)
		{
			if (uneGrille[uneLigne][leI] != 0)
			{
				positionValide = false;
			}
			if (uneLigne > 0)
			{
				if (uneGrille[uneLigne - 1][leI] != 0)
				{
					positionValide = false;
				}
			}
			if (uneLigne < 9)
			{
				if (uneGrille[uneLigne + 1][leI] != 0)
				{
					positionValide = false;
				}
			}
		}
		if (uneColonne > 0)
		{
			if (uneGrille[uneLigne][uneColonne - 1] != 0)
			{
				positionValide = false;
			}
		}
		if (uneGrille[uneLigne][uneColonne + uneLongueur] != 0)
		{
			positionValide = false;
		}
	}
	if (uneOrientation == 'v')
	{
		for (int leI = uneLigne; leI < uneLigne + uneLongueur; leI++)
		{
			if (uneGrille[leI][uneColonne] != 0)
			{
				positionValide = false;
			}
			if (uneColonne > 0)
			{
				if (uneGrille[leI][uneColonne - 1] != 0)
				{
					positionValide = false;
				}
			}
			if (uneColonne < 9)
			{
				if (uneGrille[leI][uneColonne + 1] != 0)
				{
					positionValide = false;
				}
			}
		}
		if (uneLigne > 0)
		{
			if (uneGrille[uneLigne - 1][uneColonne] != 0)
			{
				positionValide = false;
			}
		}
		if (uneGrille[uneLigne + uneLongueur][uneColonne] != 0)
		{
			positionValide = false;
		}
	}
	if (positionValide)
	{
		if (uneOrientation == 'h')
		{
			for (int leI = uneColonne; leI < uneColonne + uneLongueur; leI++)
			{
				uneGrille[uneLigne][leI] = uneLongueur;
			}
		}
		if (uneOrientation == 'v')
		{
			for (int leI = uneLigne; leI < uneLigne + uneLongueur; leI++)
			{
				uneGrille[leI][uneColonne] = uneLongueur;
			}
		}
	}
	return positionValide;
}

/*
	Fonction placerNavireJoueur
	Demande au joueur de placer un navire. On informe le joueur qu'il doit placer un navire de type (porte-avion, torpilleur...) de telle longueur.
	Le joueur saisit ensuite l'orientation (horizontale ou verticale) puis la ligne et la colonne de la case de base (haut ou gauche selon l'orientation)
	La fonction vérifie que la case de base est placée dans la grille
	Puis appelle la fonction enregisterNavire
	Valeur de retour : void
	Paramètres :
		La grille
		Le nom du navire que l'on place
		La longueur du navire
*/
void placerNavireJoueur(int uneGrille[][10], std::string unNom, int uneLongueur)
{
	bool leNavireEnregistre;
	leNavireEnregistre = false;
	do
	{
		std::cout << "Saisie d'un " << unNom << " (" << uneLongueur << " cases)" << std::endl;
		char laOrientation;
		std::cout << "Orientation (h ou v) : ";
		std::cin >> laOrientation;
		int laLigne;
		std::cout << "Saisir la ligne (1 à 10) : ";
		std::cin >> laLigne;
		std::cin.ignore();
		laLigne = laLigne - 1;
		int leMax;
		leMax = 9;
		if (laOrientation == 'v')
		{
			leMax = 10 - uneLongueur;
		}
		while (laLigne < 0 or laLigne > leMax)
		{
			std::cout << "Hors grille, saisir la ligne : ";
			std::cin >> laLigne;
			laLigne = laLigne - 1;
		}
		int laColonne;
		char leC;
		std::cout << "Saisir la colonne (A à J) : ";
		std::cin >> leC;
		laColonne = leC - 'A';
		leMax = 9;
		if (laOrientation == 'h')
		{
			leMax = 10 - uneLongueur;
		}
		while (laColonne < 0 or laColonne > leMax)
		{
			std::cout << "Hors grille, saisir la colonne : ";
			std::cin >> leC;
			laColonne = leC - 'A';
		}
		leNavireEnregistre = enregistrerNavire(uneGrille, laOrientation, laLigne, laColonne, uneLongueur);
		if (leNavireEnregistre == true)
		{
			std::cout << "Navire enregistré" << std::endl;
		}
		else
		{
			std::cout << "Placement non valide" << std::endl;
		}

	} while (leNavireEnregistre == false);
}

/*
	Fonction placerNavireAleatoirement
	Place automatiquement (orientation et coordonnées de la case de base) un navire en vérifiant que la case de base  est placée dans la grille, puis appelle la fonction enregisterNavire
	Valeur de retour : void
	Paramètres : la grille et la longueur du navire à placer
*/
void placerNavireAleatoirement(int uneGrille[][10], int uneLongueur)
{
	bool leNavireEnregistre;
	leNavireEnregistre = false;
	char laOrientation;
	int laLigne;
	int laColonne;
	do
	{
		if (rand() % 2 == 0)
		{
			laOrientation = 'v';
		}
		else
		{
			laOrientation = 'h';
		}
		int leMax = 10;
		if (laOrientation == 'v')
		{
			leMax = leMax - uneLongueur + 1;
		}
		laLigne = rand() % leMax;
		leMax = 10;
		if (laOrientation == 'h')
		{
			leMax = leMax - uneLongueur + 1;
		}
		laColonne = rand() % leMax;
	} while (enregistrerNavire(uneGrille, laOrientation, laLigne, laColonne, uneLongueur) == false);
}

/*
	Fonction initialiserGrille
	Initialise le tableau à 0
	Valeur de retour : void
	Paramètres : la grille
*/
void initialiserGrille(int uneGrille[][10])
{
	for (int leI = 0; leI < 10; leI++)
	{
		for (int leJ = 0; leJ < 10; leJ++)
		{
			uneGrille[leI][leJ] = 0;
		}
	}
}

/*
	Fonction calculerScore
	Compte le nombre de nombres négatifs présents dans le tableau
	Valeur de retour : le nombre de nombres négatifs
	Paramètre : la grille
*/
int calculerScore(int uneGrille[][10])
{
	int leScore = 0;
	for (int leI = 0; leI < 10; leI++)
	{
		for (int leJ = 0; leJ < 10; leJ++)
		{
			if (uneGrille[leI][leJ] < 0)
			{
				leScore++;
			}
		}
	}
	return leScore;
}

/*
	Fonction saisirCoupJoueur
		Demande au joueur de saisir une ligne et une colonne comprises entre 1 et 10 et A et J
	Valeur de retour : void
	Paramètres : la ligne (in/out) et la colonne (in/out)
*/
void saisirCoupJoueur(int& uneLigne, int& uneColonne)
{
	std::cout << "Au joueur de jouer" << std::endl;
	std::cout << "Saisir la ligne (1 à 10) : ";
	std::cin >> uneLigne;
	std::cin.ignore();
	uneLigne = uneLigne - 1;
	while (uneLigne < 0 or uneLigne > 9)
	{
		std::cout << "Hors grille, saisir la ligne : ";
		std::cin >> uneLigne;
		uneLigne = uneLigne - 1;
	}
	char leC;
	std::cout << "Saisir la colonne (A à J) : ";
	std::cin >> leC;
	uneColonne = leC - 'A';
	while (uneColonne < 0 or uneColonne > 9)
	{
		std::cout << "Hors grille, saisir la colonne : ";
		std::cin >> leC;
		uneColonne = leC - 'A';
	}
}

/*
	Fonction saisirCoupOrdinateur
	Choisit aléatoirement deux nombres entre 1 et 10, vérifie qu'il n'a pas déjà choisi ce coup
	Valeur de retour : void
	Paramètres : la grille qui a enregistré les coups de l'ordinateur, la case choisie (ligne et colonne in/out)
*/
void saisirCoupOrdinateur(int uneGrille[][10], int& uneLigne, int& uneColonne)
{
	do
	{
		uneLigne = rand() % 10;
		uneColonne = rand() % 10;
	} while (uneGrille[uneLigne][uneColonne] < 0 or uneGrille[uneLigne][uneColonne] == 9);
}

/*
	Fonction jouerCoup
	Renvoie vrai si la case, désignée par la ligne et la colonne, contient un navire
	Valeur de retour : booléen vrai si navire touché
	Paramètres : la grille, la case
*/
bool jouerCoup(int uneGrille[][10], int uneLigne, int uneColonne)
{
	bool leNavireTouche = false;
	if (uneGrille[uneLigne][uneColonne] == 0)
	{
		uneGrille[uneLigne][uneColonne] = 9;
	}
	if (uneGrille[uneLigne][uneColonne] >= 2 and uneGrille[uneLigne][uneColonne] <= 5)
	{
		uneGrille[uneLigne][uneColonne] = -uneGrille[uneLigne][uneColonne];
		leNavireTouche = true;
	}
	return leNavireTouche;
}

/*
	Fonction verifierNavireCoule
	Vérifie si un navire est coulé. Regarde à partir d'une case (contenant un bateau) dans la ligne ou la colonne le nombre de cases, correspondant à ce type de navire, déjà touché.
	Valeur de retour : booléen vrai si toutes les cases d'un navire sont coulées
	Paramètres : la grille, la case.
*/
bool verifierNavireCoule(int uneGrille[][10], int uneLigne, int uneColonne)
{
	bool leNavireCoule;
	leNavireCoule = false;
	int laTaille;
	laTaille = -uneGrille[uneLigne][uneColonne];
	int leNbCases;
	leNbCases = 0;
	for (int leIndice = 0; leIndice < 10; leIndice++)
	{
		if (uneGrille[leIndice][uneColonne] == -laTaille)
		{
			leNbCases++;
			if (leNbCases == laTaille)
			{
				leNavireCoule = true;
			}
		}
		else
		{
			leNbCases = 0;
		}
	}
	leNbCases = 0;
	for (int leIndice = 0; leIndice < 10; leIndice++)
	{
		if (uneGrille[uneLigne][leIndice] == -laTaille)
		{
			leNbCases++;
			if (leNbCases == laTaille)
			{
				leNavireCoule = true;
			}
		}
		else
		{
			leNbCases = 0;
		}
	}
	return leNavireCoule;
}

int main()
{
	//srand(time(0));
	int laGrilleJoueur[10][10];
	int laGrilleOrdinateur[10][10];
	bool laCreationNavire;
	int laLigne = 4;
	int laColonne = 4;


	initialiserGrille(laGrilleJoueur); //initialisation de la grille du joueur
	afficherGrille(laGrilleJoueur, laGrilleOrdinateur); //affichage de la grille du joueur et de l'ordinateur
	//laCreationNavire = enregistrerNavire(laGrilleJoueur, 'h', 1, 1, 5); 
	//std::cout << laCreationNavire << std::endl; 
	placerNavireJoueur(laGrilleJoueur, "porte-avion", 5); //le joueur place un navire  
	afficherGrille(laGrilleJoueur, laGrilleOrdinateur); //affichage de la grille du joueur et de l'ordinateur
	initialiserGrille(laGrilleOrdinateur); //Initialisation de la grille de l'ordinateur
	placerNavireAleatoirement(laGrilleOrdinateur, 5); //on place aléatoirement un navire sur la grille de l'ordinateur          
	afficherGrille(laGrilleJoueur, laGrilleOrdinateur); //On affiche les deux grilles
	saisirCoupJoueur(laLigne, laColonne); //Le joueur joue 
	jouerCoup(laGrilleJoueur, laLigne, laColonne);

	return 0;
}cd 

