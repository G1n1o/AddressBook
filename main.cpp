#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct User {
    int idUser;
    string login, password;
};

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

void addUserToFile (User newUser) {

    fstream file;
    file.open("users.txt", ios::app);

    cout << ((file.good() == true) ? "Trwa zapis danych do bazy" : "Houston mamy problem") << endl;
    Sleep(500);

    file << newUser.idUser<<"|";
    file << newUser.login <<"|";
    file << newUser.password <<"|"<< endl;

    file.close();
}

void readUsersDataFile (vector <User> &users) {
    User newUser;
    fstream file;
    int id;
    string id_str, login, password;
    string line;
    file.open("users.txt",ios::in);

    while(getline(file, line))    {
        stringstream myStream(line);

        getline(myStream, id_str, '|');
        getline(myStream, login, '|');
        getline(myStream, password, '|');

        id = stoi(id_str);

        User newUser = {id, login, password};
        users.push_back(newUser);
       }
    file.close();
}

string loginCheck (vector <User> users, string &login) {
    for (size_t i = 0; i < users.size(); i++) {
            if ((users[i].login == login) || login.empty()) {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            login = readLine();
            loginCheck(users, login);
        }
    }
    return login;
}

void registration (vector <User> &users) {
    User newUser;
    string login ="", password="";
    cout << "Podaj nazwe uzytkownika: ";
    login = readLine();

   while (login.empty()){
   if(login.empty()) {
    cout << "Podales pusty login. Podaj login jeszcze raz: ";
    login = readLine();
    }
   }

    loginCheck(users, login);

    cout << "Podaj haslo: ";
    password = readLine();

    newUser.login = login;
    newUser.password = password;
    newUser.idUser = users.size() + 1;

    addUserToFile(newUser);
    users.push_back(newUser);
    cout << "Konto zostalo zalozone."<< endl;
    Sleep(600);
}

int readAddressesDataFile (vector <Addressee> &addresses, User user) {
    Addressee newAddressee;
    fstream file;
    int id = 0;
    int idUser;
    string id_str, name, surname, phoneNumber, address, email, idUser_str;
    string line;
    file.open("addresses.txt",ios::in);

    while(getline(file, line))    {
        stringstream myStream(line);

        getline(myStream, id_str, '|');
        getline(myStream, idUser_str, '|');
        getline(myStream, name, '|');
        getline(myStream, surname, '|');
        getline(myStream, phoneNumber, '|');
        getline(myStream, address, '|');
        getline(myStream, email, '|');

        id = stoi(id_str);
        idUser = stoi (idUser_str);
        Addressee newAddressee = {id, name, surname, phoneNumber, address, email};
        if (user.idUser == idUser) {
        addresses.push_back(newAddressee);
          }
    }
    file.close();
    return id;
}

void addAdresseeToFile (Addressee newAddressee, User user) {
    fstream file;
    file.open("addresses.txt", ios::app);

    cout << ((file.good() == true) ? "Trwa zapis danych do bazy" : "Houston mamy problem") << endl;
    Sleep(500);

    file << newAddressee.id <<"|";
    file << user.idUser <<"|";
    file << newAddressee.name <<"|";
    file << newAddressee.surname <<"|";
    file << newAddressee.phoneNumber <<"|";
    file << newAddressee.address <<"|";
    file << newAddressee.email <<"|"<< endl;

    file.close();
}

void SaveChangesAddresseeInFile (Addressee &addresse, User user) {
    int id;
    string line;
    ifstream addressesFile ("addresses.txt");
    ofstream userAddressesFile ("addresses_temp.txt");

    while(getline(addressesFile, line))    {

        id = stoi(line);

        if (id == addresse.id) {
        userAddressesFile << addresse.id <<"|";
        userAddressesFile << user.idUser <<"|";
        userAddressesFile << addresse.name <<"|";
        userAddressesFile << addresse.surname <<"|";
        userAddressesFile << addresse.phoneNumber <<"|";
        userAddressesFile << addresse.address <<"|";
        userAddressesFile << addresse.email <<"|"<< endl;
        } else {
        userAddressesFile << line << endl;
       }

    }
    addressesFile.close();
    userAddressesFile.close();
    remove("addresses.txt");
    rename("addresses_temp.txt", "addresses.txt");
}

void SaveRemovesAddresseeInFile (Addressee &addresse) {
    int id;
    string line;
    ifstream addressesFile ("addresses.txt");
    ofstream userAddressesFile ("addresses_temp.txt");

    while(getline(addressesFile, line))    {

        id = stoi(line);

        if (id == addresse.id) {
        continue;
        } else {
         userAddressesFile << line << endl;
        }

    }
    addressesFile.close();
    userAddressesFile.close();
    remove("addresses.txt");
    rename("addresses_temp.txt", "addresses.txt");
}

