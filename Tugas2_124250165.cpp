// ============================================================
//   SISTEM PARKIR INAP BANDARA GSA
//   Struktur Data: BST (PTB), Stack, Queue
// ============================================================

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int KAPASITAS_PARKIR = 5;

// ============================================================
// NODE BST
// ============================================================
struct NodeBST {
    string nomorPolisi;
    string namaPemilik;
    string status;
    NodeBST* kiri;
    NodeBST* kanan;

    NodeBST(string nopol, string nama) {
        nomorPolisi = nopol;
        namaPemilik = nama;
        status = "Di Luar Parkiran";
        kiri = nullptr;
        kanan = nullptr;
    }
};

// ============================================================
// NODE STACK
// ============================================================
struct NodeStack {
    string jenis;       // "masuk" atau "keluar"
    string nomorPolisi;
    NodeStack* berikutnya;

    NodeStack(string j, string nopol) {
        jenis = j;
        nomorPolisi = nopol;
        berikutnya = nullptr;
    }
};

// ============================================================
// NODE QUEUE
// ============================================================
struct NodeQueue {
    string nomorPolisi;
    NodeQueue* berikutnya;

    NodeQueue(string nopol) {
        nomorPolisi = nopol;
        berikutnya = nullptr;
    }
};

// ============================================================
// BST (Pohon Telusur Biner)
// ============================================================
class BST {
private:
    NodeBST* akar;

    NodeBST* tambahRekursif(NodeBST* node, string nopol, string nama, bool& berhasil) {
        if (node == nullptr) {
            berhasil = true;
            return new NodeBST(nopol, nama);
        }
        if (nopol < node->nomorPolisi)
            node->kiri = tambahRekursif(node->kiri, nopol, nama, berhasil);
        else if (nopol > node->nomorPolisi)
            node->kanan = tambahRekursif(node->kanan, nopol, nama, berhasil);
        else {
            cout << "Kendaraan dengan nomor polisi tersebut sudah ada!" << endl;
            berhasil = false;
        }
        return node;
    }

    NodeBST* cariRekursif(NodeBST* node, string nopol) {
        if (node == nullptr) return nullptr;
        if (nopol == node->nomorPolisi) return node;
        if (nopol < node->nomorPolisi) return cariRekursif(node->kiri, nopol);
        return cariRekursif(node->kanan, nopol);
    }

    NodeBST* minNode(NodeBST* node) {
        NodeBST* curr = node;
        while (curr->kiri != nullptr) curr = curr->kiri;
        return curr;
    }

    NodeBST* hapusRekursif(NodeBST* node, string nopol, bool& berhasil) {
        if (node == nullptr) return nullptr;
        if (nopol < node->nomorPolisi) {
            node->kiri = hapusRekursif(node->kiri, nopol, berhasil);
        } else if (nopol > node->nomorPolisi) {
            node->kanan = hapusRekursif(node->kanan, nopol, berhasil);
        } else {
            berhasil = true;
            if (node->kiri == nullptr) {
                NodeBST* tmp = node->kanan;
                delete node;
                return tmp;
            } else if (node->kanan == nullptr) {
                NodeBST* tmp = node->kiri;
                delete node;
                return tmp;
            }
            NodeBST* successor = minNode(node->kanan);
            node->nomorPolisi = successor->nomorPolisi;
            node->namaPemilik = successor->namaPemilik;
            node->status      = successor->status;
            node->kanan = hapusRekursif(node->kanan, successor->nomorPolisi, berhasil);
        }
        return node;
    }

    void inorder(NodeBST* node, int& nomor) {
        if (node != nullptr) {
            inorder(node->kiri, nomor);
            cout << nomor++ << "\t"
                 << node->nomorPolisi << "\t\t"
                 << node->namaPemilik << "\t\t"
                 << node->status << endl;
            inorder(node->kanan, nomor);
        }
    }

    int hitungParkir(NodeBST* node) {
        if (node == nullptr) return 0;
        int count = (node->status == "Di Parkiran") ? 1 : 0;
        return count + hitungParkir(node->kiri) + hitungParkir(node->kanan);
    }

public:
    BST() { akar = nullptr; }

