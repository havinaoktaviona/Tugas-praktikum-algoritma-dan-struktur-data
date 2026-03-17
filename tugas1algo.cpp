#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// struktur produk
struct produk_baru{
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

produk_baru array_produk[100]; // menyimpan maksimal 100 produk
int jumlah_produk = 0;         // jumlah produk yang tersimpan


// fungsi membandingkan string (seperti strcmp)
int membandingkan_string(char a[], char b[]){

    int i=0;

    while(a[i] != '\0' && b[i] != '\0'){

        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;

        i++;
    }

    if(a[i]=='\0' && b[i]=='\0') return 0;
    if(a[i]=='\0') return -1;

    return 1;
}


// membaca data dari file
void loadFile(){

    FILE *pf;

    pf = fopen("shopease_db.txt","r");

    if(pf == NULL) return;

    while(fscanf(pf,"%[^|]|%[^|]|%lf|%d|%f\n",
        array_produk[jumlah_produk].name,
        array_produk[jumlah_produk].category,
        &array_produk[jumlah_produk].price,
        &array_produk[jumlah_produk].stock,
        &array_produk[jumlah_produk].rating) != EOF){

        jumlah_produk++;
    }

    fclose(pf);
}


// menyimpan data ke file
void menyimpan_data(){

    FILE *pf;

    pf = fopen("shopease_db.txt","w");

    for(int i=0;i<jumlah_produk;i++){

        fprintf(pf,"%s|%s|%.0lf|%d|%.1f\n",
        array_produk[i].name,
        array_produk[i].category,
        array_produk[i].price,
        array_produk[i].stock,
        array_produk[i].rating);
    }

    fclose(pf);
}


// menambah produk

void tambah_produk(){
	
    char ulang;

    do{

        int banyak;

        system("cls");

        cout<<"===== TAMBAH PRODUK =====\n\n";

        cout<<"Berapa produk yang ingin ditambahkan : ";
        cin>>banyak;

        cin.ignore(1000,'\n');

        if(jumlah_produk + banyak > 100){
            cout<<"Kapasitas katalog penuh!\n";
            system("pause");
            return;
        }

        for(int i=0;i<banyak;i++){

            cout<<"\nProduk ke-"<<i+1<<endl;

            cout<<"Nama Produk : ";
            cin.getline(array_produk[jumlah_produk].name,60);

            cout<<"Kategori : ";
            cin.getline(array_produk[jumlah_produk].category,30);

            cout<<"Harga : ";
            cin>>array_produk[jumlah_produk].price;

            cout<<"Stok : ";
            cin>>array_produk[jumlah_produk].stock;

            cout<<"Rating : ";
            cin>>array_produk[jumlah_produk].rating;

            cin.ignore(1000,'\n');

            jumlah_produk++;
        }

        cout<<"\nProduk berhasil ditambahkan dan disimpan di file\n";

        cout<<"Masih ingin tambah produk? (y/t) : ";
        cin>>ulang;

        cin.ignore(1000,'\n');

    }while(ulang=='y');

}


// bubble sort berdasarkan nama
void bubblesort(){

    produk_baru temp;

    for(int i=0;i<jumlah_produk-1;i++){

        for(int j=0;j<jumlah_produk-i-1;j++){

            if(membandingkan_string(array_produk[j].name,array_produk[j+1].name) > 0){

                temp = array_produk[j];
                array_produk[j] = array_produk[j+1];
                array_produk[j+1] = temp;
            }
        }
    }
}


// quick sort berdasarkan rating
int partition(int low,int high){

    float pivot = array_produk[high].rating;

    int i = low-1;

    produk_baru temp;

    for(int j=low;j<high;j++){

        if(array_produk[j].rating > pivot){

            i++;

            temp=array_produk[i];
            array_produk[i]=array_produk[j];
            array_produk[j]=temp;
        }
    }

    temp=array_produk[i+1];
    array_produk[i+1]=array_produk[high];
    array_produk[high]=temp;

    return i+1;
}

void quick_sort(int low,int high){

    if(low<high){

        int pi=partition(low,high);

        quick_sort(low,pi-1);
        quick_sort(pi+1,high);
    }
}


// menampilkan produk
void tampil_produk(){
	
	if(jumlah_produk==0){
		cout << "Belum ada produk dalam katalog\n";
		system("pause");
		return;
}

    char kembali;

    do{

        int pilih;

        system("cls");

        cout<<"===== TAMPIL PRODUK =====\n";
        cout<<"1. Urut Nama (Bubble Sort ASC)\n";
        cout<<"2. Urut Rating (Quick Sort DESC)\n";
        cout<<"Pilih : ";
        cin>>pilih;

        if(pilih==1) bubblesort();
        else if(pilih==2) quick_sort(0,jumlah_produk-1);
        else{
            cout<<"Pilihan salah\n";
            system("pause");
            continue;
        }

        system("cls");

        cout<<"===========================================================\n";
        cout<<"No  Nama Produk           Kategori     Harga    Stok Rating\n";
        cout<<"===========================================================\n";

        for(int i=0;i<jumlah_produk;i++){

            printf("%-3d %-20s %-12s %-8.0lf %-5d %.1f\n",
            i+1,
            array_produk[i].name,
            array_produk[i].category,
            array_produk[i].price,
            array_produk[i].stock,
            array_produk[i].rating);
        }

        cout<<"===========================================================\n";

        cout<<"\nKembali ke menu tampil? (y/t) : ";
        cin>>kembali;

    }while(kembali=='t');

}


// mencari produk
void cari_produk(){

    char kembali;

    do{

        char cari[60];
        bool ketemu=false;

        system("cls");

        cin.ignore(1000,'\n');

        cout<<"Masukkan nama produk : ";
        cin.getline(cari,60);

        for(int i=0;i<jumlah_produk;i++){

            if(membandingkan_string(cari,array_produk[i].name)==0){

                cout<<"\nProduk ditemukan\n";

                cout<<"Nama : "<<array_produk[i].name<<endl;
                cout<<"Kategori : "<<array_produk[i].category<<endl;
                cout<<"Harga : "<<array_produk[i].price<<endl;
                cout<<"Stok : "<<array_produk[i].stock<<endl;
                cout<<"Rating : "<<array_produk[i].rating<<endl;

                ketemu=true;
                break;
            }
        }

        if(!ketemu){

            cout<<"\nProduk tidak ditemukan\n";
        }

        cout<<"\nCari lagi? (y/t) : ";
        cin>>kembali;

    }while(kembali=='y');

}


// program utama
int main(){

    int menu;

    loadFile();

    do{

        system("cls");

        cout<<"==============================\n";
        cout<<"   SHOPEASE E-COMMERS\n";
        cout<<"==============================\n";

        cout<<"1. Tambah Produk\n";
        cout<<"2. Tampilkan Produk\n";
        cout<<"3. Cari Produk\n";
        cout<<"4. Keluar\n";

        cout<<"====================================\n";
        cout<<"Pilih : ";
        cin>>menu;

        switch(menu){

            case 1: tambah_produk(); break;

            case 2: tampil_produk(); break;

            case 3: cari_produk(); break;

            case 4:
            menyimpan_data();
            cout<<"\nTerima kasih telah mengunjungi shopEase. semoga diberi nilai bagus ole aslab:)\n";
            break;

            default:
            cout<<"Menu tidak tersedia\n";
            system("pause");
        }

    }while(menu!=4);

}
