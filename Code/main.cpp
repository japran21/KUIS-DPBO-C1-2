#include <iostream>            // Menyediakan cout untuk menampilkan teks ke konsol.
#include <string>              // Menyediakan tipe data string untuk teks.
#include "ExceptionMarket.h"   // Menyediakan exception khusus untuk kesalahan marketplace.
#include "MarketItem.h"        // Menyediakan kelas dasar item marketplace.
#include "Project.h"           // Menyediakan kelas Project.
#include "Skill.h"             // Menyediakan kelas Skill.
#include "Tool.h"              // Menyediakan kelas Tool jika diperlukan oleh program.
#include "Provider.h"          // Menyediakan template Provider untuk menyimpan item.
#include "MarketplaceAdmin.h"  // Menyediakan fungsi audit milik admin.
#include "Client.h"            // Menyediakan template Client.
#include "Freelancer.h"        // Menyediakan template Freelancer.
//Saya Muhammad Ilal Zhafran NIM 2502623 mengerjakan soal Kuis 2 dalam mata kuliah Desain Pemrograman Berorientasi Objek untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.

using namespace std;           // Agar nama std::cout dan std::string dapat ditulis tanpa std::.

// Mencetak judul bagian beserta garis pemisah agar output terstruktur.
void tampilkanBagian(const string& judul) {
    cout << "\n" << judul << '\n' // Menampilkan baris kosong, judul bagian, dan pindah baris.
        << "------------------------------------------------------------\n"; // Menampilkan garis pemisah.
}

