/**
 * @file main.cpp
 * @brief A program for managing passwords.
 * This program lets user to safely hold encrypted informations about name of passwords, passwords,
 * categories, websites, logins in .txt file. The program offers many possibilities.
 * Among other things, saving passwords, searching for passwords, sorting, generating passwords, etc.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

using std::string, std::time_t, std::tm, std::cout, std::cin, std::ofstream, std::ifstream,
        std::getline, std::vector, std::istringstream, std::ostringstream, std::ios, std::endl,
        std::rand, std::sort, std::get_time, std::mktime;

/**
 * @brief Represents a password.
 */
struct Password {
    string name;
    string password;
    string category;
    string website;
    string login;
};

/**
 * @brief Prompts the user to choose a file from a directory.
 *
 * Goes through the directory and adds files with .txt extension to vector.
 * Then function prints it and asks user which file he wants to use.
 *
 * @return The path of the selected file.
 */
string chooseFileFromDirectory() {
    string directoryPath = R"(D:\Users\Emil\PJC\)";
    vector<string> txtFiles;


    for (const auto &entry: fs::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path().filename().string());
        }
    }


    cout << "Dostepne pliki .txt:\n";
    for (int i = 0; i < txtFiles.size(); i++) {
        cout << i + 1 << ". " << txtFiles[i] << "\n";
    }


    if (txtFiles.empty()) {
        cout << "Brak plikow .txt w folderze projektu.\n";
    } else {
        cout << "Wybierz numer pliku do otwarcia: ";
        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= txtFiles.size()) {
            string selectedFile = directoryPath + txtFiles[choice - 1];
            cout << "Wybrano plik: " << selectedFile << "\n";
            return selectedFile;
        } else {
            cout << "Nieprawidlowy numer pliku.\n";
        }
    }
    return "";
}

/**
 * @brief Saves the timestamp of the current time to the specified file.
 * @param sourceFile The path of the file to save the timestamp to.
 */
void saveTimeStamp(const string &sourceFile) {
    ofstream file(sourceFile, std::ios_base::app);  // Otwórz plik w trybie "dopisywania"
    if (file.is_open()) {
        time_t seconds = ::time(nullptr);
        auto localise = ::localtime(&seconds);
        auto timestamp = ::asctime(localise);

        file << "Timestamp: " << timestamp << endl;
        file.close();
    } else {
        ::cout << "Nie udalo się otworzyc pliku.\n";
    }
}

/**
 * @brief Finds the latest timestamp in the specified file and prints it.
 * @param sourceFile The path of the file to search for timestamps.
 */
void findLatestTimeStamp(const string &sourceFile) {
    ifstream file(sourceFile);

    string line;
    string latestTimeStamp;
    time_t latestTime = 0;
    while (getline(file, line)) {
        if (line.find("Timestamp: ") != string::npos) {
            tm time{};
            istringstream iss(line.substr(11)); //na 11 elemencie linii zaczyna się data
            iss >> get_time(&time, "%a %b %d %H:%M:%S %Y");

            time_t timestamp = mktime(&time);
            if (timestamp > latestTime) {
                latestTime = timestamp;
                latestTimeStamp = line;
            }
        }
    }
    file.close();

    if (!latestTimeStamp.empty()) {
        cout << "Ostatnio odszyfrowano: " << latestTimeStamp << ::endl;
    } else {
        cout << "Brak informacji kiedy plik byl odszyfrowany";
    }
}

/**
 * @brief Encrypts the data using a simple encryption algorithm.
 * @param data The data to be encrypted.
 * @param passwordToFile The file password.
 */
void encryptData(string &data, const string &passwordToFile) {
    if (passwordToFile == "dskjfhslcklsjid182u104324m2409A&*$*!(@#)lxdkadasde12321") {
        string encryptedData = data;

        int j = 0;
        for (int i = 5; j < data.size(); i++) {
            encryptedData[j] = char(data[j] + i);
            j++;
        }
        data = encryptedData;
    }
}

/**
 * @brief Decrypts the data using the same algorithm but in reverse.
 * @param data The data to be decrypted.
 * @param passwordToFile File password.
 */
