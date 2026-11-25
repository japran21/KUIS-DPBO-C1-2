// Mencegah definisi MarketplaceAdmin dimasukkan berulang kali.
#ifndef MARKETPLACE_ADMIN_H
#define MARKETPLACE_ADMIN_H

// Menyediakan cout untuk menampilkan laporan audit.
#include <iostream>
// Menyediakan string untuk mengubah angka menjadi teks.
#include <string>

// Menyediakan fungsi formatRupiah untuk menampilkan saldo.
#include "MarketItem.h"

// Deklarasi awal template Client supaya dapat dipakai pada parameter fungsi.
template <typename T>
class Client;

// Kelas utilitas untuk memeriksa dan menampilkan ringkasan data client.
class MarketplaceAdmin {
public:
    // Fungsi audit menerima Client dengan tipe project apa pun.
    template <typename T>
    static void auditClient(const Client<T>& client) {
        // MarketplaceAdmin adalah friend Client, sehingga dapat membaca data privatnya.
        std::cout << "  Client: " << client.nama_ << '\n'
                  << "    Saldo: " << formatRupiah(client.saldo_) << '\n'
                  << "    Project terdaftar: " << client.projects_.size() << '\n'
                  << "    Total publikasi: " << client.jumlahPublikasi_ << '\n';
    }
};

// Akhir dari perlindungan include.
#endif