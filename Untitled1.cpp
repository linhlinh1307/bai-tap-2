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

    void inThongTin() {
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
        cout << "Mã phieu : " << maPhieu << ", Mã  sách: " << maSach << ", Mã nguoi dùng: " << maNguoiDung
             << ", Ngày muonn: " << ctime(&ngayMuon)
             << ", Han tra: " << ctime(&hanTra)
             << ", Trang thái: " << tinhTrangToString(tinhTrang);
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
             << ", Hieu luc: " << (dangHieuLuc ? "Con hieu luc" : "Het hieu luc") << endl;
    }
};
