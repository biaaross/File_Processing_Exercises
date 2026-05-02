#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

const std::string ACC_FILE = "accounts.csv";
const std::string TRX_FILE = "transactions.csv";
 
int nextTrxId();
// TODO: transactions.csv'deki en büyük IslemID'yi bul, +1 döndür

double getBalance(const std::string& iban);
// TODO: accounts.csv'den IBAN'a göre bakiyeyi bul ve döndür
// Bulunamazsa -1 döndür
 
bool updateBalance(const std::string& iban, double newBalance);
// TODO: temp dosya ile IBAN'ın bakiyesini güncelle
// TODO: remove + rename, başarılıysa true döndür
 
void logTransaction(const std::string& iban,
                    const std::string& type, double amount, double balance);
// TODO: transactions.csv'ye append modunda ekle
// TODO: nextTrxId,iban,type,amount,balance formatında yaz

 
void createAccount(const std::string& iban,
                   const std::string& name, double initialBalance);
// TODO: IBAN zaten var mı kontrol et (getBalance != -1)
// TODO: accounts.csv'ye append

 
void deposit(const std::string& iban, double amount);
// TODO: getBalance ile mevcut bakiyeyi al
// TODO: updateBalance ile yeni bakiyeyi yaz
// TODO: logTransaction ile kaydı ekle

 
void withdraw(const std::string& iban, double amount);
// TODO: getBalance al
// TODO: bakiye < amount ise hata ver ve return
// TODO: updateBalance + logTransaction

void transfer(const std::string& fromIban,
              const std::string& toIban, double amount);
// TODO: gönderen bakiyesi yeterli mi?
// TODO: her iki hesabı da updateBalance ile güncelle
// TODO: "transfer-giden" ve "transfer-gelen" olarak logTransaction

void printStatement(const std::string& iban);
// TODO: transactions.csv'yi oku
// TODO: IBAN eşleşen tüm işlemleri yazdır

void listAccounts();
// TODO: accounts.csv'yi oku, tüm hesapları yazdır


