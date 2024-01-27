#include "pcb.h"


Contact::Contact() : type(ContactType::INPUT), x(0), y(0), connectedContact(nullptr) {}

Contact::Contact(ContactType t, float x_coord, float y_coord) : type(t), x(x_coord), y(y_coord), connectedContact(nullptr) {}

Contact::Contact(const Contact &c) : type(c.type), x(c.x), y(c.y), connectedContact(nullptr) {}

float Contact::getX() const { return x; }
float Contact::getY() const { return y; }
Contact::ContactType Contact::getType() const { return type; }

void Contact::setX(float x_coord) { x = x_coord; }
void Contact::setY(float y_coord) { y = y_coord; }
void Contact::connect(Contact &c) {
    if (this->type != c.type && this->connectedContact == nullptr && c.connectedContact == nullptr) {
        this->connectedContact = &c;
        c.connectedContact = this;
    }
}

bool Contact::isConnected() const { return connectedContact != nullptr; }

void Contact::disconnect() {
    if (connectedContact) {
        connectedContact->connectedContact = nullptr;
        connectedContact = nullptr;
    }
}

Contact* Contact::getConnectedContact() const { return connectedContact; }

bool Contact::operator==(const Contact &c) const { return (this->x == c.x && this->y == c.y); }

float Contact::calculateDelay(const Contact &c) const {
    const float speed = 1.0f;
    float distance = std::sqrt(std::pow(this->x - c.x, 2) + std::pow(this->y - c.y, 2));
    return distance / speed;
}

void Contact::printConnection() const {
    if (isConnected()) {
        std::cout << "Контакт (" << x << ", " << y << ") соединен с ("
                  << connectedContact->x << ", " << connectedContact->y << ")" << std::endl;
    } else {
        std::cout << "Контакт (" << x << ", " << y << ") не имеет соединений." << std::endl;
    }
}

std::ostream& operator<<(std::ostream &os, const Contact &c) {
    os << "Contact Type: " << ((c.type == Contact::ContactType::INPUT) ? "Input" : "Output")
       << ", Coordinates: (" << c.x << ", " << c.y << ")";
    return os;
}


// Класс PrintedCircuitBoard

PrintedCircuitBoard::PrintedCircuitBoard() : contacts(nullptr), size(0), capacity(0) {}

PrintedCircuitBoard::PrintedCircuitBoard(const Contact* contactArray, size_t arraySize) {
    if (arraySize == 0) {
        throw std::invalid_argument("Массив не может быть 0");
    }

    size = arraySize;
    capacity = size;
    contacts = new Contact[size];

    for (size_t i = 0; i < size; ++i) {
        contacts[i] = contactArray[i];
    }
}
PrintedCircuitBoard operator+(const PrintedCircuitBoard& lhs, const PrintedCircuitBoard& rhs) {
    PrintedCircuitBoard result;

    for (size_t i = 0; i < lhs.size; ++i) {
        result += lhs.contacts[i];
    }

    for (size_t i = 0; i < rhs.size; ++i) {
        result += rhs.contacts[i];
    }

    return result;
}


void PrintedCircuitBoard::printBoard() const {
    std::cout << "Печатная плата:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Контакт " << i << ": " << contacts[i] << std::endl;
        if (contacts[i].isConnected()) {
            std::cout << "  Соединен с: " << *(contacts[i].getConnectedContact()) << std::endl;
        } else {
            std::cout << "  Не соединен" << std::endl;
        }
    }
}

PrintedCircuitBoard::PrintedCircuitBoard(const Contact& contact) {
    contacts = new Contact[1];
    contacts[0] = contact;
    size = 1;
    capacity = 1;
}

PrintedCircuitBoard& PrintedCircuitBoard::operator+=(const Contact& newContact) {
    if (!isContactPresent(newContact)) {
        Contact* newContacts = new Contact[size + 1];
        for (size_t i = 0; i < size; ++i) {
            newContacts[i] = contacts[i];
        }
        newContacts[size] = newContact;
        updatecon(newContacts);
        delete[] contacts;

        contacts = newContacts;
        size++;
    }
    return *this;
}

Contact& PrintedCircuitBoard::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return contacts[index];
}
PrintedCircuitBoard::~PrintedCircuitBoard() {
    delete[] contacts;
}

bool PrintedCircuitBoard::isContactPresent(const Contact& contact) const {
    for (size_t i = 0; i < size; ++i) {
        if (contacts[i] == contact) {
            return true;
        }
    }
    return false;
}


void PrintedCircuitBoard::addConnection(size_t index1, size_t index2) {
    if (index1 >= size || index2 >= size) {
        return;
    }

    if (contacts[index1].isConnected() || contacts[index2].isConnected()) {
        return;
    }

    if (contacts[index1].getType() != contacts[index2].getType()) {
        contacts[index1].connect(contacts[index2]);
    } else {
    }
}


void PrintedCircuitBoard::removeConnection(size_t index) {
    if (index < size && contacts[index].isConnected()) {
        contacts[index].disconnect();
    }
}

void PrintedCircuitBoard::removeContact(size_t index) {
    if (index < size) {
        removeConnection(index);
        Contact* newContacts = new Contact[size - 1];
        for (size_t i = 0, j = 0; i < size; ++i) {
            if (i != index) {
                newContacts[j++] = contacts[i];
            }
        }
        delete[] contacts;
        contacts = newContacts;
        size--;
    }
}

