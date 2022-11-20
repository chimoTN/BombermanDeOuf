#ifndef H_LOADMAP_H
#define H_LOADMAP_H

int * mapsPresentation(int countMaps, char ** arrayMapsNames);
char ** mapToPlay(int indexMap, int * nbPlayers, int * nbBombes, int * positionJoueurRow, int * positionJoueurCol, int * length, int * width, char ** arrayMapsNames);
int randomMap(int countMaps, int * arrayChoosen);

#endif

