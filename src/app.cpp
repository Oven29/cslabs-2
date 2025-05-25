#include "app.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

namespace {

void printVector(const std::vector<double>& vec) {
    std::cout << "(" << vec.size() << ") ";
    for (double num : vec) {
        std::cout << std::fixed << std::setprecision(2) << num << " ";
    }
    std::cout << std::endl;
}

void printVector(const std::vector<app::Box>& vec) {
    for (const app::Box& box : vec) {
        std::cout << box << ", V=" << box.getVolume() << std::endl;
    }
}

void printList(const std::list<double>& list) {
    std::cout << "(" << list.size() << ") ";
    for (double num : list) {
        std::cout << std::fixed << std::setprecision(2) << num << " ";
    }
    std::cout << std::endl;
}

void printList(const std::list<app::Graduate>& list) {
    for (const app::Graduate& graduate : list) {
        std::cout << graduate << std::endl;
    }
}

void printProductionMap(const std::map<std::string, int>& production) {
    std::cout << "Производственные показатели:\n";
    for (const auto& [name, total] : production) {
        std::cout << name << " — " << total << " изделий\n";
    }
}

}  // namespace

namespace app {

void run() {
    std::cout << "Введите номер задачи (1..9): ";
    int number{};
    std::cin >> number;

    if (number == 1) {
        task1();
    } else if (number == 2) {
        task2();
    } else if (number == 3) {
        task3();
    } else if (number == 4) {
        task4();
    } else if (number == 5) {
        task5();
    } else if (number == 6) {
        task6();
    } else if (number == 7) {
        task7();
    } else if (number == 8) {
        task8();
    } else if (number == 9) {
        task9();
    } else {
        std::cout << "Неверный ввод номера задачи" << std::endl;
    }
}

void task1() {
    std::string word1, word2, word3;

    std::cout << "Введите первое слово: ";
    std::cin >> word1;

    std::cout << "Введите второе слово: ";
    std::cin >> word2;

    std::cout << "Введите третье слово: ";
    std::cin >> word3;

    std::string result;
    if (!word1.empty())
        result += word1[0];
    if (!word2.empty())
        result += word2[0];
    if (!word3.empty())
        result += word3[0];

    std::cout << "Результат: " << result << std::endl;
}

void task2() {
    std::string text;

    std::cout << "Введите текст: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, text);

    size_t spacePos = text.find(' ');
    size_t dotPos = text.find('.');

    if (spacePos != std::string::npos && dotPos != std::string::npos && spacePos < dotPos) {
        std::string result = text.substr(spacePos + 1, dotPos - spacePos - 1);
        std::cout << "Результат: " << result << std::endl;
    } else {
        std::cout << "Невозможно извлечь подстроку: проверьте, что пробел и точка присутствуют, и пробел идёт до точки." << std::endl;
    }
}

void task3() {
    std::ifstream inputFile("bin/input3task.txt");
    std::ofstream outputFile("bin/output3task.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Ошибка при открытии файлов!" << std::endl;
    } else {
        std::string line;
        while (std::getline(inputFile, line)) {
            if (!line.empty() && std::isdigit(line[0])) {
                outputFile << line << std::endl;
            }
        }

        inputFile.close();
        outputFile.close();

        std::cout << "Готово" << std::endl;
    }
};

void task4() {
    std::vector<double> vec;
    const int size = 10;
    const double min = -50.0;
    const double max = 50.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    for (int i = 0; i < size; ++i) {
        vec.push_back(dis(gen));
    }

    std::cout << "Исходный вектор: ";
    printVector(vec);

    double sum = 0.0;
    for (double num : vec) {
        sum += num;
    }
    double average = sum / vec.size();
    std::cout << "Среднее значение: " << std::fixed << std::setprecision(2) << average << std::endl;

    std::vector<double> aboveAverage;
    for (double num : vec) {
        if (num > average) {
            aboveAverage.push_back(num);
        }
    }

    std::cout << "Вектор > среднего: ";
    printVector(aboveAverage);

    vec.erase(vec.begin() + 8);

    std::cout << "Вектор после удаления элемента с индексом 8: ";
    printVector(vec);
};

bool Box::operator<(const Box& other) const {
    return this->getVolume() < other.getVolume();
};

bool Box::operator==(const Box& other) const {
    return this->a == other.a && this->b == other.b && this->c == other.c;
};

double Box::getVolume() const {
    return a * b * c;
}

std::ostream& operator<<(std::ostream& os, const Box& box) {
    os << "(" << box.a << ", " << box.b << ", " << box.c << ")";
    return os;
};

void task5() {
    std::vector<Box> boxes;

    boxes.push_back(Box(1, 2, 63));
    boxes.push_back(Box(14, 57, 19));
    boxes.push_back(Box(7, 32, 20));
    boxes.push_back(Box(5, 13, 23));
    boxes.push_back(Box(10, 19, 45));
    boxes.push_back(Box(19, 9, 59));

    printVector(boxes);

    Box maxBox = boxes[0];
    for (const Box& box : boxes) {
        if (box.getVolume() > maxBox.getVolume()) {
            maxBox = box;
        }
    }

    std::cout << "Коробка с макс объёмом: " << maxBox << std::endl;
};

void task6() {
    std::list<double> list;
    const int size = 10;
    const double min = -50.0;
    const double max = 50.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    for (int i = 0; i < size; ++i) {
        list.push_back(dis(gen));
    }

    std::cout << "Исходный лсит: ";
    printList(list);

    double sum = 0.0;
    for (double num : list) {
        sum += num;
    }
    double average = sum / list.size();
    std::cout << "Среднее значение: " << std::fixed << std::setprecision(2) << average << std::endl;

    std::list<double> aboveAverage;
    for (double num : list) {
        if (num > average) {
            aboveAverage.push_back(num);
        }
    }

    std::cout << "Лист > среднего: ";
    printList(aboveAverage);

    auto it = list.begin();
    std::advance(it, 8);  // Перемещаем итератор на 8 позиций вперёд
    list.erase(it);

    std::cout << "Лист после удаления элемента с индексом 8: ";
    printList(list);
};

bool Graduate::operator<(const Graduate& other) const {
    return this->getRating() < other.getRating();
};

bool Graduate::operator==(const Graduate& other) const {
    return this->name == other.name && this->rating == other.rating;
};

double Graduate::getRating() const {
    return rating;
}

void Graduate::setRating(double rating) {
    this->rating = rating;
}

std::ostream& operator<<(std::ostream& os, const Graduate& graduate) {
    os << graduate.name << " | " << graduate.rating;
    return os;
};

void task7() {
    std::list<Graduate> graduates;

    graduates.push_back(Graduate("Иванов", 99));
    graduates.push_back(Graduate("Петров", 430));
    graduates.push_back(Graduate("Семенов", 70));
    graduates.push_back(Graduate("Котов", 540));
    graduates.push_back(Graduate("Белых", 230));
    graduates.push_back(Graduate("Черных", 350));

    printList(graduates);

    Graduate maxGraduate = graduates.front();
    for (const Graduate& graduate : graduates) {
        if (graduate.getRating() > maxGraduate.getRating()) {
            maxGraduate = graduate;
        }
    }

    std::cout << "Студент с максимальным рейтингом: " << maxGraduate << std::endl;

    std::cout << "Введите число на которое надо увеличить рейтинг всех студентов: ";
    int number{};
    std::cin >> number;

    for (Graduate& graduate : graduates) {
        graduate.setRating(graduate.getRating() + number);
    }

    printList(graduates);
};

void task8() {
    std::map<std::string, std::string> countries = {
        {"Россия",    "Москва"},
        {"Германия",  "Берлин"},
        {"Украина",   "Киев"  },
        {"Беларусь",  "Минск" },
        {"Казахстан", "Астана"}
    };

    std::string country;
    std::cout << "Введите страну: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, country);

    auto it = countries.find(country);
    if (it != countries.end()) {
        std::cout << "Столица страны " << country << " — " << it->second << std::endl;
    } else {
        std::cout << "Страна не найдена. Введите столицу для " << country << ": ";
        std::string capital;
        std::getline(std::cin, capital);
        if (!capital.empty()) {
            countries[country] = capital;
            std::cout << "Добавлено: " << country << " — " << capital << std::endl;
        } else {
            std::cout << "Столица не введена, пара не добавлена." << std::endl;
        }
    }

    for (const auto& pair : countries) {
        std::cout << pair.first << " — " << pair.second << std::endl;
    }
};

void task9() {
    std::map<std::string, int> production = {
        {"Иванов",    123},
        {"Петров",    89 },
        {"Сидоров",   108},
        {"Краснов",   132},
        {"Демин",     99 },
        {"Черепанов", 111}
    };

    printProductionMap(production);

    int totalProduced = 0;
    for (const auto& pair : production) {
        totalProduced += pair.second;
    }

    std::cout << "Всего изделий за неделю: " << totalProduced << std::endl;
};

}  // namespace app
