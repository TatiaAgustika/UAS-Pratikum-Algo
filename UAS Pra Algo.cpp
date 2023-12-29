#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

// Struktur untuk menyimpan informasi kamar hotel
struct Kamar {
    int nomorKamar;
    bool tersedia;
    std::string namaTamu;
    std::string tanggalCheckIn;
    std::string tanggalCheckOut;
    std::vector<std::string> pesanan; // Menyimpan pesanan makanan/minuman
};

// Struktur untuk menyimpan informasi menu hotel
struct Menu {
    std::string namaMenu;
    double harga;
};

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    std::cout << "================ Selamat Datang di Hotelaku ^_^ ================\n";
    std::cout << "1. Tampilkan Kamar Tersedia\n";
    std::cout << "2. Pesan Kamar\n";
    std::cout << "3. Lihat Daftar Tamu\n";
    std::cout << "4. Pesan Makan/Minum\n";
    std::cout << "5. Check Out\n";
    std::cout << "0. Keluar\n";
    std::cout << "================================================================\n";
    std::cout << "Pilih opsi: ";
}

// Fungsi untuk pesan kamar
void pesanKamar(std::vector<Kamar>& daftarKamar) {
    int nomorKamar;
    std::cout << "Masukkan nomor kamar yang ingin dipesan: ";
    std::cin >> nomorKamar;

    for (auto& kamar : daftarKamar) {
        if (kamar.nomorKamar == nomorKamar && kamar.tersedia) {
            std::cout << "Masukkan nama tamu: ";
            std::cin.ignore();
            std::getline(std::cin, kamar.namaTamu);
            std::cout << "Masukkan tanggal check-in (format: YYYY-MM-DD): ";
            std::cin >> kamar.tanggalCheckIn;
            std::cout << "Masukkan tanggal check-out (format: YYYY-MM-DD): ";
            std::cin >> kamar.tanggalCheckOut;
            kamar.tersedia = false;
            std::cout << "Pemesanan kamar oleh " << kamar.namaTamu << " berhasil!\n";
            std::cout << "Check-in: " << kamar.tanggalCheckIn << "\n";
            std::cout << "Check-out: " << kamar.tanggalCheckOut << "\n";
            return;
        }
    }

    std::cout << "Kamar tidak tersedia atau nomor kamar tidak valid.\n";
}

// Fungsi untuk menampilkan kamar yang tersedia dan belum dipesan
void tampilkanKamarTersedia(const std::vector<Kamar>& daftarKamar) {
    std::cout << "======================== Kamar Tersedia ========================\n";
    std::cout << std::setw(15) << "Nomor Kamar" << std::setw(15) << "Status" << std::endl;

    for (const auto& kamar : daftarKamar) {
        if (kamar.tersedia && kamar.namaTamu.empty()) {
            std::cout << std::setw(15) << kamar.nomorKamar << std::setw(15) << "Tersedia" << std::endl;
        }
    }

    std::cout << "================================================================\n";
}

// Fungsi untuk menampilkan daftar tamu
void tampilkanDaftarTamu(const std::vector<Kamar>& daftarKamar) {
    std::cout << "========================= Daftar Tamu ==========================\n";
    std::cout << std::setw(15) << "Nomor Kamar" << std::setw(20) << "Nama Tamu" << std::setw(20) << "Check-in" << std::setw(20) << "Check-out" << std::endl;

    for (const auto& kamar : daftarKamar) {
        if (!kamar.tersedia) {
            std::cout << std::setw(15) << kamar.nomorKamar << std::setw(20) << kamar.namaTamu
                      << std::setw(20) << kamar.tanggalCheckIn << std::setw(20) << kamar.tanggalCheckOut << std::endl;
        }
    }

    std::cout << "================================================================\n";
}

// Fungsi untuk menampilkan menu
void tampilkanDaftarMenu(const std::vector<Menu>& daftarMenu) {
    std::cout << "========================= Daftar Menu ==========================\n";
    std::cout << std::setw(20) << "Nama Menu" << std::setw(15) << "Harga" << std::endl;

    for (const auto& menu : daftarMenu) {
        std::cout << std::setw(20) << menu.namaMenu << std::setw(15) << menu.harga << std::endl;
    }

    std::cout << "================================================================\n";
}