void decryptData(string &data, const string &passwordToFile) {
    if (passwordToFile == "dskjfhslcklsjid182u104324m2409A&*$*!(@#)lxdkadasde12321") {
        string decryptedData = data;

        int j = 5 + data.size() - 1;
        for (int i = data.size() - 1; i >= 0; i--) {
            decryptedData[i] = char(data[i] - j);
            j--;
        }
        data = decryptedData;

    } else {
        cout << "Zle haslo do pliku!";
    }
    //saveTimeStamp(sourcefile); //saveTimeStamp rozdzieliłem na poszczególne metody, żeby nie zapisywał wiele razy tej samej daty do pliku
}

/**
 * @brief Gets data from a file and decrypts it.
 *
 * Function goes through whole file and assigns information to the created Password structure
 *
 * @param sourceFile The path of the file containing data.
 * @param passwordToFile Password file.
 * @return A vector of Password objects containing the decrypted data.
 */
vector<Password> getDataFromFile(const string &sourceFile, const string &passwordToFile) {
    string line;
    Password currentPassword;
    string name, password, category, website, login;
    ifstream file(sourceFile);
    vector<Password> decryptedData;
    while (getline(file, line)) {
        if (line.find("Nazwa: ") != string::npos) {

            name = "";
            for (size_t i = 7; i < line.size(); ++i) {
                name.push_back(line.at(i));
            }
            decryptData(name, passwordToFile);
            currentPassword.name = name;
            //currentPassword.name = decryptData(name);

        } else if (line.find("Haslo: ") != string::npos) {
            password = "";
            for (size_t i = 7; i < line.size(); ++i) {
                password.push_back(line.at(i));
            }
            decryptData(password, passwordToFile);
            currentPassword.password = password;
            //currentPassword.password = decryptData(password);

        } else if (line.find("Kategoria: ") != string::npos) {

            category = "";
            for (size_t i = 11; i < line.size(); ++i) {
                category.push_back(line.at(i));
            }
            decryptData(category, passwordToFile);
            currentPassword.category = category;
            //currentPassword.category = decryptData(category);

        } else if (line.find("Strona WWW: ") != string::npos) {

            website = "";
            for (size_t i = 12; i < line.size(); ++i) {
                website.push_back(line.at(i));
            }
            decryptData(website, passwordToFile);
            currentPassword.website = website;
            //currentPassword.website = decryptData(website);

        } else if (line.find("Login: ") != string::npos) {

            login = "";
            for (size_t i = 7; i < line.size(); ++i) {
                login.push_back(line.at(i));
            }
            decryptData(login, passwordToFile);
            currentPassword.login = login;
            //currentPassword.login = decryptData(login);
        }

        if (!currentPassword.name.empty() && !currentPassword.password.empty() &&
            !currentPassword.category.empty()) {
            decryptedData.push_back(currentPassword);
            currentPassword = Password(); // reset
        } //else {
        //cout << "Blad przy odczycie pliku!" << endl;
        //}
    }

    return decryptedData;
}

/**
 * @brief Checks the strength of a password.
 *
 * This function checks every parameter of the password including lowerCase, upperCase letters. It also
 * checks if the given password has digits and special characters. Then it prints the strength of password
 *
 * @param password The password to check.
 */
void isPasswordSafe(const string &password) {
    int length = password.length();
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;
    string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    for (int i = 0; i < length; i++) {
        if (islower(password[i]))
            hasLower = true;
        if (isupper(password[i]))
            hasUpper = true;
        if (isdigit(password[i]))
            hasDigit = true;
        size_t special = password.find_first_not_of(normalChars);     //znajdz wszystkie poza podanymi u góry
        if (special != string::npos)
            specialChar = true;
    }

    cout << "Sila hasla: ";
    if (hasLower && hasUpper && hasDigit &&
        specialChar && (length >= 8))
        cout << "Silne" << endl;
    else if ((hasLower || hasUpper) &&
             specialChar && (length >= 6))
        cout << "Umiarkowane" << endl;
    else
        cout << "Slabe" << endl;
}

/**
 * @brief Retrieves passwords from a file and decrypts them.
 *
 * This function goes through the whole file looking for only passwords. When it finds them, it decrypts them and
 * adds them to vector.
 *
 * @param sourcefile The path of the file containing passwords.
 * @param passwordToFile File password.
 * @return A vector of decrypted passwords.
 */
