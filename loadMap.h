#ifndef H_LOADMAP_H
#define H_LOADMAP_H

int * mapsPresentation(int countMaps, char ** arrayMapsNames);
int ** mapToPlay(int indexMap, int * nbBombes, int * length, int * width, char ** arrayMapsNames);
int randomMap(int countMaps, int * arrayChoosen);

#endif

