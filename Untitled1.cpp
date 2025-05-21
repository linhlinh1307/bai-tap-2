
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

// ==================== ENUMS ====================
enum class VaiTro { QuanTriVien, ThuThu, BanDoc };

string vaiTroToString(VaiTro v) {
    switch (v) {
        case VaiTro::QuanTriVien: return "Quan tri viên";
        case VaiTro::ThuThu: return "Thu thu";
        case VaiTro::BanDoc: return "Ban ðoc";
        default: return "Không xác ðinh";
    }
}

enum class TinhTrangMuon { DangMuon, DaTra, QuaHan };

string tinhTrangMuonToString(TinhTrangMuon t) {
    switch (t) {
        case TinhTrangMuon::DangMuon: return "Ðang muon";
        case TinhTrangMuon::DaTra: return "Ða tra";
        case TinhTrangMuon::QuaHan: return "Quá han";
        default: return "Không xác ðinh";
    }
}

// ==================== CLASS SACH ====================
class Sach {
public:
    int maSach;
    string ISBN;
    string tenSach;
    string tacGia;
    string nhaXuatBan;
    int namXuatBan;
    string ngonNgu;
    string theLoai;
    int soTrang;
    string keSach;
    bool coSan;

    Sach() : maSach(0), namXuatBan(0), soTrang(0), coSan(true) {}
    Sach(int ma, string isbn, string ten, string tacgia, string nxb, int nam, string ngonngu,
         string theloai, int trang, string ke)
        : maSach(ma), ISBN(isbn), tenSach(ten), tacGia(tacgia), nhaXuatBan(nxb), namXuatBan(nam),
          ngonNgu(ngonngu), theLoai(theloai), soTrang(trang), keSach(ke), coSan(true) {}

    void inThongTin() const {
        cout << "[" << maSach << "] " << tenSach << " - " << tacGia << " (" << namXuatBan << ") "
             << "ISBN:" << ISBN << " - " << (coSan ? "Con sách" : "Ðang muon") << endl;
    }
};

// ==================== CLASS NGUOI DUNG ====================
class NguoiDung {
public:
    int maNguoiDung;
    string tenDangNhap;
    string matKhau;
    string hoTen;
    string email;
    VaiTro vaiTro;

    NguoiDung() : maNguoiDung(0), vaiTro(VaiTro::BanDoc) {}
    NguoiDung(int ma, string ten, string mk, string hoten, string mail, VaiTro vt)
        : maNguoiDung(ma), tenDangNhap(ten), matKhau(mk), hoTen(hoten), email(mail), vaiTro(vt) {}

