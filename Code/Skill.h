// Mencegah definisi kelas Skill dimasukkan berulang kali.
#ifndef SKILL_H
#define SKILL_H

// Menyediakan tipe string dan utility untuk memindahkan nilai saat konstruksi.
#include <string>
#include <utility>

// Skill mewarisi nama, kapasitas, harga, dan validasi dari MarketItem.
#include "MarketItem.h"

// Merepresentasikan jenis kemampuan yang dapat digunakan freelancer.
class Skill : public MarketItem {
public:
    // Membuat skill dengan nama, kapasitas, dan tarif, lalu meneruskannya ke kelas dasar.
    Skill(std::string nama, int kapasitas, long long tarif)
        : MarketItem(std::move(nama), kapasitas, tarif) {}
};

// Akhir dari perlindungan include.
#endif