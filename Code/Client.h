// Mencegah definisi template Client dimasukkan berulang kali.
#ifndef CLIENT_H
#define CLIENT_H

// Menyediakan string, pemindahan nilai, dan vector untuk data client.
#include <string>
#include <utility>
#include <vector>

// Exception digunakan untuk melaporkan operasi client yang tidak valid.
#include "ExceptionMarket.h"
// Menyediakan tipe item project dan fungsi pemformatan harga.
#include "MarketItem.h"
// Client menggunakan provider untuk mencari project yang tersedia.
#include "Provider.h"

// Deklarasi awal agar nama MarketplaceAdmin dapat digunakan sebagai friend.
class MarketplaceAdmin;

// Client<T> mengelola saldo dan project untuk tipe item T.
template <typename T>
class Client {
private:
    // Nama individu atau perusahaan yang menggunakan marketplace.
    std::string nama_;
    // Provider tempat client mencari dan memvalidasi project.
    Provider<T>* provider_;
    // Saldo client yang dipakai saat publikasi.
    long long saldo_;
    // Daftar project yang telah ditambahkan oleh client.
    std::vector<T*> projects_;
    // Banyak operasi publikasi yang berhasil dilakukan.
    int jumlahPublikasi_;

    // Mengizinkan admin membaca data privat untuk keperluan audit.
    friend class MarketplaceAdmin;

public:
    // Membuat client dengan nama, provider project, dan saldo awal.
    Client(std::string nama, Provider<T>* provider, long long saldo)
        : nama_(std::move(nama)), provider_(provider), saldo_(saldo), jumlahPublikasi_(0) {
        // Nama client wajib diisi.
        if (nama_.empty()) {
            throw ExceptionMarket("Nama client tidak boleh kosong.");
        }
        // Client harus terhubung ke provider yang valid.
        if (provider_ == nullptr) {
            throw ExceptionMarket("Provider client tidak boleh null.");
        }
        // Saldo awal tidak boleh negatif.
        if (saldo_ < 0) {
            throw ExceptionMarket("Saldo client tidak boleh negatif.");
        }
    }

    // Mengembalikan nama client tanpa menyalin string.
    const std::string& getNama() const { return nama_; }

    // Menambahkan project milik provider ke daftar project client.
    void tambahProject(T* project) {
        // Tolak pointer kosong.
        if (project == nullptr) {
            throw ExceptionMarket("Project tidak boleh null.");
        }
        // Pastikan objek tersebut benar-benar terdaftar pada provider client.
        if (provider_->cariItemByNama(project->getNama()) != project) {
            throw ExceptionMarket("Project harus terdaftar pada provider client.");
        }
        // Cegah project yang sama dicatat dua kali oleh client.
        for (const T* existing : projects_) {
            if (existing == project) {
                throw ExceptionMarket("Project sudah ditambahkan ke client.");
            }
        }
        // Tambahkan project setelah lolos validasi.
        projects_.push_back(project);
    }

    // Mempublikasikan sejumlah project dan mengurangi stok serta saldo client.
    void publikasi(const std::string& namaProject, int jumlah) {
        // Cari project di provider berdasarkan nama yang diminta.
        T* project = provider_->cariItemByNama(namaProject);
        // Periksa bahwa project tersebut juga sudah ditambahkan ke client ini.
        bool dimilikiClient = false;
        for (T* registered : projects_) {
            if (registered == project) {
                dimilikiClient = true;
                break;
            }
        }
        // Tolak project yang tidak ada atau bukan bagian daftar client.
        if (project == nullptr || !dimilikiClient) {
            throw ExceptionMarket("Project tidak terdaftar pada client " + nama_ + ".");
        }
        // Jumlah publikasi harus positif.
        if (jumlah <= 0) {
            throw ExceptionMarket("Jumlah publikasi harus lebih dari nol.");
        }
        // Pastikan stok mencukupi sebelum transaksi dilakukan.
        if (jumlah > project->getStok()) {
            throw ExceptionMarket("Kapasitas project \"" + namaProject + "\" tidak mencukupi.");
        }
        // Pembagian ini memeriksa keterjangkauan tanpa mengalikan harga dan jumlah lebih dahulu.
        if (project->getHarga() > saldo_ / jumlah) {
            throw ExceptionMarket("Saldo client " + nama_ + " tidak mencukupi.");
        }

        // Kurangi stok project, lalu potong saldo dan catat publikasi yang berhasil.
        project->kurangiStok(jumlah);
        saldo_ -= project->getHarga() * jumlah;
        ++jumlahPublikasi_;
    }
};

// Akhir dari perlindungan include.
#endif