#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

class CryptoCurrency {
private:
    string name;
    float price;
public:
    CryptoCurrency(string name, float price) {
        this->name = name;
        this->price = price;
    }
    void setName(string name) {
        this->name = name;
    }
    string getName() {
        return name;
    }
    void setPrice(float price) {
        this->price = price;
    }
    float getPrice() {
        return price;
    }
};

class User {
private:
    string username;
    float balance;
    vector<CryptoCurrency> portfolio;
public:
    User(string username, float balance) {
        this->username = username;
        this->balance = balance;
    }
    void setUsername(string username) {
        this->username = username;
    }
    string getUsername() {
        return username;
    }
    void setBalance(float balance) {
        this->balance = balance;
    }
    float getBalance() {
        return balance;
    }
    void addCryptoToPortfolio(CryptoCurrency crypto) {
        portfolio.push_back(crypto);
    }
    vector<CryptoCurrency> getPortfolio() {
        return portfolio;
    }
};

class TradingPlatform {
private:
    vector<CryptoCurrency> availableCryptos;
    vector<User> users;
public:
    void addCryptoToPlatform(CryptoCurrency crypto) {
        availableCryptos.push_back(crypto);
    }
    vector<CryptoCurrency> getAvailableCryptos() {
        return availableCryptos;
    }
    void addUserToPlatform(User user) {
        users.push_back(user);
    }
    vector<User> getUsers() {
        return users;
    }
};

// Function to save all records to a file
void saveRecords(vector<User> users) {
    for (int i = 0; i < users.size(); i++) {
        string filename = users[i].getUsername() + ".txt";
        ofstream outfile(filename.c_str());
        outfile << "Username: " << users[i].getUsername() << endl;
        outfile << "Balance: " << users[i].getBalance() << endl;
        vector<CryptoCurrency> portfolio = users[i].getPortfolio();
        outfile << "Portfolio:" << endl;
        for (int j = 0; j < portfolio.size(); j++) {
            outfile << "\t" << portfolio[j].getName() << " - " << portfolio[j].getPrice() << endl;
        }
        outfile.close();
    }
}

// Function to check if it's peak trading hours (between 9AM and 5PM)
bool isPeakHours() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    if (localTime->tm_hour >= 9 && localTime->tm_hour <= 17) {
        return true;
    }
    return false;
}

int main() {
    TradingPlatform platform;

    CryptoCurrency bitcoin("Bitcoin", 60000.00);
    CryptoCurrency ethereum("Ethereum", 2000.00);

    platform.addCryptoToPlatform(bitcoin);
    platform.addCryptoToPlatform(ethereum);

    User user1("John", 5000.00);
    user1.addCryptoToPortfolio(bitcoin);
    User user2("Jane", 10000.00);
    user2.addCryptoToPortfolio(ethereum);

    platform.addUserToPlatform(user1);
    platform.addUserToPlatform(user2);

    vector<CryptoCurrency> availableCryptos = platform.getAvailableCryptos();
    vector<User> users = platform.getUsers();

    // Display available cryptos
cout << "Available Cryptos:" << endl;
for (int i = 0; i < availableCryptos.size(); i++) {
    cout << "\t" << availableCryptos[i].getName() << " - " << availableCryptos[i].getPrice() << endl;
}

// Display users and their portfolios
cout << endl << "Users:" << endl;
for (int i = 0; i < users.size(); i++) {
    cout << users[i].getUsername() << " - Balance: " << users[i].getBalance() << endl;
    vector<CryptoCurrency> portfolio = users[i].getPortfolio();
    cout << "\tPortfolio:" << endl;
    for (int j = 0; j < portfolio.size(); j++) {
        cout << "\t\t" << portfolio[j].getName() << " - " << portfolio[j].getPrice() << endl;
    }
}

// Save all records to file
saveRecords(users);

// Check if it's peak trading hours and display a notification if it is
if (isPeakHours()) {
    cout << endl << "*** It's peak trading hours! ***" << endl;
}

return 0;
}

