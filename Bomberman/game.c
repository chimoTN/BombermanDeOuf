#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include "game.h"

#define NB_OBJECT 10
#define NB_BONUS 10
#define INVINCIBILITY 2

//code ascii pour les touches du clavier : fleche haut , fleche bas, fleche gauche, fleche droite, espace:
typedef enum
{
    UPlower = 122,
    UPupper = 90,
    DOWNlower = 115,
    DOWNupper = 83,
    RIGHTlower = 100,
    RIGHTupper = 68,
    LEFTlower = 113,
    LEFTupper = 81,
    SPACE = 32,
    NOTHING = 13
} touche;

void hud (int player, int nbPlayers, int *life, int **bonus, int * tabNbBombes, int *rangeBomb, int * bonusHeart, int * invincibility){
    printf("Vie: ");
    for (int i=0; i<nbPlayers; i++)
        printf("J%d=%d ", i+1,  life[i]);

    printf("\n\nNombre bombes disponibles = %d", tabNbBombes[player]);
    printf("\nPortee de la bombe = %d", rangeBomb[player]);

    printf("\n\nBONUS");
    printf("\n Passe-Bombes  = %d",  bonus[5][player]);
    printf("\n Bomb Kick = %d",  bonus[6][player]);
    if(invincibility[player]>0){
        printf("\n Invincible = Oui");
    }else{
        printf("\n Invincible = Non");;
    }

    if (bonusHeart[player]==1){
        printf("\n Coeur = 1");
    }else{
        printf("\n Coeur = 0");
    }

     printf("\n");


}