// Fungsi utama; eksekusi program dimulai dari sini.
int main() {
    // Menampilkan judul program dan ringkasan konsep yang digunakan.
    cout << "SISTEM FREELANCE MARKETPLACE\n"
        << "Implementasi Template, STL, Friend, dan Exception\n"
        << "------------------------------------------------------------\n";
    
    // try menampung operasi yang mungkin menghasilkan ExceptionMarket.
    try {
        tampilkanBagian("DATA SKILL DAN PROJECT"); // Menandai bagian pembuatan data awal.
        Provider<Skill> skillAgency("TechTalent Agency"); // Membuat provider yang menyimpan data Skill.
        Provider<Project> projectBoard("Upwork Board"); // Membuat provider yang menyimpan data Project.

        Skill s1("C++ Programming", 100, 250000); // Membuat skill dengan kapasitas 100 dan harga 250.000.
        Skill s2("UI/UX Design", 50, 150000); // Membuat skill dengan kapasitas 50 dan harga 150.000.
        Skill s3("Java Programming", 80, 300000); // Membuat skill Java dengan kapasitas 80 dan harga 300.000.
        Skill s4("Graphic Design", 60, 200000); // Membuat skill desain grafis dengan kapasitas 60 dan harga 200.000.
        skillAgency.tambahItem(&s1); // Mendaftarkan alamat s1 ke provider skill.
        skillAgency.tambahItem(&s2); // Mendaftarkan alamat s2 ke provider skill.
        skillAgency.tambahItem(&s3); // Mendaftarkan alamat s3 ke provider skill.
        skillAgency.tambahItem(&s4); // Mendaftarkan alamat s4 ke provider skill.
        
        Project p1("Sistem Kasir v1", 10, 5000000); // Membuat project dengan stok 10 dan harga 5.000.000.
        Project p2("Desain Logo Startup", 5, 1000000); // Membuat project dengan stok 5 dan harga 1.000.000.
        Project p3("Aplikasi Android", 8, 7500000); // Membuat project aplikasi Android dengan stok 8.
        Project p4("Website Company Profile", 6, 4000000); // Membuat project website dengan stok 6.
        projectBoard.tambahItem(&p1); // Mendaftarkan alamat p1 ke provider project.
        projectBoard.tambahItem(&p2); // Mendaftarkan alamat p2 ke provider project.
        projectBoard.tambahItem(&p3); // Mendaftarkan alamat p3 ke provider project.
        projectBoard.tambahItem(&p4); // Mendaftarkan alamat p4 ke provider project.
        
        skillAgency.tampilkanStok(0); // Menampilkan seluruh skill mulai dari indeks 0.
        projectBoard.tampilkanStok(0); // Menampilkan seluruh project mulai dari indeks 0.
        
        tampilkanBagian("PUBLIKASI PROJECT CLIENT"); // Menandai proses publikasi project oleh client.
        Client<Project> client1("PT Maju Bersama", &projectBoard, 15000000); // Membuat client pertama dengan saldo 15 juta.
        client1.tambahProject(&p1); // Menghubungkan project p1 dengan client pertama.
        client1.publikasi("Sistem Kasir v1", 2); // Client pertama mempublikasikan 2 unit project.

        Client<Project> client2("CV Digital Karya", &projectBoard, 8000000); // Membuat client kedua dengan saldo 8 juta.
        client2.tambahProject(&p2); // Menghubungkan project p2 dengan client kedua.
        client2.publikasi("Desain Logo Startup", 1); // Client kedua mempublikasikan 1 unit project.
        
        Client<Project> client3("PT Inovasi Digital", &projectBoard, 20000000); // Membuat client ketiga dengan saldo 20 juta.
        client3.tambahProject(&p3); // Menghubungkan project p3 dengan client ketiga.
        client3.publikasi("Aplikasi Android", 1); // Client ketiga mempublikasikan 1 unit project.

        Client<Project> client4("CV Karya Mandiri", &projectBoard, 12000000); // Membuat client keempat dengan saldo 12 juta.
        client4.tambahProject(&p4); // Menghubungkan project p4 dengan client keempat.
        client4.publikasi("Website Company Profile", 1); // Client keempat mempublikasikan 1 unit project.

        // Menampilkan konfirmasi publikasi untuk keempat client.
        cout << "Client " << client1.getNama()
            << " berhasil mempublikasikan 2 project.\n"
            << "Client " << client2.getNama()
            << " berhasil mempublikasikan 1 project.\n"
            << "Client " << client3.getNama()
            << " berhasil mempublikasikan 1 project.\n"
            << "Client " << client4.getNama()
            << " berhasil mempublikasikan 1 project.\n";
        
        tampilkanBagian("PROSES PEKERJAAN FREELANCER"); // Menandai proses kerja freelancer.
        Freelancer<Skill, Project> freelancer1("Budi", &skillAgency); // Membuat freelancer Budi dengan akses ke provider skill.
        freelancer1.prosesKerja("C++ Programming", "Modul Pembayaran C++", 20, 1); // Budi memakai 20 unit skill C++ untuk satu pekerjaan.
        
        Freelancer<Skill, Project> freelancer2("Siti", &skillAgency); // Membuat freelancer Siti dengan provider skill yang sama.
        freelancer2.prosesKerja("UI/UX Design", "Mockup Homepage", 15, 1); // Siti memakai 15 unit skill UI/UX untuk satu pekerjaan.
        
        Freelancer<Skill, Project> freelancer3("Andi", &skillAgency); // Membuat freelancer Andi dengan provider skill yang sama.
        freelancer3.prosesKerja("Java Programming", "Backend API", 25, 1); // Andi memakai 25 unit skill Java untuk satu pekerjaan.

        Freelancer<Skill, Project> freelancer4("Rina", &skillAgency); // Membuat freelancer Rina dengan provider skill yang sama.
        freelancer4.prosesKerja("Graphic Design", "Desain Banner Promosi", 10, 1); // Rina memakai 10 unit skill desain grafis.

        cout << "Pekerjaan freelancer berhasil diproses.\n"; // Menampilkan konfirmasi pemrosesan pekerjaan.

        freelancer1.tampilkanPortofolio(); // Menampilkan daftar pekerjaan Budi.
        freelancer2.tampilkanPortofolio(); // Menampilkan daftar pekerjaan Siti.
        freelancer3.tampilkanPortofolio(); // Menampilkan daftar pekerjaan Andi.
        freelancer4.tampilkanPortofolio(); // Menampilkan daftar pekerjaan Rina.
        
        tampilkanBagian("LAPORAN AUDIT"); // Menandai bagian pemeriksaan data client oleh admin.
        MarketplaceAdmin::auditClient(client1); // Mengaudit saldo dan publikasi client pertama.
        MarketplaceAdmin::auditClient(client2); // Mengaudit saldo dan publikasi client kedua.
        MarketplaceAdmin::auditClient(client3); // Mengaudit saldo dan publikasi client ketiga.
        MarketplaceAdmin::auditClient(client4); // Mengaudit saldo dan publikasi client keempat.
        
        tampilkanBagian("UJI BATAS KAPASITAS"); // Menandai pengujian kondisi kapasitas skill berlebih.
        cout << "Mencoba menggunakan kapasitas skill melebihi batas...\n"; // Menjelaskan pengujian yang akan dilakukan.
        freelancer1.prosesKerja("UI/UX Design", "Website A", 60, 1); // Meminta 60 unit saat stok tersisa 35; seharusnya memicu exception.
        
    // Menangkap exception marketplace agar program dapat menampilkan pesan kesalahan.
    } catch (const ExceptionMarket& e) {
        cout << "ERROR: " << e.what() << '\n'; // e.what() berisi penjelasan kesalahan yang terjadi.
    }
    
    cout << "\nProgram selesai.\n"; // Menampilkan pesan akhir setelah try/catch selesai.
    return 0; // Mengembalikan 0 sebagai tanda program berakhir normal.
}