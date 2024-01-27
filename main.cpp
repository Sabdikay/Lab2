#include "func.cpp"

int main() {
    setlocale(LC_ALL, "Russian");
    PrintedCircuitBoard pcb;
    int choice;

    while (true) {
        clearScreen();
        std::cout << "1. Добавить новый контакт на плату\n"
                  << "2. Показать контакт по номеру\n"
                  << "3. Соединить контакты\n"
                  << "4. Удалить связь контакта\n"
                  << "5. Удалить контакт\n"
                  << "6. Сортировка контактов\n"
                  << "7. Показать контакты\n"
                  << "8. ТРАССЫ И СОЕДИНЕНИЯ\n"
                  << "9. Выход\n"
                  << "10. Найти наиболее удаленные связанные контакты\n"
                  << "11. Добавить экземпляр одним контактом\n"
                  << "12. Создать экземпляр платы с заданным количеством контактов\n"
                  << "13. Изменить расположение контакта\n"
                  << "14. Сравнить два контакта\n"
                  << "15. Вывод платы\n"
                  << "16. Обьединение плат\n"
                  << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
    float x, y;
    std::string typeStr;
    Contact::ContactType type;

    while (true) {
        std::cout << "Введите тип контакта (Input/Output): ";
        std::cin >> typeStr;

        if (typeStr == "Input") {
            type = Contact::ContactType::INPUT;
            break;
        } else if (typeStr == "Output") {
            type = Contact::ContactType::OUTPUT;
            break;
        } else {
            std::cout << "Неверный тип контакта. Пожалуйста, введите 'Input' или 'Output'.\n";
            // Очистить буфер ввода для следующей попытки ввода
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

    std::cout << "Введите координаты x, y: ";
    std::cin >> x >> y;

    if (std::cin.fail() || x <= 0 || y <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: координаты должны быть положительными числами.\n";
        continue;
    } else {
       pcb += Contact(type, x, y);
        std::cout << "Контакт добавлен." << std::endl;
        system("pause");
    }

    break;
}

            case 2: {
    size_t index;
    std::cout << "Введите индекс контакта: ";
    std::cin >> index;
    if (index < pcb.getSize()) { // Используем getSize вместо size
        std::cout << pcb[index] << std::endl;
    } else {
        std::cout << "Контакт с таким индексом не найден." << std::endl;
    }
    system("pause");
    break;
}


             case 3: { // Соединить контакты
    size_t index1, index2;
std::cout << "Введите индексы двух контактов для соединения: ";
std::cin >> index1 >> index2;

if (index1 < pcb.getSize() && index2 < pcb.getSize()) {
    Contact& contact1 = pcb[index1];
    Contact& contact2 = pcb[index2];

    // Проверка на уже существующее соединение
    if (contact1.isConnected() || contact2.isConnected()) {
        std::cout << "Один из контактов уже соединен." << std::endl;
    } else if (contact1.getType() != contact2.getType()) {
        contact1.connect(contact2);
        std::cout << "Контакты соединены." << std::endl;
    } else {
        std::cout << "Одинаковые типы контактов не могут быть соединены." << std::endl;
    }
} else {
    std::cout << "Неверные индексы." << std::endl;
}
system("pause");

    break;
}

case 4: { // Удалить связь контакта
size_t index;
std::cout << "Введите индекс контакта, связь которого нужно удалить: ";
std::cin >> index;
pcb.removeConnection(index);
std::cout << "Связь удалена." << std::endl;
 system("pause");
break;
}
case 5: { // Удалить контакт
size_t index;
std::cout << "Введите индекс контакта для удаления: ";
std::cin >> index;
pcb.removeContact(index);
std::cout << "Контакт удален." << std::endl;
 system("pause");
break;
}
case 6: { // Сортировка контактов
pcb.sortContacts();
std::cout << "Контакты отсортированы." << std::endl;
 system("pause");
break;
}
case 7: {
            pcb.printContacts();
             system("pause");
            break;
        }
  case 8: {
    std::cout << "Проверка соединений и трасс:" << std::endl;
    for (size_t i = 0; i < pcb.getSize(); ++i) {
        pcb[i].printConnection();
    }
    system("pause");
    break;
}

case 9: { // Выход
return 0;
}
            case 10: {
                 std::pair<size_t, size_t> farthestContactsIndices;
                float maxDistance;
               if (pcb.findFarthestConnectedContacts(farthestContactsIndices, maxDistance)) {
    std::cout << "Наиболее удаленные связанные контакты находятся на индексах: "<< farthestContactsIndices.first << " и " << farthestContactsIndices.second
                  << " с расстоянием: " << maxDistance << std::endl;
    } else {
        std::cout << "Связанные контакты не найдены." << std::endl;
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
std::cout << "Введите индексы двух контактов для сравнения: ";
std::cin >> index1 >> index2;
if (index1 < pcb.getSize() && index2 < pcb.getSize()) {
    Contact& contact1 = pcb[index1];
    Contact& contact2 = pcb[index2];


    if (contact1 == contact2 && contact1.getType() == contact2.getType()) {
        std::cout << "Контакты одного типа расположены в одной точке." << std::endl;
    } else {
        std::cout << "Контакты различны или расположены в разных точках." << std::endl;
    }
} else {
    std::cout << "Неверные индексы." << std::endl;
}
system("pause");

}
 case 15: {
            pcb.printBoard();
             system("pause");
            break;
        }

       case 16: {
            std::cout << "Объединение текущей платы с новой платой." << std::endl;
             PrintedCircuitBoard pcb2;

            pcb2 += Contact(Contact::ContactType::INPUT, 50.0, 60.0);

            PrintedCircuitBoard combinedPCB = pcb + pcb2;
            std::cout << "Объединенная плата:" << std::endl;
            combinedPCB.printBoard();
            system("pause");
            break;
        }

            default: {
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
            }
        }
    }

    return 0;
}