vector<string> getPasswordsFromFile(string &sourcefile, const string &passwordToFile) {
    ifstream file(sourcefile);
    string line;
    vector<string> passwords;
    string password;

    if (!file.is_open()) {
        cout << "Nie mozna otworzyc pliku." << endl;
        return passwords;
    }

    while (getline(file, line)) {
        if (line.find("Haslo: ") != string::npos) {
            password = "";

            for (size_t i = 7; i < line.size(); ++i) {
                password.push_back(line.at(i));
            }
            decryptData(password, passwordToFile);
            passwords.push_back(password);
            //passwords.push_back(decryptData(password));
        }
    }
    saveTimeStamp(sourcefile);
    file.close();
    return passwords;
}

/**
 * @brief Checks if a password has been used before.
 *
 * This function checks if the given password has been used in the given file. It uses getPasswordsFromFile method
 * to get string vector from it and check it.
 *
 * @param searchedPass The password to search for.
 * @param sourceFile The path of the file containing passwords.
 * @param passwordToFile File password.
 */
void wasPasswordUsed(const string &searchedPass, string &sourceFile, const string &passwordToFile) {
    bool isUsed = false;
    vector<string> passwords = getPasswordsFromFile(sourceFile, passwordToFile);

    for (const auto &element: passwords) {
        if (element.find(searchedPass) != string::npos) {
            isUsed = true;
            break;
        }
    }

    if (isUsed) {
        cout << "Haslo jest juz uzyte." << endl;
    } else {
        cout << "Haslo nie zostalo jeszcze uzyte." << endl;
    }
}

/**
 * @brief Searches for a password in the specified source file.
 * In the vector of Password structs this function looks for a given password. If it finds the password it prints
 * the information about it.
 *
 * @param sourceFile The path of the source file.
 * @param searchedPass The password to search for.
 * @param passwordToFile File password.
 * @return True if the password is found, false otherwise.
 */
bool searchPassword(const string &sourceFile, string &searchedPass, const string &passwordToFile) {
    bool found = false;

    vector<Password> decryptedData = getDataFromFile(sourceFile, passwordToFile);

    for (int i = 0; i < decryptedData.size(); ++i) {
        if(decryptedData.at(i).password == searchedPass){
            found = true;
            cout<<"Znaleziono haslo: "<<endl;
            cout<<"Nazwa: " << decryptedData.at(i).name << ", Haslo: " << decryptedData.at(i).password
            << ", Kategoria: " << decryptedData.at(i).category << endl;
            return true;
        }
    }

    if(!found){
        cout<<"Nie znaleziono hasla!"<<endl;
        return found;
    }
}

/**
 * @brief Generates a password based on user preferences.
 * This function asks user what parameters should his/her password have. It includes lowerCase, upperCase letters,
 * special characters, digits.
 *
 * @return The generated password.
 */
string generatePassword() {
    string availableChars;
    string password;
    int choice;
    int numOfCharacters;
    bool hasSmallLetters = false;
    bool hasBigLetters = false;
    bool hasSpecialChars = false;
    bool hasNumbers = false;

    cout << "Ile znakow ma miec haslo?: ";
    cin >> numOfCharacters;

    //hasSmallLetters?
    {
        cout << "Czy ma zawierac male litery?\n1. Tak \n2. Nie" << endl;
        cin >> choice;

        if (choice == 1) {
            hasSmallLetters = true;
        } else if (choice == 2) {
            hasSmallLetters = false;
        } else {
            cout << "Nieprawidlowy wybor!" << endl;
        };
    }
    //hasBigLetters?
    {
        choice = 0;
        cout << "Czy ma zawierac wielkie litery?\n1. Tak \n2. Nie" << endl;
        cin >> choice;

        if (choice == 1) {
            hasBigLetters = true;
        } else if (choice == 2) {
            hasBigLetters = false;
        } else {
            cout << "Nieprawidlowy wybor!" << endl;
        };
    }
    //hasSpecialChars?
    {
        choice = 0;
        cout << "Czy ma zawierac znaki specjalne?\n1. Tak \n2. Nie" << endl;
        cin >> choice;

        if (choice == 1) {
            hasSpecialChars = true;
        } else if (choice == 2) {
            hasSpecialChars = false;
        } else {
            cout << "Nieprawidlowy wybor!" << endl;
        }
    }
    //hasNumbers?
    {
        choice = 0;
        cout << "Czy ma zawierac cyfry?\n1. Tak \n2. Nie" << endl;
        cin >> choice;

        if (choice == 1) {
            hasNumbers = true;
        } else if (choice == 2) {
            hasNumbers = false;
        } else {
            cout << "Nieprawidlowy wybor!" << endl;
        }
    }

    if (hasSmallLetters) {
        availableChars += "abcdefghijklmnopqrstuvwxyz";
    }

    if (hasBigLetters) {
        availableChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    if (hasSpecialChars) {
        availableChars += "!@#$%^&*()_+{}[]<>?";
    }

    if (hasNumbers) {
        availableChars += "1234567890";
    }


    for (int i = 0; i < numOfCharacters; ++i) {
        int indeks = rand() % availableChars.size();
        password += availableChars[indeks];
    }

    choice = 0;
    cout << "Wygenerowane haslo to: " << password << endl;
    cout << "Czy haslo moze byc?\n1. Tak \n2. Nie" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            return password;
            break;
        case 2:
            generatePassword();
            break;
        default:
            cout << "Nieprawidlowy wybor!";
    }
}

