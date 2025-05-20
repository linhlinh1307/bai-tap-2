#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

const std::string FILE_PATH = "thu vien.txt";
// ==================== ENUMS ====================
enum class VaiTro { QuanTriVien, ThuThu, BanDoc };

string vaiTroToString(VaiTro v) {
    switch (v) {
        case VaiTro::QuanTriVien: return "Quản trị viên";
        case VaiTro::ThuThu: return "Thủ thư";
        case VaiTro::BanDoc: return "Bạn đọc";
        default: return "Không xác định";
    }
}

enum class TinhTrangMuon { DangMuon, DaTra, QuaHan };

string tinhTrangMuonToString(TinhTrangMuon t) {
    switch (t) {
        case TinhTrangMuon::DangMuon: return "Đang mượn";
        case TinhTrangMuon::DaTra: return "Đã trả";
        case TinhTrangMuon::QuaHan: return "Quá hạn";
        default: return "Không xác định";
    }
}

// ==================== CLASS SACH ====================
class Sach {
private:
    int m_maSach, m_namXuatBan, m_soLuong;
    string m_ISBN, m_tenSach, m_tacGia, m_nhaXuatBan, m_keSach;
    //bool m_CoSan;
public:
    Sach(int ma, int nam, int so_luong, string isbn, string ten, string tac_gia, string nxb, string ke) //bool co_san
        : m_maSach(ma), m_namXuatBan(nam), m_soLuong(so_luong), m_ISBN(isbn), m_tenSach(ten), m_tacGia(tac_gia), m_nhaXuatBan(nxb), 
        m_keSach(ke) {}; //m_CoSan(co_san) 

    string inThongTin() {
        return ("[" + to_string(m_maSach) + "] " + m_tenSach + " - " + m_tacGia + " (" + to_string(m_namXuatBan) + ") " +
             "ISBN:" + m_ISBN + " - ");
    }
};

// ==================== CLASS NGUOI DUNG ====================
class NguoiDung {
public:
    int maNguoiDung;
    string tenDangNhap, matKhau, hoTen, email;
    VaiTro vaiTro;

    NguoiDung(int ma, string ten, string mk, string hoten, string mail, VaiTro vt)
        : maNguoiDung(ma), tenDangNhap(ten), matKhau(mk), hoTen(hoten), email(mail), vaiTro(vt) {}

    void inThongTin() {
        cout << "[" << maNguoiDung << "] " << hoTen << " (" << tenDangNhap << ") - Vai tro: " << vaiTroToString(vaiTro) << endl;
    }
};

// ==================== CLASS PHIEU MUON ====================
class PhieuMuon {
public:
    int maPhieu;
    int maSach;
    int maNguoiDung;
    time_t ngayMuon;
    time_t hanTra;
    time_t ngayTra;
    TinhTrangMuon tinhTrang;

    PhieuMuon(int maPhieu, int maSach, int maNguoiDung, time_t muon, time_t han)
        : maPhieu(maPhieu), maSach(maSach), maNguoiDung(maNguoiDung), ngayMuon(muon), hanTra(han),
          ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}

    void inThongTin() {
        cout << "Mã phiếu : " << maPhieu << ", Mã  sách: " << maSach << ", Mã người dùng: " << maNguoiDung
             << ", Ngày mượn: " << ctime(&ngayMuon)
             << ", Hạn trả: " << ctime(&hanTra)
             << ", Trạng thái: " << tinhTrangMuonToString(tinhTrang);
        if (tinhTrang == TinhTrangMuon::DaTra) {
            cout << ", Ngày trả: " << ctime(&ngayTra);
        }
    }
};

// ==================== CLASS DAT TRUOC ====================
class DatTruoc {
public:
    int maDatTruoc;
    int maSach;
    int maNguoiDung;
    time_t ngayDat;
    bool dangHieuLuc;

    DatTruoc(int ma, int sach, int nguoidung, time_t ngay)
        : maDatTruoc(ma), maSach(sach), maNguoiDung(nguoidung), ngayDat(ngay), dangHieuLuc(true) {}

