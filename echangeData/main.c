/*
    Live Server on port 8888
*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#define DEFAULT_BUFLEN 512

#pragma comment(lib,"ws2_32.lib") //Winsock Library



// Fonction qui initialise la carte avec la largeur et la longueur et permet de choisir le nombre de joueur
void initialiser_carte(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{

    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {

            if (i == 0 || i == longeur - 1)
            {
                carte[i][j] = '#';
            }
            else if (j == 0 || j == largeur - 1)
            {
                carte[i][j] = '#';
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
            else
            {
                carte[i][j] = ' ';
            }
        }
    }
}

// Fonction qui affiche la carte avec int longeur int largeur et actualis� les d�placements des joueurs et les bombes
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

// Fonction qui place les murs indestructibles sur tous les cot�s de la carte

void placer_murs(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{


    for (int i = 0; i < longeur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (i == 0 || i == longeur - 1)
            {
                carte[i][j] = '#';
            }
            else if (j == 0 || j == largeur - 1)
            {
                carte[i][j] = '#';
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
                carte[i][j] = '#';
            }
        }
    }
}

// Fonction qui place les mur destructibles partout o� il n'y a pas de murs indestructibles au hasard

void placer_murs_destructibles(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur])
{
    int nb_murs = 0;
    int nb_murs_max = (longeur * largeur) / 8;
    int x, y;
    srand(time(NULL));
    while (nb_murs < nb_murs_max)
    {
        x = rand() % (longeur - 2) + 1;
        y = rand() % (largeur - 2) + 1;
        if (carte[x][y] == ' ')
        {
            carte[x][y] = '+';
            nb_murs++;
        }
    }
}


//Fonction pour une placer une bombe sur la carte
void placer_bombe(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur], int x, int y)
{
    carte[x][y] = 111;

                if (carte[x + 1][y] != '#' && carte[x+1][y] == '+'){
                    carte[x + 1][y] = ' ';
                    int bonus = rand() % 100;
                    if (bonus < 30){
                        carte[x + 1][y] = 'b';
                    }
                }
                if (carte[x - 1][y] != '#' && carte[x-1][y] == '+'){
                    carte[x - 1][y] = ' ';
                    int bonus = rand() % 100;
                    if (bonus < 30){
                        carte[x - 1][y] = 'b';
                    }
                }
                if (carte[x][y + 1] != '#' && carte[x][y+1] == '+'){
                    carte[x][y + 1] = ' ';
                    int bonus = rand() % 100;
                    if (bonus < 30){
                        carte[x][y + 1] = 'b';
                    }

                }
                if (carte[x][y - 1] != '#' && carte[x][y-1] == '+'){
                    carte[x][y - 1] = ' ';

                    int bonus = rand() % 100;
                    if (bonus < 30){
                        carte[x][y - 1] = 'b';
                    }
                }
                if (carte[x+2][y] != '#' && carte[x+1][y] == ' ' && carte[x+2][y] == '+'){
                    carte[x+2][y] = ' ';
                }
                if (carte[x-2][y] != '#' && carte[x+1][y] == ' ' && carte[x-2][y] == '+'){
                    carte[x-2][y] = ' ';

                }
                if (carte[x][y+2] != '#' && carte[x+1][y] == ' ' && carte[x][y+2] == '+'){
                    carte[x][y+2] = ' ';
                }
                if (carte[x][y-2] != '#' && carte[x+1][y] != ' ' && carte[x][y-2] == '+'){
                    carte[x][y-2] = ' ';
                }
}


//code ascii pour les touches du clavier fleche haut , fleche bas, fleche gauche, fleche droite, espace

typedef enum
{
    HAUT = 72,
    BAS = 80,
    GAUCHE = 75,
    DROITE = 77,
    SPACE = 32
} touche;


//Fonction qui pemet de d�placer mon joueur 1 sur la carte en fonction des touches du clavier
void deplacement_joueur1(int longeur, int largeur, int nb_joueur, char carte[longeur][largeur], int x, int y)
{
    int touche = 0;
    touche = getch();
    switch (touche)
    {
    case HAUT:
            if (carte[x - 1][y] != '#' && carte[x - 1][y] != '+')
            {
                carte[x][y] = ' ';
                x--;
                carte[x][y] = 49;
            }
        break;
    case BAS:
            if (carte[x + 1][y] != '#'  && carte[x+1] [y] != '+')
            {
                carte[x][y] = ' ';
                x++;
                carte[x][y] = 49;
            }
        break;
    case GAUCHE:
            if (carte[x][y - 1] != '#' && carte[x][y - 1] != '+')
            {
                carte[x][y] = ' ';
                y--;
                carte[x][y] = 49;
            }
        break;
    case DROITE:
            if (carte[x][y + 1] != '#' && carte[x][y + 1] != '+')
            {
                carte[x][y] = ' ';
                y++;
                carte[x][y] = 49;
            }
        break;
    case SPACE:
       //transformer la case du dessus en un espace vide
        placer_bombe(longeur, largeur, nb_joueur, carte, x, y);
        break;
    }
     system("cls");
}


int main(int argc , char *argv[])
{

    //====================================================
    //================     SRVEUR PART    ================
    //====================================================


    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    char *message;

    //BUFFER
    char recvbuf[DEFAULT_BUFLEN];
    int iResult, iSendResult;
    int recvbuflen = DEFAULT_BUFLEN;

    //on branche la prise
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //On cree le socket IPV4 en TCP
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

    //la structure du socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //On Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    puts("Bind done");

    //On ecoute les connexion (limiter a 4)
    listen(s , 4);

    //On accept les entree
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);


    //====================================================
    //================  ON LANCE LE JEUX  ================
    //====================================================



    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        puts("Connection accepted");

        //Reply to the client
        message = "BOMBERMAN\n";
        send(new_socket , message , strlen(message) , 0);

        //=============================
        //test d'envoie et de reception
        //=============================




        //recommencer le programme une fois fini
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
                printf("Entrez une longeur de carte impaire : ");
                scanf("%d", &longeur);
            }
            //obliger le joueur a mettre une largeur impaire et d'au moins 7
            while (largeur % 2 == 0 || largeur < 7)
            {
                printf("Entrez une largeur de carte impaire : ");
                scanf("%d", &largeur);
            }

            printf("Entrez le nombre de joueur : ");
            scanf("%d", &nb_joueur);
            char carte[longeur][largeur];

            //initialiser la carte
            initialiser_carte(longeur, largeur, nb_joueur, carte);
            placer_murs(longeur, largeur, nb_joueur, carte);
            placer_murs_destructibles(longeur, largeur, nb_joueur, carte);
            int x = 1;
            int y = 1;

            // boucle pour actualiser les d�placements des joueurs
            while (1)
            {

                //============================================
                //              ENVOIE CARTE
                //============================================
                //la carte

                //on envoie la carte au client


                for (int i = 0; i < longeur; i++)
                {
                    for (int j = 0; j < largeur; j++)
                    {
                        printf("%c", carte[i][j]);

                        message = carte[i][j];
                        send(new_socket , message , strlen(message) , 0);
                    }
                    printf("\n");

                    message = "\n";
                    send(new_socket , message , strlen(message) , 0);
                }



                //afficher la carte
                afficher_carte(longeur, largeur, carte);

                deplacement_joueur1(longeur, largeur, nb_joueur, carte, x, y);
                if (carte[x - 1][y] == 49)
                {
                    x -= 1;
                }
                if (carte[x + 1][y] == 49)
                {
                    x += 1;
                }
                if (carte[x][y - 1] == 49)
                {
                    y -= 1;
                }
                if (carte[x][y + 1] == 49)
                {
                    y += 1;
                }

            }
           printf("Voulez vous recommencer ? 1 = oui 0 = non : ");
           scanf("%d", &recommencer);
        }
    }



    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
        return 1;
    }

    //on ferme
    closesocket(s);
    WSACleanup();

    return 0;
}
