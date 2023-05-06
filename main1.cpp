#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;
class User
{
private:
    string firstName;
    string lastName;
    string username;
    string email;
    string phoneNumber;
    string password;
    string creditCardNumber;
    string expiry;
    string cvv;
    double balance;

public:
    bool logged_in;
    User()
    {
        firstName = "";
        lastName = "";
        username = "";
        email = "";
        phoneNumber = "";
        password = "";
        creditCardNumber = "";
        expiry = "";
        cvv = "";
        balance = 0;
        logged_in = false;
    }

    bool is_logged_in()
    {
        return logged_in;
    }

    string get_first_name()
    {
        return firstName;
    }
    void set_first_name(string firstName)
    {
        this->firstName = firstName;
    }
    void set_last_name(string lastName)
    {
        this->lastName = lastName;
    }
    void set_username(string username)
    {
        this->username = username;
    }
    void set_email(string email)
    {
        this->email = email;
    }
    void set_phone_number(string phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }
    void set_password(string password)
    {
        this->password = password;
    }
    void set_credit_card_number(string creditCardNumber)
    {
        this->creditCardNumber = creditCardNumber;
    }
    void set_expiry(string expiry)
    {
        this->expiry = expiry;
    }
    void set_cvv(string cvv)
    {
        this->cvv = cvv;
    }
    void set_balance(double balance)
    {
        this->balance = balance;
    }
    string get_password()
    {
        return password;
    }
    string get_last_name()
    {
        return lastName;
    }

    string get_username()
    {
        return username;
    }

    string get_email()
    {
        return email;
    }

    string get_phone_number()
    {
        return phoneNumber;
    }

    string get_credit_card_number()
    {
        return creditCardNumber;
    }

    string get_expiry()
    {
        return expiry;
    }

    string get_cvv()
    {
        return cvv;
    }
    double get_balance()
    {
        return balance;
    }
    string login()
    {
        // Prompt user to enter username and password
        string username1, password1;
        cout << "Enter username: ";
        cin >> username1;
    retry:
        cout << "Enter password: ";
        cin >> password1;
        set_password(password1);
        logged_in = false;

        // Check if user exists in file
        string filename = username1 + ".txt";
        ifstream file(filename, ios::in);
        if (file.good())
        {
            string line;
            string pass;
            while (!file.eof())
            {
                getline(file, line);
                if (line == username1)
                {
                    while (getline(file, pass))
                    {
                        if (pass == password1)
                        {
                            cout << "Login successful!" << endl;
                            load_account_info(username1);
                            logged_in = 1;
                            return username1;
                        }
                    }
                    if (logged_in == 0)
                    {
                        int opt;
                        cout << "Incorrect password!" << endl;
                        cout << "press 1 to try again or 0 to exit" << endl;
                        cin >> opt;
                        if (opt == 1)
                        {
                            goto retry;
                        }
                        else
                        {
                            logged_in = 0;
                            break;
                        }
                    }
                }
            }
            if (logged_in == 0)
            {
                cout << "Username does not exist!" << endl;
            }
            file.close();
        }
        else
        {
            cout << "User does not exist!" << endl;
            logged_in = 0;
        }
        return username1;
    }
    void signup()
    {
        // Prompt user to enter information
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter phone number: ";
        cin >> phoneNumber;
        cout << "Enter credit card number: ";
        cin >> creditCardNumber;
        cout << "Enter expiry: ";
        cin >> expiry;
        cout << "Enter CVV: ";
        cin >> cvv;
        cout << "Set password: ";
        cin >> password;
        cout << "Enter Amount You have in your bankAccount: ";
        cin >> balance;

        // Save user information to file
        string filename = username + ".txt";
        ofstream file(filename, ios_base::app);
        file << firstName << endl;
        file << lastName << endl;
        file << username << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << creditCardNumber << endl;
        file << expiry << endl;
        file << cvv << endl;
        file << password << endl;
        file << balance;
        file.close();

        cout << "Signup successful!" << endl;
    }
    void load_account_info(string user)
    {
        string filename = user + ".txt";
        ifstream file(filename, ios::in);
        string line;
        if (file.good())
        {
            while (!file.eof())
            {
                getline(file, firstName);
                getline(file, lastName);
                getline(file, username);
                getline(file, email);
                getline(file, phoneNumber);
                getline(file, creditCardNumber);
                getline(file, expiry);
                getline(file, cvv);
                getline(file, password);
                file >> balance;
                break;
            }
            file.close();
        }
    }
};
class Account_setting : public User