//Fonction qui affiche la carte pour visualiser le changement de position des joueurs et des bombes
void print_map(char ** map, int width, int length){
    system("cls");
    printf("//----------CASSE-BRIQUES----------\\\\ \n");
    for (int i = 0; i < width; i++){
        for (int j = 0; j < length; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("=======================\n");
}


void check_bombe(char ** map, int width, int length, int player, int nbPlayers, int * playersInGame, int * tabNbBombes, int ** tabBombes, int *** positionBombes, int delayBombe, int * rangeBomb,int *life, int *bonusHeart, int *invincibility){
    //a chaque fin de tour, on check si une bombe doit apparaitre. (un joueur vient de quitter la case où elle était)
    for(int i = 0 ; i < nbPlayers ; i++){
        for(int j = 0 ; j < tabNbBombes[i] ; j++){
            if(tabBombes[i][j]==delayBombe-nbPlayers){
                //récupérer la position et faire apparaitre la bombe
                int row = positionBombes[i][j][0];
                int col = positionBombes[i][j][1];

                if(!(map[row][col] >= (int)'1' && map[row][col] <= (int)(nbPlayers+'0'))){
                    map[row][col] = 111;
                }else{
                    //TODO
                }
            }
        }
    }

    //a chaque fin de tour, on check si une bombe doit exploser.
    for(int i = 0 ; i < nbPlayers ; i++){
        for(int j = 0 ; j < tabNbBombes[i] ; j++){
            if(tabBombes[i][j] == 1){

                //DOWN
                int f=1;
                int rowMin=0;
                while(f<=rangeBomb[i]){
                    if(positionBombes[i][j][0]+f > width-1 ){ //si c'est plus grand que le max de rows, alors on remonte à partir de row=0
                        if(explosion_bombe(map,rowMin++,positionBombes[i][j][1], nbPlayers, playersInGame, life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }else{
                        if(explosion_bombe(map,positionBombes[i][j][0]+f,positionBombes[i][j][1], nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }
                    f++;
                }

                //UP
                f=1;
                int rowMax = width-1;
                while(f<=rangeBomb[i]){
                    if(positionBombes[i][j][0]-f < 0 ){ //si c'est plus petit que le min de rows, alors on redescend à partir de row=rowMax
                        if(explosion_bombe(map,rowMax--,positionBombes[i][j][1], nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }else{
                        if(explosion_bombe(map,positionBombes[i][j][0]-f,positionBombes[i][j][1], nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }
                    f++;
                }

                //RIGHT
                f=1;
                int colMin=0;
                while(f<=rangeBomb[i]){
                    if(positionBombes[i][j][1]+f > length-1 ){ //si c'est plus grand que le max de cols, alors on repart de la gauche à partir de col=colMin
                        if(explosion_bombe(map,positionBombes[i][j][0],colMin++, nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }else{
                        if(explosion_bombe(map,positionBombes[i][j][0],positionBombes[i][j][1]+f, nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }
                    f++;
                }

                //LEFT
                f=1;
                int colMax=length-1;
                while(f<=rangeBomb[i]){
                    if(positionBombes[i][j][1]-f < 0 ){ //si c'est plus petit que le min de cols, alors on repart de la droite à partir de col=colMax
                        if(explosion_bombe(map,positionBombes[i][j][0],colMax--, nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    }else{
                        if(explosion_bombe(map,positionBombes[i][j][0],positionBombes[i][j][1]-f, nbPlayers, playersInGame,life,bonusHeart,invincibility)){
                            f+=rangeBomb[i]; //sortir de la plage du while
                        }
                    f++;
                    }
                }
                explosion_bombe(map, positionBombes[i][j][0], positionBombes[i][j][1], nbPlayers, playersInGame,life,bonusHeart,invincibility);

                //NETTOYAGE
                positionBombes[i][j][0]=0;
                positionBombes[i][j][1]=0;
            }
        }
    }

    //actualisation des compteurs ; à chaque tour, le compteur descend d'1.
    for(int i = 0 ; i < nbPlayers ; i++){
        for(int j = 0 ; j < tabNbBombes[i] ; j++){
            if(tabBombes[i][j] != 0){
                tabBombes[i][j]--;
            }
        }
    }

}

int explosion_bombe(char ** carte, int row, int col, int nbPlayer, int * playersInGame, int *life, int *bonusHeart, int *invincibility){
    int nb1=0;
    int nb2=0;
    int time1=time(NULL);
    int time2;
    srand(time(NULL));

    nb1 = rand() % 2; // 1/3 chance d'avoir un objet
    nb2 = rand() % NB_OBJECT;

    if (carte[row][col]!='#'){
        if (carte[row][col]=='+'){
            if (nb1>0){
                carte[row][col]=' ';
            }else{
                carte[row][col]=nb2+'A';
            }
            return 1;
        }else{
            if(carte[row][col]>='1' && carte[row][col]<= nbPlayer+'0' ){ // touche un joueur
                if (invincibility[carte[row][col]-'0'-1]<1 ){ //Pas invincible?
                    if(bonusHeart[carte[row][col]-'0'-1]!=1){  // Bonus coeur
                        life[carte[row][col]-'0'-1]-=1; // life--
                    }else{
                        bonusHeart[carte[row][col]-'0'-1]++;
                    }
                }

                //check si le joueur a encore une vie.. ou pas
                if(life[carte[row][col]-'0'-1]==0){
                    carte[row][col]=' ';
                    playersInGame[carte[row][col]-'0'-1]=0;
                }
            }else{
                carte[row][col]=' ';    // "Si ce n'est pas un mur" => fait dans l'appelle de la fonction => pour les joueurs ou objets a casser
            }
                            return 0;
        }
    }

}

//Fonction pour une placer une bombe sur la map
void put_bombe(char ** map, int row, int col, int player, int  * tabNbBombes, int ** tabBombes, int *** positionBombes, int delayBombe){

    //code pour objet : tabBombes = realloc(tabBombes, 2*sizeof(int));
    for(int i = 0 ; i < tabNbBombes[player] ; i++){
        if(tabBombes[player][i]==0){
            tabBombes[player][i]=delayBombe;

            positionBombes[player][i][0]=row;
            positionBombes[player][i][1]=col;

            tabNbBombes[player]--;
            return;
        }else{
            return;
        }
    }
}

int playBot(char ** map, int * positionJoueurRow, int * positionJoueurCol, int player, int width, int length){
    int touche;

    int tabPossibilities[5]={0};
    int possibilities=0;
    int random=0;


    //si le bot peut aller en haut
    if(map[positionJoueurRow[player] - 1][positionJoueurCol[player]] == ' '){
        tabPossibilities[possibilities]=UPlower;
        possibilities+=1;
    }
    //si le bot peut aller en bas
    if(map[positionJoueurRow[player] + 1][positionJoueurCol[player]] == ' '){
        tabPossibilities[possibilities]=DOWNlower;
        possibilities+=1;
    }
    //si le bot peut aller à gauche
    if(map[positionJoueurRow[player]][positionJoueurCol[player] - 1] == ' '){
        tabPossibilities[possibilities]=LEFTlower;
        possibilities+=1;
    }
    //si le bot peut aller à droite
    if(map[positionJoueurRow[player]][positionJoueurCol[player] + 1] == ' '){
        tabPossibilities[possibilities]=RIGHTlower;
        possibilities+=1;
    }

    //on peut toujours mettre une bombe
    tabPossibilities[possibilities]=SPACE;
    possibilities+=1;

    if(possibilities==0){
        //si aucune possibilité, alors il ne fait rien
        return 0;
    }else{
        //Générer nombre aléatoire entre 0 et possibilities
        srand(time(NULL));
        random = rand() % possibilities;
        touche = tabPossibilities[random];
        printf("\nrandom touche : %d", touche);
        return touche;
    }
}

//Fonction qui pemet de déplacer le joueur sur la carte en fonction des touches du clavier
void deplacement_joueur(char ** map, int * positionJoueurRow, int * positionJoueurCol, int player, int nbPlayers, int width, int length, int * tabNbBombes, int ** tabBombes, int *** positionBombe, int delayBombe, char * grabObject){

    printf("\n Au tour du joueur.... %d !!", (player+1));
    int touche;
    //si c'est le joueur 1, le laisser jouer. Sinon pour les autres, faire appel au bot.
    if(player==0){
        printf("\n C'est a toi de jouer !");
        touche = getch();

    }else{
        touche = playBot(map, positionJoueurRow, positionJoueurCol, player, width, length);
        if(touche != 0 ){
            printf("\n touche du bot : %d = %d\n", player+1, touche);
            //doucement pour qu'on voit tout le monde jouer son tour
            sleep(1);
        }
    }
    switch (touche){
        case UPlower:
        case UPupper:
            //si on est sur la première ligne
            if(positionJoueurRow[player] == 0){
                if (map[width-1][positionJoueurCol[player]] !='#'
                    && map[width-1][positionJoueurCol[player]]!='+'
                    && map[width-1][positionJoueurCol[player]]!=111
                    && !(map[width-1][positionJoueurCol[player]]>='1'
                    && map[width-1][positionJoueurCol[player]]<= nbPlayers+'0')){
                    map[0][positionJoueurCol[player]] = ' ';



                    positionJoueurRow[player]=width-1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }else{
                if ( map[positionJoueurRow[player] - 1][positionJoueurCol[player]] !='#'
                    && map[positionJoueurRow[player] - 1][positionJoueurCol[player]]!='+'
                    && map[positionJoueurRow[player] - 1][positionJoueurCol[player]]!=111
                    && !(map[positionJoueurRow[player] - 1][positionJoueurCol[player]]>='1'
                    && map[positionJoueurRow[player] - 1][positionJoueurCol[player]]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = ' ';

                    if(map[positionJoueurRow[player] - 1][positionJoueurCol[player]]!=' '){
                        *grabObject=map[positionJoueurRow[player] - 1][positionJoueurCol[player]];
                    }else{
                        *grabObject='/';
                    }

                    positionJoueurRow[player]-=1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }
            break;
        case DOWNlower:
        case DOWNupper:
            //si on est sur la dernière ligne
            if(positionJoueurRow[player] == width-1){
                if (map[0][positionJoueurCol[player]] !='#'
                    && map[0][positionJoueurCol[player]]!='+'
                    && map[0][positionJoueurCol[player]]!=111
                    && !(map[0][positionJoueurCol[player]]>='1')
                    && map[0][positionJoueurCol[player]]<= nbPlayers+'0'){
                    map[width-1][positionJoueurCol[player]] = ' ';



                    positionJoueurRow[player]=0;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }else{
                if (map[positionJoueurRow[player] + 1][positionJoueurCol[player]] !='#'
                    && map[positionJoueurRow[player] + 1][positionJoueurCol[player]]!='+'
                    && map[positionJoueurRow[player] + 1][positionJoueurCol[player]]!=111
                    && !(map[positionJoueurRow[player] + 1][positionJoueurCol[player]]>='1'
                    && map[positionJoueurRow[player] + 1][positionJoueurCol[player]]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = ' ';

                    if(map[positionJoueurRow[player] + 1][positionJoueurCol[player]]!=' '){
                        *grabObject=map[positionJoueurRow[player] + 1][positionJoueurCol[player]];
                    }else{
                        *grabObject='/';
                    }

                    positionJoueurRow[player]+=1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }
            break;
        case LEFTlower:
        case LEFTupper:
            //si on est sur la première colonne
            if(positionJoueurCol[player] == 0){
                if (map[positionJoueurRow[player]][length-1] !='#'
                    && map[positionJoueurRow[player]][length-1]!='+'
                    && map[positionJoueurRow[player]][length-1]!=111
                    && !(map[positionJoueurRow[player]][length-1]>='1'
                    && map[positionJoueurRow[player]][length-1]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][0] = ' ';
                    positionJoueurCol[player]=length-1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }else{
                if (map[positionJoueurRow[player]][positionJoueurCol[player] - 1] !='#'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] - 1]!='+'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] - 1]!=111
                    && !(map[positionJoueurRow[player]][positionJoueurCol[player] - 1]>='1'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] - 1]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = ' ';

                    if(map[positionJoueurRow[player]][positionJoueurCol[player]-1]!=' '){
                        *grabObject=map[positionJoueurRow[player]][positionJoueurCol[player]-1];
                    }else{
                        *grabObject='/';
                    }

                    positionJoueurCol[player]-=1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }
            break;
        case RIGHTlower:
        case RIGHTupper:
            //si on est sur la dernière colonne
            if(positionJoueurCol[player] == length-1){
                if (map[positionJoueurRow[player]][0] !='#'
                    && map[positionJoueurRow[player]][0]!='+'
                    && map[positionJoueurRow[player]][0]!=111
                    && !(map[positionJoueurRow[player]][0]>='1'
                    && map[positionJoueurRow[player]][0]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][length-1] = ' ';
                    positionJoueurCol[player]=0;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }else{
                if (map[positionJoueurRow[player]][positionJoueurCol[player] + 1] !='#'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] + 1]!='+'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] + 1]!=111
                    && !(map[positionJoueurRow[player]][positionJoueurCol[player] + 1]>='1'
                    && map[positionJoueurRow[player]][positionJoueurCol[player] + 1]<= nbPlayers+'0')){
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = ' ';

                    if(map[positionJoueurRow[player]][positionJoueurCol[player]+1]!=' '){
                        *grabObject=map[positionJoueurRow[player]][positionJoueurCol[player]+1];
                    }else{
                        *grabObject='/';
                    }

                    positionJoueurCol[player]+=1;
                    map[positionJoueurRow[player]][positionJoueurCol[player]] = (player+1)+'0';
                }
            }
            break;
        case SPACE:
            // poser une bombe si on est pas déjà sur une bombe
            put_bombe(map, positionJoueurRow[player], positionJoueurCol[player], player, tabNbBombes, tabBombes, positionBombe, delayBombe);
            break;
        case NOTHING:
            break;
        default:
            break;
    }
}

//Fonction qui gère le jeu et les déplacements
void game(char ** map, int width, int length, int nbPlayers, int * playersInGame, int * tabNbBombes, int * positionJoueurRow, int * positionJoueurCol, int ** tabBombes, int *** positionBombe, int delayBombe, int * rangeBomb, int ** bonus, int * life, int * bonusHeart, int * invincibility){
    int gaming = 1;
    while(gaming){
        // boucle pour actualiser les déplacements des joueurs
        for(int p = 0 ; p < nbPlayers ; p++){
            //si le joueur en cours est toujours en vie ou pas
            if(playersInGame[p]==1){
                char grabObject='/';
                //déroulement d'un tour
                print_map(map, width, length);
                hud(p, nbPlayers, life, bonus, tabNbBombes, rangeBomb, bonusHeart, invincibility);
                //déplacement du joueur
                deplacement_joueur(map, positionJoueurRow, positionJoueurCol, p, nbPlayers, width, length, tabNbBombes, tabBombes, positionBombe, delayBombe, &grabObject);
                if (invincibility[p]>=1 && invincibility[p]<=INVINCIBILITY){ //2 tours d'invincibilité
                    invincibility[p]++;
                }
                //affichage vies
                printf("\nLife[%d]= %d\n", p, life[p] );

                //bonus
                // RAMASSER BONUS
                if (grabObject!='/'){
                    bonus[grabObject-'A'][p]=1;

                    for(int i=0; i<NB_BONUS; i++){
                        for(int j=0; j<nbPlayers; j++){
                            printf("Bonus[%c][%d] = %d\n", i+'A', j, bonus[i][j] );
                        }
                    }
                }
                /*
    bonus[0] = Bomb Up = nbBomb+1
    bonus[1] = Bomb Down = nbBomb-1

    bonus[2] = Flamme Jaune = rangeBomb+1
    bonus[3] = Flamme Bleue = rangeBomb-1
    bonus[4] = Flamme Rouge = rangeBomb => max

    bonus[5] = Passe-Bombes = marcher sur les bombes + desactivation bonus[6]
    bonus[6] = Bomb Kick = football + desactivation bonus[5]
    bonus[7] = Invincibilité
    bonus[8] = Coeur = invisibilité une seule fois + maximum 1 dans la partie
    bonus[9] = Vie = life+1
    */
                /*
                if(bonus[0][player]==1){
                }
                if(bonus[1][player]==1){
                }
                */

                if(bonus[2][p]==1){
                    bonus[2][p]=0;
                    rangeBomb[p]+=1;

                }
                if(bonus[3][p]==1){
                    bonus[3][p]=0;
                    rangeBomb[p]-=1;
                }
                if(bonus[4][p]==1){
                    bonus[4][p]=0;
                    rangeBomb[p]=100;

                }
                /*
                if(bonus[5][player]==1){

                }
                if(bonus[6][player]==1){

                }*/
                if(bonus[7][p]==1){
                    bonus[7][p]=0;
                    invincibility[p]=INVINCIBILITY;
                }

                if(bonus[8][p]==1){
                  bonus[8][p]=0;
                  if (bonusHeart[p]!=1){
                    bonusHeart[p]++;
                  }
                }

                if(bonus[9][p]==1){
                    bonus[9][p]=0;
                    life[p]++;
                }
                //fin bonus


                //vérification de la map (bombes à exploser, etc
                check_bombe(map, width, length, p, nbPlayers, playersInGame, tabNbBombes, tabBombes, positionBombe, delayBombe, rangeBomb,life,bonusHeart,invincibility);
                //vérification condition de fin
                int result = checkIfEndGame(map, width, length);
                printf("\n RESULT : %d ", result);
                //le joueur 1 est mort...
                if(result == -5){
                    print_map(map, width, length);
                    gaming=0;
                    printf("\n Oh non.. tu as perdu !! Essaies encore ! \n");
                    break;
                //il ne reste qu'une personne : c'est le gagnant !
                }else if(result!= 100 && result != 0){
                    print_map(map, width, length);
                    gaming=0;
                    printf("\n Youhouu ! VICTOIRE du joueur %d !\n", result);
                    break;
                } //plus personne sur le terrain ? dommage ! personne n'a gagné
                else if(result == 100){
                    print_map(map, width, length);
                    gaming=0;
                    printf("\n Oh oh... Personne ne gagne ! \n");
                    break;
                }
            }
        }
    }
    printf("\n Merci d'avoir joue !! \n");
}

//Fonction qui vérifie si la partie est finie ; le dernier joueur présent a gagné
int checkIfEndGame(char ** map, int width, int length){
    int count=0;
    int winner=0;
    int player1dead=1;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < length; j++){
            if(map[i][j] >= 49 && map[i][j] <= 52){
                if(map[i][j] == 49){
                    player1dead=0;
                }
                count+=1;
                winner=map[i][j]- '0';
            }
        }
    }
    if(player1dead==1){
        return -5;
    }
    if(count==1){
        return winner;
    }
    if(count==0){
        return 100;
    }
    return 0;
}

void playSoloGame(){
    int i;
    int j;
    printf("coucou");
    int countMaps = countFiles("maps");
    printf("coucou");
    int length=0;
    int width=0;
    int nbBombes=0;
    int nbPlayers=0;
    int delayBombe=0;


    //2 joueurs minimum dans la partie, on realloc par la suite si besoin
    //tableau de positions de Lignes --> indice 0 : ligne où se trouve le joueur 1 ; indice 1 : ligne où se trouve le joueur 2
    int * positionJoueurRow = malloc( 2 * sizeof(int));
    if(positionJoueurRow == NULL){
        return 1;
    }printf("coucou");
    //tableau de positions de Colonnes
    int * positionJoueurCol = malloc( 2 * sizeof(int));
    if(positionJoueurCol == NULL){
        return 1;
    }

    //récupérer le nom de toutes les maps
    char ** arrayMapsNames = tabOfFiles();
    if(arrayMapsNames == NULL){
        return 1;
    }
    //affichage des maps disponibles et choix par l'utilisateur
    int * arrayChoosen= mapsPresentation(countMaps, arrayMapsNames);
    if(arrayChoosen == NULL){
        return 1;
    }
    int indexOfChoosenMap = randomMap(countMaps, arrayChoosen);

    //Initialisation de tous les paramètres de la partie selon la map choisie
    char ** mapFinal = mapToPlay(indexOfChoosenMap, &nbPlayers, &nbBombes, positionJoueurRow, positionJoueurCol, &length, &width, arrayMapsNames);
    if(mapFinal == NULL){
        return 1;
    }

    int * playersInGame=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int
    for(i=0; i < nbPlayers; ++i){
        playersInGame[i]=1;
    }

    int * tabNbBombes = calloc( nbPlayers, sizeof(int));
    for(i=0; i < nbPlayers; ++i){
        tabNbBombes[i]=3;
    }

    delayBombe=nbPlayers*3+1;
    //tableau de compteur de secondes pour les bombes en attente de visualisation ; un joueur pose une bombe, mais ne voit la bombe que quand il se décale d'une case
    int ** tabBombes = calloc( nbPlayers, sizeof(int *));
    if(tabBombes == NULL){
        return 1;
    }else{
        for(i=0; i < nbPlayers; ++i){
        tabBombes[i]=calloc( tabNbBombes[i], sizeof(int));   //pour chaque joueur, on alloue n int (nbBombes dispo)
        }
    }

    int *** positionBombe = malloc( nbPlayers * sizeof(int **));
    if(positionBombe == NULL){
        return 1;
    }else{
        for(i=0; i < nbPlayers; ++i){
            positionBombe[i]=malloc( tabNbBombes[i] * sizeof(int *));
        }
        for(i=0; i < nbPlayers; ++i){
            for(j=0; j < tabNbBombes[i]; ++j){
                positionBombe[i][j]=calloc( 2, sizeof(int));
            }
        }
    }
    printf("Nombres de joueurs : %d \n", nbPlayers);

    int *rangeBomb=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int
    for (i=0; i < nbPlayers; ++i){
        rangeBomb[i]=2;
    }

    int *bonusHeart=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int
    int *invincibility=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int

    int *life=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int
    for (int i=0; i<nbPlayers; ++i){
        life[i]=1;
    }


    // CREATION TABLEAU CHECK BONUS/JOUEUR
    int ** bonus = calloc( NB_BONUS, sizeof(int *));   //allocation d'un tableau de n cases, (n pointeurs)
    if(bonus == NULL){
        return 1;
    }else{
        for(int i=0; i < NB_BONUS; ++i){
            bonus[i]=calloc( nbPlayers, sizeof(int));   //pour chaque case, on alloue n int
        }
    }

    //affichage
    printf("\nVoici la carte choisie :\n");
    for(i = 0 ; i < width ; i++){
        for(j = 0 ; j < length ; j++){
            printf("%c", mapFinal[i][j]);
        }
        printf("\n");
    }
    printf("Nombres de joueurs : %d \n", nbPlayers);


    // JEU
    // JEU
    // JEU
    game(mapFinal, width, length, nbPlayers, playersInGame, tabNbBombes, positionJoueurRow, positionJoueurCol, tabBombes, positionBombe, delayBombe, rangeBomb, bonus, life, bonusHeart, invincibility);


    //bots pour partie solo
    //probleme : ne pas pouvoir reposer une bombe là où on est

    // désallocation
    for(i = 0; i < countMaps; ++i) {
        free(arrayMapsNames[i]);
    }
    free(arrayMapsNames);

    free(positionJoueurRow);
    free(positionJoueurCol);
    free(arrayChoosen);
printf("\nhey !!");
    free(bonusHeart);
    free(invincibility);
    free(life);

    for(i = 0; i < NB_BONUS; ++i) {
        free(bonus[i]);
    }
    free(bonus);
printf("\nhey !!");
    for(i = 0; i < nbPlayers; ++i) {
        free(tabBombes[i]);
    }

    free(rangeBomb);
    free(playersInGame);
printf("\nhey !!");
    for(i=0; i < nbPlayers; ++i){
        for(j=0; j < tabNbBombes[i]; ++j){
            free(positionBombe[i][j]);
        }
    }
    for(i=0; i < nbPlayers; ++i){
            free(positionBombe[i]);
    }
    free(tabNbBombes);
    free(positionBombe);
printf("\nhey !!");
    free(mapFinal);
printf("\nhey !!");
    free(tabBombes);

printf("\nhey !!");
}