    void tambah(string nopol, string nama) {
        bool berhasil = false;
        akar = tambahRekursif(akar, nopol, nama, berhasil);
        if (berhasil)
            cout << "Data kendaraan berhasil ditambahkan" << endl;
    }

    NodeBST* cari(string nopol) {
        return cariRekursif(akar, nopol);
    }

    void tampilSemua() {
        if (akar == nullptr) {
            cout << "Belum ada data kendaraan." << endl;
            return;
        }
        cout << "\nNo\tNomor Polisi\t\tNama Pemilik\t\tStatus" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        int nomor = 1;
        inorder(akar, nomor);
        cout << endl;
    }

    void hapus(string nopol) {
        bool berhasil = false;
        akar = hapusRekursif(akar, nopol, berhasil);
        if (berhasil)
            cout << "Data kendaraan berhasil dihapus" << endl;
        else
            cout << "Kendaraan tidak ditemukan!" << endl;
    }

    int hitungDiParkiran() {
        return hitungParkir(akar);
    }
};

// ============================================================
// STACK (Linked List)
// ============================================================
class Stack {
private:
    NodeStack* top;

public:
    Stack() { top = nullptr; }

    void push(string jenis, string nopol) {
        NodeStack* baru = new NodeStack(jenis, nopol);
        baru->berikutnya = top;
        top = baru;
    }

    NodeStack* pop() {
        if (top == nullptr) return nullptr;
        NodeStack* tmp = top;
        top = top->berikutnya;
        tmp->berikutnya = nullptr;
        return tmp;
    }

    bool kosong() { return top == nullptr; }
};

// ============================================================
// QUEUE (Linked List)
// ============================================================
class Queue {
private:
    NodeQueue* depan;
    NodeQueue* belakang;

public:
    Queue() { depan = nullptr; belakang = nullptr; }

    void enqueue(string nopol) {
        NodeQueue* baru = new NodeQueue(nopol);
        if (belakang == nullptr) {
            depan = belakang = baru;
        } else {
            belakang->berikutnya = baru;
            belakang = baru;
        }
    }

    string dequeue() {
        if (depan == nullptr) return "";
        NodeQueue* tmp = depan;
        string nopol = tmp->nomorPolisi;
        depan = depan->berikutnya;
        if (depan == nullptr) belakang = nullptr;
        delete tmp;
        return nopol;
    }

    bool kosong() { return depan == nullptr; }

    void tampilAntrian() {
        if (kosong()) {
            cout << "Antrian kosong" << endl;
            return;
        }
        NodeQueue* curr = depan;
        while (curr != nullptr) {
            cout << curr->nomorPolisi << " menunggu giliran masuk parkiran" << endl;
            curr = curr->berikutnya;
        }
    }
};

// ============================================================
// SISTEM PARKIR
// ============================================================
class SistemParkir {
private:
    BST bst;
    Stack stack;
    Queue queue;

    string keHurufBesar(string str) {
        for (char& c : str) c = toupper(c);
        return str;
    }

public:
    void tambahKendaraan(string nopol, string nama) {
        bst.tambah(keHurufBesar(nopol), nama);
    }

    void tampilKendaraan() {
        bst.tampilSemua();
    }

    void kendaraanMasuk(string nopol) {
        nopol = keHurufBesar(nopol);
        NodeBST* node = bst.cari(nopol);
        if (node == nullptr) {
            cout << "Kendaraan tidak ditemukan!" << endl;
            return;
        }
        if (node->status == "Di Parkiran") {
            cout << "Kendaraan sudah berada di dalam parkiran!" << endl;
            return;
        }
        if (bst.hitungDiParkiran() < KAPASITAS_PARKIR) {
            node->status = "Di Parkiran";
            stack.push("masuk", nopol);
            cout << "Kendaraan berhasil masuk" << endl;
        } else {
            queue.enqueue(nopol);
            cout << "Parkiran penuh, kendaraan masuk ke dalam antrian" << endl;
        }
    }

