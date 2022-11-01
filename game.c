#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

int playSoloGame(){
    int i;
    int j;
    int countMaps = countFiles("maps");
    int length=0;
    int width=0;
    int nbBombes=0;

    //récupérer le nom de toutes les maps
    char ** arrayMapsNames = tabOfFiles();

    //affichage des maps disponibles et choix par l'utilisateur
    int * arrayChoosen= mapsPresentation(countMaps, arrayMapsNames);
    int indexOfChoosenMap = randomMap(countMaps, arrayChoosen);

    //affichage
    char ** mapFinal = mapToPlay(indexOfChoosenMap, &nbBombes, &length, &width, arrayMapsNames);

    printf("\nVoici la carte choisie :\n");
    //affichage
    for(i = 0 ; i < width ; i++){
        for(j = 0 ; j < length ; j++){
            printf("%c", mapFinal[i][j]);
        }
        printf("\n");
    }

     // désallocation
    for(i = 0; i < countMaps; ++i) {
        free(arrayMapsNames[i]);
    }
    free(arrayMapsNames);

    return 0;
}
