#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <time.h>
#include "files.h"
#include "loadMap.h"
#include "game.h"

int main(){
    int play=1;
    int choice;
    //MENU DEMARRAGE
    /*
    - 1) Démarrer
    - 2) Démarrer le serveur
    - 3) Rejoindre un serveur
    - 4) Quitter
    */
    while(play){
        printf("\nBienvenue !");
        printf("\nTapez :\n- 1 pour demarrer une partie en solo \n- 2 pour demarrer un serveur de jeu\n- 3 pour rejoindre un serveur de jeu\n- 4 pour quitter le jeu\n Votre saisie: ");
        fflush(stdin);
        scanf("%d", &choice);

        if (choice>=1 && choice<=4 ){
            switch (choice){
                case 1:
                    playSoloGame();
                    break;
                case 2:
                    //launchGameServer();
                    break;
                case 3:
                    //joinGameServer();
                    break;
                case 4:
                    printf("\n========================================\n");
                    printf("|| Merci d'avoir joue a Casse Briques ! ||\n");
                    printf("||   J'espere on se reverra bientot !   ||\n");
                    printf("||                  :)                  ||\n");
                    printf("==========================================\n");
                    return 0;
                default:
                    break;
            }

        }else{
                printf("Erreur de saisie ! Veuillez recommencer\n");
        }

    }

    return 0;
}