/**
 * @brief Saves a password to a file.
 * This function creates a Password struct, assigns values to its variables and saves it to given file
 *
 * @param password The password to save.
 * @param sourceFile The path of the file to save to.
 * @param passwordToFile File password.
 */
void savePassword(const string &password, string &sourceFile, const string &passwordToFile) {
    int choice = 0;

    ofstream file(sourceFile, ios::app);
    Password data;
    isPasswordSafe(password);
    data.password = password;

    cout << "Podaj nazwe: ";
    cin >> data.name;
    cout << "Podaj kategorie: ";
    cin >> data.category;

    cout << "Czy ma strone WWW?\n1. Tak \n2. Nie" << endl;
    cin >> choice;
    if (choice == 1) {
        cout << "Podaj strone WWW: ";
        cin >> data.website;
    }

    choice = 0;
    cout << "Czy ma login?\n1. Tak \n2. Nie" << endl;
    cin >> choice;
    if (choice == 1) {
        cout << "Podaj login: ";
        cin >> data.login;
    };



    encryptData(data.name, passwordToFile);
    encryptData(data.password, passwordToFile);
    encryptData(data.category, passwordToFile);

    if (!data.website.empty()) {
        encryptData(data.website, passwordToFile);
    }

    if (!data.login.empty()) {
        encryptData(data.login, passwordToFile);
    }


    {
        file << "Nazwa: " << data.name << endl;
        file << "Haslo: " << data.password << endl;
        file << "Kategoria: " << data.category << endl;

        if (!data.website.empty()) {
            file << "Strona WWW: " << data.website << endl;
        }

        if (!data.login.empty()) {
            file << "Login: " << data.login << endl;
        }
    }

    file.close();
}

/**
 * @brief Sorts password entries in different ways and displays the sorted results.
 * This function asks user how to sort data from file. Then sorts it in one of three different ways
 * and displays the results.
 *
 * @param sourcefile The path of the file containing passwords.
 * @param passwordToFile File password.
 */
void sortPassword(const string &sourcefile, const string &passwordToFile) {
    vector<Password> entries;
    ifstream file(sourcefile);

    if (!file.is_open()) {
        cout << "Nie mozna otworzyc pliku: ";
        return;
    }

    entries = getDataFromFile(sourcefile, passwordToFile);

    saveTimeStamp(sourcefile);  //próba odszyfrowania przy sortowaniu
    file.close();
    int choice;
    cout << "Po czym chcesz sortowac?\n1. Po nazwie i kategorii\n2. Po haslach i kategorii\n3. Po nazwie i haslach\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            sort(entries.begin(), entries.end(), [](const Password &p1, const Password &p2) {
                if (p1.name == p2.name) {
                    return p1.category > p2.category;
                } else {
                    return p1.name > p2.name;
                }
            });                                                                         //if p1.name == p2.name {return p1.category > p2.category}
            for (const Password &entry: entries) {
                cout << "Nazwa: " << entry.name << ", Kategoria: " << entry.category << ", Haslo: " << entry.password
                     << endl;
            }
        }
            break;
        case 2: {
            sort(entries.begin(), entries.end(), [](const Password &p1, const Password &p2) -> bool {
                if (p1.password == p2.password) {
                    return p1.category > p2.category;
                } else {
                    return p1.password > p2.password;
                }
            });
            for (const Password &entry: entries) {
                cout << "Haslo: " << entry.password << ", Kategoria: " << entry.category << ", Nazwa: " << entry.name
                     << endl;
            }
        }
            break;
        case 3: {
            sort(entries.begin(), entries.end(), [](const Password &p1, const Password &p2) {
                if (p1.name == p2.name) {
                    return p1.password > p2.password;
                } else {
                    return p1.name > p2.name;
                }
            });
            for (const Password &entry: entries) {
                cout << "Nazwa: " << entry.name << ", Haslo: " << entry.password << ", Kategoria: " << entry.category
                     << endl;
            }
        }
            break;
        default:
            cout << "Nieprawidłowy wybór!" << endl;
    }
}