    void inThongTin() const {
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

    PhieuMuon() : maPhieu(0), maSach(0), maNguoiDung(0), ngayMuon(0), hanTra(0), ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}
    PhieuMuon(int maPhieu, int maSach, int maNguoiDung, time_t muon, time_t han)
        : maPhieu(maPhieu), maSach(maSach), maNguoiDung(maNguoiDung), ngayMuon(muon), hanTra(han),
          ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}

    void inThongTin() {
        cout << "Mã phieu : " << maPhieu << ", Mã  sách: " << maSach << ", Mã nguoi dùng: " << maNguoiDung
             << ", Ngày muonn: " << ctime(&ngayMuon)
             << ", Han tra: " << ctime(&hanTra)
             << ", Trang thái: " << tinhTrangMuonToString(tinhTrang);
        if (tinhTrang == TinhTrangMuon::DaTra) {
            cout << ", Ngày tra: " << ctime(&ngayTra);
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

    DatTruoc() : maDatTruoc(0), maSach(0), maNguoiDung(0), ngayDat(0), dangHieuLuc(true) {}
    DatTruoc(int ma, int sach, int nguoidung, time_t ngay)
        : maDatTruoc(ma), maSach(sach), maNguoiDung(nguoidung), ngayDat(ngay), dangHieuLuc(true) {}

    void inThongTin() {
        cout << "Mã ðat truoc: " << maDatTruoc << ", Mã sách: " << maSach << ", Mã nguoi dùng: " << maNguoiDung
             << ", Ngày: " << ctime(&ngayDat)
             << ", Hieu luc: " << (dangHieuLuc ? "Con hieu luc" : "H?t hi?u l?c") << endl;
    }
};

// ==================== CLASS THU VIEN ====================
class ThuVien {
private:
    vector<Sach> danhSachSach;
    int maSachCuoi = 0;

public:
    void themSach(const Sach& sach) {
        Sach moi = sach;
        moi.maSach = ++maSachCuoi;
        danhSachSach.push_back(moi);
        cout << "Ðã thêm sách voi ma " << moi.maSach << endl;
    }

    bool suaSach(int ma, const Sach& capNhat) {
        for (auto& s : danhSachSach) {
            if (s.maSach == ma) {
                s = capNhat;
                s.maSach = ma;
                cout << "Ða cap nhat sách ma " << ma << "." << endl;
                return true;
            }
        }
        cout << "Không tim thay sách ma " << ma << "." << endl;
        return false;
    }

    bool xoaSach(int ma) {
        auto it = remove_if(danhSachSach.begin(), danhSachSach.end(),
                            [ma](const Sach& s) { return s.maSach == ma; });
        if (it != danhSachSach.end()) {
            danhSachSach.erase(it, danhSachSach.end());
            cout << "Ða xóa sách ma " << ma << "." << endl;
            return true;
        }
        cout << "Không tim thay sách ma " << ma << "." << endl;
        return false;
    }

    vector<Sach> timKiemSach(const string& tuKhoa) {
        vector<Sach> ketQua;
        string tuKhoaThuong = tuKhoa;
        transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);

        for (const auto& s : danhSachSach) {
            string tongHop = s.tenSach + " " + s.tacGia + " " + s.theLoai + " " + s.nhaXuatBan;
            string tongHopThuong = tongHop;
            transform(tongHopThuong.begin(), tongHopThuong.end(), tongHopThuong.begin(), ::tolower);

            if (tongHopThuong.find(tuKhoaThuong) != string::npos) {
                ketQua.push_back(s);
            }
        }
        return ketQua;
    }

    void sapXepSach(const string& tieuChi) {
        if (tieuChi == "ten") {
            sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
                return a.tenSach < b.tenSach;
            });
        } else if (tieuChi == "tacgia") {
            sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
                return a.tacGia < b.tacGia;
            });
        } else if (tieuChi == "nam") {
            sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
                return a.namXuatBan < b.namXuatBan;
            });
        } else {
            cout << "Tiêu chí sap xep không hop li." << endl;
        }
    }

    void inDanhSachSach() {
        cout << "----- Danh sách sách (" << danhSachSach.size() << " cuón) -----" << endl;
        for (const auto& s : danhSachSach) {
            s.inThongTin();
        }
    }

    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Loi khi mo tep da luu." << endl;
            return;
        }
        for (const auto& s : danhSachSach) {
            fout << s.maSach << "|" << s.ISBN << "|" << s.tenSach << "|" << s.tacGia << "|" << s.nhaXuatBan << "|"
                 << s.namXuatBan << "|" << s.ngonNgu << "|" << s.theLoai << "|" << s.soTrang << "|" << s.keSach << "|"
                 << s.coSan << "\n";
        }
        fout.close();
        cout << "Ða luu sách vào tep " << tenTep << endl;
    }

    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Không có tep de tai sách." << endl;
            return;
        }
        danhSachSach.clear();
        string dong;
        while (getline(fin, dong)) {
            Sach s;
            size_t pos = 0, truoc = 0;
            vector<string> truong;
            while ((pos = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, pos - truoc));
                truoc = pos + 1;
            }
            truong.push_back(dong.substr(truoc));

            if (truong.size() == 11) {
                s.maSach = stoi(truong[0]);
                s.ISBN = truong[1];
                s.tenSach = truong[2];
                s.tacGia = truong[3];
                s.nhaXuatBan = truong[4];
                s.namXuatBan = stoi(truong[5]);
                s.ngonNgu = truong[6];
                s.theLoai = truong[7];
                s.soTrang = stoi(truong[8]);
                s.keSach = truong[9];
                s.coSan = (truong[10] == "1");

                danhSachSach.push_back(s);
                if (s.maSach > maSachCuoi) maSachCuoi = s.maSach;
            }
        }
        fin.close();
        cout << "Ða tai sách tu tep " << tenTep << endl;
    }
};
// ==================== QUAN LI NGUOI DÙNG ====================

