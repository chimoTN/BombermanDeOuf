#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "loadMap.h"

int * mapsPresentation(int countMaps, char ** arrayMapsNames){
    int m;

    int * arrayChoosen = malloc(countMaps*sizeof(int));

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
                    }
                }
            }

            //transformation
            //- “x” pour un mur indestructible
            //- “m” pour un mur destructible
            //- “p” pour un emplacement d’apparition d’un joueur
            //- un espace pour une case vide
            /*for(int j = 0 ; j < mapWidth ; j++){
                for(int k = 0 ; k < mapLength ; k++){
                    if(mapChar[j][k]=='x')mapGame[j][k]='#';
                    if(mapChar[j][k]=='m')mapGame[j][k]='#';
                    if(mapChar[j][k]=='p')mapGame[j][k]='#';
                    if(mapChar[j][k]==13)mapGame[j][k]='#';
                }
            }*/

            //affichage
            printf("\nCarte %d : \n",m+1);
            for(j = 0 ; j < mapWidth ; j++){
                for(k = 0 ; k < mapLength ; k++){
                    printf("%c", mapChar[j][k]);
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
    return arrayChoosen;
}

int ** mapToPlay(int indexMap, int * nbBombes, int * length, int * width, char ** arrayMapsNames){
    int i;
    int m;
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
        nbBombes = atoi (resultString);

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
                    }
                }
            }

            //transformation
            //- “x” pour un mur indestructible
            //- “m” pour un mur destructible
            //- “p” pour un emplacement d’apparition d’un joueur
            //- un espace pour une case vide
            /*for(int j = 0 ; j < mapWidth ; j++){
                for(int k = 0 ; k < mapLength ; k++){
                    if(mapChar[j][k]=='x')mapGame[j][k]='#';
                    if(mapChar[j][k]=='m')mapGame[j][k]='#';
                    if(mapChar[j][k]=='p')mapGame[j][k]='#';
                    if(mapChar[j][k]==13)mapGame[j][k]='#';
                }
            }*/
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
    for(i = 0 ; i < j ; i++){
        //printf("listOfChoice[%d]=%d\n",i,listOfChoice[i]);
    }
    //Générer nombre aléatoire entre 0 et j
    //printf("\n j = %d", j-1);
    srand(time(NULL));
    indiceChosen = rand() % j;

    //c'est la map stockée à l'indice indiceChosen dans arrayChoosen
    return indiceChosen;
}
