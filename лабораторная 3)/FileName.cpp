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
        std::cout << "Продукт успешно добавлен." << std::endl;
    } else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
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
                std::cout << "Найден продукт: " << line << std::endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "Продукт с таким названием не найден." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
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
            if (icost < costi || icost == costi) {

                if (cnt == 0)
                {
                    std::cout << "Найдены продукты: "<< std::endl << line << std::endl;
                    cnt++;
                }
                else std::cout << line << std::endl;
                found = true;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "Продукты попадающие в ценовую категорию не найдены." << std::endl;
        }
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void sortProductByKolvo() {
    std::ifstream inFile("products.txt");
    if (inFile.is_open()) {
        // Чтение данных и сортировка (пузырьковая сортировка)
        std::string lines[100]; // Предполагаем, что не более 100 студентов
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
        // Запись отсортированных данных обратно в файл
        std::ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Продукты отсортированны по количеству." << std::endl;
        } else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    int choice;
    std::string name;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавление продукта" << std::endl;
        std::cout << "2. Поиск продукта по названию" << std::endl;
        std::cout << "3. Сортировать продукты по количеству" << std::endl;
        std::cout << "4. Поиск продуктов по потолку цены" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string name;
                double cost;
                int kolvo;
                std::cout << "Введите название: ";
                std::getline(std::cin, name);
                if (name.empty()) {
                    std::cout << "Ввод прерван." << std::endl;
                    break;
                }
                std::cout << "Введите стоимость продукта: ";
                std::cin >> cost;
                std::cout << "Введите количество продукта: ";
                std::cin >> kolvo;
                Product newProduct = {name, cost, kolvo};
                addProductToFile(newProduct);
                break;
            }
            case 2: {
                std::cin.ignore();
                std::cout << "Введите ФИО студента для поиска: ";
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
                std::cout << "Введите ценовое ограничение для поиска: ";
                double costi;
                std::cin >> costi;
                searchProductByCost(costi);
                break;
            }
            case 0: {
                std::cout << "Программа завершена." << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}