int main() {

    int choice;

    while (true) {

        std::cout << "\n====== BANK SYSTEM ======\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Transfer\n";
        std::cout << "5. List Accounts\n";
        std::cout << "6. Print Statement\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::string iban, iban2, name;
        double amount;

        switch (choice) {

        case 1:
            std::cout << "IBAN: ";
            std::cin >> iban;
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Initial Balance: ";
            std::cin >> amount;
            createAccount(iban, name, amount);
            break;

        case 2:
            std::cout << "IBAN: ";
            std::cin >> iban;
            std::cout << "Amount: ";
            std::cin >> amount;
            deposit(iban, amount);
            break;

        case 3:
            std::cout << "IBAN: ";
            std::cin >> iban;
            std::cout << "Amount: ";
            std::cin >> amount;
            withdraw(iban, amount);
            break;

        case 4:
            std::cout << "From IBAN: ";
            std::cin >> iban;
            std::cout << "To IBAN: ";
            std::cin >> iban2;
            std::cout << "Amount: ";
            std::cin >> amount;
            transfer(iban, iban2, amount);
            break;

        case 5:
            listAccounts();
            break;

        case 6:
            std::cout << "IBAN: ";
            std::cin >> iban;
            printStatement(iban);
            break;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}


  
int nextTrxId() {
    std::ifstream readProcess(TRX_FILE);
    if(!readProcess) {
        std::cerr<<"File not Opened"<<std::endl;
        return 1;
    }
    int maxId = 0;
    std::string line;
    while(getline(readProcess,line)) {
        std::stringstream ss(line);
        std::string word;
        getline(ss,word,',');
        int id = std::stoi(word);
        if(id>maxId) {
            maxId = id;
        }
    
    }
    return maxId + 1;
}



double getBalance(const std::string& iban) {
    std::ifstream readBalance(ACC_FILE);
    if(!readBalance) {
        std::cerr<<"File not Opened"<<std::endl;
        return -1;
    }
    std::string line;
    while(getline(readBalance,line)) {
        std::string ibanno,name,balance;
        std::stringstream ss(line);
        getline(ss,ibanno,',');
        getline(ss,name,',');
        getline(ss,balance,',');

        if(iban==ibanno) {
            return std::stod(balance);
        }
    }
return -1;
}



bool updateBalance(const std::string& iban, double newBalance) {
    std::ifstream readUpdate(ACC_FILE);
    std::ofstream writeUpdate("temp.csv");
    if(!readUpdate || !writeUpdate) {
        std::cerr<<"File not Opened"<<std::endl;
        return false;
    }
    bool found = false;
    std::string line;
    while(getline(readUpdate,line)) {
        std::stringstream ss(line);
        std::string ibanno,name,balance;
        getline(ss,ibanno,',');
        getline(ss,name,',');
        getline(ss,balance,',');

        if(iban==ibanno) {
            writeUpdate <<ibanno<<","<<name<<","<<newBalance<<std::endl;
            found = true;
        }
        else {

writeUpdate << line <<std::endl;
        }
    }
    writeUpdate.close();
    readUpdate.close();
     if (!found) {
        remove("temp.csv");
        return false;
    }

    remove(ACC_FILE.c_str());
    rename("temp.csv", ACC_FILE.c_str());

    return true;

}
 

void logTransaction(const std::string& iban,
                    const std::string& type, double amount, double balance) {

                        std::ofstream writelog(TRX_FILE,std::ios::app);
                        if(!writelog) {
                            std::cerr<<"File not Opened"<<std::endl;
                            return;
                        }
                        int id = nextTrxId();
                        writelog << id << ","
                        << iban << ","
                        << type << ","
                        << amount << ","
                        << balance << std::endl;
                    }



void createAccount(const std::string& iban,
                   const std::string& name, double initialBalance) {

    std::ifstream readCreate(ACC_FILE);

    std::string line;
    bool found = false;

    while (getline(readCreate, line)) {
        std::stringstream ss(line);
        std::string ibanno;
        getline(ss, ibanno, ',');

        if (ibanno == iban) {
            found = true;
            break;
        }
    }
    readCreate.close();

    if (found) {
        std::cerr << "IBAN already exists!" << std::endl;
        return;
    }

    std::ofstream writeCreate(ACC_FILE, std::ios::app);
    if (!writeCreate) {
        std::cerr << "File not Opened" << std::endl;
        return;
    }

    writeCreate << iban << ","
                << name << ","
                << initialBalance << std::endl;
}



void deposit(const std::string& iban, double amount) {

    if (amount <= 0) {
        std::cerr << "Invalid deposit amount!" << std::endl;
        return;
    }

    double currentBalance = getBalance(iban);

    if (currentBalance == -1) {
        std::cerr << "Account not found!" << std::endl;
        return;
    }

    double newBalance = currentBalance + amount;

    if (!updateBalance(iban, newBalance)) {
        std::cerr << "Balance update failed!" << std::endl;
        return;
    }

    logTransaction(iban, "deposit", amount, newBalance);
}



void withdraw(const std::string& iban, double amount) {

    if (amount <= 0) {
        std::cerr << "Invalid withdraw amount!" << std::endl;
        return;
    }

    double currentBalance = getBalance(iban);

    if (currentBalance == -1) {
        std::cerr << "Account not found!" << std::endl;
        return;
    }

    if (currentBalance < amount) {
        std::cerr << "Insufficient balance!" << std::endl;
        return;
    }

    double newBalance = currentBalance - amount;

    if (!updateBalance(iban, newBalance)) {
        std::cerr << "Balance update failed!" << std::endl;
        return;
    }

    logTransaction(iban, "withdraw", amount, newBalance);
}



void transfer(const std::string& fromIban,
              const std::string& toIban, double amount) {

    if (amount <= 0) {
        std::cerr << "Invalid transfer amount!" << std::endl;
        return;
    }

    double fromBalance = getBalance(fromIban);
    double toBalance = getBalance(toIban);

    if (fromBalance == -1 || toBalance == -1) {
        std::cerr << "Account not found!" << std::endl;
        return;
    }

    if (fromBalance < amount) {
        std::cerr << "Insufficient balance!" << std::endl;
        return;
    }

    double newFromBalance = fromBalance - amount;
    double newToBalance = toBalance + amount;

    // Önce göndereni güncelle
    if (!updateBalance(fromIban, newFromBalance)) {
        std::cerr << "Sender update failed!" << std::endl;
        return;
    }

    // Sonra alıcıyı güncelle
    if (!updateBalance(toIban, newToBalance)) {
        std::cerr << "Receiver update failed!" << std::endl;

        // Basit geri alma (rollback mantığı)
        updateBalance(fromIban, fromBalance);
        return;
    }

    logTransaction(fromIban, "transfer-giden", amount, newFromBalance);
    logTransaction(toIban, "transfer-gelen", amount, newToBalance);
}



void printStatement(const std::string& iban) {

    std::ifstream file(TRX_FILE);

    if (!file) {
        std::cerr << "Transactions file not opened!" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    std::cout << "ID | IBAN | TYPE | AMOUNT | BALANCE" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    while (getline(file, line)) {

        std::stringstream ss(line);

        std::string id, fileIban, type, amount, balance;

        getline(ss, id, ',');
        getline(ss, fileIban, ',');
        getline(ss, type, ',');
        getline(ss, amount, ',');
        getline(ss, balance, ',');

        if (fileIban == iban) {
            std::cout << id << " | "
                      << fileIban << " | "
                      << type << " | "
                      << amount << " | "
                      << balance << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found for this IBAN." << std::endl;
    }
}



void listAccounts() {

    std::ifstream file(ACC_FILE);

    if (!file) {
        std::cerr << "Accounts file not opened!" << std::endl;
        return;
    }

    std::string line;

    std::cout << "IBAN | NAME | BALANCE" << std::endl;
    std::cout << "--------------------------" << std::endl;

    while (getline(file, line)) {

        std::stringstream ss(line);

        std::string iban, name, balance;

        getline(ss, iban, ',');
        getline(ss, name, ',');
        getline(ss, balance, ',');

        std::cout << iban << " | "
                  << name << " | "
                  << balance << std::endl;
    }
}