#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <cmath>



class Contact {
public:
    enum class ContactType { INPUT, OUTPUT };

private:
    ContactType type;
    float x, y;
    Contact* connectedContact;

public:
    Contact();
    Contact(ContactType t, float x_coord, float y_coord);
    Contact(const Contact &c);

    float getX() const;
    float getY() const;
    ContactType getType() const;

    void setX(float x_coord);
    void setY(float y_coord);

    void connect(Contact &c);
    bool isConnected() const;
    void disconnect();
    Contact* getConnectedContact() const;

    bool operator==(const Contact &c) const;
    float calculateDelay(const Contact &c) const;
    void printConnection() const;

    friend std::ostream& operator<<(std::ostream &os, const Contact &c);
};

class PrintedCircuitBoard {
private:
    Contact* contacts;
    size_t size;
    size_t capacity;
    bool isContactPresent(const Contact& contact) const;

public:
    PrintedCircuitBoard();//строка 47
    PrintedCircuitBoard(const Contact& contact);//одним контактом строка 59
    PrintedCircuitBoard(const Contact* contactArray, size_t arraySize);//принимающий массив строка 51
    PrintedCircuitBoard(const PrintedCircuitBoard& other);//строка 84
    PrintedCircuitBoard(PrintedCircuitBoard&& other) noexcept;//перемещ 78
    PrintedCircuitBoard& operator=(const PrintedCircuitBoard& other);//присваивания строка 95
    PrintedCircuitBoard& operator=(PrintedCircuitBoard&& other) noexcept;
    ~PrintedCircuitBoard();//строка 72
    PrintedCircuitBoard& operator+=(const Contact& newContact);
    Contact& operator[](size_t index); // Реализация в func.cpp, строка 83

    void addConnection(size_t index1, size_t index2);
    void removeConnection(size_t index);
    void removeContact(size_t index);

     bool findFarthestConnectedContacts(std::pair<size_t, size_t>& farthestContactsIndices, float& maxDistance);///
    void sortContacts();
    size_t getSize() const;
    void printContacts() const; // Реализация в func.cpp, строка 210
    void printBoard() const; //Реализация в func.cpp, строка 62

    void changeContactLocation();
    void addContactsFromExisting();
    void addSingleContact();
    bool shouldcon(const Contact& a, const Contact& b);
    void updatecon(Contact*t);

    friend PrintedCircuitBoard operator+(const PrintedCircuitBoard& lhs, const PrintedCircuitBoard& rhs);///
    friend std::ostream& operator<<(std::ostream& os, const PrintedCircuitBoard& pcb);
    friend std::istream& operator>>(std::istream& is, PrintedCircuitBoard& pcb);
};


class InputException : public std::exception {
public:
    const char* what() const noexcept override;
};

class EOFException : public std::exception {
public:
    const char* what() const noexcept override;
};

void clearScreen();

#endif
