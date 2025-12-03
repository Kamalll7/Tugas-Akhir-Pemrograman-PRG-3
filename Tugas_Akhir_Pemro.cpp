#include <bits/stdc++.h>
using namespace std;

// Struct data, disimpan dalam bulan(12) yang berisi vector untuk menampung seluruh data transaksi yang terjadi di bulan tersebut
struct bulan {
    struct transaksidata {
        int tgl;
        string kategori;
        string subkategori;
        long long rupiah;
    };

    vector<transaksidata> catatan; 
};

// Bubble sort data per tanggal secara ascending
void urutkanData(vector<bulan::transaksidata>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool perluTukar = false;
            // Cek Tanggal (Ascending)
            if (data[j].tgl > data[j+1].tgl) {
                perluTukar = true;
            }
            // Jika tanggal sama, cek Kategori
            else if (data[j].tgl == data[j+1].tgl) {
                if (data[j].kategori > data[j+1].kategori) {
                    perluTukar = true;
                }
                // Jika kategori sama, cek Nominal
                else if (data[j].kategori == data[j+1].kategori) {
                    if (data[j].rupiah > data[j+1].rupiah) {
                        perluTukar = true;
                    }
                }
            }
            if (perluTukar) {
                swap(data[j], data[j+1]);
            }
        }
    }
}

// Input pemasukan atau pengeluaran (Pilihan 1)
void inputrupiah(vector<bulan>& manager){
    system("cls");
    int date, month, jumlah;

    cout << "=== INPUT TRANSAKSI ===" << endl;
    cout << "Masukkan Bulan (angka 1-12) : "; 
    cin >> month;
    if (month < 1 || month > 12) {
        cout << "Bulan tidak valid!" << endl;
        system("pause"); return;
    }
    cout << "Masukkan Tanggal            : "; 
    cin >> date;
    
    cout << "Berapa banyak transaksi yang ingin diinput? : ";
    cin >> jumlah;
    cout << "------------------------------------------------" << endl;

    for(int i = 0; i < jumlah; i++) {
        bulan::transaksidata dataBaru;
        dataBaru.tgl = date;

        cout << endl << "Data ke-" << (i+1) << endl;
        cout << "Jenis Transaksi (1. Pemasukan, 2. Pengeluaran): ";
        int pilihan;
        cin >> pilihan;

        if(pilihan == 1){
            dataBaru.kategori = "Pemasukan";
            cout << "Keterangan Pemasukan : ";
            cin >> dataBaru.subkategori;
            cout << "Nominal (Rp)         : ";
            cin >> dataBaru.rupiah;
        }
        else if(pilihan == 2){
            dataBaru.kategori = "Pengeluaran";
            cout << "Keterangan Pengeluaran: ";
            cin >> dataBaru.subkategori;
            cout << "Nominal (Rp)          : ";
            cin >> dataBaru.rupiah;
        } else {
            cout << "Pilihan salah, data dilewati." << endl;
            continue; 
        }
        manager[month-1].catatan.push_back(dataBaru);
    }
    
    urutkanData(manager[month-1].catatan);
    
    cout << endl << "Berhasil menyimpan data!" << endl;
    cout << "Tekan enter untuk kembali.";
    cin.ignore(); cin.get();
}

// Cetak header laporan (Pilihan 2)
void cetakHeader() {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(4) << "NO"
         << "| " << left << setw(15) << "TANGGAL - BULAN"
         << "| " << left << setw(30) << "KATEGORI - SUBKATEGORI"
         << "| " << left << setw(12) << "RUPIAH"
         << "|" << endl;
    cout << "----------------------------------------------------------------------" << endl;
}

// Cetak baris (pilihan 2)
void cetakBaris(int no, int tgl, int bln, string kat, string sub, long long rp) {
    string gabung = kat + " - " + sub;
    string rupiahStr = "Rp." + to_string(rp);
    cout << "| " << left << setw(4)  << no
         << "| " << left << setw(15) << (to_string(tgl) + " - " + to_string(bln))
         << "| " << left << setw(30) << gabung
         << "| " << left << setw(12) << rupiahStr
         << "|" << endl;
}

