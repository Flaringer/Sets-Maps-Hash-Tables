#include <iostream>
#include <vector>
#include <set>
#include <string>
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
private:
    std::set<std::string> cowSet;
public:
    std::string shipName;
    std::vector<Cow*> cowInventory;
    int numCows;

    Ship(const std::string& shipName) : shipName(shipName), numCows(0) {}

    ~Ship() {
        for (Cow* cow : cowInventory) {
            delete cow;
        }
        std::cout << "Ship " << shipName << " has been destroyed, along with its cows.\n";
    }

    void abductCow(Cow* cow) {
        if (cowSet.find(cow->name) != cowSet.end()) {
            std::cout << "Error: Cow with name " << cow->name << " is already on the ship.\n";
            delete cow;
        } else {
            cowSet.insert(cow->name);
            cowInventory.push_back(cow);
            numCows++;
            std::cout << "Cow " << cow->name << " has been abducted.\n";
        }
    }
};

void blowUpShip(Ship* ship) {
    delete ship;
}

int main() {
    std::unique_ptr<Ship> ship = nullptr;
    int choice;

    do {
        std::cout << "1. Create a ship\n";
        std::cout << "2. Abduct a cow\n";
        std::cout << "3. Self-destruct\n";
        std::cout << "4. Quit\n";
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
                    std::cout << "No ship exists to destroy.\n";
                } else {
                    blowUpShip(ship.release());
                }
                break;

            case 4:
                std::cout << "Goodbye!\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
