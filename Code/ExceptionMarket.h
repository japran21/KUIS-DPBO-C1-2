// Mencegah isi header didefinisikan lebih dari sekali dalam satu kompilasi.
#ifndef EXCEPTION_MARKET_H
#define EXCEPTION_MARKET_H

// Menyediakan std::runtime_error sebagai kelas dasar exception.
#include <stdexcept>
// Menyediakan std::string untuk menyimpan pesan kesalahan.
#include <string>

// Exception khusus untuk kesalahan yang terjadi pada sistem marketplace.
class ExceptionMarket : public std::runtime_error {
public:
    // Meneruskan pesan kesalahan ke kelas dasar agar dapat dibaca melalui what().
    explicit ExceptionMarket(const std::string& message)
        : std::runtime_error(message) {}
};

// Akhir dari perlindungan include.
#endif