void saveChangesInUsersFiles (vector <User> &users) {
    fstream file;
    file.open("temp.txt", ios::app);

    cout << ((file.good() == true) ? "" : "Houston mamy problem");
    Sleep(400);

    for (size_t i = 0; i < users.size(); i++) {
        file << users[i].idUser <<"|";
        file << users[i].login <<"|";
        file << users[i].password <<"|"<< endl;
    }
    file.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");
}

void addPerson (vector <Addressee> &addresses, User user, int &lastId) {
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

    id = (lastId == 0) ? 1 : lastId + 1;

    newAddressee.id = id;
    newAddressee.name = name;
    newAddressee.surname = surname;
    newAddressee.phoneNumber = phoneNumber;
    newAddressee.address = address;
    newAddressee.email = email;

    addAdresseeToFile(newAddressee, user);
    addresses.push_back(newAddressee);
    lastId++;
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
        system("pause");
        return;
    }

    for (const Addressee &addressee : addresses) {
        printData(addressee);
    }
    system("pause");
}

void editAddressee(vector <Addressee> &addresses, User user) {
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
                Sleep(200);
                break;

            case '2':
                cout << "Podaj nowe nazwisko: " << endl;
                addresses[i].surname = readLine();
                cout << "Nazwisko zostalo zmienione. " << endl;
                Sleep(200);
                break;

            case '3':
                cout << "Podaj nowy numer telefonu: " << endl;
                addresses[i].phoneNumber = readLine();
                cout << "Numer zostal zmieniony. " << endl;
                Sleep(200);
                break;

            case '4':
                cout << "Podaj nowy adres: " << endl;
                addresses[i].address = readLine();
                cout << "Adres zostal zmieniony. " << endl;
                Sleep(200);
                break;

            case '5':
                cout << "Podaj nowy adres mailowy: " << endl;
                addresses[i].email = readLine();
                cout << "Adres mailowy zostal zmieniony. " << endl;
                Sleep(200);
                break;

            case '6':
                break;

            default:
                cout << "Nie ma takiej opcji!. Wpisz ponownie!"<< endl;
                Sleep(400);
            }
            SaveChangesAddresseeInFile(addresses[i], user);
            break;
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
                SaveRemovesAddresseeInFile(addresses[i]);
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

void changePassword (User &user) {
    system ("cls");
    cout << ">>>>>>>>>>>>>>  ZMIANA HASLA <<<<<<<<<<<<<<<<<<<" << endl << endl;
    cout << "Podaj nowe haslo: ";
    user.password = readLine();
    cout << "Haslo zostalo zmienione"<< endl;
    Sleep(200);
}

void goToAddressBook (User &user) {
    char choice;
    int lastId = 0;
    vector <Addressee> addresses;
    lastId = readAddressesDataFile(addresses, user);

    while (choice != '9') {
        system ("cls");
        cout << ">>>>>>>>>>>>>>  Ksiazka Adresowa <<<<<<<<<<<<<<<<<<<" << endl << endl;
        cout << "1. Dodaj nowego adresata" << endl;
        cout << "2. Wyszukaj adresata po Imieniu" << endl;
        cout << "3. Wyszukaj adresata po Nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow"<< endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl << endl;
        cout << "Twoj wybor: ";
        choice = readSign();

        switch (choice) {
        case '1': addPerson(addresses, user, lastId); break;
        case '2': searchByName(addresses); break;
        case '3': searchBySurname(addresses); break;
        case '4': showAllAdresses(addresses); break;
        case '5': removeAddressee(addresses); break;
        case '6': editAddressee(addresses, user); break;
        case '7': changePassword(user); break;
        case '9': break;
        default:
            cout << "Nie ma takiej opcji!. Wpisz ponownie!"<< endl;
            Sleep(500);
        }
    }
}

void logging (vector <User> &users) {
    string login, password;
    cout << "Podaj nazwe uzytkownika: ";
    login = readLine();
    size_t i=0;

    while (i < users.size()) {
        if (users[i].login == login) {
            for (int j = 0; j < 3; j++) {
                cout << "Podaj haslo, pozostalo prob "<< 3-j<<": ";
                password= readLine();
                if (users[i].password == password) {
                    goToAddressBook(users[i]);
                    saveChangesInUsersFiles(users);
                    return;
                }
            }
            cout << "Podales 3 razy bledne haslo. Odczekaj 3 sekundy aby sprobowac ponownie" << endl;
            Sleep (3000);
        } else {
            i++;
        }
    }
    cout  << "Nie ma uzytkownika z takim loginem";
    Sleep(1000);
}

int main() {
    char choice;
    vector <User> users;
    readUsersDataFile(users);


    while (true) {
        system ("cls");
        cout << ">>>>>>>>>> MENU UZYTKOWNIKA <<<<<<<<<<"<< endl << endl;;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Koniec programu" << endl << endl;
        cout << "Twoj wybor: ";
        choice = readSign();

        switch (choice) {
        case '1': registration(users); break;
        case '2': logging(users); break;
        case '9': exit(0); break;
        default:
            cout << "Nie ma takiej opcji!. Wpisz ponownie!"<< endl;
            Sleep(500);
        }
    }
    return 0;
}
