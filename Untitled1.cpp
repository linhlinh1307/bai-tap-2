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
        case VaiTro::QuanTriVien: return "Quan tri vi�n";
        case VaiTro::ThuThu: return "Thu thu";
        case VaiTro::BanDoc: return "Ban �oc";
        default: return "Kh�ng x�c �inh";
    }
}

enum class TinhTrangMuon { DangMuon, DaTra, QuaHan };

string tinhTrangMuonToString(TinhTrangMuon t) {
    switch (t) {
        case TinhTrangMuon::DangMuon: return "�ang muon";
        case TinhTrangMuon::DaTra: return "�a tra";
        case TinhTrangMuon::QuaHan: return "Qu� han";
        default: return "Kh�ng x�c �inh";
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

    void inThongTin() {
        cout << "[" << maSach << "] " << tenSach << " - " << tacGia << " (" << namXuatBan << ") "
             << "ISBN:" << ISBN << " - " << (coSan ? "Con s�ch" : "�ang muon") << endl;
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

    PhieuMuon() : maPhieu(0), maSach(0), maNguoiDung(0), ngayMuon(0), hanTra(0), ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}
    PhieuMuon(int maPhieu, int maSach, int maNguoiDung, time_t muon, time_t han)
        : maPhieu(maPhieu), maSach(maSach), maNguoiDung(maNguoiDung), ngayMuon(muon), hanTra(han),
          ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}

    void inThongTin() {
        cout << "M� phieu : " << maPhieu << ", M�  s�ch: " << maSach << ", M� nguoi d�ng: " << maNguoiDung
             << ", Ng�y muonn: " << ctime(&ngayMuon)
             << ", Han tra: " << ctime(&hanTra)
             << ", Trang th�i: " << tinhTrangToString(tinhTrang);
        if (tinhTrang == TinhTrangMuon::DaTra) {
            cout << ", Ng�y tra: " << ctime(&ngayTra);
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
        cout << "M� �at truoc: " << maDatTruoc << ", M� s�ch: " << maSach << ", M� nguoi d�ng: " << maNguoiDung
             << ", Ng�y: " << ctime(&ngayDat)
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
        cout << "�� th�m s�ch voi ma " << moi.maSach << endl;
    }

    bool suaSach(int ma, const Sach& capNhat) {
        for (auto& s : danhSachSach) {
            if (s.maSach == ma) {
                s = capNhat;
                s.maSach = ma;
                cout << "�a cap nhat s�ch ma " << ma << "." << endl;
                return true;
            }
        }
        cout << "Kh�ng tim thay s�ch ma " << ma << "." << endl;
        return false;
    }

    bool xoaSach(int ma) {
        auto it = remove_if(danhSachSach.begin(), danhSachSach.end(),
                            [ma](const Sach& s) { return s.maSach == ma; });
        if (it != danhSachSach.end()) {
            danhSachSach.erase(it, danhSachSach.end());
            cout << "�a x�a s�ch ma " << ma << "." << endl;
            return true;
        }
        cout << "Kh�ng tim thay s�ch ma " << ma << "." << endl;
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
            cout << "Ti�u ch� sap xep kh�ng hop li." << endl;
        }
    }

    void inDanhSachSach() {
        cout << "----- Danh s�ch s�ch (" << danhSachSach.size() << " cu�n) -----" << endl;
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
        cout << "�a luu s�ch v�o tep " << tenTep << endl;
    }

    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Kh�ng c� tep de tai s�ch." << endl;
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
        cout << "�a tai s�ch tu tep " << tenTep << endl;
    }
};