{
private:
    string file_name;

public:
    void change_password(string filename)
    {
        string prev_password;
        int count = 0;
        char ch1;

    retry1:
        cout << "Enter previous password: ";
        cin >> prev_password;

        string current_password;
        vector<string> lines;

        fstream file(filename + ".txt", ios::in);
        if (file.fail())
        {
            cout << "Error opening file!\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
            if (lines.size() == 9)
            {
                current_password = line;
            }
        }
        file.close();

        if (prev_password == current_password)
        {
            string new_pass;
            cout << "Enter new password: ";
            cin >> new_pass;

            lines[8] = new_pass;

            fstream file(filename + ".txt", ios::out | ios::trunc);
            if (file.fail())
            {
                cout << "Error opening file!\n";
                return;
            }

            for (int i = 0; i < lines.size(); i++)
            {
                file << lines[i] << endl;
            }
            file.close();

            set_password(new_pass);
            cout << "Password changed successfully!\n";
        }
        else
        {
            count++;
            cout << "Previous password does not match!\n";
            if (count < 3)
            {
                goto retry1;
            }
            else
            {
                cout << "You have entered the wrong password 3 times. Please try again later\n";
            }
        }
    }

    void change_name(string filename)
    {
        string new_firstname, new_lastname;
        cout << "Enter new first name: ";
        cin >> new_firstname;
        cout << "Enter new last name: ";
        cin >> new_lastname;
        set_first_name(new_firstname);
        set_last_name(new_lastname);
        // Read the existing data from the file
        fstream read_file(filename + ".txt", ios::in);
        if (read_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(read_file, line))
            lines.push_back(line);

        read_file.close();

        // Write the new data to the file
        fstream write_file(filename + ".txt", ios::out | ios::trunc);
        if (write_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        // Write the new first name to the first line
        write_file << new_firstname << endl;

        // Write the new last name to the second line
        write_file << new_lastname << endl;

        // Copy the remaining lines from the vector to the file
        for (int i = 2; i < lines.size(); i++)
            write_file << lines[i] << endl;

        write_file.close();

        cout << "Name changed successfully!\n";
    }

    void change_email(string filename)
    {
        string new_email;
        cout << "Enter new email: ";
        cin >> new_email;
        set_email(new_email);

        fstream read_file(filename + ".txt", ios::in);
        if (read_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(read_file, line))
            lines.push_back(line);

        read_file.close();

        lines[3] = new_email;

        fstream write_file(filename + ".txt", ios::out | ios::trunc);
        if (write_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        for (int i = 0; i < lines.size(); i++)
            write_file << lines[i] << endl;

        write_file.close();

        cout << "Email changed successfully!\n";
    }

    void change_phone(string filename)
    {
        string new_phone;
        cout << "Enter new phone number: ";
        cin >> new_phone;

        fstream read_file(filename + ".txt", ios::in);
        if (read_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(read_file, line))
            lines.push_back(line);

        read_file.close();

        lines[4] = new_phone;

        fstream write_file(filename + ".txt", ios::out | ios::trunc);
        if (write_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }
        for (int i = 0; i < lines.size(); i++)
            write_file << lines[i] << endl;

        write_file.close();

        cout << "Phone number changed successfully!\n";
    }

    void add_balance(string filename)
    {
        // Read the account information from the file into a vector
        vector<string> lines;
        ifstream read_file(filename + ".txt");
        if (read_file.is_open())
        {
            string line;
            while (getline(read_file, line))
            {
                lines.push_back(line);
            }
            read_file.close();
        }
        else
        {
            cout << "Error opening file!\n";
            return;
        }

        // Get the current balance from the vector and update it with user input
        double balance = stod(lines[9]);
        cout << "Current balance: " << balance << endl;
        double amount;
        cout << "Enter the amount to add: ";
        cin >> amount;
        balance += amount;

        // Update the balance in the vector and write the new information to the file
        lines[9] = to_string(balance);

        ofstream write_file(filename + ".txt");
        if (write_file.is_open())
        {
            for (int i = 0; i < lines.size(); i++)
            {
                write_file << lines[i] << endl;
            }
            write_file.close();
            cout << "Balance added successfully! New balance: " << balance << endl;
        }
        else
        {
            cout << "Error opening file!\n";
        }
    }
    void withdraw_amount(string filename)
    {
        // Read the account information from the file into a vector
        vector<string> lines;
        ifstream read_file(filename + ".txt");
        if (read_file.is_open())
        {
            string line;
            while (getline(read_file, line))
            {
                lines.push_back(line);
            }
            read_file.close();
        }
        else
        {
            cout << "Error opening file!\n";
            return;
        }

        // Get the current balance from the vector and update it with user input
        double balance = stod(lines[9]);
        double amount;
        cout << "Enter amount you want to withdraw: ";
        cin >> amount;
        if (amount > balance)
        {
            cout << "You don't have enough balance to withdraw this amount\n";
            return;
        }
        else if (amount < 0)
        {
            cout << "You can't withdraw negative amount\n";
            return;
        }
        else if (amount == 0)
        {
            cout << "You can't withdraw 0 amount\n";
            return;
        }
        else
        {
            balance -= amount;
        }
        // Update the balance in the vector and write the new information to the file
        lines[9] = to_string(balance);
        ofstream write_file(filename + ".txt");
        if (write_file.is_open())
        {
            for (int i = 0; i < lines.size(); i++)
            {
                write_file << lines[i] << endl;
            }
            write_file.close();
            cout << "Withdrawl Successful\nNew Balnace: " << balance << endl;
        }
        else
        {
            cout << "Error opening file!\n";
        }
    }
    void view_history(string filename)
    {
        int counter = 0;
        int counter1 = 1;
        ifstream file(filename + ".txt");
        string line;
        while (getline(file, line))
        {
            counter++;
            if (counter > 10)
            {
                cout << counter1 << "-" << line << endl;
                counter1++;
            }
        }
    }
    void display_data(string filename)
    {
        string firstName1;
        string lastName1;
        string username1;
        string email1;
        string phoneNumber1;
        string password1;
        string creditCardNumber1;
        string expiry1;
        string cvv1;
        double balance1;
        string file = filename + ".txt";
        ifstream read(file, ios::in);
        string line;
        while (!read.eof())
        {
            getline(read, firstName1);
            getline(read, lastName1);
            getline(read, username1);
            getline(read, email1);
            getline(read, phoneNumber1);
            getline(read, creditCardNumber1);
            getline(read, expiry1);
            getline(read, cvv1);
            getline(read, password1);
            read >> balance1;
            break;
        }
        set_first_name(firstName1);
        set_last_name(lastName1);
        set_username(username1);
        set_email(email1);
        set_phone_number(phoneNumber1);
        set_credit_card_number(creditCardNumber1);
        set_expiry(expiry1);
        set_cvv(cvv1);
        set_password(password1);
        set_balance(balance1);

        cout << "First name: " << get_first_name() << endl;
        cout << "Last name: " << get_last_name() << endl;
        cout << "Username: " << get_username() << endl;
        cout << "Email: " << get_email() << endl;
        cout << "Phone number: " << get_phone_number() << endl;
        cout << "Credit card number: " << get_credit_card_number() << endl;
        cout << "Expiry: " << get_expiry() << endl;
        cout << "CVV: " << get_cvv() << endl;
        cout << "Balance: " << get_balance() << endl;

        read.close();
    }
};
class Crypto : public User
{
public:
    Crypto(string n, string s, double p) : name(n), symbol(s), price(p) {}

    string get_name() const { return name; }
    string get_symbol() const { return symbol; }
    double get_price() const { return price; }

private:
    string name;
    string symbol;
    double price;
};

vector<Crypto> cryptos;

void load_data()
{
    ifstream file("cryptos.txt");
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string name, symbol;
            double price;
            getline(iss, name, ',');
            getline(iss, symbol, ',');
            iss >> price;
            Crypto crypto(name, symbol, price);
            cryptos.push_back(crypto);
        }
        file.close();
    }
}