/**
 * @brief Edits a password entry in a file.
 * This function asks user for a password and then, if found, lets him edit every information about the password
 * @param sourceFile The path of the file containing passwords.
 * @param passwordToFile File password.
 */
void editPassword(const string &sourceFile, const string &passwordToFile) {
    string searchedPass;
    int choice;
    cout << "Podaj szukane haslo: ";
    cin >> searchedPass;
    if (searchPassword(sourceFile, searchedPass, passwordToFile)) {
        ifstream inFile(sourceFile);
        ofstream outFile(R"(D:\Users\Emil\PJC\temp.txt)", ios::app);
        string line;

        if (inFile.is_open() && outFile.is_open()) {
            while (getline(inFile, line)) {
                if (line.find("Nazwa: ") == 0) {
                    if (line.length() > 7) {
                        string currentName = line.substr(7);
                        string newName;
                        decryptData(currentName, passwordToFile);
                        cout << "Obecna nazwa: " << currentName << ::endl;
                        cout << "Nowa nazwa: ";
                        cin.ignore();
                        getline(cin, newName);
                        line = "Nazwa: " + newName;
                    }
                } else if (line.find("Haslo: ") == 0) {
                    if (line.length() > 7) {
                        string currentPassword = line.substr(7);
                        string newPassword;
                        decryptData(currentPassword, passwordToFile);
                        cout << "Obecne haslo: " << currentPassword << ::endl;
                        cout << "Nowe haslo: ";
                        cin.ignore();
                        getline(cin, newPassword);
                        line = "Haslo: " + newPassword;
                    }
                } else if (line.find("Kategoria: ") == 0) {
                    if (line.length() > 11) {
                        string currentCategory = line.substr(11);
                        string newCategory;
                        decryptData(currentCategory, passwordToFile);
                        cout << "Obecna kategoria: " << currentCategory << ::endl;
                        cout << "Nowa kategoria: ";
                        cin.ignore();
                        getline(::cin, newCategory);
                        line = "Kategoria: " + newCategory;
                    }
                } else if (line.find("Strona WWW: ") == 0) {
                    if (line.length() > 12) {
                        string currentWebsite = line.substr(12);
                        string newWebsite;
                        decryptData(currentWebsite, passwordToFile);
                        cout << "Obecna strona WWW: " << currentWebsite << ::endl;
                        cout << "Nowa strona WWW: ";
                        cin.ignore();
                        getline(::cin, newWebsite);
                        line = "Strona WWW: " + newWebsite;
                    }
                } else if (line.find("Login: ") == 0) {
                    if (line.length() > 7) {
                        string currentLogin = line.substr(7);
                        string newLogin;
                        decryptData(currentLogin, passwordToFile);
                        cout << "Obecny login: " << currentLogin << ::endl;
                        cout << "Nowy login: ";
                        cin.ignore();
                        getline(::cin, newLogin);
                        line = "Login: " + newLogin;
                    }
                }
                encryptData(line, passwordToFile);
                outFile << line << endl;
            }
            saveTimeStamp(sourceFile);

            //rename nie dziala ze zmienna outFile wiec podaję string
            if (rename(R"(D:\Users\Emil\PJC\temp.txt)", R"(D:\Users\Emil\PJC\data.txt)") == 0) {
                cout << "Dane zostały pomyslnie zaktualizowane." << endl;
            } else {
                cout << "Blad: Nie mozna zmienic nazwy pliku." << endl;
            }
            inFile.close();
            outFile.close();
        } else {
            cout << "Blad: Nie mozna otworzyc pliku do odczytu lub zapisu." << endl;
        }
    } else {
        cout << "Blad: Podane haslo nie istnieje w pliku." << endl;
    }
}

