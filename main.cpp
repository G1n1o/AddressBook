#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>
#include <string>

using namespace std;

struct Addressee {
    int id;
    string name, surname, phoneNumber, address, email;
};

string readLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int readNumber() {
    string input;
    int number;

    while (true) {
        getline(cin,input);

        stringstream myStream(input);
        if (myStream >> number) {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie: " << endl;
    }

    return number;
}

char readSign() {
    string input;
    char sign = {0};

    while (true) {
        input = readLine();
        if (input.length() == 1 ) {
            sign = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie: " << endl;
    }
    return sign;
}

void printData (Addressee addressee) {
    cout << endl;
    cout << left;
    cout << setw (20) <<  "ID: "  << setw (20) <<  addressee.id << endl;
    cout << setw (20) << "Imie: "  << setw (20) <<  addressee.name << endl;
    cout << setw (20) << "Nazwisko: "  << setw (20) <<  addressee.surname << endl;
    cout << setw (20) << "Nr. Telefonu: "  << setw (20) <<  addressee.phoneNumber << endl;
    cout << setw (20) << "Adres: "  <<  setw (20) << addressee.address << endl;
    cout << setw (20) << "Adres mailowy: "  <<  setw (20) << addressee.email << endl;
    cout << endl;
}

void addToFile (Addressee newAddressee) {
    fstream file;
    file.open("ksiazka.txt", ios::app);

    cout << ((file.good() == true) ? "Trwa zapis danych do bazy" : "Houston mamy problem") << endl;
    Sleep(500);

    file << newAddressee.id <<"|";
    file << newAddressee.name <<"|";
    file << newAddressee.surname <<"|";
    file << newAddressee.phoneNumber <<"|";
    file << newAddressee.address <<"|";
    file << newAddressee.email <<"|"<< endl;

    file.close();
}

void saveChangesInFile (vector <Addressee> &addresses) {
    fstream file;
    file.open("temp.txt", ios::app);

    cout << ((file.good() == true) ? "" : "Houston mamy problem");
    Sleep(500);

    for (size_t i = 0; i < addresses.size(); i++) {
        file << addresses[i].id <<"|";
        file << addresses[i].name <<"|";
        file << addresses[i].surname <<"|";
        file << addresses[i].phoneNumber <<"|";
        file << addresses[i].address <<"|";
        file << addresses[i].email <<"|"<< endl;
    }
    file.close();

    remove("ksiazka.txt");
    rename("temp.txt", "ksiazka.txt");
}

void readDataFile (vector <Addressee> &addresses) {
    Addressee newAddressee;
    fstream file;
    int id;
    string id_str, name, surname, phoneNumber, address, email;
    string line;
    int lineNumber = 1;
    file.open("ksiazka.txt",ios::in);

    if(file.good()==false) {
        cout<< "Brak danych do wczytania!";
        Sleep (800);
    }

    while(getline(file, line))    {
        stringstream myStream(line);

        getline(myStream, id_str, '|');
        getline(myStream, name, '|');
        getline(myStream, surname, '|');
        getline(myStream, phoneNumber, '|');
        getline(myStream, address, '|');
        getline(myStream, email, '|');

        id = stoi(id_str);

        Addressee newAddressee = {id, name, surname, phoneNumber, address, email};
        addresses.push_back(newAddressee);
        lineNumber++;
    }
    file.close();
}

void addPerson (vector <Addressee> &addresses) {
    Addressee newAddressee;
    int id;
    string name, surname, phoneNumber, address, email;

    cout << "Podaj Imie: ";
    name = readLine();

    cout << "Podaj Nazwisko : ";
    surname = readLine();

    cout << "Podaj numer telefonu: ";
    phoneNumber = readLine();

    cout << "Podaj adres: ";
    address = readLine();

    cout << "Podaj adres mailowy: ";
    email = readLine();


    id = addresses.empty() ? 1 : addresses.back().id +1;

    newAddressee.id = id;
    newAddressee.name = name;
    newAddressee.surname = surname;
    newAddressee.phoneNumber = phoneNumber;
    newAddressee.address = address;
    newAddressee.email = email;

    addToFile(newAddressee);
    addresses.push_back(newAddressee);
    cout << "Adresat zostal dodany. "<< endl;
    Sleep(500);

}

void searchByName ( vector <Addressee> addresses) {
    string name;
    int counter = 0;
    cout << "Podaj imie szukanego adresata: ";
    name = readLine();

    for (size_t i = 0; i < addresses.size(); i++) {
        if (addresses[i].name == name) {
            printData(addresses[i]);
            counter ++;
        }
    }

    if (counter == 0) {
        cout << "Nie ma w bazie adresata z takim imieniem" << endl << endl;
    } else {
        cout << "Znaleziono " << counter << " adresatow" << endl << endl;
    }

    system("pause");
}

void searchBySurname ( vector <Addressee> addresses) {
    string surname;
    int counter = 0;
    cout << "Podaj nazwisko szukanego adresata: ";
    surname = readLine();

    for (size_t i = 0; i < addresses.size(); i++) {
        if (addresses[i].surname == surname) {
            printData(addresses[i]);
            counter ++;
        }
    }

    if (counter == 0) {
        cout << "Nie ma w bazie adresata z takim nazwiskiem" << endl << endl;
    } else {
        cout << "Znaleziono " << counter << " adresatow" << endl<< endl;
    }
    system("pause");
}

void showAllAdresses (vector <Addressee> addresses) {
    system ("cls");

    if (addresses.empty()) {
        cout << endl<< "Baza adresowa jest pusta" << endl << endl;
        return;
    }

    for (const Addressee &addressee : addresses) {
        printData(addressee);
    }
    system("pause");
}

void editAddressee(vector <Addressee> &addresses) {
    system ("cls");
    int id;
    int counter = 0;
    char choice;
    cout << ">>>>>>>>>>>>>>  EDYCJA ADRESATA <<<<<<<<<<<<<<<<<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz edytowac: " ;
    id = readNumber();

    for (size_t i = 0; i < addresses.size(); i++) {
        if (addresses[i].id == id) {

            counter ++;
            system ("cls");
            cout << ">>>>>>>>>>>>>>  EDYCJA ADRESATA <<<<<<<<<<<<<<<<<<<" << endl << endl;
            cout << "Edytujesz adresata:  "<< addresses[i].name << " "<< addresses[i].surname << endl <<endl;
            cout << "Wybierz opcje do edycji: " << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Adres" << endl;
            cout << "5. Adres mailowy" << endl;
            cout << "6. Powrot do menu. " << endl << endl;
            cout << "Twoj wybor: ";

            choice = readSign();

            switch (choice) {
            case '1':
                cout << "Podaj nowe imie: " << endl;
                addresses[i].name = readLine();
                cout << "Imie zostalo zmienione. " << endl;
                Sleep(400);
                break;

            case '2':
                cout << "Podaj nowe nazwisko: " << endl;
                addresses[i].surname = readLine();
                cout << "Nazwisko zostalo zmienione. " << endl;
                Sleep(400);
                break;

            case '3':
                cout << "Podaj nowy numer telefonu: " << endl;
                addresses[i].phoneNumber = readLine();
                cout << "Numer zostal zmieniony. " << endl;
                Sleep(400);
                break;

            case '4':
                cout << "Podaj nowy adres: " << endl;
                addresses[i].address = readLine();
                cout << "Adres zostal zmieniony. " << endl;
                Sleep(400);
                break;

            case '5':
                cout << "Podaj nowy adres mailowy: " << endl;
                addresses[i].email = readLine();
                cout << "Adres mailowy zostal zmieniony. " << endl;
                Sleep(400);
                break;

            case '6':
                break;

            default:
                cout << "Nie ma takiej opcji!. Wpisz ponownie!"<< endl;
                Sleep(400);
            }
            saveChangesInFile(addresses);
        }
    }
    if(counter == 0) {
        cout << endl <<"Nie ma w bazie adresata z takim ID" << endl << endl;
    }

    system("pause");
}

void removeAddressee(vector <Addressee> &addresses) {
    system ("cls");
    int id;
    int counter = 0;
    char choice;
    cout << ">>>>>>>>>>>>>>  USUWANIE ADRESATA <<<<<<<<<<<<<<<<<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz usunac: " ;
    id = readNumber();

    for (size_t i = 0; i < addresses.size(); i++) {
        if (addresses[i].id == id) {
            counter ++;
            cout << "Potwierdz usuniecie adresata "<< addresses[i].name << " "<< addresses[i].surname << " naciskajac klawisz 't':";
            choice = readSign();
            if (choice == 't') {
                addresses.erase(addresses.begin() + i);
                cout << "Usunieto adresata o ID: " << id << endl;
                Sleep(200);
                saveChangesInFile(addresses);
                break;
            } else {
                cout << "Nie potwierdzono usuniecia adresata..."<< endl;
            }
        }
    }
    if(counter == 0) {
        cout << endl <<"Nie ma w bazie adresata z takim ID" << endl << endl;
    }
    system("pause");
}

int main() {
    char choice;
    vector <Addressee> addresses;
    readDataFile(addresses);

    while (true) {
        system ("cls");
        cout << ">>>>>>>>>>>>>>  Ksiazka Adresowa <<<<<<<<<<<<<<<<<<<" << endl << endl;
        cout << "1. Dodaj nowego adresata" << endl;
        cout << "2. Wyszukaj adresata po Imieniu" << endl;
        cout << "3. Wyszukaj adresata po Nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow"<< endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Koniec programu" << endl << endl;
        cout << "Twoj wybor: ";
        choice = readSign();

        switch (choice) {
        case '1': addPerson(addresses); break;
        case '2': searchByName(addresses); break;
        case '3': searchBySurname(addresses); break;
        case '4': showAllAdresses(addresses); break;
        case '5': removeAddressee(addresses); break;
        case '6': editAddressee(addresses); break;
        case '9': exit(0); break;
        default:
            cout << "Nie ma takiej opcji!. Wpisz ponownie!"<< endl;
            Sleep(500);
        }
    }
    return 0;
}

