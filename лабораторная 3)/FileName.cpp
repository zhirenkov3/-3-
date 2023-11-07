#include <iostream>
#include <fstream>
#include <string>

struct Product {
    std::string name;
    double cost;
    int kolvo;
};

void addProductToFile(const Product& product) {
    std::ofstream outFile("products.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << product.name << "," << product.cost << "," << product.kolvo << std::endl;
        outFile.close();
        std::cout << "������� ������� ��������." << std::endl;
    } else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }
}

void searchProductByName(const std::string& name) {
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            size_t pos = line.find(',');
            std::string fullName = line.substr(0, pos);
            if (fullName == name) {
                std::cout << "������ �������: " << line << std::endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "������� � ����� ��������� �� ������." << std::endl;
        }
    } else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }
}
void searchProductByCost(const double& costi) {
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        int cnt = 0;
        while (std::getline(inFile, line)) {
            int pos = line.find(',');
            int pos2 = line.find_last_of(',');
            double icost = std::stod(line.substr(pos + 1, pos2 - pos - 1));
            std::cout << icost << std::endl;
            if (icost <= costi ) {

                if (cnt == 0)
                {
                    std::cout << "������� ��������: "<< std::endl << line << std::endl;
                    cnt++;
                }
                else std::cout << line << std::endl;
                found = true;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "�������� ���������� � ������� ��������� �� �������." << std::endl;
        }
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }
}

void sortProductByKolvo() {
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        // ������ ������ � ���������� (����������� ����������)
        std::string lines[100]; // ������������, ��� �� ����� 100 ���������
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                int kolvo1 = std::stoi(lines[j].substr(pos1 + 1));
                int kolvo2 = std::stoi(lines[j + 1].substr(pos2 + 1));
                if (kolvo1 < kolvo2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // ������ ��������������� ������ ������� � ����
        std::ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "�������� �������������� �� ����������." << std::endl;
        } else {
            std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
        }
    } else {
        std::cerr << "�� ������� ������� ���� ��� ������." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    int choice;
    std::string name;

    do {
        std::cout << "����:" << std::endl;
        std::cout << "1. ���������� ��������" << std::endl;
        std::cout << "2. ����� �������� �� ��������" << std::endl;
        std::cout << "3. ����������� �������� �� ����������" << std::endl;
        std::cout << "4. ����� ��������� �� ������� ����" << std::endl;
        std::cout << "0. �����" << std::endl;
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string name;
                double cost;
                int kolvo;
                std::cout << "������� ��������: ";
                std::getline(std::cin, name);
                if (name.empty()) {
                    std::cout << "���� �������." << std::endl;
                    break;
                }
                std::cout << "������� ��������� ��������: ";
                std::cin >> cost;
                std::cout << "������� ���������� ��������: ";
                std::cin >> kolvo;
                Product newProduct = {name, cost, kolvo};
                addProductToFile(newProduct);
                break;
            }
            case 2: {
                std::cin.ignore();
                std::cout << "������� �������� �������� ��� ������: ";
                std::getline(std::cin, name);
                searchProductByName(name);
                break;
            }
            case 3: {
                sortProductByKolvo();
                break;
            }
            case 4: {
                std::cin.ignore();
                std::cout << "������� ������� ����������� ��� ������: ";
                double costi;
                std::cin >> costi;
                searchProductByCost(costi);
                break;
            }
            case 0: {
                std::cout << "��������� ���������." << std::endl;
                break;
            }
            default: {
                std::cout << "�������� �����. ���������� �����." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}