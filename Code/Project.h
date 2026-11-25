// Mencegah definisi kelas Project dimasukkan berulang kali.
#ifndef PROJECT_H
#define PROJECT_H

// Menyediakan tipe string dan utility untuk memindahkan nilai saat konstruksi.
#include <string>
#include <utility>

// Project memakai data umum dan validasi yang disediakan MarketItem.
#include "MarketItem.h"

// Merepresentasikan pekerjaan yang tersedia untuk dipublikasikan client.
class Project : public MarketItem {
public:
    // Membuat project dengan nama, kapasitas, dan harga awal.
    Project(std::string nama, int kapasitas, long long harga)
        : MarketItem(std::move(nama), kapasitas, harga) {}
};

// Akhir dari perlindungan include.
#endif