class QuanLyNguoiDung {
private:
    vector<NguoiDung> danhSachNguoiDung;   // Danh sách nguoi dùng
    int idCuoi = 0;                   // ID nguoi dùng cuoi cùng

public:
    // Thêm nguoi dùng moi
    void themNguoiDung(const NguoiDung& nguoiDung) {
        NguoiDung nguoiMoi = nguoiDung;
        nguoiMoi.maNguoiDung = ++idCuoi;
        danhSachNguoiDung.push_back(nguoiMoi);
        cout << "Ð? thêm ngý?i dùng v?i ID " << nguoiMoi.maNguoiDung << endl;
    }

    // Sua thông tin nguoi dùng theo ID
    bool suaNguoiDung(int id, const NguoiDung& nguoiCapNhat) {
        for (auto& u : danhSachNguoiDung) {
            if (u.maNguoiDung == id) {
                u = nguoiCapNhat;
                u.maNguoiDung = id; // Giu nguyên ID
                cout << "Ða cap nhat nguoi dùng có ID " << id << "." << endl;
                return true;
            }
        }
        cout << "Không tim thay nguoi dùng có ID " << id << "." << endl;
        return false;
    }

    // Xóa nguoi dùng theo ID
    bool xoaNguoiDung(int id) {
        auto it = remove_if(danhSachNguoiDung.begin(), danhSachNguoiDung.end(),
                            [id](const NguoiDung& u) { return u.maNguoiDung == id; });
        if (it != danhSachNguoiDung.end()) {
            danhSachNguoiDung.erase(it, danhSachNguoiDung.end());
            cout << "Ða xóa nguoi dùng có ID " << id << "." << endl;
            return true;
        }
        cout << "Không tim thay nguoi dùng có ID " << id << "." << endl;
        return false;
    }

    // Tim kiem nguoi dùng theo tu khóa
    vector<NguoiDung> timKiemNguoiDung(const string& tuKhoa) {
        vector<NguoiDung> ketQua;
        string tuKhoaThuong = tuKhoa;
        transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);

        for (const auto& u : danhSachNguoiDung) {
            string ketHop = u.maNguoiDung + " " + u.hoTen + " " + u.email;
            string ketHopThuong = ketHop;
            transform(ketHopThuong.begin(), ketHopThuong.end(), ketHopThuong.begin(), ::tolower);

            if (ketHopThuong.find(tuKhoaThuong) != string::npos) {
                ketQua.push_back(u);
            }
        }
        return ketQua;
    }

    // In toàn bo danh sách nguoi dùng
    void inTatCaNguoiDung() {
        cout << "----- Danh sách nguoi dùng (" << danhSachNguoiDung.size() << " nguoi) -----" << endl;
        for (const auto& u : danhSachNguoiDung) {
            u.inThongTin();
        }
    }

    // Luu danh sách nguoi dùng vào tep
    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Loi khi mo tep ðe luu nguoi dùng." << endl;
            return;
        } 
        for (const auto& u : danhSachNguoiDung) {
            fout << u.maNguoiDung << "|" << u.tenDangNhap << "|" << u.matKhau << "|" << u.hoTen << "|"
                 << u.email << "|" << (int)u.vaiTro << "\n";
        }
        fout.close();
        cout << "Ða luu nguoi dùng vào tep " << tenTep << endl;
    }

    // Tai danh sách nguoi dùng tu tep
    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Không có tep nào ðe tai nguoi dùng." << endl;
            return;
        }
        danhSachNguoiDung.clear();
        string dong;
        while (getline(fin, dong)) {
            NguoiDung u;
            size_t viTri = 0, truoc = 0;
            vector<string> truong;
            while ((viTri = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, viTri - truoc));
                truoc = viTri + 1;
            }
            truong.push_back(dong.substr(truoc));

            if (truong.size() == 6) {
                u.maNguoiDung = stoi(truong[0]);
                u.tenDangNhap = truong[1];
                u.matKhau = truong[2];
                u.hoTen = truong[3];
                u.email = truong[4];
                u.vaiTro = static_cast<VaiTro>(stoi(truong[5]));

                danhSachNguoiDung.push_back(u);
                if (u.maNguoiDung > idCuoi) idCuoi = u.maNguoiDung;
            }
        }
        fin.close();
        cout << "Ða tai nguoi dùng tu tep " << tenTep << endl;
    }
};
// ==================== QUAN LI NGUOI D�NG ====================

