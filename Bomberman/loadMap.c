#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include "loadMap.h"

int * mapsPresentation(int countMaps, char ** arrayMapsNames){
    int m;
    int choice=0;
    int * arrayChoosen = malloc(countMaps*sizeof(int));

    while(choice==0){
        printf("Voici les cartes disponibles :\n");

        for(m=0; m<countMaps; ++m) {
            int j;
            int k;
            int count=0;
            FILE *fp;
            char * path[50];
            char line[200];
            char buff[50];
            char * nameMap;
            char * resultString;
            char a;
            char c;
            int size;
            int nbBombes;
            int mapLength;
            int mapWidth;


            nameMap = strdup(arrayMapsNames[m]);
            //printf("nameMap = %s\n", nameMap);
            sprintf(path,"maps/%s",nameMap);

            fp = fopen(path,"rt");
            if(fp == NULL){
                return 1;
            }else{
                resultString = fgets(line, 100, fp);
                int nbBombes = atoi (resultString);
                //printf("nbBombes = %d\n", nbBombes);

                fgets(line, 100, fp);
                //isoler la longueur et la largeur

                //Dans line, j'ai toute la ligne


                //Longueur
                size = strlen(line)-1;

                for(j = 0 ; j < size ; j++){
                    a = line[j];
                    if(a==' '){
                        break;
                    }
                    buff[j]=a;
                }
                buff[j]='\0';
                mapLength = atoi(buff);


                for(k = j+1 ; k < size ; k++){
                    a = line[k];
                    buff[count]=a;
                    count++;
                }
                buff[k]='\0';
                mapWidth = atoi(buff);


                char mapChar[mapWidth][mapLength];
                char mapGame[mapWidth][mapLength];

                //Ensuite, on va récupérer le tableau de char
                for(j = 0 ; j < mapWidth ; j++){
                    for(k = 0 ; k < mapLength ; k++){
                        c = fgetc(fp);
                        if(c==10){
                            k--;
                        }else{
                            mapChar[j][k]=c;
                            mapGame[j][k]=c;
                        }
                    }
                }

                //transformation
                //- “x” pour un mur indestructible
                //- “m” pour un mur destructible
                //- “p” pour un emplacement d’apparition d’un joueur
                //- un espace pour une case vide
                for(int j = 0 ; j < mapWidth ; j++){
                    for(int k = 0 ; k < mapLength ; k++){
                        if(mapChar[j][k]=='x'){
                            mapGame[j][k]='#';
                        }
                        if(mapChar[j][k]=='m'){
                            mapGame[j][k]='+';
                        }
                        if(mapChar[j][k]=='p'){
                            mapGame[j][k]='J';
                        }
                    }
                }

                //affichage
                printf("\nCarte %d : \n",m+1);
                for(j = 0 ; j < mapWidth ; j++){
                    for(k = 0 ; k < mapLength ; k++){
                        printf("%c", mapGame[j][k]);
                    }
                    printf("\n");
                }

                //choix du user
                char selection;
                printf("Veuillez saisir X pour choisir la carte ou rien pour passer.\n");
                fflush(stdin);
                scanf("%c",&selection);
                //printf("%c\n",selection);
                if(selection=='X'){
                    arrayChoosen[m]=1;
                }else{
                    arrayChoosen[m]=0;
                }
            }

            fclose(fp);
        }
        for(int a = 0 ; a < countMaps ; a++){
            if(arrayChoosen[a]==1){
                choice=1;
            }
        }
        if(choice==0){
            printf("\n\n\n\n\n\nMerci de faire une selection pour pouvoir jouer ! ");
        }
    }
    return arrayChoosen;
}

char ** mapToPlay(int indexMap, int * nbPlayers, int * nbBombes, int * positionJoueurRow, int * positionJoueurCol, int * length, int * width, char ** arrayMapsNames){
    int i;
    int j;
    int k;
    int count=0;

    FILE *fp;
    char * path[50];
    char line[200];
    char buff[50];
    char * nameMap;
    char * resultString;
    char a;
    char c;
    int size;
    char ** mapChar;

    nameMap = strdup(arrayMapsNames[indexMap]);
    sprintf(path,"maps/%s",nameMap);

    fp = fopen(path,"rt");
    if(fp == NULL){
        return 1;
    }else{
        resultString = fgets(line, 100, fp);
        *nbBombes = atoi (resultString);

        fgets(line, 100, fp);
        //Longueur
        size = strlen(line)-1;

        for(j = 0 ; j < size ; j++){
            a = line[j];
            if(a==' '){
                break;
            }
            buff[j]=a;
        }
        buff[j]='\0';
        *length = atoi(buff);


        for(k = j+1 ; k < size ; k++){
            a = line[k];
            buff[count]=a;
            count++;
        }
        buff[k]='\0';
        *width = atoi(buff);

        mapChar = malloc( *width * sizeof(char *));   //allocation d'un tableau de n cases, (n pointeurs)
        if(mapChar == NULL){
            return 1;
        }else{
            for(i=0; i < *width; ++i){
                mapChar[i]=malloc( *length * sizeof(char));   //pour chaque case, on alloue n char
            }

            //char mapGame[width][length];

            //Ensuite, on va récupérer le tableau de char
            for(j = 0 ; j < *width ; j++){
                for(k = 0 ; k < *length ; k++){
                    c = fgetc(fp);
                    if(c==10){
                        k--;
                    }else{
                        mapChar[j][k]=c;
                        if(c=='p'){
                            *nbPlayers+=1;
                        }
                    }
                }
            }

            //connaitre les emplacements de tous les joueurs
            //realloc les tableaux de position si nbPlayers>2
            if(*nbPlayers > 2){
                size_t size = _msize( positionJoueurCol );
                printf_s( "Size of block after malloc of 1000 longs: %u\n", size );

                int * tempCol = realloc(positionJoueurCol, *nbPlayers * sizeof(int));
                int * tempRow = realloc(positionJoueurRow, *nbPlayers * sizeof(int));

                *positionJoueurCol= tempCol;
                *positionJoueurRow= tempRow;
                size = _msize( tempCol );
                printf_s( "Size of block after malloc of more 1000 longs: %u\n", size );
            }
            // transformation de la map:
            //- “x” pour un mur indestructible
            //- “m” pour un mur destructible
            //- “p” pour un emplacement d’apparition d’un joueur
            //- un espace pour une case vide
            int playerNum=0;
            for(int j = 0 ; j < *width ; j++){
                for(int k = 0 ; k < *length ; k++){
                    if(mapChar[j][k]=='x'){
                        mapChar[j][k]='#';
                    }
                    if(mapChar[j][k]=='m'){
                        mapChar[j][k]='+';
                    }
                    if(mapChar[j][k]=='p'){
                        mapChar[j][k]=(playerNum+1)+'0';

                        positionJoueurRow[playerNum]=j;
                        positionJoueurCol[playerNum]=k;

                        playerNum++;
                    }
                }
            }
        }
        fclose(fp);
    }
    return mapChar;

}

int randomMap(int countMaps, int * arrayChoosen){
    int i;
    int j;
    int listOfChoice[countMaps];
    int indiceChosen;

    for(i = 0 ; i < countMaps ; i++){
        if(arrayChoosen[i]==1){
            listOfChoice[j]=i;
            j++;
        }
    }
    //Générer nombre aléatoire entre 0 et j
    srand(time(NULL));
    indiceChosen = rand() % j;

    //c'est la map stockée à l'indice indiceChosen dans arrayChoosen
    return listOfChoice[indiceChosen];
}
