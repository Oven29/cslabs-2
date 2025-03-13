#include "app.hpp"
#include "../house/house.hpp"
#include "../planet/planet.hpp"

#include <cstring>
#include <iostream>
#include <limits>

namespace {

const int BUFFER_SIZE = 256;
const int defaultSize = 0;
const char* housesSourceFilename = "houses.txt";

bool isValidInteractiveType(int type) {
    return type >= static_cast<int>(app::InteractiveType::print) && type <= static_cast<int>(app::InteractiveType::exit);
}

}  // namespace

namespace app {

ProgramMode getProgramMode(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], "-it") == 0) {
        return ProgramMode::interactive;
    }

    return ProgramMode::demonstrative;
}

void runDemonstrativeMode() {
    const char* filename = "source.txt";

    planet::Planet** solarSystem = new planet::Planet*[BUFFER_SIZE];
    int size = 0;
    planet::Planet::readFromFile(filename, solarSystem, size);

    std::cout << std::endl << "Before sorting" << std::endl;
    planet::Planet::print(solarSystem, size);
    planet::Planet::sort(solarSystem, size);
    std::cout << std::endl << "After sorting" << std::endl;
    planet::Planet::print(solarSystem, size);

    char* plutoName = new char[6];
    std::strcpy(plutoName, "Pluno");
    planet::Planet* pluto = new planet::Planet(plutoName, 2280, 0, 1);
    delete plutoName;
    std::cout << std::endl << *pluto << " - appending to solar system" << std::endl << std::endl;
    planet::Planet::append(solarSystem, size, pluto);
    planet::Planet::print(solarSystem, size);
    planet::Planet* removePlanet = solarSystem[std::min(size, 5)];
    std::cout << std::endl << *removePlanet << " - removing from solar system" << std::endl << std::endl;
    planet::Planet::remove(solarSystem, size, removePlanet);
    planet::Planet::print(solarSystem, size);

    const char* fileout = "output.txt";
    std::cout << "Write changes to file " << fileout << std::endl;
    planet::Planet::writeToFile(fileout, solarSystem, size);

    delete[] solarSystem;
}

InteractiveType getInteractiveType() {
    while (true) {
        std::cout << "===" << std::endl
                  << "print - 1 " << std::endl
                  << "read from file - 2" << std::endl
                  << "write to file - 3" << std::endl
                  << "append element - 4" << std::endl
                  << "remove element - 5" << std::endl
                  << "sort - 6" << std::endl
                  << "edit - 7" << std::endl
                  << "exit - 8" << std::endl;

        int type{};
        std::cin >> type;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 8." << std::endl;
            continue;
        }

        if (isValidInteractiveType(type)) {
            return static_cast<InteractiveType>(type);
        }

        std::cin.clear();
        std::cout << "Invalid choice! Please enter a number between 1 and 8." << std::endl;
    }
}

void editHouse(house::House*& el) {
    std::cout << "number - 1; countOfFloors - 2; countOfApartaments - 3" << std::endl;
    int n;
    std::cin >> n;
    if (n < 1 || n > 3) {
        std::cout << "Wrong input" << std::endl;
    } else {
        int newValue;
        std::cout << "Enter new value" << std::endl;
        std::cin >> newValue;
        FieldToEdit fieldToEdit = static_cast<FieldToEdit>(n);
        switch (fieldToEdit) {
            case FieldToEdit::number: {
                std::cout << "Number updated" << std::endl;
                el->setNumber(newValue);
                break;
            }
            case FieldToEdit::countOfFloors: {
                std::cout << "Count of floors updated" << std::endl;
                el->setCountOfFloors(newValue);
                break;
            }
            case FieldToEdit::countOfApartaments: {
                std::cout << "Count of apartaments updated" << std::endl;
                el->setCountOfApartaments(newValue);
                break;
            }
        }
    }
}

void runInteractiveMode() {
    bool running = true;
    int size = defaultSize;
    house::House** housingDepartament = new house::House*[size];

    while (running) {
        switch (getInteractiveType()) {
            case InteractiveType::print: {
                if (size == 0) {
                    std::cout << "empty" << std::endl;
                } else {
                    house::House::print(housingDepartament, size);
                }
                break;
            }
            case InteractiveType::read: {
                house::House::readFromFile(housesSourceFilename, housingDepartament, size);
                std::cout << "Data read from file " << housesSourceFilename << std::endl;
                break;
            }
            case InteractiveType::write: {
                char* filename = new char[BUFFER_SIZE];
                std::cout << "Enter filename: ";
                std::cin >> filename;
                house::House::writeToFile(filename, housingDepartament, size);
                std::cout << "Data wrote to file " << filename << std::endl;
                delete[] filename;
                break;
            }
            case InteractiveType::append: {
                std::cout << "Enter new element (street number floors apartaments)" << std::endl;
                char* street = new char[BUFFER_SIZE];
                int number{}, countOfFloors{}, countOfApartaments{};
                std::cin >> street >> number >> countOfFloors >> countOfApartaments;
                house::House* newElement = new house::House(street, number, countOfFloors, countOfApartaments);
                delete[] street;
                house::House::append(housingDepartament, size, newElement);
                std::cout << *newElement << " added to db" << std::endl;
                break;
            }
            case InteractiveType::remove: {
                house::House::print(housingDepartament, size);
                std::cout << "Enter element id to remove" << std::endl;
                int id;
                std::cin >> id;
                bool removed = house::House::remove(housingDepartament, size, id);
                std::cout << "Element with id=" << id;
                if (removed) {
                    std::cout << " removed from db" << std::endl;
                } else {
                    std::cout << " not found in db" << std::endl;
                }
                break;
            }
            case InteractiveType::sort: {
                house::House::sort(housingDepartament, size);
                std::cout << "Data was sorted" << std::endl;
                break;
            }
            case InteractiveType::edit: {
                house::House::print(housingDepartament, size);
                std::cout << "Enter id element to edit" << std::endl;
                int id;
                std::cin >> id;
                house::House* houseToEdit = nullptr;
                for (int i = 0; i < size; i++) {
                    if (housingDepartament[i]->getId() == id) {
                        houseToEdit = housingDepartament[i];
                        break;
                    }
                }
                if (houseToEdit == nullptr) {
                    std::cout << "House with id=" << id << " not found" << std::endl;
                    break;
                }
                editHouse(houseToEdit);
                break;
            }
            case InteractiveType::exit: {
                std::cout << "Goodbuy!" << std::endl;
                for (int i = 0; i < size; i++) {
                    delete housingDepartament[i];
                }
                delete[] housingDepartament;
                running = false;
                break;
            }
        }
    }
}

void run(int argc, char** argv) {
    switch (getProgramMode(argc, argv)) {
        case ProgramMode::interactive: {
            std::cout << "Welcome!" << std::endl;
            runInteractiveMode();
            break;
        }
        case ProgramMode::demonstrative:
            runDemonstrativeMode();
            break;
    }
}

}  // namespace app
