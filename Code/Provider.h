// Mencegah definisi template Provider dimasukkan berulang kali.
#ifndef PROVIDER_H
#define PROVIDER_H

// Menyediakan tipe indeks tanpa tanda dan koleksi vector.
#include <cstddef>
// Menyediakan cout untuk menampilkan daftar item.
#include <iostream>
// Menyediakan string untuk nama provider dan pencarian item.
#include <string>
// Menyediakan std::move pada konstruktor.
#include <utility>
// Menyediakan vector sebagai penyimpanan kumpulan pointer item.
#include <vector>

// Exception digunakan untuk melaporkan input provider/item yang tidak valid.
#include "ExceptionMarket.h"
// Menyediakan fungsi formatRupiah yang dipakai saat menampilkan harga.
#include "MarketItem.h"

// Provider<T> mengelola kumpulan item bertipe T, misalnya Skill atau Project.
template <typename T>
class Provider {
private:
    // Nama pihak/provider yang menyediakan item.
    std::string nama_;
    // Pointer ke item; objek item dimiliki oleh bagian program yang membuatnya.
    std::vector<T*> items_;

public:
    // Membuat provider dan menolak nama kosong.
    explicit Provider(std::string nama) : nama_(std::move(nama)) {
        if (nama_.empty()) {
            throw ExceptionMarket("Nama provider tidak boleh kosong.");
        }
    }

    // Mendaftarkan item baru setelah memeriksa pointer dan duplikasi nama/alamat.
    void tambahItem(T* item) {
        // Pointer kosong tidak dapat digunakan sebagai item.
        if (item == nullptr) {
            throw ExceptionMarket("Item provider tidak boleh null.");
        }
        // Item yang sama atau item dengan nama yang sama tidak boleh didaftarkan ulang.
        for (const T* existing : items_) {
            if (existing == item || existing->getNama() == item->getNama()) {
                throw ExceptionMarket("Item \"" + item->getNama() + "\" sudah terdaftar.");
            }
        }
        // Simpan pointer setelah semua pemeriksaan berhasil.
        items_.push_back(item);
    }

    // Mencari item berdasarkan nama; mengembalikan nullptr jika tidak ditemukan.
    T* cariItemByNama(const std::string& nama) const {
        for (T* item : items_) {
            if (item->getNama() == nama) {
                return item;
            }
        }
        return nullptr;
    }

    // Mengembalikan jumlah item yang dikelola provider.
    std::size_t jumlahItem() const { return items_.size(); }
    // Mengembalikan nama provider.
    const std::string& getNama() const { return nama_; }
    // Memberikan akses baca ke kumpulan pointer item.
    const std::vector<T*>& getItems() const { return items_; }

    // Menampilkan daftar item mulai dari indeks yang diberikan.
    void tampilkanStok(int mulaiDari) const {
        // Pastikan indeks tidak negatif dan tidak melewati akhir daftar.
        if (mulaiDari < 0 || static_cast<std::size_t>(mulaiDari) > items_.size()) {
            throw ExceptionMarket("Indeks awal stok provider tidak valid.");
        }

        // Menampilkan identitas provider dan label daftar item.
        std::cout << "\nDAFTAR ITEM PROVIDER: " << nama_ << '\n'
                  << "  Barang yang tersedia:\n";

        // Beri informasi khusus jika indeks awal tepat di akhir daftar.
        if (static_cast<std::size_t>(mulaiDari) == items_.size()) {
            std::cout << "    Tidak ada item untuk ditampilkan.\n";
        }

        // Tampilkan nama, stok, dan harga semua item sejak indeks awal.
        for (std::size_t i = static_cast<std::size_t>(mulaiDari); i < items_.size(); ++i) {
            std::cout << "    Item: " << items_[i]->getNama() << '\n'
                      << "      Stok: " << items_[i]->getStok() << '\n'
                      << "      Harga: " << formatRupiah(items_[i]->getHarga()) << '\n';
        }
    }
};

// Akhir dari perlindungan include.
#endif