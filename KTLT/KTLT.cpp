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
        std::cout << "Khong tim thay ma cau hoi." << std::endl;
    }
}

void xoaCauHoi(std::vector<CauHoi>& danhSachCauHoi) {
    std::string maCauHoi;
    std::cout << "Nhap ma cau hoi can xoa: ";
    std::cin.ignore();
    std::getline(std::cin, maCauHoi);

    auto it = danhSachCauHoi.begin();
    bool found = false;
    while (it != danhSachCauHoi.end()) {
        if ((it->getMaCauHoi()) == ("Ma cau hoi : " + maCauHoi)) {
            found = true;
            it = danhSachCauHoi.erase(it);
            std::cout << "Da xoa cau hoi thanh cong." << std::endl;
        }
        else {
            ++it;
        }
    }

    if (!found) {
        std::cerr << "Khong tim thay cau hoi voi ma cau hoi: " << maCauHoi << std::endl;
    }
    else {
        // Cập nhật danh sách câu hỏi vào file
        ghiDanhSachCauHoiVaoFile(danhSachCauHoi);
    }
}

void ghiDeVaoFile(const std::vector<CauHoi>& danhSachCauHoi) {
    std::ofstream file("de_thi.txt");
    if (file.is_open()) {
        for (const auto& cauHoi : danhSachCauHoi) {
            file << cauHoi.getMaCauHoi() << std::endl;
            file << cauHoi.getNoiDung() << std::endl;
            for (int i = 0; i < DAPAN; ++i) {
                file << cauHoi.getDapAn(i) << std::endl;
            }
            // Do not write the correct answer to the file
            // file << cauHoi.getDapAnDung() << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Khong the ghi vao file." << std::endl;
    }
}

void docDeTuFile(std::vector<CauHoi>& danhSachCauHoi) {
    std::ifstream file("de_thi.txt");
    if (file.is_open()) {
        std::string maCauHoi, noiDung, dapAn[DAPAN];
        while (std::getline(file, maCauHoi) && std::getline(file, noiDung)) {
            for (int i = 0; i < DAPAN; ++i) {
                std::getline(file, dapAn[i]);
            }
            CauHoi ch(maCauHoi, noiDung, dapAn, "");
            danhSachCauHoi.push_back(ch);
        }
        file.close();
    }
    else {
        std::cerr << "Khong the mo file." << std::endl;
    }
}


void sinhDeThiNgauNhien(std::vector<CauHoi>& danhSachCauHoi, int soCauHoi) {
    std::vector<CauHoi> deThi;
    std::srand(std::time(0));
    std::random_shuffle(danhSachCauHoi.begin(), danhSachCauHoi.end());
    for (int i = 0; i < soCauHoi && i < danhSachCauHoi.size(); ++i) {
        deThi.push_back(danhSachCauHoi[i]);
    }
    ghiDeVaoFile(deThi);
    std::cout << "Da tao de thi voi " << soCauHoi << " cau hoi va luu vao file de_thi.txt" << std::endl;
}

void thi(const std::vector<CauHoi>& danhSachCauHoi) {
    std::ifstream file("danh_sach_cau_hoi.txt");
    if (!file.is_open()) {
        std::cerr << "Khong the mo file." << std::endl;
        return;
    }

    std::string maCauHoi, noiDung, dapAn[DAPAN], dapAnDung;
    int diem = 0;
    std::string dapAnCuaBan;

    // Duyệt qua từng câu hỏi trong đề
    for (int i = 0; i < danhSachCauHoi.size(); ++i) {
        bool found = false;
        file.clear(); // Đặt lại trạng thái của file
        file.seekg(0); // Di chuyển con trỏ về đầu file

        // Đọc từng câu hỏi từ file danh_sach_cau_hoi.txt
        while (std::getline(file, maCauHoi)) {
            std::getline(file, noiDung);
            for (int j = 0; j < DAPAN; ++j) {
                std::getline(file, dapAn[j]);
            }
            std::getline(file, dapAnDung);

            // So sánh mã câu hỏi
            if (maCauHoi == danhSachCauHoi[i].getMaCauHoi()) {
                found = true;
                // So sánh đáp án
                std::cout << "Cau hoi " << (i + 1) << ":" << std::endl;
                danhSachCauHoi[i].hienThi();
                std::cout << "Nhap dap an cua ban (A/B/C/D): ";
                std::cin >> dapAnCuaBan;
                std::cout << std::endl;
                if (("Dap an chinh xac : " + dapAnCuaBan) == dapAnDung) {
                    diem++;
                }
                break;
            }
        }

        if (!found) {
            std::cerr << "Khong tim thay cau hoi co ma: " << danhSachCauHoi[i].getMaCauHoi() << std::endl;
        }
    }
    std::cout << "Ban da tra loi dung " << diem << " tren " << danhSachCauHoi.size() << " cau hoi." << std::endl;
    file.close();
}


int main() {
    std::vector<CauHoi> danhSachCauHoi;

    docDuLieuTuFile(danhSachCauHoi);

    int luaChon;
    do {
        std::cout << "1. Hien thi tat ca cac cau hoi" << std::endl;
        std::cout << "2. Them cau hoi moi" << std::endl;
        std::cout << "3. Sua cau hoi" << std::endl;
        std::cout << "4. Xoa cau hoi" << std::endl;
        std::cout << "5. Sinh de thi ngau nhien" << std::endl;
        std::cout << "6. Thi thu" << std::endl;
        std::cout << "0. Thoat" << std::endl;
        std::cout << "Lua chon cua ban: ";
        std::cin >> luaChon;

        switch (luaChon) {
        case 1:
            hienThiTatCaCauHoi(danhSachCauHoi);
            break;
        case 2:
            themCauHoi(danhSachCauHoi);
            break;
        case 3:
            suaCauHoi(danhSachCauHoi);
            break;
        case 4:
            xoaCauHoi(danhSachCauHoi);
            break;
        case 5: {
            int soCauHoi;
            std::cout << "Nhap so luong cau hoi muon tao de thi: ";
            std::cin >> soCauHoi;
            std::cin.ignore(); // ignore newline character left in buffer
            sinhDeThiNgauNhien(danhSachCauHoi, soCauHoi);
            break;
        }
        case 6: {
            std::vector<CauHoi> deThi;
            docDeTuFile(deThi);
            if (!deThi.empty()) {
                thi(deThi);
            }
            else {
                std::cout << "Khong co de thi nao duoc tao. Vui long tao de thi truoc." << std::endl;
            }
            break;
        }
        case 0:
            std::cout << "Ket thuc chuong trinh." << std::endl;
            break;
        default:
            std::cout << "Lua chon khong hop le. Vui long thu lai." << std::endl;
            break;
        }
    } while (luaChon != 0);

    return 0;
}
