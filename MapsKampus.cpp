#include "MapsKampus.h"
void mainMenu(){
    cout << endl;
    cout << "==============================================================="<< endl;
    cout << "                             Pilih Menu                        " << endl;
    cout << "==============================================================="<< endl;
    cout << "1. Daftar Semua Gedung dan Jalan"<< endl;
    cout << "2. Rute terpendek dari Gate 1 ke MSU" << endl;
    cout << "3. Gedung terdekat dari lokasi sekarang" << endl;
    cout << "4. Rute terpendek lokasi sekarang ke MSU" << endl;
    cout << "5. Estimasi waktu sampe dengan rute terbaik dari Gate 1 ke MSU" << endl;
    cout << "6. Keluar"<< endl;
    cout << "==============================================================="<< endl;
    cout << "masukan menu << ";
};

void createGedung(string namaGedung, adrGedung &v){
    v = new gedung;
    v->firstJalan = NULL;
    v->nextGedung = NULL;
    v->namaGedung = namaGedung;
}

void initGedung(mapsKampus &G){
    G.firstGedung = NULL;
}

void addGedung(mapsKampus &G, string namaGedung){
    adrGedung v;
    createGedung(namaGedung, v);
    adrGedung p = G.firstGedung;
    if(G.firstGedung == NULL) {
        G.firstGedung = v;
    } else {
        while (p->nextGedung != NULL) {
            p = p->nextGedung;
        }
        p->nextGedung = v;
    }
}

void buildGraph(mapsKampus &G){
    initGedung(G);
    string newGedung[7] = {"Gate_1", "TUCH", "GKU", "Danau", "Cacuk", "MSU", "Asrama_Putri"};
    int i = 0;
    while (i < 7) {
        addGedung(G, newGedung[i]);
        i++;
    }
}

adrJalan createJalan(infoJalan p){
    adrJalan jln = new jalan;
    jln->info.panjang = p.panjang;
    jln->info.namaJalan = p.namaJalan;
    jln->info.gedungTujuan = p.gedungTujuan;
    jln->nextJalan = NULL;
    return jln;
}

void addJalan(mapsKampus &G, string namaGedung, infoJalan p){
    adrGedung k = searchGedung(G, namaGedung);
    adrJalan l;
    if(k != NULL) {
        if(k->firstJalan == NULL) {
            k->firstJalan = createJalan(p);
        } else {
            l = k->firstJalan;
            while(l->nextJalan != NULL) {
                l = l->nextJalan;
            }
            l->nextJalan = createJalan(p);
        }
    }
}

adrGedung searchGedung(mapsKampus &G, string namaGedung){
    adrGedung gedung = G.firstGedung;
    while(gedung != NULL) {
        if(gedung->namaGedung == namaGedung){
            return gedung;
        }
        gedung = gedung->nextGedung;
    }
    return NULL;
}

