#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

// Fonction qui initialise la carte avec la largeur et la longueur et pouvoir choisir le nombre de joueur 
void initialiser_carte(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{

    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {

            if (i == 0 || i == longeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (j == 0 || j == largeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (i == 1 && j == 1 && nb_joueur >= 1)
            {
                //1 en unicode
                carte[i][j] = 49;
            }
            else if (i == 1 && j == largeur - 2 && nb_joueur >= 2)
            {
                carte[i][j] = 50;
            }
            else if (i == longeur - 2 && j == 1 && nb_joueur >= 3)
            {
                carte[i][j] = 51;
            }
            else if (i == longeur - 2 && j == largeur - 2 && nb_joueur >= 4)
            {
                carte[i][j] = 52;
            }
            else
            {
                carte[i][j] = ' ';
            }
        }
    }
}

// Fonction qui place les murs indestructibles sur tous les cotés de la carte 

void placer_murs(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{

    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (i == 0 || i == longeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (j == 0 || j == largeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (i == 1 && j == 1 && nb_joueur >= 1)
            {
                carte[i][j] = 49;
            }
            else if (i == 1 && j == largeur - 2 && nb_joueur >= 2)
            {
                carte[i][j] = 50;
            }
            else if (i == longeur - 2 && j == 1 && nb_joueur >= 3)
            {
                carte[i][j] = 51;
            }
            else if (i == longeur - 2 && j == largeur - 2 && nb_joueur >= 4)
            {
                carte[i][j] = 52;
            }
            else if (i % 2 == 0 && j % 2 == 0)
            {
                carte[i][j] = 219;
            }
        }
    }
}



// Fonction qui place les mur destructibles partout où il n'y a pas de murs indestructibles sauf sur les cases à cotés des joueurs
void placer_murs_destructibles(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{
    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (i == 0 || i == longeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (j == 0 || j == largeur - 1)
            {
                carte[i][j] = 219;
            }
            else if (i == 1 && j == 1 && nb_joueur >= 1)
            {
                carte[i][j] = 49;
            }
            else if (i == 1 && j == largeur - 2 && nb_joueur >= 2)
            {
                carte[i][j] = 50;
            }
            else if (i == longeur - 2 && j == 1 && nb_joueur >= 3)
            {
                carte[i][j] = 51;
            }
            else if (i == longeur - 2 && j == largeur - 2 && nb_joueur >= 4)
            {
                carte[i][j] = 52;
            }
            else if (i % 2 == 0 && j % 2 == 0)
            {
                carte[i][j] = 219;
            }
            else if (carte[i][j] != 219 && carte[i][j] != 49 && carte[i][j] != 50 && carte[i][j] != 51 && carte[i][j] != 52)
            {
                carte[i][j] = 178;
            }
        }
    }
}


//code ascii pour les touches du clavier fleche haut , fleche bas, fleche gauche, fleche droite
#define HAUT 72
#define BAS 80
#define GAUCHE 75
#define DROITE 77


//Fonction qui pemet de déplacer mon joueur 1 sur la carte en fonction des touches du clavier
void deplacement_joueur1(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur], int x, int y)
{
    int touche = 0;
    touche = getch();
    switch (touche)
    {
    case HAUT:
        if (carte[x - 1][y] != 219)
        {
            carte[x - 1][y] = 49;
            carte[x][y] = ' ';

        }
        break;
    case BAS:
        if (carte[x + 1][y] != 219)
        {
            carte[x + 1][y] = 49;
            carte[x][y] = ' ';

        }
        break;
    case GAUCHE:
        if (carte[x][y - 1] != 219)
        {
            carte[x][y - 1] = 49;
            carte[x][y] = ' ';
        }
        break;
    case DROITE:
        if (carte[x][y + 1] != 219)
        {
            carte[x][y + 1] = 49;
            carte[x][y] = ' ';
        }
        break;
    }
     system("cls");
}





// Fonction qui affiche la carte avec int longeur int largeur et actualisé les déplacements des joueurs
void afficher_carte(int longeur, int largeur, char carte[longeur][largeur])
{
    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            printf("%c", carte[i][j]);
        }
        printf("\n");
    }
}








// Fonction qui place les bonus

// void placer_bonus(int longeur, int largeur, char carte[longeur][largeur])
// {
//     int nb_bonus = 0;
//     int nb_bonus_max = (longeur * largeur) / 10;
//     while (nb_bonus < nb_bonus_max)
//     {
//         int x = rand() % (longeur - 2) + 1;
//         int y = rand() % (largeur - 2) + 1;
//         if (carte[x][y] == ' ')
//         {
//             carte[x][y] = 'B';
//             nb_bonus++;
//         }
//     }
// }


// // Fonction qui place les joueurs

// void placer_joueurs(int longeur, int largeur, char carte[longeur][largeur])
// {
//     int nb_joueurs = 0;
//     int nb_joueurs_max = 4;
//     while (nb_joueurs < nb_joueurs_max)
//     {
//         int x = rand() % (longeur - 2) + 1;
//         int y = rand() % (largeur - 2) + 1;
//         if (carte[x][y] == ' ')
//         {
//             carte[x][y] = 'p';
//             nb_joueurs++;
//         }
//     }
// }


//fonction main qui demander la longueur et la largeur de la carte puis l'intialiser et l'afficher
int main()
{
    //recommencer le programme un fois fini
    int recommencer = 1;
    while (recommencer == 1)
    {
        //initialisation de la carte
        int longeur = 0;
        int largeur = 0;
        int nb_joueur = 0;
        //obliger le joueur a mettre une longeur impaire et d'au moins 7
        while (longeur % 2 == 0 || longeur < 7)
        {
            printf("Entrez la longeur de la carte (impair et au moins 7) : ");
            scanf("%d", &longeur);
        }
        //obliger le joueur a mettre une largeur impaire et d'au moins 7
        while (largeur % 2 == 0 || largeur < 7)
        {
            printf("Entrez la largeur de la carte (impair et au moins 7) : ");
            scanf("%d", &largeur);
        }
        printf("Entrez le nombre de joueur : ");
        scanf("%d", &nb_joueur);
        char carte[longeur][largeur];
        //initialiser la carte  
        initialiser_carte(longeur, largeur, nb_joueur, carte);
        placer_murs(longeur, largeur, nb_joueur, carte);
        placer_murs_destructibles(longeur, largeur, nb_joueur, carte);
        // placer_bonus(longeur, largeur, carte);
        int x = 1;
        int y = 1;
        // boucle pour actualiser les déplacements des joueurs
        while (1)
        {
            afficher_carte(longeur, largeur, carte);
            deplacement_joueur1(longeur, largeur, nb_joueur, carte, x, y);
            //actualiser les déplacements des joueurs x et y quand le joueur appuie sur les fleches
            if (carte[x - 1][y] == 49)
            {
                x = x - 1;
            }
            if (carte[x + 1][y] == 49)
            {
                x = x + 1;
            }
            if (carte[x][y - 1] == 49)
            {
                y = y - 1;
            }
            if (carte[x][y + 1] == 49)
            {
                y = y + 1;
            }

        }
       printf("Voulez vous recommencer ? 1 = oui 0 = non : ");
        scanf("%d", &recommencer);
    }
    return 0;
} 