    void kendaraanKeluar(string nopol) {
        nopol = keHurufBesar(nopol);
        NodeBST* node = bst.cari(nopol);
        if (node == nullptr) {
            cout << "Kendaraan tidak ditemukan!" << endl;
            return;
        }
        if (node->status != "Di Parkiran") {
            cout << "Kendaraan tidak sedang berada di parkiran!" << endl;
            return;
        }
        node->status = "Di Luar Parkiran";
        stack.push("keluar", nopol);
        cout << "Kendaraan berhasil keluar" << endl;

        if (!queue.kosong()) {
            string nopolAntrian = queue.dequeue();
            NodeBST* nodeAntrian = bst.cari(nopolAntrian);
            if (nodeAntrian != nullptr) {
                nodeAntrian->status = "Di Parkiran";
                stack.push("masuk", nopolAntrian);
            }
            cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian" << endl;
        }
    }

    void hapusKendaraan(string nopol) {
        bst.hapus(keHurufBesar(nopol));
    }

    void undo() {
        NodeStack* aksi = stack.pop();
        if (aksi == nullptr) {
            cout << "Tidak ada aksi untuk di-undo" << endl;
            return;
        }
        NodeBST* node = bst.cari(aksi->nomorPolisi);
        if (aksi->jenis == "masuk") {
            if (node != nullptr) node->status = "Di Luar Parkiran";
            cout << "Undo: Kendaraan keluar dari parkiran" << endl;
        } else {
            if (node != nullptr) node->status = "Di Parkiran";
            cout << "Undo: Kendaraan masuk kembali ke parkiran" << endl;
        }
        delete aksi;
    }

    void tampilAntrian() {
        queue.tampilAntrian();
    }
};

// ============================================================
// MENU CLI
// ============================================================
void tampilMenu() {
    system("cls");
    cout << "\n=============================================" << endl;
    cout << "      SISTEM PARKIR INAP BANDARA GSA" << endl;
    cout << "=============================================" << endl;
    cout << "  1. Tambah Data Kendaraan" << endl;
    cout << "  2. Tampil Semua Kendaraan" << endl;
    cout << "  3. Catat Kendaraan Masuk" << endl;
    cout << "  4. Catat Kendaraan Keluar" << endl;
    cout << "  5. Hapus Data Kendaraan" << endl;
    cout << "  6. Undo Aksi Terakhir" << endl;
    cout << "  7. Tampil Antrian Kendaraan" << endl;
    cout << "  0. Keluar" << endl;
    cout << "=============================================" << endl;
    cout << "Pilih menu: ";
}

int main() {
    SistemParkir sistem;
    int pilihan;
    string nopol, nama;

    do {
        tampilMenu();
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\n--- Tambah Data Kendaraan ---" << endl;
            cout << "Nomor Polisi (contoh: B 1234 ABC): ";
            getline(cin, nopol);
            cout << "Nama Pemilik: ";
            getline(cin, nama);
            if (!nopol.empty() && !nama.empty())
                sistem.tambahKendaraan(nopol, nama);
            else
                cout << "Input tidak boleh kosong!" << endl;

        } else if (pilihan == 2) {
            cout << "\n--- Daftar Kendaraan ---" << endl;
            sistem.tampilKendaraan();

        } else if (pilihan == 3) {
            cout << "\n--- Catat Kendaraan Masuk ---" << endl;
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            if (!nopol.empty())
                sistem.kendaraanMasuk(nopol);
            else
                cout << "Input tidak boleh kosong!" << endl;

        } else if (pilihan == 4) {
            cout << "\n--- Catat Kendaraan Keluar ---" << endl;
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            if (!nopol.empty())
                sistem.kendaraanKeluar(nopol);
            else
                cout << "Input tidak boleh kosong!" << endl;

        } else if (pilihan == 5) {
            cout << "\n--- Hapus Data Kendaraan ---" << endl;
            cout << "Nomor Polisi: ";
            getline(cin, nopol);
            if (!nopol.empty())
                sistem.hapusKendaraan(nopol);
            else
                cout << "Input tidak boleh kosong!" << endl;

        } else if (pilihan == 6) {
            cout << "\n--- Undo Aksi Terakhir ---" << endl;
            sistem.undo();

        } else if (pilihan == 7) {
            cout << "\n--- Antrian Kendaraan ---" << endl;
            sistem.tampilAntrian();

        } else if (pilihan == 0) {
            cout << "\nTerima kasih telah menggunakan Sistem Parkir Bandara GSA!" << endl;

        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
        }

    } while (pilihan != 0);

    return 0;
}