class QuanLyNguoiDung {
private:
    vector<NguoiDung> danhSachNguoiDung;   // Danh s�ch nguoi d�ng
    int idCuoi = 0;                   // ID nguoi d�ng cuoi c�ng

public:
    // Th�m nguoi d�ng moi
    void themNguoiDung(const NguoiDung& nguoiDung) {
        NguoiDung nguoiMoi = nguoiDung;
        nguoiMoi.maNguoiDung = ++idCuoi;
        danhSachNguoiDung.push_back(nguoiMoi);
        cout << "�? th�m ng�?i d�ng v?i ID " << nguoiMoi.maNguoiDung << endl;
    }

    // Sua th�ng tin nguoi d�ng theo ID
    bool suaNguoiDung(int id, const NguoiDung& nguoiCapNhat) {
        for (auto& u : danhSachNguoiDung) {
            if (u.maNguoiDung == id) {
                u = nguoiCapNhat;
                u.maNguoiDung = id; // Giu nguy�n ID
                cout << "�a cap nhat nguoi d�ng c� ID " << id << "." << endl;
                return true;
            }
        }
        cout << "Kh�ng tim thay nguoi d�ng c� ID " << id << "." << endl;
        return false;
    }

    // X�a nguoi d�ng theo ID
    bool xoaNguoiDung(int id) {
        auto it = remove_if(danhSachNguoiDung.begin(), danhSachNguoiDung.end(),
                            [id](const NguoiDung& u) { return u.maNguoiDung == id; });
        if (it != danhSachNguoiDung.end()) {
            danhSachNguoiDung.erase(it, danhSachNguoiDung.end());
            cout << "�a x�a nguoi d�ng c� ID " << id << "." << endl;
            return true;
        }
        cout << "Kh�ng tim thay nguoi d�ng c� ID " << id << "." << endl;
        return false;
    }

    // Tim kiem nguoi d�ng theo tu kh�a
    vector<NguoiDung> timKiemNguoiDung(const string& tuKhoa) {
        vector<NguoiDung> ketQua;
        string tuKhoaThuong = tuKhoa;
        transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);

        for (const auto& u : danhSachNguoiDung) {
            string ketHop = u.maNguoiDung + " " + u.hoTen + " " + u.email;
            string ketHopThuong = ketHop;
            transform(ketHopThuong.begin(), ketHopThuong.end(), ketHopThuong.begin(), ::tolower);

            if (ketHopThuong.find(tuKhoaThuong) != string::npos) {
                ketQua.push_back(u);
            }
        }
        return ketQua;
    }

    // In to�n bo danh s�ch nguoi d�ng
    void inTatCaNguoiDung() {
        cout << "----- Danh s�ch nguoi d�ng (" << danhSachNguoiDung.size() << " nguoi) -----" << endl;
        for (const auto& u : danhSachNguoiDung) {
            u.inThongTin();
        }
    }

    // Luu danh s�ch nguoi d�ng v�o tep
    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Loi khi mo tep �e luu nguoi d�ng." << endl;
            return;
        } 
        for (const auto& u : danhSachNguoiDung) {
            fout << u.maNguoiDung << "|" << u.tenDangNhap << "|" << u.matKhau << "|" << u.hoTen << "|"
                 << u.email << "|" << (int)u.vaiTro << "\n";
        }
        fout.close();
        cout << "�a luu nguoi d�ng v�o tep " << tenTep << endl;
    }

    // Tai danh s�ch nguoi d�ng tu tep
    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Kh�ng c� tep n�o �e tai nguoi d�ng." << endl;
            return;
        }
        danhSachNguoiDung.clear();
        string dong;
        while (getline(fin, dong)) {
            NguoiDung u;
            size_t viTri = 0, truoc = 0;
            vector<string> truong;
            while ((viTri = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, viTri - truoc));
                truoc = viTri + 1;
            }
            truong.push_back(dong.substr(truoc));

            if (truong.size() == 6) {
                u.maNguoiDung = stoi(truong[0]);
                u.tenDangNhap = truong[1];
                u.matKhau = truong[2];
                u.hoTen = truong[3];
                u.email = truong[4];
                u.vaiTro = static_cast<VaiTro>(stoi(truong[5]));

                danhSachNguoiDung.push_back(u);
                if (u.maNguoiDung > idCuoi) idCuoi = u.maNguoiDung;
            }
        }
        fin.close();
        cout << "�a tai nguoi d�ng tu tep " << tenTep << endl;
    }
};