/**
 * @brief Removes a password from the specified source file.
 * In the vector of Password structs this funtion looks for a given by user password to delete. If it finds the
 * given password it deletes all the data connected with it.
 *
 * @param sourcefile The path of the source file.
 * @param passwordToFile File password.
 */
void removePassword(const string &sourcefile, const string &passwordToFile) {
    string toDelete;
    cout << "Podaj haslo do usuniecia: ";
    cin >> toDelete;

    ifstream file(sourcefile);

    vector<Password> entries;

    if (searchPassword(sourcefile, toDelete, passwordToFile)) {
        decryptData(toDelete, passwordToFile);
        entries = getDataFromFile(sourcefile, passwordToFile);

        for (int i = 0; i < entries.size(); ++i) {
            if (entries.at(i).password == toDelete) {
                cout << "Usuwanie hasla: " << toDelete<<endl;
                entries.erase(entries.begin() + i);
                break; //inaczej usunęło by wiele takich samych haseł
            }
        }

        if (!entries.empty()) {
            ofstream outFile(R"(D:\Users\Emil\PJC\temp.txt)", ios::app);
            for (const Password &entry: entries) {

                string name = entry.name;
                string password = entry.password;
                string category = entry.category;
                encryptData(name, passwordToFile);
                encryptData(password, passwordToFile);
                encryptData(category, passwordToFile);

                outFile << "Nazwa: " << name << endl;
                outFile << "Haslo: " << password << endl;
                outFile << "Kategoria: " << category << endl;

                if (!entry.website.empty()) {
                    string website = entry.website;
                    encryptData(website, passwordToFile);
                    outFile << "Strona WWW: " << website << endl;
                }

                if (!entry.login.empty()) {
                    string login = entry.login;
                    encryptData(login, passwordToFile);
                    outFile << "Login: " << entry.login << endl;
                }
            }
            rename(R"(D:\Users\Emil\PJC\temp.txt)", R"(D:\Users\Emil\PJC\data.txt)");
            saveTimeStamp(sourcefile);
        } else {
            cout << "Blad podczas odczytu z pliku!";
        }
        int choice;
        cout<<"Czy chcesz usunac kolejne haslo?\n1.Tak\n2.Nie\n";
        cin>>choice;

        //usuwanie wielu hasel jako rekurencja
        switch (choice) {
            case 1:
                removePassword(sourcefile, passwordToFile);
                break;
            case 2: return;
        }

    }


}

/**
 * @brief Removes a category from the specified source file.
 * In the vector of Password structs this function looks for a given by user category to delete. If it finds the
 * given category it deletes all the passwords with this category.
 *
 * @param sourceFile The path of the source file.
 * @param passwordToFile File password.
 */
void removeCategory(const string &sourceFile, const string &passwordToFile) {
    string toDelete;
    bool found = false;
    cout << "Podaj kategorie do usuniecia: ";
    cin >> toDelete;

    ifstream inFile(sourceFile);

    vector<Password> decryptedData = getDataFromFile(sourceFile, passwordToFile);
    for (int i = 0; i < decryptedData.size(); ++i) {
        if(decryptedData.at(i).category==toDelete){
            decryptedData.erase(decryptedData.begin()+i);
            found=true;
            //bez break bo usunie wiele haseł.
        }
    }

    if(!found){
        cout<<"Nie ma takiej kategorii"<<endl;
    }else{
        //zapis
        cout<<"Usunieto wpisy z kategoria filmy";
        ofstream outFile(R"(D:\Users\Emil\PJC\temp.txt)", ios::app);
        for (const auto &entry: decryptedData) {
            string name = entry.name;
            string password = entry.password;
            string category = entry.category;
            encryptData(name, passwordToFile);
            encryptData(password, passwordToFile);
            encryptData(category, passwordToFile);
            outFile << "Nazwa: " << name << endl;
            outFile << "Haslo: " << password << endl;
            outFile << "Kategoria: " << category << endl;

            if (!entry.website.empty()) {
                string website = entry.website;
                encryptData(website, passwordToFile);
                outFile << "Strona WWW: " << website << endl;
            }

            if (!entry.login.empty()) {
                string login = entry.login;
                encryptData(login, passwordToFile);
                outFile << "Login: " << login << endl;
            }
        }
        rename(R"(D:\Users\Emil\PJC\temp.txt)", R"(D:\Users\Emil\PJC\data.txt)");
        outFile.close();
    }
}