// Fungsi untuk mencari jalur terpendek menggunakan Dijkstra
int minDistance(int dist[], bool visited[], int n) {
    int min = MAX_DIST, min_index;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

int calculateShortestDistance(mapsKampus &G, string src, string dst, int &dstIndex, int previous[], string gedung[], adrGedung gedungArray[], int numGedung) {
    adrGedung temp = G.firstGedung;
    int dist[MAX_GEDUNG];
    bool visited[MAX_GEDUNG];
    while (temp != NULL) {
        gedung[numGedung] = temp->namaGedung; //Array Nama Gedung[]
        gedungArray[numGedung] = temp; // Array gedung[]
        numGedung++; // increament
        temp = temp->nextGedung;
    }
    // numGedung = 7
    // set default value to inedex
    for (int i = 0; i < numGedung; i++) {
        dist[i] = MAX_DIST;
        visited[i] = false;
        previous[i] = -1;
    }

    // mencari apakah gedung ada atau tidak
    int srcIndex = -1;
    for (int i = 0; i < numGedung; i++) {
        if (gedung[i] == src) {
            srcIndex = i;
        }
        if (gedung[i] == dst) {
            dstIndex = i;
        }
    }

    if (srcIndex == -1 || dstIndex == -1) {
        cout << "Gedung tidak ditemukan!" << endl;
        return -1;
    }

    dist[srcIndex] = 0;

    for (int count = 0; count < numGedung - 1; count++) {
        int u = minDistance(dist, visited, numGedung);
        visited[u] = true;

        adrGedung currentGedung = gedungArray[u];
        adrJalan currentJalan = currentGedung->firstJalan;

        while (currentJalan != nullptr) {
            int idxTujuan = -1;
            for (int i = 0; i < numGedung; i++) {
                if (gedung[i] == currentJalan->info.gedungTujuan) {
                    idxTujuan = i;
                    break;
                }
            }

            if (idxTujuan != -1 && !visited[idxTujuan] && dist[u] != MAX_DIST && dist[u] + currentJalan->info.panjang < dist[idxTujuan]) {
                dist[idxTujuan] = dist[u] + currentJalan->info.panjang;
                previous[idxTujuan] = u;
            }
            currentJalan = currentJalan->nextJalan;
        }
    }

    return dist[dstIndex];
}

string getShortestPath(int dstIndex, int previous[], string gedung[]) {
    string path = gedung[dstIndex];
    int current = dstIndex;
    while (previous[current] != -1) {
        current = previous[current];
        path = gedung[current] + " -> " + path;
    }
    return path;
}

void fastTestRoute(mapsKampus &G, string src, string dst) {

    int numGedung = 0;
    string gedung[MAX_GEDUNG];
    adrGedung gedungArray[MAX_GEDUNG];

    int previous[MAX_GEDUNG];
    int dstIndex = -1;
    int shortestDistance = calculateShortestDistance(G, src, dst, dstIndex, previous, gedung, gedungArray, numGedung);

    if (shortestDistance == -1) {
        return; // Gedung tidak ditemukan
    }

    if (shortestDistance == MAX_DIST) {
        cout << "Tidak ada jalur antara " << src << " dan " << dst << endl;
    } else {
        string shortestPath = getShortestPath(dstIndex, previous, gedung);

        cout << "Panjang jalur terpendek: " << shortestDistance << " meter." << endl;
        cout << "Jalur yang dilalui: " << shortestPath << endl;
    }
}

void estimateTime(mapsKampus &G, string kendaraan){
    int dstIndex =-1, numGedung =0;
    float kecepatan;
    int previous[MAX_GEDUNG];
    string gedung[MAX_GEDUNG];
    adrGedung gedungArray[MAX_GEDUNG];
    float jarak = calculateShortestDistance(G, "Gate_1", "MSU", dstIndex, previous, gedung, gedungArray, numGedung);
    if(kendaraan == "jalan_kaki"){
        kecepatan = 5.0;
        cout << "Perkiraan sampe " <<(jarak/(kecepatan*1000.0))*60.0<< " menit";
    }else if(kendaraan == "beam") {
        kecepatan = 15.0;
        cout << "Perkiraan sampe " <<(jarak/(kecepatan*1000.0))*60.0<< " menit";
    }else {
        cout <<"[error]pilihan tidak valid" << endl;
    }
};

void printGraph(mapsKampus &G) {
    // Mencetak graf gedung dan jalan dalam bentuk ASCII
    adrGedung currentGedung = G.firstGedung;

    cout << "===== VISUALISASI GRAF KAMPUS =====\n";
    while (currentGedung != nullptr) {
        cout << "Gedung: " << currentGedung->namaGedung << endl;
        adrJalan currentJalan = currentGedung->firstJalan;

        while (currentJalan != nullptr) {
            cout << "   |\n";
            cout << "   |==> [" << currentJalan->info.namaJalan << "]\n";
            cout << "       Tujuan: " << currentJalan->info.gedungTujuan << endl;
            cout << "       Panjang: " << currentJalan->info.panjang << " meter" << endl;
            currentJalan = currentJalan->nextJalan;
        }

        cout << "\n";
        cout << "-----------------------------------\n";
        currentGedung = currentGedung->nextGedung;
    }
}

void gedungTerdekat(mapsKampus &G, string gedung){
   adrGedung dataGedung = searchGedung(G, gedung);
    adrJalan firstJalan = dataGedung->firstJalan;
    while (firstJalan != NULL){
        cout << "--->"<<firstJalan->info.gedungTujuan << endl;
        firstJalan = firstJalan->nextJalan;
    }
};