// Fungsi untuk pesan makanan/minuman
void pesanMenu(std::vector<Kamar>& daftarKamar, const std::vector<Menu>& daftarMenu) {
    int nomorKamar;
    std::cout << "Masukkan nomor kamar untuk pesan makanan/minuman: ";
    std::cin >> nomorKamar;

    auto it = std::find_if(daftarKamar.begin(), daftarKamar.end(),
                           [nomorKamar](const Kamar& kamar) { return kamar.nomorKamar == nomorKamar && !kamar.tersedia; });

    if (it != daftarKamar.end()) {
        int pilihanMenu;
        std::cout << "Pilih menu yang ingin dipesan:\n";
        tampilkanDaftarMenu(daftarMenu);
        std::cout << "Masukkan nomor menu: ";
        std::cin >> pilihanMenu;

        if (pilihanMenu >= 1 && pilihanMenu <= static_cast<int>(daftarMenu.size())) {
            it->pesanan.push_back(daftarMenu[pilihanMenu - 1].namaMenu);
            std::cout << "Pesanan " << daftarMenu[pilihanMenu - 1].namaMenu << " untuk kamar "
                      << nomorKamar << " berhasil ditambahkan!\n";
        } else {
            std::cout << "Nomor menu tidak valid.\n";
        }
    } else {
        std::cout << "Nomor kamar tidak valid atau kamar belum dipesan.\n";
    }
}

// Fungsi untuk menampilkan pesanan makanan/minuman
void tampilkanPesanan(const std::vector<Kamar>& daftarKamar) {
    std::cout << "======================= Pesanan Makanan/Minuman ========================\n";
    std::cout << std::setw(15) << "Nomor Kamar" << std::setw(30) << "Pesanan" << std::endl;

    for (const auto& kamar : daftarKamar) {
        if (!kamar.tersedia && !kamar.pesanan.empty()) {
            std::cout << std::setw(15) << kamar.nomorKamar << std::setw(30);

            for (const auto& pesanan : kamar.pesanan) {
                std::cout << pesanan << ", ";
            }

            std::cout << std::endl;
        }
    }

    std::cout << "========================================================================\n";
}

// Fungsi untuk check out
void checkOut(std::vector<Kamar>& daftarKamar) {
    int nomorKamar;
    std::cout << "Masukkan nomor kamar untuk check out: ";
    std::cin >> nomorKamar;

    auto it = std::find_if(daftarKamar.begin(), daftarKamar.end(),
                           [nomorKamar](const Kamar& kamar) { return kamar.nomorKamar == nomorKamar && !kamar.tersedia; });

    if (it != daftarKamar.end()) {
        it->tersedia = true;
        it->namaTamu.clear();
        it->tanggalCheckIn.clear();
        it->tanggalCheckOut.clear();
        it->pesanan.clear();
        std::cout << "Check out untuk kamar " << nomorKamar << " berhasil!\n";
    } else {
        std::cout << "Nomor kamar tidak valid atau kamar belum dipesan.\n";
    }
}

int main() {
    // Inisialisasi beberapa kamar
    std::vector<Kamar> daftarKamar;
    for (int i = 101; i <= 108; ++i) {
        daftarKamar.push_back({i, true, "", "", "", {}});
    }

    // Inisialisasi beberapa menu
    std::vector<Menu> daftarMenu = {
        {"Nasi Goreng", 15.0},
        {"Mie Goreng", 12.0},
        {"Ayam Bakar", 20.0}
    };

    int pilihan;
    do {
        tampilkanMenu();
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanKamarTersedia(daftarKamar);
                break;
            case 2:
                pesanKamar(daftarKamar);
                break;
            case 3:
                tampilkanDaftarTamu(daftarKamar);
                break;
            case 4:
                pesanMenu(daftarKamar, daftarMenu);
                break;
            case 5:
                checkOut(daftarKamar);
                break;
            case 0:
                std::cout << "Program selesai.\n";
                break;
            default:
                std::cout << "Opsi tidak valid. Silakan pilih lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}
