# KUIS-DPBO-C1-2

## DESAIN
<img width="742" height="627" alt="image" src="https://github.com/user-attachments/assets/08f74b1e-323e-480d-bb21-0b40419dc3dc" />

## ALUR 
Sistem berpusat pada pengelolaan item pasar digital yang diatur oleh sebuah Provider untuk 
memfasilitasi transaksi antara Client dan Freelancer. 

• Pusat Kelas Abstrak (MarketItem): Sistem menggunakan kelas abstrak MarketItem 
sebagai rancangan dasar (cetak biru) yang memiliki atribut nama, kapasitas, dan harga. 
Kelas ini diwarisi secara langsung oleh tiga kelas spesifik yaitu Project, Skill, dan Tool.  
• Pengelolaan Item oleh Provider: Sistem membuat objek Provider<T> yang bertugas 
menampung daftar item-item pasar tersebut dalam sebuah vektor (stokItem).  
• Interaksi Client: Objek Client<T> memiliki saldo private dan daftar proyek. Klien 
berinteraksi dengan Provider<T> untuk memublikasikan proyek.  
• Interaksi Freelancer: Objek Freelancer<T_in, T_out> memiliki daftar portofolio dan 
berinteraksi dengan Provider<T_in> untuk mengakses Skill yang dibutuhkan dalam 
proses kerjanya.  
• Validasi dan Error Handling: Ketika terjadi pemrosesan yang melibatkan kelas 
MarketItem (seperti pengurangan kapasitas), sistem dapat berinteraksi dengan kelas 
ExceptionMarket untuk menangani error atau anomali data.  
• Audit Sistem: Kelas MarketplaceAdmin berfungsi sebagai auditor yang melakukan 
pengecekan data terhadap Client<T>. Klien memberikan izin akses khusus (friend) 
kepada kelas admin ini 
UML - - 
Inheritance: 
Digunakan pada: Garis dari Project, Skill, dan Tool yang menunjuk ke arah 
MarketItem 
Alasan: Menandakan bahwa ketiga kelas tersebut merupakan kelas turunan (anak) 
yang mewarisi sifat dan metode dari kelas abstrak induknya yaitu MarketItem. 
Composition : 
Digunakan pada: Garis yang menghubungkan Client<T>, Freelancer<T_in, T_out>, 
dan Provider<T> menuju ke arah kelas MarketItem 
- - - 
Alasan: Dalam diagram ini, belah ketupat hitam melambangkan hubungan kepemilikan 
yang kuat. Artinya, kelas-kelas tersebut menampung, memiliki, dan menyatukan objek 
MarketItem (melalui vektor) sebagai bagian penting dari struktur internal mereka. 
Association : 
Digunakan pada: Garis yang menghubungkan antara Client<T> dengan Provider<T>, 
serta Freelancer<T_in, T_out> dengan Provider<T>.  
Alasan: Menandakan adanya hubungan interaksi atau penggunaan layanan secara 
general antara Klien/Freelancer dengan Provider tanpa kepemilikan mutlak di antara 
mereka. 
Ketergantungan Friend : 
Digunakan pada: Garis dari Client<T> yang menunjuk ke arah 
MarketplaceAdmin.  
Alasan: Menandakan bahwa Client<T> memberikan hak akses istimewa (friend) 
kepada MarketplaceAdmin sehingga admin dapat membaca atribut private (seperti 
saldoPrivate) yang ada di dalam kelas Klien 
Asosiasi Berarah (Garis lurus dengan panah terbuka biasa): 
Digunakan pada: Garis dari kelas MarketItem yang menunjuk lurus ke kelas 
ExceptionMarket. 
Alasan: Menandakan bahwa MarketItem berinteraksi atau melempar (throw) pesan 
error menuju kelas ExceptionMarket ketika diperlukan sebuah penanganan eksepsi. 
SESUAI PERMINTAAN 
1. Konsep Jobs Center pada Sistem Sistem mewujudkan Jobs Center melalui kelas 
Provider. Kelas ini bertindak sebagai agensi pusat atau papan lowongan (job 
board) yang menjembatani dua pihak: tempat di mana Client mempublikasikan 
ketersediaan Project, dan tempat di mana Freelancer menawarkan atau mencari 
Skill. Entitas yang diperdagangkan di dalam Jobs Center ini diturunkan dari 
kelas induk MarketItem 
2. Custom Template Class. 
▪ Provider<T>: Memungkinkan pembuatan Jobs Center dengan berbagai 
fokus layanan tanpa harus menulis ulang kode untuk setiap jenisnya. 
Misalnya, instansiasi Provider<Skill> bertindak sebagai pusat bakat 
(agensi skill), sedangkan Provider<Project> bertindak sebagai pusat 
lowongan kerja. 
▪ Freelancer<T_in, T_out>: Mendefinisikan logika operasional pekerja di 
Jobs Center, di mana mereka membutuhkan bahan baku/input (T_in 
seperti Skill) untuk memproduksi sebuah hasil (T_out seperti Project 
untuk portofolio). 
▪ Client<T>: Memungkinkan klien dikonfigurasi untuk menangani jenis 
transaksi pasar tertentu secara dinamis. 
3. Pemanfaatan STL 
▪ Program menggunakan std::vector (seperti vector<T*> stokItem pada 
Provider dan vector<T*> daftarProject pada Client) untuk menampung 
data item pasar, riwayat proyek, dan portofolio secara dinamis. Hal ini 
memastikan Jobs Center dapat mengelola penambahan atau pencarian 
lowongan tanpa batasan ukuran memori statis. 
4. Pemanfaatan Kelas Friend (Friend Class) 
•  Kelas Client memiliki atribut uang berupa - double saldoPrivate 
yang disembunyikan (private) agar tidak bisa diakses oleh kelas lain maupun 
sembarang Freelancer. 
•  Untuk keperluan regulasi Jobs Center, dibuat kelas MarketplaceAdmin 
yang dideklarasikan sebagai Friend Class di dalam Client. Ini memberikan hak 
istimewa kepada Admin untuk mengaudit saldo privat klien tanpa melanggar 
prinsip enkapsulasi program. 
5. Pemanfaatan Exception Handling 
▪ Logika pengurangan kuota ditempatkan di metode kurangiKapasitas(). 
Jika sisa jam kerja atau slot Project berada di bawah nol, operasi tidak 
sekadar mencetak pesan error biasa, melainkan melempar (throw) objek 
dari kelas ExceptionMarket. Mekanisme ini memutus alur program 
secara paksa agar sisa kuota di Jobs Center tidak pernah bernilai negatif.


## DOKUMENTASI
<img width="666" height="682" alt="image" src="https://github.com/user-attachments/assets/de787d74-3af7-428c-982d-6295f1ec3a60" />
