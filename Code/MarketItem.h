// Mencegah definisi MarketItem dimasukkan berulang kali.
#ifndef MARKET_ITEM_H
#define MARKET_ITEM_H

// Menyediakan string untuk nama item dan utility untuk std::move.
#include <string>
#include <utility>

// Digunakan untuk melaporkan data item atau jumlah stok yang tidak valid.
#include "ExceptionMarket.h"

// Mengubah bilangan menjadi format rupiah dengan titik sebagai pemisah ribuan.
inline std::string formatRupiah(long long nilai) {
    // Mengubah nilai numerik menjadi teks agar dapat diberi pemisah ribuan.
    const std::string angka = std::to_string(nilai);
    // Menyimpan hasil angka yang sudah diberi pemisah.
    std::string hasil;
    // Menyediakan ruang string secukupnya untuk angka dan titik pemisah.
    hasil.reserve(angka.size() + angka.size() / 3);

    // Memeriksa setiap digit untuk menentukan posisi titik pemisah ribuan.
    for (std::size_t i = 0; i < angka.size(); ++i) {
        // Titik ditambahkan sebelum digit jika masih ada kelipatan tiga digit di belakangnya.
        if (i > 0 && (angka.size() - i) % 3 == 0) {
            hasil += '.';
        }
        // Menambahkan digit saat ini ke hasil format.
        hasil += angka[i];
    }

    // Menambahkan simbol rupiah pada angka yang telah diformat.
    return "Rp " + hasil;
}

// Kelas dasar yang menyimpan data umum untuk semua item marketplace.
class MarketItem {
private:
    // Nama item yang ditampilkan dan digunakan saat pencarian.
    std::string nama_;
    // Jumlah item atau kapasitas yang masih tersedia.
    int stok_;
    // Harga item dalam rupiah.
    long long harga_;

public:
    // Membuat item dan memvalidasi nama, stok, serta harga awalnya.
    MarketItem(std::string nama, int stok, long long harga)
        : nama_(std::move(nama)), stok_(stok), harga_(harga) {
        // Item harus memiliki nama agar dapat dikenali.
        if (nama_.empty()) {
            throw ExceptionMarket("Nama item tidak boleh kosong.");
        }
        // Stok dan harga negatif tidak diizinkan.
        if (stok_ < 0 || harga_ < 0) {
            throw ExceptionMarket("Stok dan harga tidak boleh negatif.");
        }
    }

    // Destructor virtual memungkinkan kelas turunan dihapus melalui pointer kelas dasar.
    virtual ~MarketItem() = default;

    // Mengembalikan nama item tanpa menyalin string.
    const std::string& getNama() const { return nama_; }
    // Mengembalikan jumlah stok saat ini.
    int getStok() const { return stok_; }
    // Mengembalikan harga item.
    long long getHarga() const { return harga_; }

    // Mengurangi stok setelah memastikan jumlah dan stok yang tersedia valid.
    void kurangiStok(int jumlah) {
        // Pengurangan nol atau negatif tidak diperbolehkan.
        if (jumlah <= 0) {
            throw ExceptionMarket("Jumlah harus lebih dari nol.");
        }
        // Operasi ditolak jika jumlah yang diminta melebihi stok.
        if (jumlah > stok_) {
            throw ExceptionMarket("Stok item \"" + nama_ + "\" tidak mencukupi.");
        }
        // Stok dikurangi hanya setelah seluruh validasi lolos.
        stok_ -= jumlah;
    }
};

// Akhir dari perlindungan include.
#endif