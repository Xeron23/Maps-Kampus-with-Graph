#ifndef MAPSKAMPUS_H_INCLUDED
#define MAPSKAMPUS_H_INCLUDED
#include <iostream>
using namespace std;
const int MAX_GEDUNG = 100;
const int MAX_DIST = 1000000;

struct infoJalan{
    char namaJalan;
    int panjang;
    string gedungTujuan;
};
typedef struct gedung *adrGedung;
typedef struct jalan *adrJalan;
struct gedung {
    string namaGedung;
    adrGedung nextGedung;
    adrJalan firstJalan;
};
struct jalan {
    infoJalan info;
    adrJalan nextJalan;
};
struct mapsKampus {
    adrGedung firstGedung;
};
void mainMenu();
void createGedung(string namaGedung, adrGedung &v);
void initGedung(mapsKampus &G);
void addGedung(mapsKampus &G, string namaGedung);
void buildGraph(mapsKampus &G);
adrJalan createJalan(infoJalan p);
void addJalan(mapsKampus &G, string namaGedung, infoJalan p);
adrGedung searchGedung(mapsKampus &G, string namaGedung);
int minDistance(int dist[], bool visited[], int n);
int calculateShortestDistance(mapsKampus &G, string src, string dst, int &dstIndex, int previous[], string gedung[], adrGedung gedungArray[], int numGedung);
string getShortestPath(int dstIndex, int previous[], string gedung[]);
void fastTestRoute(mapsKampus &G, string src, string dst);
void estimateTime(mapsKampus &G, string kendaraan);
void printGraph(mapsKampus &G);
void gedungTerdekat(mapsKampus &G, string gedung);
#endif // MAPSKAMPUS_H_INCLUDED
