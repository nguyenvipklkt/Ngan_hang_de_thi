#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int DAPAN = 4;

class CauHoi {
private:
    std::string maCauHoi;
    std::string noiDung;
    std::string dapAn[DAPAN];
    std::string dapAnDung;

public:
    CauHoi() {}

    CauHoi(std::string maCauHoi, std::string noiDung, std::string dapAn[DAPAN], std::string dapAnDung) {
        this->maCauHoi = maCauHoi;
        this->noiDung = noiDung;
        for (int i = 0; i < DAPAN; ++i) {
            this->dapAn[i] = dapAn[i];
        }
        this->dapAnDung = dapAnDung;
    }

    void hienThi() const {
        std::cout << maCauHoi << std::endl;
        std::cout << noiDung << std::endl;
        for (int i = 0; i < DAPAN; ++i) {
            std::cout << dapAn[i] << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
    }

    std::string getMaCauHoi() const { return maCauHoi; }
    std::string getNoiDung() const { return noiDung; }
    std::string getDapAn(int index) const { return dapAn[index]; }
    std::string getDapAnDung() const { return dapAnDung; }

    void setNoiDung(const std::string& nd) { noiDung = nd; }
    void setDapAn(int index, const std::string& da) { dapAn[index] = da; }
    void setDapAnDung(const std::string& dad) { dapAnDung = dad; }
};

void hienThiTatCaCauHoi(const std::vector<CauHoi>& danhSachCauHoi) {
    for (const auto& cauHoi : danhSachCauHoi) {
        cauHoi.hienThi();
    }
}

void ghiDanhSachCauHoiVaoFile(const std::vector<CauHoi>& danhSachCauHoi) {
    std::ofstream file("danh_sach_cau_hoi.txt");
    if (file.is_open()) {
        for (const auto& cauHoi : danhSachCauHoi) {
            file << cauHoi.getMaCauHoi() << std::endl;
            file << cauHoi.getNoiDung() << std::endl;
            for (int i = 0; i < DAPAN; ++i) {
                file << cauHoi.getDapAn(i) << std::endl;
            }
            file << cauHoi.getDapAnDung() << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Khong the ghi vao file." << std::endl;
    }
}

bool kiemTraTrungMaCauHoi(const std::vector<CauHoi>& danhSachCauHoi, const std::string& maCauHoi) {
    for (const auto& cauHoi : danhSachCauHoi) {
        if (cauHoi.getMaCauHoi() == ("Ma cau hoi : " + maCauHoi)) {
            return true;
        }
    }
    return false;
}

void themCauHoi(std::vector<CauHoi>& danhSachCauHoi) {
    std::string maCauHoi, noiDung, dapAn[DAPAN], dapAnDung;

    std::cout << "Nhap ma cau hoi: ";
    std::cin.ignore(); // Để tránh trường hợp nhập maCauHoi bị ảnh hưởng bởi buffer của std::cin
    std::getline(std::cin, maCauHoi);

    if (kiemTraTrungMaCauHoi(danhSachCauHoi, maCauHoi)) {
        std::cerr << "Ma cau hoi da ton tai. Vui long nhap ma cau hoi khac." << std::endl;
        return;
    }

    std::cout << "Nhap noi dung cau hoi: ";
    std::getline(std::cin, noiDung);

    std::cout << "Nhap dap an A: ";
    std::getline(std::cin, dapAn[0]);

    std::cout << "Nhap dap an B: ";
    std::getline(std::cin, dapAn[1]);

    std::cout << "Nhap dap an C: ";
    std::getline(std::cin, dapAn[2]);

    std::cout << "Nhap dap an D: ";
    std::getline(std::cin, dapAn[3]);

    std::cout << "Nhap dap an dung (A/B/C/D): ";
    std::getline(std::cin, dapAnDung);

    for (int i = 0; i < DAPAN; i++) {
        if (i == 0) {
            dapAn[i] = "A. " + dapAn[i];
        }
        else if (i == 1) {
            dapAn[i] = "B. " + dapAn[i];
        }
        else if (i == 2) {
            dapAn[i] = "C. " + dapAn[i];
        }
        else if (i == 3) {
            dapAn[i] = "D. " + dapAn[i];
        }
    }

    maCauHoi = "Ma cau hoi : " + maCauHoi;
    noiDung = "Noi dung : " + noiDung;
    dapAnDung = "Dap an chinh xac : " + dapAnDung;
    CauHoi ch(maCauHoi, noiDung, dapAn, dapAnDung);
    danhSachCauHoi.push_back(ch);
    // Ghi câu hỏi mới vào file
    ghiDanhSachCauHoiVaoFile(danhSachCauHoi);
}

void docDuLieuTuFile(std::vector<CauHoi>& danhSachCauHoi) {
    std::ifstream file("danh_sach_cau_hoi.txt");
    if (file.is_open()) {
        std::string maCauHoi, noiDung, dapAn[DAPAN], dapAnDung;
        while (std::getline(file, maCauHoi) && std::getline(file, noiDung)) {
            for (int i = 0; i < DAPAN; ++i) {
                std::getline(file, dapAn[i]);
            }
            std::getline(file, dapAnDung);
            CauHoi ch(maCauHoi, noiDung, dapAn, dapAnDung);
            danhSachCauHoi.push_back(ch);
        }
        file.close();
    }
    else {
        std::cerr << "Khong the mo file." << std::endl;
    }
}

void suaCauHoi(std::vector<CauHoi>& danhSachCauHoi) {
    std::string maCauHoi;
    std::cout << "Nhap ma cau hoi can sua: ";
    std::cin.ignore();
    std::getline(std::cin, maCauHoi);

    bool found = false;
    for (auto& cauHoi : danhSachCauHoi) {
        if (cauHoi.getMaCauHoi() == ("Ma cau hoi : " + maCauHoi)) {
            found = true;
            std::string noiDung, dapAn[DAPAN], dapAnDung;

            std::cout << "Nhap noi dung moi cua cau hoi: ";
            std::getline(std::cin, noiDung);

            std::cout << "Nhap dap an A moi: ";
            std::getline(std::cin, dapAn[0]);

            std::cout << "Nhap dap an B moi: ";
            std::getline(std::cin, dapAn[1]);

            std::cout << "Nhap dap an C moi: ";
            std::getline(std::cin, dapAn[2]);

            std::cout << "Nhap dap an D moi: ";
            std::getline(std::cin, dapAn[3]);

            std::cout << "Nhap dap an dung moi (A/B/C/D): ";
            std::getline(std::cin, dapAnDung);

            cauHoi.setNoiDung("Noi dung : " + noiDung);
            for (int i = 0; i < DAPAN; i++) {
                if (i == 0) {
                    cauHoi.setDapAn(i, "A. " + dapAn[i]);
                }
                else if (i == 1) {
                    cauHoi.setDapAn(i, "B. " + dapAn[i]);
                }
                else if (i == 2) {
                    cauHoi.setDapAn(i, "C. " + dapAn[i]);
                }
                else if (i == 3) {
                    cauHoi.setDapAn(i, "D. " + dapAn[i]);
                }
            }
            cauHoi.setDapAnDung("Dap an chinh xac : " + dapAnDung);
            // Ghi danh sách câu hỏi đã sửa vào file
            ghiDanhSachCauHoiVaoFile(danhSachCauHoi);
            std::cout << "Da sua cau hoi thanh cong." << std::endl;
            break;
        }
    }

    if (!found) {
        std::cerr << "Khong tim thay ma cau hoi: " << maCauHoi << std::endl;
    }
}

void xoaCauHoi(std::vector<CauHoi>& danhSachCauHoi) {
    std::string maCauHoi;
    std::cout << "Nhap ma cau hoi can xoa: ";
    std::cin.ignore();
    std::getline(std::cin, maCauHoi);

    auto it = std::remove_if(danhSachCauHoi.begin(), danhSachCauHoi.end(),
        [&maCauHoi](const CauHoi& cauHoi) {
            return cauHoi.getMaCauHoi() == ("Ma cau hoi : " + maCauHoi);
        });

    if (it != danhSachCauHoi.end()) {
        danhSachCauHoi.erase(it, danhSachCauHoi.end());
        // Ghi danh sách câu hỏi sau khi xóa vào file
        ghiDanhSachCauHoiVaoFile(danhSachCauHoi);
        std::cout << "Da xoa cau hoi thanh cong." << std::endl;
    }
    else {
        std::cerr << "Khong tim thay ma cau hoi: " << maCauHoi << std::endl;
    }
}

void hoanVi(int a[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        std::swap(a[i], a[j]);
    }
}

void thiThu(const std::vector<CauHoi>& danhSachCauHoi, int soLuongCauHoi) {
    if (soLuongCauHoi > danhSachCauHoi.size()) {
        std::cerr << "Khong du cau hoi de thi." << std::endl;
        return;
    }

    int* chiso = new int[danhSachCauHoi.size()];
    for (int i = 0; i < danhSachCauHoi.size(); i++) {
        chiso[i] = i;
    }

    hoanVi(chiso, danhSachCauHoi.size());

    int soCauDung = 0;
    std::ofstream lichSu("lich_su.txt", std::ios::app);

    for (int i = 0; i < soLuongCauHoi; i++) {
        const CauHoi& cauHoi = danhSachCauHoi[chiso[i]];
        cauHoi.hienThi();
        std::string dapAn;
        std::cout << "Nhap dap an cua ban (A/B/C/D): ";
        std::cin >> dapAn;

        //lichSu << "Ma cau hoi: " << cauHoi.getMaCauHoi() << std::endl;
        //lichSu << "Noi dung: " << cauHoi.getNoiDung() << std::endl;
        /*for (int j = 0; j < DAPAN; ++j) {
            lichSu << cauHoi.getDapAn(j) << std::endl;
        }*/
        //lichSu << "Dap an ban chon: " << dapAn << std::endl;
        //lichSu << "Dap an dung: " << cauHoi.getDapAnDung() << std::endl;
        //lichSu << "-----------------------------" << std::endl;

        // Extracting the correct answer character from dapAnDung
        std::string correctAnswer = cauHoi.getDapAnDung();
        if (("Dap an chinh xac : " + dapAn) == correctAnswer) {
            soCauDung++;
        }
    }

    double diem = (double)soCauDung / soLuongCauHoi * 10;
    std::cout << "So cau tra loi dung: " << soCauDung << "/" << soLuongCauHoi << std::endl;
    std::cout << "Diem cua ban: " << diem << std::endl;
    lichSu << "So cau tra loi dung: " << soCauDung << "/" << soLuongCauHoi << std::endl;
    lichSu << "Diem cua ban: " << diem << std::endl;
    lichSu << "=============================" << std::endl;

    lichSu.close();
    delete[] chiso;
}


void hienThiLichSu() {
    std::ifstream file("lich_su.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Khong the mo file lich su." << std::endl;
    }
}

int main() {
    std::vector<CauHoi> danhSachCauHoi;
    docDuLieuTuFile(danhSachCauHoi);

    int luaChon;
    do {
        std::cout << "1. Them cau hoi" << std::endl;
        std::cout << "2. Hien thi tat ca cau hoi" << std::endl;
        std::cout << "3. Sua cau hoi" << std::endl;
        std::cout << "4. Xoa cau hoi" << std::endl;
        std::cout << "5. Thi thu" << std::endl;
        std::cout << "6. Hien thi lich su thi thu" << std::endl;
        std::cout << "0. Thoat" << std::endl;
        std::cout << "Nhap lua chon: ";
        std::cin >> luaChon;

        switch (luaChon) {
        case 1:
            themCauHoi(danhSachCauHoi);
            break;
        case 2:
            hienThiTatCaCauHoi(danhSachCauHoi);
            break;
        case 3:
            suaCauHoi(danhSachCauHoi);
            break;
        case 4:
            xoaCauHoi(danhSachCauHoi);
            break;
        case 5: {
            int soLuongCauHoi;
            std::cout << "Nhap so luong cau hoi muon thi: ";
            std::cin >> soLuongCauHoi;
            thiThu(danhSachCauHoi, soLuongCauHoi);
            break;
        }
        case 6:
            hienThiLichSu();
            break;
        case 0:
            std::cout << "Thoat chuong trinh." << std::endl;
            break;
        default:
            std::cerr << "Lua chon khong hop le." << std::endl;
            break;
        }
    } while (luaChon != 0);

    return 0;
}