bool PrintedCircuitBoard::findFarthestConnectedContacts(std::pair<size_t, size_t>& farthestContactsIndices, float& maxDistance) {
    maxDistance = 0;
    bool found = false;
    for (size_t i = 0; i < size; ++i) {
        if (contacts[i].isConnected()) {
            Contact* connectedContact = contacts[i].getConnectedContact();
            for (size_t j = 0; j < size; ++j) {
                if (&contacts[j] == connectedContact) {
                    float distance = contacts[i].calculateDelay(*connectedContact);
                    if (distance > maxDistance) {
                        maxDistance = distance;
                        farthestContactsIndices = {i, j};
                        found = true;
                    }
                    break;
                }
            }
        }
    }
    return found;
}


void PrintedCircuitBoard::sortContacts() {
    for (size_t i = 0; i < size - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < size; ++j) {
            if ((contacts[j].getX() < contacts[min_idx].getX()) ||
                (contacts[j].getX() == contacts[min_idx].getX() && contacts[j].getY() < contacts[min_idx].getY())) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(contacts[i], contacts[min_idx]);
        }
    }
}

PrintedCircuitBoard::PrintedCircuitBoard(const PrintedCircuitBoard& other) {
    size = other.size;
    capacity = other.capacity;
    contacts = new Contact[capacity];
    for (size_t i = 0; i < size; ++i) {
        contacts[i] = other.contacts[i];
    }
}

PrintedCircuitBoard& PrintedCircuitBoard::operator=(const PrintedCircuitBoard& other) {
    if (this != &other) {
        size_t newCapacity = other.capacity;
        Contact* newContacts = new Contact[newCapacity];

        for (size_t i = 0; i < other.size; ++i) {
            newContacts[i] = other.contacts[i];
        }
        delete[] contacts;

        size = other.size;
        capacity = newCapacity;

        contacts = newContacts;
        ///updatecon();
    }
    return *this;
}

PrintedCircuitBoard& PrintedCircuitBoard::operator=(PrintedCircuitBoard&& other) noexcept {
    if (this != &other) {
        delete[] contacts;

        contacts = other.contacts;
        size = other.size;
        capacity = other.capacity;

        other.contacts = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}


size_t PrintedCircuitBoard::getSize() const { return size; }

void PrintedCircuitBoard::printContacts() const {
    for (size_t i = 0; i < size; i++) {
        std::cout << contacts[i] << std::endl;
    }
}

void PrintedCircuitBoard::changeContactLocation() {
    size_t index;
    float newX, newY;
    std::cout << "Введите номер контакта для изменения его расположения: ";
    std::cin >> index;

    if (index < size) {
        std::cout << "Введите новые координаты x и y: ";
        std::cin >> newX >> newY;
        contacts[index].setX(newX);
        contacts[index].setY(newY);
        std::cout << "Координаты контакта обновлены." << std::endl;
    } else {
        std::cout << "Контакт с таким номером не найден." << std::endl;
    }
}

void PrintedCircuitBoard::addContactsFromExisting() {
    size_t numContacts, index;
    std::cout << "Введите количество контактов для добавления: ";
    std::cin >> numContacts;
    for (size_t i = 0; i < numContacts; ++i) {
        std::cout << "Введите индекс контакта #" << i + 1 << ": ";
        std::cin >> index;
        if (index < size) {
            *this += contacts[index];
        } else {
            std::cout << "Контакт с индексом " << index << " не существует." << std::endl;
        }
    }
}

void PrintedCircuitBoard::addSingleContact() {
    float x, y;
    std::string typeStr;
    Contact::ContactType type;
    std::cout << "Введите тип контакта (Input/Output): ";
    std::cin >> typeStr;
    type = (typeStr == "Input") ? Contact::ContactType::INPUT : Contact::ContactType::OUTPUT;
    while (true) {
        std::cout << "Введите координаты x, y (должны быть положительными числами): ";
        if (!(std::cin >> x >> y) || x <= 0 || y <= 0) {
            std::cout << "Некорректный ввод. Пожалуйста, введите положительные числа для координат x и y." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    Contact newContact(type, x, y);
    *this += newContact;
    std::cout << "Контакт добавлен на плату." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const PrintedCircuitBoard& pcb) {
    for (size_t i = 0; i < pcb.getSize(); i++) {
        os << "Contact " << i << ": " << pcb.contacts[i] << std::endl;
    }
    return os;
}


std::istream& operator>>(std::istream& is, Contact& contact) {
    std::string typeStr;
    float x, y;

    is >> typeStr >> x >> y;

    Contact::ContactType type;
    if (typeStr == "Input") {
        type = Contact::ContactType::INPUT;
    } else if (typeStr == "Output") {
        type = Contact::ContactType::OUTPUT;
    } else {
        is.setstate(std::ios::failbit);
        return is;
    }

    contact = Contact(type, x, y);

    return is;
}

bool PrintedCircuitBoard::shouldcon(const Contact& a, const Contact& b) {
    return a.getType() != b.getType()&& a.getX() == b.getX() && a.getY() == b.getY();
}


void PrintedCircuitBoard::updatecon(Contact*t) {

    for (size_t i = 0; i < size; ++i) {
        t[i].disconnect();
    }


    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (shouldcon(contacts[i],contacts[j])) {
                t[i].connect(t[j]);
                t[j].connect(t[i]);
            }
        }
    }
}






const char* InputException::what() const noexcept {
    return "Ошибка ввода данных";
}

const char* EOFException::what() const noexcept {
    return "Неожиданный конец файла или потока ввода";
}

void clearScreen() {
    #if defined _WIN32
    system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    #elif defined (__APPLE__)
    system("clear");
    #endif
}
