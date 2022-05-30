#include "stdlib.h"
#include "string.h"
#include "models/station.h"

Station *stationParse(char *str) {
    Station *station = malloc(sizeof(Station));
    char *delim = ",", *word = strtok(str, delim);
    station->name = word;
    word = strtok(NULL, delim);
    station->prev = word;
    word = strtok(NULL, delim);
    station->weight = atoi(word);
    return station;
}
