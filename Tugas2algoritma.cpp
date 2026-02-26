#include <iostream>
using namespace std;

struct Buku {
    string nama;
    int harga;
};

int main() {

    Buku buku[6] = {
        {"algoritma pemrograman", 50000},
        {"bisnis manajemen", 60000},
        {"dasar-dasar perminyakan", 45000},
        {"geologi dasar", 70000},
        {"harry potter", 65000},
        {"", 0}   // sentinel
    };

    string cari, input;
    bool found;
    char ulang = 'y';

    do {
        found = false;

        cout << "Masukkan nama buku yang ingin anda cari: ";
        getline(cin, cari);

        cout << "Pilih metode pencarian:" << endl;
        cout << "1. Sequential Search" << endl;
        cout << "2. Binary Search" << endl;
        cout << "Pilihan: ";
        getline(cin, input);

        if (input[0] == '1') {

            cout << "Pilih jenis Sequential Search: " << endl;
            cout << "1. Non Sentinel" << endl;;
            cout << "2. Sentinel" << endl;
            cout << "Pilihan: ";
            getline(cin, input);

            if (input[0] == '1') {
                int i = 0;

                while (i < 5 && !found) {
                    if (buku[i].nama == cari) {
                        found = true;
                    } else {
                        i++;
                    }
                }

                if (found) {
                    cout << "Buku ditemukan" << endl;
                    cout << "Nama Buku : " << buku[i].nama << endl;
                    cout << "Harga     : Rp " << buku[i].harga << endl;
                    cout << "Index     : " << i << endl;
                } else {
                    cout << "Buku tidak ditemukan" << endl;
                }
            }

            else if (input[0] == '2') {
                int i = 0;
                buku[5].nama = cari;

                while (buku[i].nama != cari) {
                    i++;
                }

                if (i < 5) {
                    cout << "Buku ditemukan" << endl;
                    cout << "Nama Buku : " << buku[i].nama << endl;
                    cout << "Harga     : Rp " << buku[i].harga << endl;
                    cout << "Index     : " << i << endl;
                } else {
                    cout << "Buku tidak ditemukan" << endl;
                }
            } else {
                cout << "Pilihan tidak valid" << endl;
            }
        }

        else if (input[0] == '2') {
            int i = 0, j = 4, k;

            while (i <= j && !found) {
                k = (i + j) / 2;

                if (buku[k].nama == cari) {
                    found = true;
                } else if (cari < buku[k].nama) {
                    j = k - 1;
                } else {
                    i = k + 1;
                }
            }

            if (found) {
                cout << "Buku ditemukan" << endl;
                cout << "Nama Buku : " << buku[k].nama << endl;
                cout << "Harga     : Rp " << buku[k].harga << endl;
                cout << "Index     : " << k << endl;
            } else {
                cout << "Buku tidak ditemukan" << endl;
            }
        }

        else {
            cout << "Pilihan tidak valid" << endl;
        }

        cout << "Apakah ingin mencari judul buku yang lain? (y/n): ";
        getline(cin, input);
        ulang = input[0];

    } while (ulang == 'y' || ulang == 'Y');

    cout << "Program selesai babay" << endl;
}
