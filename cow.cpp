#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

class Cow {
public:
    std::string name;

    Cow(const std::string& name) : name(name) {}
    ~Cow() {
        std::cout << "Cow " << name << " has been destroyed.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Cow& cow) {
        os << "Cow Name: " << cow.name;
        return os;
    }
};

class Ship {
public:
    std::string shipName;
    std::map<std::string, Cow*> cowInventory;
    int numCows;

    Ship(const std::string& shipName) : shipName(shipName), numCows(0) {}

    ~Ship() {
        for (auto& pair : cowInventory) {
            delete pair.second;
        }
        std::cout << "Ship " << shipName << " has been destroyed, along with its cows.\n";
    }

    void abductCow(Cow* cow) {
        auto result = cowInventory.insert({cow->name, cow});
        if (!result.second) {
            std::cout << "Error: Cow with name " << cow->name << " is already on the ship.\n";
            delete cow;
        } else {
            numCows++;
            std::cout << "Cow " << cow->name << " has been abducted.\n";
        }
    }

    void dropOffCow() {
        if (cowInventory.empty()) {
            std::cout << "No cows to drop off.\n";
            return;
        }
        auto it = cowInventory.begin();
        std::advance(it, rand() % cowInventory.size());
        std::cout << "Dropping off cow: " << it->second->name << "\n";
        delete it->second;
        cowInventory.erase(it);
        numCows--;
    }

    void dropOffCow(const std::string& cowID) {
        auto it = cowInventory.find(cowID);
        if (it != cowInventory.end()) {
            std::cout << "Dropping off cow: " << it->second->name << "\n";
            delete it->second;
            cowInventory.erase(it);
            numCows--;
        } else {
            std::cout << "Error: Cow with name " << cowID << " not found on the ship.\n";
        }
    }

    void displayInventory() const {
        if (cowInventory.empty()) {
            std::cout << "No cows on the ship.\n";
            return;
        }
        for (const auto& pair : cowInventory) {
            std::cout << *(pair.second) << "\n";
        }
    }
};

void blowUpShip(Ship* ship) {
    delete ship;
}

int main() {
    std::unique_ptr<Ship> ship = nullptr;
    int choice;
    srand(static_cast<unsigned int>(time(0)));

    do {
        std::cout << "1. Create a ship\n";
        std::cout << "2. Abduct a cow\n";
        std::cout << "3. Drop off a cow\n";
        std::cout << "4. Display inventory\n";
        std::cout << "5. Self-destruct\n";
        std::cout << "6. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (ship != nullptr) {
                    std::cout << "A ship already exists. Destroy it before creating a new one.\n";
                } else {
                    std::string shipName;
                    std::cout << "Enter ship name: ";
                    std::cin >> shipName;
                    ship = std::make_unique<Ship>(shipName);
                    std::cout << "Ship " << shipName << " has been created.\n";
                }
                break;

            case 2:
                if (ship == nullptr) {
                    std::cout << "No ship exists. Create a ship first.\n";
                } else {
                    std::string cowName;
                    std::cout << "Enter cow name: ";
                    std::cin >> cowName;
                    ship->abductCow(new Cow(cowName));
                }
                break;

            case 3:
                if (ship == nullptr) {
                    std::cout << "No ship exists. Create a ship first.\n";
                } else {
                    std::string cowName;
                    std::cout << "Enter cow name to drop off (or press Enter for random drop off): ";
                    std::cin.ignore();
                    std::getline(std::cin, cowName);
                    if (cowName.empty()) {
                        ship->dropOffCow();
                    } else {
                        ship->dropOffCow(cowName);
                    }
                }
                break;

            case 4:
                if (ship == nullptr) {
                    std::cout << "No ship exists. Create a ship first.\n";
                } else {
                    ship->displayInventory();
                }
                break;

            case 5:
                if (ship == nullptr) {
                    std::cout << "No ship exists to destroy.\n";
                } else {
                    blowUpShip(ship.release());
                }
                break;

            case 6:
                std::cout << "Goodbye!\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