void view_market_data()
{
    for (const auto &crypto : cryptos)
    {
        cout << crypto.get_name() << " (" << crypto.get_symbol() << "): $" << crypto.get_price() << endl;
    }
}
double get_balance(string filename)
{
    double balance;
    string line;
    ifstream file(filename + ".txt");
    if (file.is_open())
    {
        for (int i = 1; i <= 10; i++)
        {
            getline(file, line);
            if (i == 10)
            {
                balance = stod(line);
            }
        }
        file.close();
        return balance;
    }
    else
    {
        cout << "Error opening file!" << endl;
        return -1;
    }
}
void deduct_balance(string filename, double amount)
{
    vector<string> lines;
    string line;

    // Read all the lines from the file into a vector
    ifstream read_file(filename + ".txt");
    if (read_file.is_open())
    {
        while (getline(read_file, line))
        {
            lines.push_back(line);
        }
        read_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Check if the file contains at least 10 lines
    if (lines.size() < 10)
    {
        cout << "File should contain at least 10 lines!" << endl;
        return;
    }

    // Extract the balance from the 10th line and add the specified amount
    double balance = stod(lines[9]);
    balance -= amount;

    // Update the balance in the 10th line of the file
    ofstream write_file(filename + ".txt");
    if (write_file.is_open())
    {
        for (int i = 0; i < lines.size(); i++)
        {
            if (i == 9)
            {
                write_file << fixed << setprecision(2) << balance << endl;
            }
            else
            {
                write_file << lines[i] << endl;
            }
        }
        write_file.close();
        cout << "Current balance: " << balance << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }
}
void add_data_tofile(string filename, string cryptoname, double amount, double price, string nature)
{
    // Construct the line to add to the file
    string line = cryptoname + "(" + to_string(amount) + ") = " + to_string(price) + " : " + nature;
    // Read all the lines from the file into a vector
    vector<string> lines;
    string current_line;
    ifstream read_file(filename + ".txt");
    if (read_file.is_open())
    {
        while (getline(read_file, current_line))
        {
            lines.push_back(current_line);
        }
        read_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Insert the new line after the 10th line in the vector
    if (lines.size() >= 10)
    {
        lines.insert(lines.begin() + 10, line);
    }
    else
    {
        lines.push_back(line);
    }

    // Write the updated lines back to the file
    ofstream write_file(filename + ".txt");
    int counter = 0;
    if (write_file.is_open())
    {
        for (const string &line : lines)
        {

            write_file << line << endl;
        }
        write_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }
}
void buy_crypto(string filename)
{
    string name;
    cout << "Enter the name of the cryptocurrency you want to buy: ";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (const auto &crypto : cryptos)
    {
        if (crypto.get_name() == name)
        {
            found = true;
            double amount, cryptoamount;
        retry1:
            cout << "Enter the amount you want to invest: ";
            cin >> amount;
            if (cin.fail())
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto retry1;
            }

            cryptoamount = (amount / crypto.get_price());
            cout << "You will get " << cryptoamount << " " << crypto.get_symbol() << " for " << amount << " USDT." << endl;
            cout << "Do you want to confirm the purchase (Y/N)? ";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                double balance = get_balance(filename);
                if (balance < amount)
                {
                    cout << "You do not have enough balance to buy " << amount << " " << crypto.get_symbol() << "." << endl;
                    return;
                }
                add_data_tofile(filename, crypto.get_name(), cryptoamount, amount, "bought");
                cout << "Purchase confirmed." << endl;
                deduct_balance(filename, amount);
            }
            else
            {
                cout << "Purchase cancelled." << endl;
            }
            return;
        }
    }
    cout << "Could not find the cryptocurrency with the Name " << name << "." << endl;
}
void crypto_wallet(string filename)
{
    ifstream file(filename + ".txt");
    string line;
    vector<string> crp_names;
    vector<double> crp_amounts;
    vector<double> crp_prices;
    vector<string> lines;

    string crp_name;
    double crp_amount = 0;
    double crp_price = 0;
    int counter = 0;
    double total = 0;
    while (getline(file, line))
    {
        counter++;
        if (counter > 10)
        {
            istringstream iss(line);
            getline(iss, crp_name, '(');
            iss >> crp_amount;
            iss.ignore(3);
            iss >> crp_price;
            crp_names.push_back(crp_name);
            crp_amounts.push_back(crp_amount);
            crp_prices.push_back(crp_price);
        }
    }
    file.close();
    for (int i = 0; i < crp_names.size(); i++)
    {
        for (int j = i + 1; j < crp_names.size(); j++)
        {
            if (crp_names[i] == crp_names[j])
            {

                crp_amounts[i] += crp_amounts[j];
                crp_prices[i] += crp_prices[j];
                crp_amounts.erase(crp_amounts.begin() + j);
                crp_names.erase(crp_names.begin() + j);
                crp_prices.erase(crp_prices.begin() + j);
                j--;
            }
        }
    }
    for (int i = 0; i < crp_names.size(); i++)
    {
        if (crp_amounts[i] == 0)
        {
            crp_amounts.erase(crp_amounts.begin() + i);
            crp_names.erase(crp_names.begin() + i);
            crp_prices.erase(crp_prices.begin() + i);
        }
    }

    for (int i = 0; i < crp_names.size(); i++)
    {
        cout << i + 1 << "-" << crp_names[i] << " { " << crp_amounts[i] << " } " << endl;
        cout << "Amount in USDT: " << crp_prices[i] << "$" << endl;
        cout << endl;
    }
    for (int i = 0; i < crp_names.size(); i++)
    {
        total += crp_prices[i];
    }
    cout << "Total amount in your wallet is: " << total << "$" << endl;
    ofstream write_file(filename + "_wallet.txt");
    if (write_file.is_open())
    {
        for (int i = 0; i < crp_names.size(); i++)
        {
            write_file << crp_names[i] + "(" << crp_amounts[i] << ") = " << crp_prices[i] << endl;
        }
        write_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }
}

