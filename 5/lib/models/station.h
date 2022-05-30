#ifndef STATION_H
#define STATION_H

typedef struct Station {
    char *name;
    char *prev;
    int weight;
} Station;

Station *stationParse(char *str);

#endif // STATION_H
