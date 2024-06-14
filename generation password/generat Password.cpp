#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include "libpass.h"

using namespace std;

int main() {
 	string garis="|===============================================================|\n";
		cout<<garis;
		cout<<"|\t\tSelamat Data di Pembuatan Sempel Password\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
				cout<<"|\t\t\tInstagram:aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tFacebook :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tGithub   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tLinked   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tWebsite  :AditiyaSubakti.com\t\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
		cout<<"|\t\t*dibuat Oleh Aditiya Subakti\t\t\t|\n";
		cout<<garis;
    
    int start;
    int end;
    string nfile ;// default value
    string modenya; // default value
    
    string nama_PD; // posisi nama di Depan
    string nama_PB; // posisi nama di Belakang
    string nama_PB_And_PD; // ya atau tidak mode posisi nama di depan dan di belakang
    string dari_tahun; // dari tahun
    string sampai_tahun; // sampai tahun
    string tbh_tgl; // ya atau tidak opsi tambahan jika tidak mau ada nama nya saja

    cout << "Masukkan jumlah angka default [1 9]: ";
    cin >> start >> end;
    cin.ignore(); // ignore the newline character after reading integers

    cout << "Masukkan nama file default [pass.txt]: ";
    getline(cin, nfile);
    
    cout << "Masukkan modenya default [in]: ";
    getline(cin, modenya);

    cout << "Masukkan nama posisi depan: ";
    getline(cin, nama_PD);
    
    cout << "Masukkan nama posisi belakang: ";
    getline(cin, nama_PB);
    
    cout << "Apakah ingin menggunakan nama di depan dan belakang (ya/tidak)? ";
    getline(cin, nama_PB_And_PD);
    
    cout << "Masukkan tahun mulai: ";
    getline(cin, dari_tahun);
    
    cout << "Masukkan tahun akhir: ";
    getline(cin, sampai_tahun);
    
    cout << "Apakah ingin menambahkan tanggal,bulan,dan tahun lahir aja (ya/tidak)? ";
    getline(cin, tbh_tgl);

    PasswordMake(start, end, nfile, modenya, nama_PD, nama_PB, nama_PB_And_PD, dari_tahun, sampai_tahun, tbh_tgl);
  	MessageBox(NULL, "Password Berhasil Di Buat!", "SUCCESS", MB_OK);
    return 0;
}