void sell_crypto(string filename)
{
    crypto_wallet(filename);
    ifstream file(filename + "_wallet.txt");
    vector<string> lines;
    vector<double> f_crp_amounts;
    string line;
    double crp_amount = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> crp_amount;
        f_crp_amounts.push_back(crp_amount);
    }
    file.close();
    if (f_crp_amounts.size() == 0)
    {
        cout << "You do not have any cryptocurrencies to sell." << endl;
        return;
    }
    else
    {
        ifstream file(filename + "_wallet.txt");
        vector<string> lines;
        vector<string> f_crp_names;
        vector<double> f_crp_amounts;
        vector<double> f_crp_prices;
        string line;
        string crp_name;
        double crp_amount = 0;
        double crp_price = 0;
        while (getline(file, line))
        {
            istringstream iss(line);
            getline(iss, crp_name, '(');
            iss >> crp_amount;
            iss.ignore(3);
            iss >> crp_price;
            f_crp_names.push_back(crp_name);
            f_crp_amounts.push_back(crp_amount);
            f_crp_prices.push_back(crp_price);
        }
        file.close();
        string name;
        double amount, usdt;
        cout << "Enter the name of the cryptocurrency you want to sell: ";
        cin.ignore();
        getline(cin, name);
    retry_amount:
        cout << "Enter the amount you want to sell: ";
        cin >> amount;
        if (cin.fail())
        {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto retry_amount;
        }
        for (int i = 0; i < f_crp_names.size(); i++)
        {
            if (f_crp_names[i] == name)
            {
                if (f_crp_amounts[i] < amount)
                {
                    cout << "You do not have enough balance to sell " << amount << " " << name << "." << endl;
                    return;
                }
                else
                {
                    usdt = amount * (f_crp_prices[i] / f_crp_amounts[i]);
                    cout << "Selling " << amount << " " << name << " will give you " << usdt << " USDT." << endl;
                    cout << "Do you want to confirm the sale (Y/N)? ";
                    char confirm;
                    cin >> confirm;
                    if (confirm == 'Y' || confirm == 'y')
                    {
                        if (f_crp_amounts[i] == 0)
                        {
                            f_crp_amounts.erase(f_crp_amounts.begin() + i);
                            f_crp_names.erase(f_crp_names.begin() + i);
                            f_crp_prices.erase(f_crp_prices.begin() + i);
                        }
                        amount = amount * (-1);
                        usdt = usdt * (-1);
                        add_data_tofile(filename, name, amount, usdt, "sold");
                        f_crp_amounts[i] -= amount;
                        f_crp_prices[i] -= usdt;
                        // cout << "after";
                        // cout << f_crp_amounts[i] << endl;
                        // cout << f_crp_prices[i] << endl;
                        ofstream file(filename + "_wallet.txt", ios::out);
                        if (file.is_open())
                        {
                            if (f_crp_names[i] == name)
                            {
                                file << f_crp_names[i] << "(" << f_crp_amounts[i] << ")" << f_crp_prices[i] << endl;
                            }
                            file.close();
                        }
                        else
                        {
                            cout << "Error opening file!" << endl;
                            return;
                        }
                        cout << "Sale confirmed." << endl;
                        ifstream read_file(filename + ".txt");
                        vector<string> lines;
                        string line;
                        while (getline(read_file, line))
                        {
                            lines.push_back(line);
                        }
                        read_file.close();
                        usdt = usdt * (-1);
                        double balance = stod(lines[9]);
                        balance += usdt;
                        lines[9] = to_string(balance);
                        ofstream write_file(filename + ".txt");
                        if (write_file.is_open())
                        {
                            for (int i = 0; i < lines.size(); i++)
                            {
                                write_file << lines[i] << endl;
                            }
                            write_file.close();
                        }
                    }
                    else
                    {
                        cout << "Sale cancelled." << endl;
                    }
                    return;
                }
            }
        }
    }
}
void check_balance(string filename)
{
    ifstream file(filename + ".txt");
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    cout << "Your current balance is " << lines[9] << " USDT." << endl;
}

