#include <iostream>
using namespace std;
int main()
{
	// membuat array int dengan panjang bebas dan nilai yang bebas
	int h = 6; 
	int halaman[6] = {6,12,18,24,30,46};
	int *ptr = halaman; // pointer menunjuk ke alamat array
	
	// mengoutputkan isi nilai array pada int halaman
	cout << "Isi nilai dari array :" ;
	for (int i = 0; i<h; i++)
{
	cout << *(ptr + i) << " ";
}
	cout << endl << endl; // ini saya kasih karena tulisan maksimal kesamping jadi saya beri spasi aja
	
	// mencari nilai maksimal dan minimal tanpa index
	int maksimal = *ptr;
	int minimal = *ptr;
	for (int i = 0; i < h; i++)
	{
		
		if (*(ptr + i) > maksimal) maksimal = *(ptr + i); // mencari nilai maksimal
		if (*(ptr + i) > minimal) minimal = *(ptr + i); // mencari nilai minimal
	}
		// mencari nominal rata-rata
		int jumlah = 0;
		for (int i = 0; i<h; i++)
	{
		jumlah = jumlah + *(ptr + i);
	}
		float rata_rata = (float)jumlah;
		
		// mengoutputkan seluruh hasil dari maksimal, minimal dan rata-rata
		cout << "Nominal Maksimal :" << maksimal << endl;
		cout << "Nominal Minimal :" << minimal << endl;
		cout << "Nominal Rata-rata :" << rata_rata << endl;
}
		
