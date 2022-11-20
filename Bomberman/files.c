#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <time.h>
#include "files.h"

int countFiles(char * directory){
    int countMaps=0;
    struct dirent *dir;
    DIR *d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] == '.') continue;

            countMaps+=1;
        }
        closedir(d);
    }else{
        return -1;
    }
    free(dir);

    return countMaps;
}

char ** tabOfFiles(){
    //Etape 1
    //Récupérer toutes les maps disponibles
    char **arrayMapsNames;
    char * buff;
    int i;
    int countMapNames=0;

    int countMaps = countFiles("maps"); //combien il y a de maps disponibles

    // allocation
    arrayMapsNames=malloc( countMaps * sizeof(char *));   //allocation d'un tableau de n cases, (n pointeurs)

    if(arrayMapsNames != NULL){
        for(i=0; i<countMaps; ++i){
            arrayMapsNames[i]=malloc( 20 * sizeof(char));   //pour chaque case, on alloue n char
        }

        struct dirent *dir;
        // opendir() renvoie un pointeur de type DIR.
        DIR *d = opendir("maps");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] == '.') continue;

                buff = strdup(dir->d_name);
                arrayMapsNames[countMapNames] = buff; //on stocke le nom du fichier dans le tableau
                countMapNames+=1;
            }
            closedir(d);
        }

    }

    return arrayMapsNames;
}
