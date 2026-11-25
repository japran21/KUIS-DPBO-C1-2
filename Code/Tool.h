// Mencegah definisi kelas Tool dimasukkan berulang kali.
#ifndef TOOL_H
#define TOOL_H

// Menyediakan tipe string dan utility untuk memindahkan nilai saat konstruksi.
#include <string>
#include <utility>

// Tool menggunakan data dasar item marketplace.
#include "MarketItem.h"

// Merepresentasikan alat atau produk lain yang memiliki stok dan harga.
class Tool : public MarketItem {
public:
    // Membuat tool dengan nama, stok, dan harga awal.
    Tool(std::string nama, int stok, long long harga)
        : MarketItem(std::move(nama), stok, harga) {}
};

// Akhir dari perlindungan include.
#endif