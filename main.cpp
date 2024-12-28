#include <iostream>
#include "MapsKampus.h"
using namespace std;

int main()
{
    mapsKampus p;
    infoJalan k;
    buildGraph(p);

    // Gedung Gate 1
    k.panjang = 250;
    k.namaJalan = 'A';
    k.gedungTujuan = "Danau";
    addJalan(p, "Gate_1", k);

    k.panjang = 75;
    k.namaJalan = 'B';
    k.gedungTujuan = "TUCH";
    addJalan(p, "Gate_1", k);

    k.panjang = 110;
    k.namaJalan = 'C';
    k.gedungTujuan = "GKU";
    addJalan(p, "Gate_1", k);

    // Gedung TUCH
    k.panjang = 75;
    k.namaJalan = 'B';
    k.gedungTujuan = "Gate_1";
    addJalan(p, "TUCH", k);

    k.panjang = 80;
    k.namaJalan = 'D';
    k.gedungTujuan = "Danau";
    addJalan(p, "TUCH", k);

    k.panjang = 250;
    k.namaJalan = 'E';
    k.gedungTujuan = "Cacuk";
    addJalan(p, "TUCH", k);

    k.panjang = 50;
    k.namaJalan = 'F';
    k.gedungTujuan = "GKU";
    addJalan(p, "TUCH", k);

    // Danau
    k.panjang = 250;
    k.namaJalan = 'A';
    k.gedungTujuan = "Gate_1";
    addJalan(p, "Danau", k);

    k.panjang = 80;
    k.namaJalan = 'D';
    k.gedungTujuan = "TUCH";
    addJalan(p, "Danau", k);

    k.panjang = 125;
    k.namaJalan = 'H';
    k.gedungTujuan = "Cacuk";
    addJalan(p, "Danau", k);

    k.panjang = 230;
    k.namaJalan = 'G';
    k.gedungTujuan = "MSU";
    addJalan(p, "Danau", k);

    // GKU
    k.panjang = 110;
    k.namaJalan = 'C';
    k.gedungTujuan = "Gate_1";
    addJalan(p, "GKU", k);

    k.panjang = 50;
    k.namaJalan = 'F';
    k.gedungTujuan = "TUCH";
    addJalan(p, "GKU", k);

    k.panjang = 100;
    k.namaJalan = 'J';
    k.gedungTujuan = "Cacuk";
    addJalan(p, "GKU", k);

    k.panjang = 50;
    k.namaJalan = 'L';
    k.gedungTujuan = "Asrama_Putri";
    addJalan(p, "GKU", k);

    //Cacuk
    k.panjang = 250;
    k.namaJalan = 'E';
    k.gedungTujuan = "TUCH";
    addJalan(p, "Cacuk", k);

    k.panjang = 125;
    k.namaJalan = 'H';
    k.gedungTujuan = "Danau";
    addJalan(p, "Cacuk", k);

    k.panjang = 100;
    k.namaJalan = 'J';
    k.gedungTujuan = "GKU";
    addJalan(p, "Cacuk", k);

    k.panjang = 110;
    k.namaJalan = 'I';
    k.gedungTujuan = "MSU";
    addJalan(p, "Cacuk", k);


    // MSU
    k.panjang = 230;
    k.namaJalan = 'G';
    k.gedungTujuan = "Danau";
    addJalan(p, "MSU", k);

    k.panjang = 110;
    k.namaJalan = 'I';
    k.gedungTujuan = "Cacuk";
    addJalan(p, "MSU", k);

    k.panjang = 200;
    k.namaJalan = 'K';
    k.gedungTujuan = "Asrama_Putri";
    addJalan(p, "MSU", k);

    // Asrama putri
    k.panjang = 50;
    k.namaJalan = 'L';
    k.gedungTujuan = "GKU";
    addJalan(p, "Asrama_Putri", k);

    k.panjang = 200;
    k.namaJalan = 'K';
    k.gedungTujuan = "MSU";
    addJalan(p, "Asrama_Putri", k);

    bool stop = false;
    int pilihan;
    string lokasi;
    while (!stop) {
        mainMenu();
        cin >> pilihan;
        if(pilihan ==1) {
            printGraph(p);
        }else if (pilihan ==2) {
            fastTestRoute(p, "Gate_1", "MSU");
        }else if(pilihan == 3) {
            cout << "Lokasi anda <<";
            cin >>lokasi;
            cout << "Gedung terdekat dari gedung " << lokasi << endl;
            gedungTerdekat(p, lokasi);
        }else if(pilihan == 4){
            cout << "Lokasi anda<< ";
            cin >> lokasi;
            fastTestRoute(p, lokasi, "MSU");
        }else if(pilihan == 5) {
            cout << "Pilih kendaraan (jalan kaki/beam)"<< endl << "<<";
            cin >> lokasi;
            estimateTime(p, lokasi);
        }else if (pilihan == 6){
            stop = true;
            cout << "Terimakasih"<< endl;
        }else {
            cout << "[error]Masukan pilihan yang valid"<< endl;
        }

    }
}