    void inThongTin() {
        cout << "Mã đặt trước: " << maDatTruoc << ", Mã sách: " << maSach << ", Mã người dùng: " << maNguoiDung
             << ", Ngày: " << ctime(&ngayDat)
             << ", Hiệu lực: " << (dangHieuLuc ? "Còn hiệu lực" : "Hết hiệu lực") << endl;
    }
};

// ==================== INPUT ========================
Sach sach() {

    int ma, namXuatBan, soLuong;
    string ISBN, tenSach, tacGia, nhaXuatBan, ngonNgu, theLoai, keSach;

    cout << "Nhập mã sách (số nguyên dương): "; cin >> ma;

    cout << "Nhập năm xuất bản: "; cin >> namXuatBan;

    cout << "Nhập số lượng sách: "; cin >> soLuong;

    cout << "Nhập mã ISBN: "; getline(cin >> ws, ISBN);

    cout << "Nhập tên sách: "; getline(cin >> ws, tenSach);

    cout << "Nhập tên tác giả: "; getline(cin >> ws, tacGia);

    cout << "Nhập tên nhà xuất bản: "; getline(cin >> ws, nhaXuatBan);

    cout << "Nhập kệ sách: "; getline(cin >> ws, keSach);

    return Sach(ma, namXuatBan, soLuong, ISBN, tenSach, tacGia, nhaXuatBan, keSach);
}
void them_sach() {
    char tiep_tuc {};
    ofstream outFile(FILE_PATH, ios::app);
    if (!outFile.is_open()) {
        cout << "Lỗi: Không thể mở file!" << endl;
        return;
    }
    do {
        cout << "\nNhập thông tin sách: \n";
        Sach book = sach();
        outFile << '\n' << book.inThongTin();
        cout << "Nhập thêm sách? (y/n)\n";
        cin >> tiep_tuc;
    } while (tiep_tuc == 'y' || tiep_tuc == 'Y');
    outFile.close();
}
void view_all() {
    ifstream inFile;
    string line;
    inFile.open(FILE_PATH, ios::in);
    if (!inFile.is_open()) {
        cout << "Lỗi: Không thể mở file!" << endl;
        return;
    }
    else {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }

}

string toLower(const string& str) {
    stringstream ss;
    for (char c : str) {
        ss << (char)tolower(c);
    }
    return ss.str();
}

void find_book() {
   ifstream inFile(FILE_PATH, ios::in);
   string line;
   string key_word {}; cout << "Nhập từ khóa cần tìm: "; getline(cin >> ws, key_word);
   bool founded = false;
   if (!inFile.is_open()) {
    cout << "Lỗi: không thể mở file!" << endl;
    return;
   }
   else {
    while (getline(inFile, line)) {
        if (toLower(line).find(key_word) != string::npos) {
            cout << line << endl;
            founded = true;
        }
    }
    if (!founded) cout << "Không tìm thấy\n";
   }
}


void chuc_nang() {
    cout << "====================QUẢN LÝ THƯ VIỆN====================\n\n";
    int lua_chon; 
    do { 
        
        cout << "0. Thoát chương trình\n"
             << "1. Thêm sách\n" 
             << "2. Xem toàn bộ sách\n" 
             << "3. Tìm kiếm sách\n" 
             << "Chọn số từ (0-3): "; 
        while (!(cin >> lua_chon)) {  
            cin.clear();  
            cin.ignore(1000, '\n');  
            cout << "Lựa chọn không hợp lệ! Vui lòng nhập một số từ 0 đến 3: ";
        }
        switch (lua_chon) {
            case 0:
                return;
            case 1: 
                them_sach();
                break;
            case 2: 
                view_all();
                break;
            case 3:
                find_book();
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại.\n";
        }
    } while (lua_chon != 0);
    
}

int main() {
    chuc_nang();
    
    return 0;
}
