#include <iostream> //Untuk I/O
#include <vector> //Array Dinamis
#include <string> //Type Data String
#include <iomanip> //Untuk manipulasi lebar kolom
#include <time.h> //Untuk fungsi waktu(Time) 
#include <conio.h> //Untuk menunggu input keyboard
using namespace std;

// Struktur data untuk akun pengguna
struct Akun {
    string username;
    string password;
    string role;
};

// Struktur data untuk barang
struct Barang {
	int id_barang;
    string nama;
    int stok;
    int harga;
    int year;
};

// Struktur data untuk pegawai
struct Pegawai {
    string nama;
    string noIdentitas;
    string alamat;
    string username;
    string password;
    string role;
};

struct BarangKeluar{
	string namaCustomer;
	int noFaktur;
	int id_customer;
	string namaBarang;
	int totalBarang;
	string date;
};

struct BarangMasuk{
	string namaVendor;
	int qty;
	string date;
	string namaBarang;
	int noFaktur;
};

// Daftar akun yang sudah terdaftar
vector<Akun> akunList;
// Daftar barang
vector<Barang> barangList;
// Daftar pegawai
vector<Pegawai> pegawaiList;
// Daftar Barang Masuk
vector<BarangMasuk> barangMasukList;
// Daftar Barang Keluar
vector<BarangKeluar> barangKeluarList;

string usernameAktif = "";
string roleAktif = "";   

// Fungsi untuk membuat akun baru
void buatAkun() {
	cout << "\nSign Up" << endl;
	string username;
	string password;
	
    Akun akunBaru;
    Pegawai pegawai;
    
    cout << "username: ";
    cin >> username;
    cout << "password: ";
    cin >> password;
    
    // Menentukan role (Admin atau Pegawai)
    int rolePilihan;
    cout << "Pilih role (1 = Admin, 2 = Pegawai): ";
    cin >> rolePilihan;
    if (rolePilihan == 1) {
        akunBaru.role = "admin";
        akunBaru.username = username;
   		akunBaru.password = password;
   		akunList.push_back(akunBaru);
    } else if (rolePilihan == 2) {
        pegawai.role = "pegawai";
		cout << "nama : ";
        cin.ignore(); // Untuk menghindari masalah dengan input string setelah cin
        getline(cin, pegawai.nama);
        cout << "id pegawai: ";
        getline(cin, pegawai.noIdentitas);
        cout << "alamat : ";
        getline(cin, pegawai.alamat);
        pegawai.username = username;
    	pegawai.password = password;
    	pegawaiList.push_back(pegawai);
    } else {
        cout << "Role tidak valid.\n";
        return;
    }
    cout << "Akun berhasil dibuat.\n";
}

