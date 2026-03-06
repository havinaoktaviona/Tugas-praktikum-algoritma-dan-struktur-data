#include <iostream>
using namespace std;

//menampilkan semua data nama mahasiswa
void tampilData(string namaMahasiswa[], int jumlahMahasiswa) // fungsi untuk menampilkan data nama mahasiswa
{
    for (int i = 0; i < jumlahMahasiswa; i++) // perulangan menampilkan semua data array
    {
        cout << namaMahasiswa[i] << endl; 
    }
}

//bubble sort untuk mengurutkan nama secara ascending
void bubblesort(string namaMahasiswa[], int jumlahMahasiswa)
{
    for(int i = 0; i < jumlahMahasiswa - 1; i++) // perulangan proses sorting
    {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) // membandingkan dua data yang bersebelahan
        {
            if(namaMahasiswa[j] > namaMahasiswa[j+1])
            {
                string temp = namaMahasiswa[j]; // menyimpan sementara nilai nama mahasiswa
                namaMahasiswa[j] = namaMahasiswa[j+1]; // menukar posisi dengan data berikutnya
                namaMahasiswa[j+1] = temp; // mengembalikan nilai sementara
            }
        }
    }
}

// quick sort mengurutkan data secara descending
void quick_sort(string namaMahasiswa[], int awal, int akhir)
{
    int low = awal; // index awal array
    int high = akhir; // index akhir array

    string pivot = namaMahasiswa[(awal + akhir) / 2]; //menentukan pivot dari tengah array

    do
    {
        while(namaMahasiswa[low] > pivot) //mencari data yang lebih kecil dari pivot
            low++; // maju ke index berikutnya

        while(namaMahasiswa[high] < pivot) // mencari data yang lebih besar dari pivot
            high--; // mundur ke index sebelumnya

        if(low <= high) // jika posisi low belum melewati high maka tukar data
        {
            string temp = namaMahasiswa[low]; // menyimpan sementara
            namaMahasiswa[low] = namaMahasiswa[high]; // menukar posisi data
            namaMahasiswa[high] = temp; // mengembalikan nilai sementara

            low++;
            high--;
        }

    } while(low <= high); // perulangan selama low belum melewati high

    if(awal < high) // rekursi bagian kiri array
        quick_sort(namaMahasiswa, awal, high);

    if(low < akhir) // rekursi bagian kanan array
        quick_sort(namaMahasiswa, low, akhir);
}

int main()
{
    string namaMahasiswa[100]; 
    int totalMahasiswa = 0;    
    char pilihUlang;

    do // perulangan program user ingin melakukan input data
    {
        int jumlahMahasiswa;

        cout << "Masukkan jumlah mahasiswa: ";
        cin >> jumlahMahasiswa;

        cout << "Masukkan nama mahasiswa:" << endl;

        for(int i = 0; i < jumlahMahasiswa; i++)
        {
            cin >> ws; // membersihkan sisa enter dari input sebelumnya
            getline(cin, namaMahasiswa[totalMahasiswa]); // menyimpan nama ke array
            totalMahasiswa++; // menambah jumlah total mahasiswa
        }

        cout << "\nData sebelum diurutkan:" << endl;
        tampilData(namaMahasiswa, totalMahasiswa);

        bubblesort(namaMahasiswa, totalMahasiswa); // memanggil fungsi bubble sorting
        cout << "\nData setelah diurutkan (Bubble Sort Ascending):" << endl;
        tampilData(namaMahasiswa, totalMahasiswa); // menampilkan data hasil bubble sort

        quick_sort(namaMahasiswa, 0, totalMahasiswa-1); // memanggil quick sort
        cout << "\nData setelah diurutkan (Quick Sort Descending):" << endl;
        tampilData(namaMahasiswa, totalMahasiswa); // menampilkan data hasil quick sort

        cout << "\nApakah ingin menginput nama mahasiswa lagi? (y/t): ";
        cin >> pilihUlang;

    } while(pilihUlang == 'y' || pilihUlang == 'Y'); // jika "y" maka program akan mengulang

    cout << "\nProgram selesai." << endl;
    
    return 0;
}
