// Mencegah definisi template Freelancer dimasukkan berulang kali.
#ifndef FREELANCER_H
#define FREELANCER_H

// Menyediakan cout untuk output portofolio.
#include <iostream>
// Menyediakan string untuk nama, skill, dan pekerjaan.
#include <string>
// Menyediakan std::move pada konstruktor.
#include <utility>
// Menyediakan vector untuk menyimpan riwayat pekerjaan.
#include <vector>

// Exception digunakan untuk kesalahan data atau kapasitas skill.
#include "ExceptionMarket.h"
// Provider digunakan untuk mencari skill yang tersedia.
#include "Provider.h"

// Freelancer menggunakan tipe skill dan tipe project sebagai parameter template.
template <typename SkillType, typename ProjectType>
class Freelancer {
private:
    // Menyimpan rincian satu pekerjaan pada portofolio.
    struct EntriPortofolio {
        // Skill yang dipakai untuk pekerjaan ini.
        std::string namaSkill;
        // Nama pekerjaan yang telah diselesaikan.
        std::string namaPekerjaan;
        // Jumlah unit skill yang digunakan.
        int jumlahUnit;
    };

    // Nama freelancer.
    std::string nama_;
    // Provider tempat freelancer mencari dan mengurangi stok skill.
    Provider<SkillType>* providerSkill_;
    // Kumpulan pekerjaan yang telah diproses freelancer.
    std::vector<EntriPortofolio> portofolio_;

public:
    // Membuat freelancer dan menghubungkannya ke provider skill.
    Freelancer(std::string nama, Provider<SkillType>* providerSkill)
        : nama_(std::move(nama)), providerSkill_(providerSkill) {
        // Nama freelancer wajib diisi.
        if (nama_.empty()) {
            throw ExceptionMarket("Nama freelancer tidak boleh kosong.");
        }
        // Provider skill wajib tersedia.
        if (providerSkill_ == nullptr) {
            throw ExceptionMarket("Provider skill freelancer tidak boleh null.");
        }
    }

    // Memproses pekerjaan dengan skill, jumlah unit, dan jumlah pekerjaan yang diminta.
    void prosesKerja(const std::string& namaSkill,
                     const std::string& namaPekerjaan,
                     int jumlahUnit,
                     int jumlahPekerjaan) {
        // Pekerjaan harus memiliki nama.
        if (namaPekerjaan.empty()) {
            throw ExceptionMarket("Nama pekerjaan tidak boleh kosong.");
        }
        // Jumlah unit dan jumlah pekerjaan harus bernilai positif.
        if (jumlahPekerjaan <= 0 || jumlahUnit <= 0) {
            throw ExceptionMarket("Jumlah unit dan jumlah pekerjaan harus lebih dari nol.");
        }

        // Cari skill yang akan digunakan melalui provider.
        SkillType* skill = providerSkill_->cariItemByNama(namaSkill);
        // Hentikan proses jika skill tidak terdaftar.
        if (skill == nullptr) {
            throw ExceptionMarket("Skill \"" + namaSkill + "\" tidak ditemukan.");
        }
        // Periksa kapasitas dengan pembagian agar perbandingan tidak mengalikan angka lebih dulu.
        if (jumlahUnit > skill->getStok() / jumlahPekerjaan) {
            throw ExceptionMarket("Kapasitas skill \"" + namaSkill + "\" tidak mencukupi.");
        }

        // Hitung seluruh unit yang dibutuhkan dan kurangi stok skill.
        const int totalUnit = jumlahUnit * jumlahPekerjaan;
        skill->kurangiStok(totalUnit);
        // Catat pekerjaan setelah stok berhasil dikurangi.
        portofolio_.push_back({namaSkill, namaPekerjaan, totalUnit});
    }

    // Menampilkan semua pekerjaan yang sudah dicatat dalam portofolio.
    void tampilkanPortofolio() const {
        std::cout << "\nPORTOFOLIO FREELANCER: " << nama_ << '\n';
        // Tampilkan keterangan jika belum ada pekerjaan.
        if (portofolio_.empty()) {
            std::cout << "  Belum ada pekerjaan.\n";
            return;
        }

        // Tampilkan rincian setiap pekerjaan satu per satu.
        for (const EntriPortofolio& entri : portofolio_) {
            std::cout << "  Pekerjaan:\n"
                      << "    Nama pekerjaan: " << entri.namaPekerjaan << '\n'
                      << "    Skill: " << entri.namaSkill << '\n'
                      << "    Unit: " << entri.jumlahUnit << '\n';
        }
    }
};

// Akhir dari perlindungan include.
#endif