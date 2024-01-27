#include "func.cpp"

int main() {
    setlocale(LC_ALL, "Russian");
    PrintedCircuitBoard pcb;
    int choice;

    while (true) {
        clearScreen();
        std::cout << "1. �������� ����� ������� �� �����\n"
                  << "2. �������� ������� �� ������\n"
                  << "3. ��������� ��������\n"
                  << "4. ������� ����� ��������\n"
                  << "5. ������� �������\n"
                  << "6. ���������� ���������\n"
                  << "7. �������� ��������\n"
                  << "8. ������ � ����������\n"
                  << "9. �����\n"
                  << "10. ����� �������� ��������� ��������� ��������\n"
                  << "11. �������� ��������� ����� ���������\n"
                  << "12. ������� ��������� ����� � �������� ����������� ���������\n"
                  << "13. �������� ������������ ��������\n"
                  << "14. �������� ��� ��������\n"
                  << "15. ����� �����\n"
                  << "16. ����������� ����\n"
                  << "�������� ��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
    float x, y;
    std::string typeStr;
    Contact::ContactType type;

    while (true) {
        std::cout << "������� ��� �������� (Input/Output): ";
        std::cin >> typeStr;

        if (typeStr == "Input") {
            type = Contact::ContactType::INPUT;
            break;
        } else if (typeStr == "Output") {
            type = Contact::ContactType::OUTPUT;
            break;
        } else {
            std::cout << "�������� ��� ��������. ����������, ������� 'Input' ��� 'Output'.\n";
            // �������� ����� ����� ��� ��������� ������� �����
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

    std::cout << "������� ���������� x, y: ";
    std::cin >> x >> y;

    if (std::cin.fail() || x <= 0 || y <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������: ���������� ������ ���� �������������� �������.\n";
        continue;
    } else {
       pcb += Contact(type, x, y);
        std::cout << "������� ��������." << std::endl;
        system("pause");
    }

    break;
}

            case 2: {
    size_t index;
    std::cout << "������� ������ ��������: ";
    std::cin >> index;
    if (index < pcb.getSize()) { // ���������� getSize ������ size
        std::cout << pcb[index] << std::endl;
    } else {
        std::cout << "������� � ����� �������� �� ������." << std::endl;
    }
    system("pause");
    break;
}


             case 3: { // ��������� ��������
    size_t index1, index2;
std::cout << "������� ������� ���� ��������� ��� ����������: ";
std::cin >> index1 >> index2;

if (index1 < pcb.getSize() && index2 < pcb.getSize()) {
    Contact& contact1 = pcb[index1];
    Contact& contact2 = pcb[index2];

    // �������� �� ��� ������������ ����������
    if (contact1.isConnected() || contact2.isConnected()) {
        std::cout << "���� �� ��������� ��� ��������." << std::endl;
    } else if (contact1.getType() != contact2.getType()) {
        contact1.connect(contact2);
        std::cout << "�������� ���������." << std::endl;
    } else {
        std::cout << "���������� ���� ��������� �� ����� ���� ���������." << std::endl;
    }
} else {
    std::cout << "�������� �������." << std::endl;
}
system("pause");

    break;
}

case 4: { // ������� ����� ��������
size_t index;
std::cout << "������� ������ ��������, ����� �������� ����� �������: ";
std::cin >> index;
pcb.removeConnection(index);
std::cout << "����� �������." << std::endl;
 system("pause");
break;
}
case 5: { // ������� �������
size_t index;
std::cout << "������� ������ �������� ��� ��������: ";
std::cin >> index;
pcb.removeContact(index);
std::cout << "������� ������." << std::endl;
 system("pause");
break;
}
case 6: { // ���������� ���������
pcb.sortContacts();
std::cout << "�������� �������������." << std::endl;
 system("pause");
break;
}
case 7: {
            pcb.printContacts();
             system("pause");
            break;
        }
  case 8: {
    std::cout << "�������� ���������� � �����:" << std::endl;
    for (size_t i = 0; i < pcb.getSize(); ++i) {
        pcb[i].printConnection();
    }
    system("pause");
    break;
}

case 9: { // �����
return 0;
}
            case 10: {
                 std::pair<size_t, size_t> farthestContactsIndices;
                float maxDistance;
               if (pcb.findFarthestConnectedContacts(farthestContactsIndices, maxDistance)) {
    std::cout << "�������� ��������� ��������� �������� ��������� �� ��������: "<< farthestContactsIndices.first << " � " << farthestContactsIndices.second
                  << " � �����������: " << maxDistance << std::endl;
    } else {
        std::cout << "��������� �������� �� �������." << std::endl;
    }
                system("pause");
                break;
            }
            case 11: {
                pcb.addSingleContact();
                system("pause");
                break;
            }
             case 12: {
        pcb.addContactsFromExisting();
        system("pause");
        break;
    }
      case 13: {
        pcb.changeContactLocation();
        system("pause");
        break;
    }

                     case 14: {
size_t index1, index2;
std::cout << "������� ������� ���� ��������� ��� ���������: ";
std::cin >> index1 >> index2;
if (index1 < pcb.getSize() && index2 < pcb.getSize()) {
    Contact& contact1 = pcb[index1];
    Contact& contact2 = pcb[index2];


    if (contact1 == contact2 && contact1.getType() == contact2.getType()) {
        std::cout << "�������� ������ ���� ����������� � ����� �����." << std::endl;
    } else {
        std::cout << "�������� �������� ��� ����������� � ������ ������." << std::endl;
    }
} else {
    std::cout << "�������� �������." << std::endl;
}
system("pause");

}
 case 15: {
            pcb.printBoard();
             system("pause");
            break;
        }

       case 16: {
            std::cout << "����������� ������� ����� � ����� ������." << std::endl;
             PrintedCircuitBoard pcb2;

            pcb2 += Contact(Contact::ContactType::INPUT, 50.0, 60.0);

            PrintedCircuitBoard combinedPCB = pcb + pcb2;
            std::cout << "������������ �����:" << std::endl;
            combinedPCB.printBoard();
            system("pause");
            break;
        }

            default: {
                std::cout << "�������� �����. ����������, ���������� �����." << std::endl;
            }
        }
    }

    return 0;
}