// Cetak laporan secara terurut ascending (Pilihan 2)
void laporan(vector<bulan>& manager){
    system("cls");
    cout << "=== LAPORAN KEUANGAN ===" << endl;
    cout << "Masukkan Bulan (1-12): ";
    int bulanke; cin >> bulanke;
    if (bulanke < 1 || bulanke > 12) return;

    // Selalu sort sebelum cetak
    urutkanData(manager[bulanke-1].catatan);

    cout << "Dari tanggal : "; int r1; cin >> r1;
    cout << "Sampai tanggal: "; int r2; cin >> r2;

    system("cls");
    cout << "Laporan Bulan " << bulanke << " (Tgl " << r1 << " s/d " << r2 << ")" << endl;
    cetakHeader();

    long long totMasuk = 0, totKeluar = 0;
    int counter = 1;

    for (auto& d : manager[bulanke-1].catatan) {
        if (d.tgl >= r1 && d.tgl <= r2) {
            if (d.kategori == "Pemasukan") totMasuk += d.rupiah;
            else totKeluar += d.rupiah;
            
            cetakBaris(counter++, d.tgl, bulanke, d.kategori, d.subkategori, d.rupiah);
        }
    }

    if (counter == 1) cout << "       Tidak ada data." << endl;
    
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Total Pemasukan   : Rp." << totMasuk << endl;
    cout << "Total Pengeluaran : Rp." << totKeluar << endl;
    cout << "Sisa Saldo        : Rp." << (totMasuk - totKeluar) << endl; 
    
    cout << endl << "Tekan enter kembali...";
    cin.ignore(); cin.get();
}

