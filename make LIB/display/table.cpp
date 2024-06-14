#include <iostream>
#include <sstream>

using namespace std;

struct TiketPaketEksklusif {
    int id;
    string jenis;
    double harga;
};

class PaketEksklusif {
private:
    TiketPaketEksklusif tiketArray[100];
    int jumlahTiket;

public:
    PaketEksklusif() : jumlahTiket(0) {}

    void tambahTiket(int id, const string& tiketPaketEksklusif, double hargaPaketEksklusif) {
        TiketPaketEksklusif tiketBaru = { id, tiketPaketEksklusif, hargaPaketEksklusif };
        tiketArray[jumlahTiket++] = tiketBaru;
    }

    void tampilkanPaket() const {
        cout << "\nIsi Paket Eksklusif:\n";
        for (int i = 0; i < jumlahTiket; ++i) {
            cout << "ID: " << tiketArray[i].id << ", Jenis: " << tiketArray[i].jenis << ", Harga: " << tiketArray[i].harga << endl;
        }
    }

    double getHargaByNomor(int nomor) const {
        if (nomor >= 1 && nomor <= jumlahTiket) {
            return tiketArray[nomor - 1].harga;
        }
        return -1.0;
    }
};

string format(double price) {
    stringstream ss;
    ss << fixed << price;
    return ss.str();
}

void MenuPaketEksklusif(int JumlahPaketEksklusif, string tiketPaketEksklusif[], double hargaPaketEksklusif[]) {
    cout << "=====Paket Ekslusif=====" << endl << endl;
    for (int i = 0; i < JumlahPaketEksklusif; i++) {
        cout << i + 1 << ". " << tiketPaketEksklusif[i] << " \t Rp." << format(hargaPaketEksklusif[i]) << endl;
    }
    cout << "=========================" << endl << endl;
}

int main() {
    PaketEksklusif paket;
    int JumlahPaketEksklusif = 2;
    string tiketPaketEksklusif[JumlahPaketEksklusif] = { "Pantai + hotel + Guide", "Pegunungan + guide +villa" };
    double hargaPaketEksklusif[JumlahPaketEksklusif] = { 5000000, 4000000 };
    int pilihan;

    do {
        cout << "\n==============================\n";
        cout << "PILIH MENU:\n";
        cout << "1. Beli TiketPaketEksklusif\n";
        cout << "2. History Pembelian\n";
        cout << "3. Cek Harga TiketPaketEksklusif\n";
        cout << "0. Keluar\n";
        cout << "==============================\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            int id;
            string tiketPaketEksklusif;
            double hargaPaketEksklusif;
MenuPaketEksklusif(JumlahPaketEksklusif, tiketPaketEksklusif, hargaPaketEksklusif);
            int beli;
            cout << "Pilih PaketPaketEksklusif Yang mau Beli 1-2 :";
            cin >> beli;
            for (int i = 0; i < JumlahPaketEksklusif; i++) {
                if (i == beli - 1) {
                    id = rand();
                    tiketPaketEksklusif = tiketPaketEksklusif[i];
                    hargaPaketEksklusif = hargaPaketEksklusif[i];
                    cout << "ID TiketPaketEksklusif: " << id << endl;
                    cout << "Jenis TiketPaketEksklusif: " << tiketPaketEksklusif[i] << endl;
                    cout << "Harga TiketPaketEksklusif: " << hargaPaketEksklusif[i] << endl;
                    cout << "\n Ketik y untuk beli :";
                    char lnjt;
                    cin >> lnjt;
                    if (lnjt == 'y' || lnjt == 'Y') {
                        paket.tambahTiket(id, tiketPaketEksklusif, hargaPaketEksklusif);
                        cout << "TiketPaketEksklusif berhasil disimpan.\n";
                    }
                    else {
                        break;
                    }
                }
            }

            break;
        }
        case 2:
            paket.tampilkanPaket();
            break;
        case 3: {
            int nomor;
            cout << "Masukkan Nomor TiketPaketEksklusif: ";
            cin >> nomor;

            double harga = paket.getHargaByNomor(nomor);
            if (harga != -1.0) {
                cout << "Harga TiketPaketEksklusif dengan Nomor " << nomor << ": " << harga << endl;
            }
            else {
                cout << "Nomor TiketPaketEksklusif tidak valid.\n";
            }
            break;
        }
        case 0:
            cout << "\nProgram Berakhir.\n";
            break;
        default:
            cout << "\nPilihan tidak valid.\n";
            break;
        }
    } while (pilihan != 0);

   // return 0;
}