int main()
{
    char opt, choice;
    char ch, opt11;
    string filename;
    string pass, username, password;

    cout << "----------- Welcome to CryptoCurrency Trading platform ------------" << endl;
move:
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter option: ";
    cin >> choice;
    choice = choice - '0';

    switch (choice)
    {
    case 1:
    {
        User user;
        filename = user.login();
        if (user.is_logged_in() == 1)
        {
            goto jump;
        }
        else
        {
            goto move;
        }
    }
    break;
    case 2:
    {
        User user;
        user.signup();
        goto move;
    }
    break;
    case 3:
    {
        exit(0);
    }
    default:
        cout << "Invalid choice!" << endl;
        cout << "Do you want to try again (Y/N)? " << endl;
        cin >> opt11;
        if (opt11 == 'Y' || opt11 == 'y')
        {
            goto move;
        }
        else
        {
            return 0;
        }
    }
jump:
    cout << "1. View Market Data" << endl;
    cout << "2. Trade" << endl;
    cout << "3. View Trading History" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Withdraw Amount" << endl;
    cout << "6. View Crypto Wallet" << endl;
    cout << "7. Account Settings" << endl;
    cout << "8. logout" << endl;
    cout << "Enter any option: ";
    cin >> opt;
    opt = opt - '0';
    switch (opt)
    {
    case 1:
    {
        load_data();
        view_market_data();
        goto jump;
    }
    break;
    case 2:
    {
        char option1;
        load_data();
    move1:
        cout << "1. Buy Crypto" << endl;
        cout << "2. Sell Crypto" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter option number: ";
        cin >> option1;
        option1 = option1 - '0';

        switch (option1)
        {
        case 1:
        {
            buy_crypto(filename);
            goto move1;
        }
        break;
        case 2:
        {
            sell_crypto(filename);
            goto move1;
        }
        break;
        case 3:
        {
            goto jump;
        }
        default:
        {
            cout << "Invalid choice!" << endl;
            goto move1;
        }
        }
    }
    break;
    case 3:
    {
        Account_setting account;
        account.view_history(filename);
        goto jump;
    }
    case 4:
    {
        check_balance(filename);
        goto jump;
    }
    break;
    case 5:
    {
        Account_setting account;
        account.withdraw_amount(filename);
        goto jump;
    }
    case 6:
    {
        crypto_wallet(filename);
        goto jump;
    }
    break;
    case 7:
    {
        Account_setting account;
        char ch11;
        char option;
        do
        {
            cout << "1. Change password\n";
            cout << "2. Change name\n";
            cout << "3. Change email\n";
            cout << "4. Change phone number\n";
            cout << "5. Add amount to balance\n";
            cout << "6. Display data\n";
            cout << "7. Exit\n";
            cout << "Enter option number: ";
            cin >> option;
            option = option - '0';
            switch (option)
            {
            case 1:
            {
                account.change_password(filename);
                break;
            }
            case 2:
            {
                account.change_name(filename);
                break;
            }
            case 3:
            {
                account.change_email(filename);
                break;
            }
            case 4:
            {
                account.change_phone(filename);
                break;
            }
            case 5:
            {
                account.add_balance(filename);
                break;
            }
            case 6:
            {
                account.display_data(filename);
                break;
            }
            case 7:
            {
                goto jump;
                break;
            }
            default:
                cout << "Invalid option" << endl;
                break;
            }
            cout << "Do you want to continue (Y/N)? ";
            cin.ignore();
            cin >> ch11;
        } while (ch11 == 'Y' || ch11 == 'y');
    }
    break;
    case 8:
    {
        goto move;
    }
    break;
    default:
    {
        cout << "Invalid option" << endl;
        char ch1;
        cout << "Do you want to try again (Y/N)? " << endl;
        cin >> ch1;
        if (ch1 == 'Y' || ch1 == 'y')
        {
            goto jump;
        }
        else
        {
            goto move;
        }
    }
    }
    return 0;
}