// Cari data (Pilihan 3)
void cariData(vector<bulan>& manager) {
    system("cls");
    cout << "=== PENCARIAN DATA ===" << endl;
    cout << "1. Cari berdasarkan Tanggal & Bulan Tertentu" << endl;
    cout << "2. Cari Pemasukan/Pengeluaran TERTINGGI" << endl;
    cout << "3. Cari berdasarkan Nominal (Rupiah)" << endl;
    cout << "Pilihan: ";
    int opsi; cin >> opsi;

    // Opsi 1: berdasarkan tanggal dan bulan
    if (opsi == 1) {
        int m, d;
        cout << "Masukkan Bulan (1-12): "; cin >> m;
        cout << "Masukkan Tanggal     : "; cin >> d;
        
        system("cls");
        cout << "Hasil Pencarian Tanggal " << d << " Bulan " << m << endl;
        cetakHeader();
        
        int cnt = 1;
        long long tm = 0, tk = 0;
        if (m >= 1 && m <= 12) {
            // Biar rapi sort lagi
            urutkanData(manager[m-1].catatan); 

            for (auto& data : manager[m-1].catatan) {
                if (data.tgl == d) {
                    if (data.kategori == "Pemasukan") tm += data.rupiah;
                    else tk += data.rupiah;
                    cetakBaris(cnt++, data.tgl, m, data.kategori, data.subkategori, data.rupiah);
                }
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
        cout << "Total di hari ini -> Masuk: Rp." << tm << ", Keluar: Rp." << tk << endl;
    }

    // Opsi 2 : Berdasarkan data tertinggi
    else if (opsi == 2) {
        cout << endl << "Cari Tertinggi untuk: " << endl;
        cout << "1. Pemasukan" << endl;
        cout << "2. Pengeluaran" << endl;
        cout << "Pilih: ";
        int tipe; cin >> tipe;
        string targetKat = (tipe == 1) ? "Pemasukan" : "Pengeluaran";

        cout << "Lingkup pencarian:" << endl;
        cout << "1. Harian (Cari hari dengan total tertinggi)" << endl;
        cout << "2. Bulanan (Cari bulan dengan total tertinggi)" << endl;
        cout << "Pilih: ";
        int scope; cin >> scope;

        long long maxTotal = -1;
        int bestBulan = -1;
        int bestTanggal = -1; 

        // Opsi Harian
        if (scope == 1) {
            for (int i = 0; i < 12; i++) {
                long long dailySum[32] = {0}; 
                for (auto& data : manager[i].catatan) {
                    if (data.kategori == targetKat) {
                        dailySum[data.tgl] += data.rupiah;
                    }
                }
                for (int t = 1; t <= 31; t++) {
                    if (dailySum[t] > maxTotal) {
                        maxTotal = dailySum[t];
                        bestBulan = i + 1;
                        bestTanggal = t;
                    }
                }
            }
            
            system("cls");
            if (maxTotal <= 0) {
                cout << "Tidak ada data transaksi " << targetKat << "." << endl;
            } else {
                cout << "=== CATATAN " << targetKat << " HARIAN TERTINGGI ===" << endl;
                cout << "Jatuh pada Tanggal " << bestTanggal << " Bulan " << bestBulan << endl;
                cout << "Dengan Total: Rp." << maxTotal << endl << endl;
                cout << "Rincian Transaksi hari tersebut:" << endl;
                
                // Urutkan untuk tampilan rincian
                urutkanData(manager[bestBulan-1].catatan);

                cetakHeader();
                int cnt = 1;
                for (auto& data : manager[bestBulan-1].catatan) {
                    if (data.tgl == bestTanggal && data.kategori == targetKat) {
                        cetakBaris(cnt++, data.tgl, bestBulan, data.kategori, data.subkategori, data.rupiah);
                    }
                }
                cout << "----------------------------------------------------------------------" << endl;
            }
        }
        // Opsi Bulanan
        else if (scope == 2) {
            for (int i = 0; i < 12; i++) {
                long long monthSum = 0;
                for (auto& data : manager[i].catatan) {
                    if (data.kategori == targetKat) {
                        monthSum += data.rupiah;
                    }
                }
                if (monthSum > maxTotal) {
                    maxTotal = monthSum;
                    bestBulan = i + 1;
                }
            }

            system("cls");
            if (maxTotal <= 0) {
                cout << "Tidak ada data transaksi." << endl;
            } else {
                cout << "=== CATATAN " << targetKat << " BULANAN TERTINGGI ===" << endl;
                cout << "Jatuh pada Bulan ke-" << bestBulan << endl;
                cout << "Dengan Total: Rp." << maxTotal << endl << endl;
                cout << "Rincian Transaksi bulan tersebut:" << endl;
                
                urutkanData(manager[bestBulan-1].catatan);

                cetakHeader();
                int cnt = 1;
                for (auto& data : manager[bestBulan-1].catatan) {
                    if (data.kategori == targetKat) {
                        cetakBaris(cnt++, data.tgl, bestBulan, data.kategori, data.subkategori, data.rupiah);
                    }
                }
                cout << "----------------------------------------------------------------------" << endl;
            }
        }
    }

    // Opsi 3 : Berdasarkan nominal
    else if (opsi == 3) {
        cout << endl << "Cari Nominal pada:" << endl;
        cout << "1. Pemasukan" << endl;
        cout << "2. Pengeluaran" << endl;
        cout << "Pilih: ";
        int tipe; cin >> tipe;
        string targetKat = (tipe == 1) ? "Pemasukan" : "Pengeluaran";
        
        cout << "Masukkan Nominal yang dicari: Rp.";
        long long cariRp; cin >> cariRp;

        system("cls");
        cout << "Hasil Pencarian " << targetKat << " dengan nominal Rp." << cariRp << endl;
        cetakHeader();

        int cnt = 1;
        bool found = false;
        
        for (int i = 0; i < 12; i++) {
            urutkanData(manager[i].catatan);
            
            for (auto& data : manager[i].catatan) {
                if (data.kategori == targetKat && data.rupiah == cariRp) {
                    cetakBaris(cnt++, data.tgl, (i+1), data.kategori, data.subkategori, data.rupiah);
                    found = true;
                }
            }
        }
        cout << "----------------------------------------------------------------------" << endl;
        if (!found) cout << "Data tidak ditemukan." << endl;
    }

    cout << endl << "Tekan enter untuk kembali...";
    cin.ignore(); cin.get();
}

vector<bulan> tahun(12);

int main(){
    while(true){
        system("cls");
        cout << "======================[ SISTEM MANAJEMEN KEUANGAN ]======================" << endl << endl;
        cout << "Pilihan: " << endl;
        cout << "1. Input Transaksi" << endl;
        cout << "2. Tampilkan Laporan" << endl;
        cout << "3. Cari Data" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu: ";
        int pilihan;
        cin >> pilihan;
        
        if(pilihan == 1){
            inputrupiah(tahun);
        } else if(pilihan == 2){
            laporan(tahun);
        } else if(pilihan == 3){
            cariData(tahun);
        } else if(pilihan == 4){
            break;
        }
    }
    return 0;
}