// Fungsi untuk login
bool login(string& role) {
    string username, password;
    cout << "\nLogin" << endl;
    cout << "username: ";
    cin >> username;
    cout << "password: ";
    cin >> password;

    // Cari akun yang sesuai dengan username dan password 
    for (int i = 0; i < akunList.size(); i++) {
        if (akunList[i].username == username && akunList[i].password == password) {
            role = akunList[i].role;
            usernameAktif = akunList[i].username; 
            roleAktif = akunList[i].role;
            return true;
        }
    }
    for (int i = 0; i < pegawaiList.size(); i++) {
        if (pegawaiList[i].username == username && pegawaiList[i].password == password) {
            role = pegawaiList[i].role;
            usernameAktif = pegawaiList[i].username; 
            roleAktif = pegawaiList[i].role;
            return true;
        }
    }
    return false;
}
void tambahBarangKeluar(){
	cout << "\nMasukkan id barang: ";
    BarangKeluar barangKeluar;
    int qty;
    int id;
    int idCustomer;
	cin >> id;
	bool found = false;
    cout << "\n\t\t\t\tDetail Barang\n";
    for (int i = 0; i < barangList.size(); i++) {
        if (barangList[i].id_barang == id) {
            cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
			cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
			cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
            cout << setw(5) << barangList[i].id_barang
			<< setw(15) << barangList[i].nama
			<< setw(15) << barangList[i].stok
			<< setw(20) << barangList[i].harga
			<< setw(20) << barangList[i].year << endl;
			cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
			cout << "Nama Customer : ";
			cin.ignore(); getline(cin,barangKeluar.namaCustomer);
			cout << "Id Customer : ";cin>>idCustomer;
			cout << "Quantity :  ";cin >> qty;
			cout << "No. Faktur : ";cin >> barangKeluar.noFaktur;
			cout << "Tanggal : ";
			cin.ignore(); getline(cin,barangKeluar.date);
			barangList[i].stok - qty;        
			for(int i = 0; i < barangKeluarList.size(); i++){
			    if(barangKeluarList[i].id_customer == idCustomer){
				    cout << "Id Customer Sudah Ada" << endl;
				    return;
				}
			}
			if (barangList[i].stok >= qty) {
			    barangList[i].stok -= qty; // Kurangi stok
			    cout << "\nBarang berhasil Dikirim " << endl;
			} else {
			    cout << "\nStok tidak mencukupi! Hanya " << barangList[i].stok << " yang tersedia.\n";
			}
			barangKeluar.id_customer = idCustomer;
			barangKeluar.totalBarang = qty;
			barangKeluarList.push_back(barangKeluar);
            found = true;
            break;
        }
    }
    if (!found) {
    	cout << "\t\t\t\tBarang tidak ditemukan.\n";
    }
}
void viewBarangKeluar(){
	cout << "\n\t\t\tDaftar Barang Keluar\n";
    if(barangList.size() < 1){
        cout << "\t\t\tBarang tidak ditemukan.\n";
	}else{
		if(barangKeluarList.size() == 0){
			cout << "\t\t\tData Barang Keluar Kosong.\n";
		}else{
			cout << "+-----+--------------------+--------------+--------------+---------------------\n";
			cout << "|   Id" << "         Customer" << "       	Quantity" << "    No. Faktur" <<   "        Tanggal "<< "         |" << endl;
			cout << "+-----+--------------------+--------------+--------------+---------------------\n";
	        for (int i = 0; i < barangKeluarList.size(); i++) {
	            cout << setw(5) << barangKeluarList[i].id_customer
				<< setw(15) << barangKeluarList[i].namaCustomer
				<< setw(15) << barangKeluarList[i].totalBarang
				<< setw(18) << barangKeluarList[i].noFaktur
				<< setw(25) << barangKeluarList[i].date << endl;
	        }
	        cout << "+-----+--------------------+--------------+--------------+---------------------\n";		
		}
	}
}