/**
 * @brief Adds a category to the list of available categories.
 * @param categories The vector of available categories.
 */
void addCategory(const string &sourceFile, const string &passwordToFile) {
    string newCategory;
    vector<string> categories;
    cout << "Podaj nazwe nowej kategorii: ";
    cin >> newCategory;


    if (find(categories.begin(), categories.end(), newCategory) != categories.end()) {
        cout << "Kategoria o podanej nazwie juz istnieje.\n";
        return;
    }


    categories.push_back(newCategory);
    cout << "Dodano nową kategorie.\n";
}


//poprawne haslo do pliku: dskjfhslcklsjid182u104324m2409A&*$*!(@#)lxdkadasde12321
//void autodestruction();

/**
 * @brief The entry point of the program.
 * Main method displays the main menu of the program giving the user eight options to choose from.
 * @return An integer representing the exit status of the program.
 */
int main() {
    int choice;
    string sourceFile;
    string passToFile;
    cout << "1. Podaj plik zrodlowy\n2. Wybierz plik z folderu programu" << endl;
    cin >> choice;

    if (choice == 1) {
        cin >> sourceFile;
        cout << "Podaj haslo do pliku zrodlowego: ";
        cin >> passToFile;
    } else {
        sourceFile = chooseFileFromDirectory();
        if (sourceFile.empty()) {
            return 1;
        }
        cout << "Podaj haslo do pliku zrodlowego: ";
        cin >> passToFile;
    }


    //passToFile=="dskjfhslcklsjid182u104324m2409A&*$*!(@#)lxdkadasde12321"
    if (passToFile == "dskjfhslcklsjid182u104324m2409A&*$*!(@#)lxdkadasde12321") {
        findLatestTimeStamp(sourceFile);
        choice = 0;
        while (true) {
            cout << endl;
            cout << "----------- MENEDZER HASEL -----------\n";
            cout << "1. Dodaj haslo\n";
            cout << "2. Wyszukaj hasla\n";
            cout << "3. Sortuj hasla\n";
            cout << "4. Edytuj haslo\n";
            cout << "5. Usun haslo\n";
            cout << "6. Dodaj kategorie\n";
            cout << "7. Usun kategorie wraz z haslami\n";
            cout << "8. Wyjdz\n";
            cout << "---------------------------------------\n";
            cout << "Wybierz opcje: ";
            cin >> choice;
            cin.ignore();      //nie wczyta entera

            switch (choice) {
                case 1: {
                    int generatePass;
                    cout << "Wygenerowac haslo?\n1. Tak \n2. Nie" << endl;
                    cin >> generatePass;

                    if (generatePass == 1) {
                        savePassword(generatePassword(), sourceFile, passToFile);
                    } else if (generatePass == 2) {
                        string password;
                        cout << "Podaj haslo do zapisania: ";
                        cin >> password;
                        wasPasswordUsed(password, sourceFile, passToFile);
                        savePassword(password, sourceFile, passToFile);
                    } else {
                        cout << "Nieprawidlowy wybor!";
                        break;
                    }
                }
                    break;
                case 2: {
                    string searchedPass;
                    cout << "Podaj szukane haslo: ";
                    cin >> searchedPass;
                    searchPassword(sourceFile, searchedPass, passToFile);
                }
                    break;
                case 3: {
                    sortPassword(sourceFile, passToFile);
                }
                    break;
                case 4: {
                    editPassword(sourceFile, passToFile);
                }
                    break;
                case 5: {
                    removePassword(sourceFile, passToFile);
                    break;
                }
                case 6: {
                    addCategory(sourceFile, passToFile);
                    break;
                }
                    break;
                case 7: {
                    removeCategory(sourceFile, passToFile);
                    break;
                }
                case 8: {
                    return 0;
                    break;
                }
                default:
                    cout << "Bledny wybor.\n";
                    break;
            }
        }
    } else {
        cout << "Nieprawidlowe haslo";
        return 1;
    }
}