void tambahBarangMasuk(){
	BarangMasuk itemBarangMasuk;
	int id;
	int qty;
    cout << "\nBarang Masuk" << endl;
    cout << "Masukkan id barang : ";
    cin >> id;
    bool found = false;        
    for (int i = 0; i < barangList.size(); i++) {
        if (barangList[i].id_barang == id) {
            cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
			cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
			cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
            cout << setw(5) << barangList[i].id_barang
			<< setw(15) << barangList[i].nama
			<< setw(15) << barangList[i].stok
			<< setw(18) << barangList[i].harga
			<< setw(20) << barangList[i].year << endl;
			cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
			cout << "Nama Vendor : ";cin.ignore(); getline(cin,itemBarangMasuk.namaVendor);
			cout << "Tambahkan Quantity : "; cin>>qty;
			cout << "Tanggal : ";cin.ignore(); getline(cin,itemBarangMasuk.date);
			cout << "No. Faktur : ";cin>>itemBarangMasuk.noFaktur;
			if (qty == 0) {
			    barangList[i].stok;
			} else {
			    barangList[i].stok += qty;
			    cout << "Barang : " << barangList[i].nama << ", Berhasil Ditambahkan Sebanyak : " << qty<< ", Pada Tanggal : " << itemBarangMasuk.date << endl;
			}
			itemBarangMasuk.namaBarang = barangList[i].nama;
			itemBarangMasuk.qty = qty;
			barangMasukList.push_back(itemBarangMasuk);
            found = true;
        	break;
        }
    }
    if (!found) {
        cout << "Barang tidak ditemukan.\n";
    }
}
void viewBarangMasuk(){
	cout << "\n\t\t\tDaftar Barang Masuk\n";
    if(barangList.size() < 1){
        cout << "\t\t\tBarang tidak ditemukan.\n";
	}else{
		if(barangMasukList.size() == 0){
			cout << "\t\t\tData Barang Masuk Kosong.\n";
		}else{
			cout << "+--------------+-------------------+-------------+-------------+----------------------+\n";
			cout << "| No. Faktur" << "          Vendor" << "       	Barang" << "       Quantity" <<   "          Tanggal "<< "       |" << endl;
			cout << "+--------------+-------------------+-------------+-------------+----------------------+\n";
	        for (int i = 0; i < barangMasukList.size(); i++) {
	            cout << setw(8) << barangMasukList[i].noFaktur
				<< setw(22) << barangMasukList[i].namaVendor
				<< setw(15) << barangMasukList[i].namaBarang
				<< setw(12) << barangMasukList[i].qty
				<< setw(25) << barangMasukList[i].date << endl;
	        }
	        cout << "+--------------+-------------------+-------------+-------------+----------------------+\n";	
		}
	}
}
// Fungsi untuk menampilkan menu kelola barang
void kelolaBarang() {
    int pilihan;
    do {
        cout << "\nKelola Barang\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Daftar Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Cari Barang\n";
        cout << "6. Barang Keluar\n";
        cout << "7. Barang Masuk\n";
        cout << "8. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            // Tambah Barang
            cout << "\nTambah Barang" << endl;
            Barang baru;
            cout << "Id Barang: ";
            cin >> baru.id_barang;
            cout << "Nama Barang: ";
            cin.ignore(); 
			getline(cin,baru.nama);
//            cin >> baru.nama;
            cout << "Stok Barang: ";
            cin >> baru.stok;
            cout << "Harga Barang: ";
            cin >> baru.harga;
            cout << "Keluaran Tahun: ";
            cin >> baru.year;
            barangList.push_back(baru);
            cout << "Barang berhasil ditambahkan.\n";
            break;
        }
        case 2: {
            // Lihat Daftar Barang
            cout << "\n\t\t\t\tDaftar Barang\n";
            if(barangList.size() < 1){
            	cout << "\t\t\t\tBarang tidak ditemukan.\n";
			}else{
				cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
				cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
				cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
            	for (int i = 0; i < barangList.size(); i++) {
            		cout << setw(5) << barangList[i].id_barang
					<< setw(15) << barangList[i].nama
					<< setw(15) << barangList[i].stok
					<< setw(12) <<"Rp." << barangList[i].harga
					<< setw(20) << barangList[i].year << endl;
            	}
            	cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";	
			}
            break;
        }
        case 3: {
            // Update Barang
            cout << "\nUpdate Barang" << endl;
            int idBarang;
            cout << "Masukkan id barang yang ingin diupdate: ";
            cin >> idBarang;

            bool found = false;
            for (int i = 0; i < barangList.size(); i++) {
                if (barangList[i].id_barang == idBarang) {
                    cout << "Masukkan harga baru: ";
                    cin >> barangList[i].harga;
                    cout << "Masukkan keluaran tahun baru: ";
                    cin >> barangList[i].year;
                    cout << "Barang berhasil diperbarui.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Barang tidak ditemukan.\n";
            }
            break;
        }
        case 4: {
            // Hapus Barang
            cout << "\nHapus Barang" << endl;
            int idBarang;
            cout << "Masukkan id barang yang ingin dihapus: ";
            cin >> idBarang;

            bool found = false;
            for (int i = 0; i < barangList.size(); i++) {
                if (barangList[i].id_barang == idBarang) {
                    barangList.erase(barangList.begin() + i);
                    cout << "Barang berhasil dihapus.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Barang tidak ditemukan.\n";
            } 
            break;
        }
        case 5: {
            // Cari Barang
            int id;
            cout << "\nCari Barang" << endl;
            cout << "Masukkan id barang yang ingin dicari: ";
            cin >> id;

            bool found = false;
            cout << "\n\t\t\t\tBarang Ditemukan\n";
            
            for (int i = 0; i < barangList.size(); i++) {
                if (barangList[i].id_barang == id) {
                	cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
					cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
					cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
                	cout << setw(5) << barangList[i].id_barang
					<< setw(20) << barangList[i].nama
					<< setw(10) << barangList[i].stok
					<< setw(18) << barangList[i].harga
					<< setw(18) << barangList[i].year << endl;
					cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\t\t\t\tBarang tidak ditemukan.\n";
            }
            break;
        }
        case 6: {
        	int pilih;
        	do{
        		cout << "\nBarang Keluar" << endl;
				cout << "1. Tambah Barang Keluar" << endl;
				cout << "2. History" << endl;
				cout << "3. Kembali" << endl;
				cout << "Pilih : "; cin>>pilih;
				switch(pilih){
					case 1:{
						tambahBarangKeluar();
						break;
					}
					case 2:{
						viewBarangKeluar();
						break;
					}
					case 3:{
						cout << "Kembali ke menu Kelola Barang" << endl;
						break;
					}
					default:{
						cout << "Masukkan pilihan yang valid" << endl;
						break;
					}
				}
			}while(pilih!=3);
			break;
		}
		case 7:{
			int pilih;
        	do{
        		cout << "\nBarang Masuk" << endl;
				cout << "1. Tambah Barang Masuk" << endl;
				cout << "2. History" << endl;
				cout << "3. Kembali" << endl;
				cout << "Pilih : "; cin>>pilih;
				switch(pilih){
					case 1:{
						tambahBarangMasuk();
						break;
					}
					case 2:{
						viewBarangMasuk();
						break;
					}
					case 3:{
						cout << "Kembali ke menu Kelola Barang" << endl;
						break;
					}
					default:{
						cout << "Masukkan pilihan yang valid" << endl;
						break;
					}
				}
			}while(pilih!=3);
			break;
		}
        case 8: {
            // Kembali ke menu utama
            cout << "Kembali ke menu utama.\n";
            break;
        }
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    } while (pilihan != 8);
}

void viewProfiles(){
	string passAccount;
	cout << "Enter Password : ";cin >> passAccount;
	for(int i = 0; i < pegawaiList.size(); i++){	
		if(passAccount == pegawaiList[i].password){
			cout << "\nYOUR PROFILES" << endl;
			cout << "ID : " << pegawaiList[i].noIdentitas << endl; 
			cout << "Nama : " << pegawaiList[i].nama << endl;
			cout << "Alamat : " << pegawaiList[i].alamat << endl;
			cout << "Role : " << pegawaiList[i].role << endl;
		}else{
			cout << "Tolong Masukkan Password Yang Valid" << endl;
			viewProfiles();
		}
	}
}

void changePasswords(){
	Pegawai pegawai;
	string newPassword;
	string confirm;
	bool passwordChange = false;
	
	while(!passwordChange){
		for(int i = 0; i < pegawaiList.size(); i++){
			cout << "Confirmation Password : "; cin >> confirm;
			if (pegawaiList[i].password == confirm){
				cout << "Update Password : "; cin >> newPassword;
				pegawaiList[i].password = newPassword;
				pegawaiList.push_back(pegawai);
				cout << "Update Password Successfully" << endl;
				passwordChange = true;
				break;
			}
		}
		if(!passwordChange){
			cout << "Please Input Valid Password" << endl;
		}
	}
}

void menuSettings(){
	int pilihan;
	cout << "\n=============" << endl;
	cout << "Settings\n";
	cout << "=============" << endl;
	cout << "1. My Profiles\n";
	cout << "2. Change Password\n";
	cout << "3. Back\n" << endl;
	while(true){
		cout << "Pilihan: ";
	    cin >> pilihan;
		if(pilihan == 1){
			viewProfiles();
			break;
		}	
		else if(pilihan == 2){
			changePasswords();
			break;
		}else if(pilihan == 3){
			break;
		}else{
			cout << "Please Input Valid Value" << endl;
			continue;
		}
	}
}

void inputName(string &namaPegawai){
	while (true){
	    cout << "nama : ";
	    cin.ignore(); // Untuk menghindari masalah dengan input string setelah cin
	    getline(cin, namaPegawai);
	    if(namaPegawai.empty()){
	    	continue;
	    }
	    break;
	}
}

void inputId(string &id){
    while(true){
    	cout << "id pegawai: ";
    	getline(cin, id);
    	if(id.empty()){
    		continue;
		}
		break;
	}
}

void inputAlamat(string &alamat){
	while(true){
    	cout << "alamat : ";
        getline(cin, alamat);
    	if(alamat.empty()){
    		continue;
		}
		break;
	}
}

void inputUsername(string &username){
	while(true){
		cout << "username : ";
    	cin >> username;	
    	if(username.empty()){
    		continue;
		}
		break;
	}
}
void inputPassword(string &password){
	while(true){
		cout << "password : ";
    	cin >> password;	
    	if(password.empty()){
    		continue;
		}
		break;
	}
}


void kelolaPegawai() {
    int pilihan;
    do {
        cout << "\nMenu Kelola Pegawai\n";
        cout << "1. Lihat Daftar Pegawai\n";
        cout << "2. Tambah Pegawai\n";
        cout << "3. Update Pegawai\n";
        cout << "4. Hapus Pegawai\n";
        cout << "5. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            // Lihat Daftar Pegawai
            cout << "\n\t\t\t\tDaftar Pegawai\n";
            if (pegawaiList.size() < 1) {
                cout << "\t\t\t\tPegawai tidak ditemukan.\n";
            }else{
            	cout << "+-------------+------------+---------------+---------------------+--------------+\n";
				cout << "|   Username" << "         Nama" << "       Identitas" << "         Alamat" << "            Role        |" << endl;
				cout << "+-------------+------------+---------------+---------------------+--------------+\n";
            	for (int i = 0; i < pegawaiList.size(); i++) {
            		cout << setw(10) << pegawaiList[i].username
					<< setw(15) << pegawaiList[i].nama 
					<< setw(10) << pegawaiList[i].noIdentitas 
					<< setw(28) << pegawaiList[i].alamat
					<< setw(12) << pegawaiList[i].role << endl;
            	}
            	cout << "+-----+-------+------------+---------------+---------------------+--------------+\n";
			}
			break;
        }
        case 2: {
            // Tambah Pegawai
        	cout << endl << "Tambah Pegawai" << endl;
            Pegawai pegawaiBaru;
            string namaPegawai, id, alamat, username, password;
            
            inputName(namaPegawai);
           	inputId(id);
           	inputAlamat(alamat);
           	inputUsername(username);
           	inputPassword(password);
            
            pegawaiBaru.nama = namaPegawai;
            pegawaiBaru.noIdentitas = id;
            pegawaiBaru.alamat = alamat;
            pegawaiBaru.username = username;
            pegawaiBaru.password = password;
            pegawaiBaru.role = "pegawai";  // Secara default pegawai adalah pegawai
            pegawaiList.push_back(pegawaiBaru);
            cout << "Pegawai berhasil ditambahkan.\n";
            
            Akun akunBaru;
			akunBaru.username = pegawaiBaru.username;
			akunBaru.password = pegawaiBaru.password;
			akunBaru.role = pegawaiBaru.role; // Peran sama dengan pegawai
			akunList.push_back(akunBaru); // Masukkan akunBaru ke akunList
            break;
        }
        case 3: {
            // Update Pegawai
            string id;
            cout << endl << "Update Pegawai" << endl;
            cout << "Masukkan id pegawai yang ingin diupdate: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < pegawaiList.size(); i++) {
                if (pegawaiList[i].noIdentitas == id) {
                    cout << "Masukkan nama pegawai baru: ";
                    cin.ignore();
                    getline(cin, pegawaiList[i].nama);
                    cout << "Masukkan nomor identitas pegawai baru: ";
                    getline(cin, pegawaiList[i].noIdentitas);
                    cout << "Masukkan alamat pegawai baru: ";
                    getline(cin, pegawaiList[i].alamat);
                    cout << "Data pegawai berhasil diperbarui.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Pegawai tidak ditemukan.\n";
            }
            break;
        }
        case 4: {
            // Hapus Pegawai
            string id;
            cout << endl << "Hapus Pegawai" << endl;
            cout << "Masukkan id pegawai yang ingin dihapus: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < pegawaiList.size(); i++) {
                if (pegawaiList[i].noIdentitas == id) {
                    pegawaiList.erase(pegawaiList.begin() + i);
                    cout << "Pegawai berhasil dihapus.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Pegawai tidak ditemukan.\n";
            }
            break;
        }
        case 5: {
            // Kembali ke menu admin
            cout << "Kembali ke menu admin.\n";
            break;
        }
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

// Menu Admin
void menuAdmin() {
    int pilihan;
    do {
    	cout << "\n-------------------------" << endl;
		cout << "Sistem Inventory Barang" << endl;
		cout << "-------------------------";
        cout << "\n===== Menu Admin =====\n";     
		cout << "Admin : " << usernameAktif << endl;
        cout << "1. Kelola Barang\n";
        cout << "2. Kelola Pegawai\n";
        cout << "3. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            kelolaBarang();
            break;
        case 2:
            kelolaPegawai();
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);
}

// Fungsi untuk menu pegawai
void menuPegawai() {
    int pilihan;
    do {
    	cout << "\n-------------------------" << endl;
		cout << "Sistem Inventory Barang" << endl;
		cout << "-------------------------";
        cout << "\n===== Menu Pegawai =====\n";
        cout << "Pegawai : " << usernameAktif << endl;
        cout << "1. Lihat Daftar Barang\n";
        cout << "2. Cari Barang\n";
        cout << "3. Lihat Barang Keluar\n";
        cout << "4. Lihat Barang Masuk\n";
        cout << "5. Settings\n";
        cout << "6. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            // Lihat Daftar Barang untuk Pegawai
            cout << "\n\t\t\t\tDaftar Barang\n";
            if(barangList.size() < 1){
            	cout << "\t\t\t\tBarang tidak ditemukan.\n";
			}else{
				cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
				cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
				cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
            	for (int i = 0; i < barangList.size(); i++) {
            		cout << setw(5) << barangList[i].id_barang
					<< setw(20) << barangList[i].nama
					<< setw(10) << barangList[i].stok
					<< setw(18) << barangList[i].harga
					<< setw(18) << barangList[i].year << endl;
            	}
            	cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
			}
            break;
        }
        case 2: {
            // Cari Barang
            int id;
            cout << "\nCari Barang " << endl;
            cout << "Masukkan id untuk barang yang ingin dicari: ";
            cin >> id;

            bool found = false;
            cout << "\n\t\t\t\tBarang Ditemukan\n";
            
            for (int i = 0; i < barangList.size(); i++) {
                if (barangList[i].id_barang == id) {
                	cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
					cout << "|   Id" << "         Nama" << "       	Stock" << "           Harga" << "            Keluaran Tahun     |" << endl;
					cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
                	cout << setw(5) << barangList[i].id_barang
					<< setw(20) << barangList[i].nama
					<< setw(10) << barangList[i].stok
					<< setw(18) << barangList[i].harga
					<< setw(18) << barangList[i].year << endl;
					cout << "+-----+--------------------+--------------+--------------+--------------------------+\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\t\t\t\tBarang tidak ditemukan.\n";
            }
            break;
        }
        case 3:{
        	viewBarangKeluar();
			break;
		}
		case 4:{
			viewBarangMasuk();
			break;
		}
		case 5:{
			menuSettings();
			break;
		}
        case 6:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);
}

int main() {
    string role;
    int pilihanLogin;
    int pilihanMain;
    cout << "-------------------------" << endl;
	cout << "Sistem Inventory Barang" << endl;
	cout << "-------------------------";

    do {
        cout << "\n1. Login\n";
        cout << "2. SignUp\n";
        cout << "3. Keluar\n";
        cout << "Pilih : ";
        cin >> pilihanLogin;

        switch (pilihanLogin) {
        case 1:
            if (login(role)) {
                cout << "Login berhasil sebagai : " << role << endl;
                if (role == "admin") {
                	menuAdmin();  // Menu Admin
                } else if (role == "pegawai") {
                    menuPegawai();  // Menu Pegawai
                }
            } else {
                cout << "Login gagal. Username atau password salah.\n";
            }
            break;
        case 2:
            buatAkun();  // Fungsi untuk membuat akun baru
            break;
        case 3:
            cout << "Terima kasih!.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            continue;
        }
    } while (pilihanLogin != 3);
    return 0;
}

