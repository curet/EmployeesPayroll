// JOSE C.S. CURET

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <list>

using namespace std;

class Employees{
private:
    string name;
    int idNumber;
    double hoursWorked;
    double hourlyPayRate;
    list <Employees> employeesInfo;
public:

    Employees() : idNumber(0), name(), hourlyPayRate(0.00), hoursWorked(0.00) {}
    Employees(int id, string name, double rate, double hrsWorked) :
    idNumber(id), name(name), hourlyPayRate(rate), hoursWorked(hrsWorked) {}

    void readFile();
    void readFileEmployeesInfo();
    void readFileEmployeesHoursWorked();
    void sortEmployeesPerIncome();
    void displayPayrollInfo();

};


void Employees::readFile() {

    readFileEmployeesInfo();
    readFileEmployeesHoursWorked();
}


void Employees::readFileEmployeesInfo(){


    cout << "Please enter the name of the file that contains employees Information"
            "\nPlease include the extension of the file you would like to analyze"
         << " (e.g. example.txt, example.dat)" << endl;

    ifstream inputFile;
    string nameOfFile;
    cin >> nameOfFile;
    inputFile.open(nameOfFile);

    while(!inputFile){
        inputFile.clear();
        cout << "Invalid Input!" << endl;
        cout << "Review your filename" << endl;

        cin >> nameOfFile;
        inputFile.open(nameOfFile);
    }

    while(!inputFile.eof()){
        inputFile >> idNumber >> hourlyPayRate;

        inputFile.ignore(1);
        getline(inputFile, name);

        employeesInfo.push_back(Employees(idNumber, name, hourlyPayRate, 0.00));
    }


    inputFile.close();
}

void Employees::readFileEmployeesHoursWorked(){


    cout << "Please enter the name of the file that contains employees hours worked"
            "\nPlease include the extension of the file you would like to analyze"
         << " (e.g. example.txt, example.dat)" << endl;

    ifstream inputFile;
    string nameOfFile;
    cin >> nameOfFile;
    inputFile.open(nameOfFile);

    while(!inputFile){
        inputFile.clear();
        cout << "Invalid Input!" << endl;
        cout << "Review your filename" << endl;

        cin >> nameOfFile;
        inputFile.open(nameOfFile);
    }

    list <Employees>::iterator iter;

    while(inputFile >> idNumber >> hoursWorked){

        bool idFound = false;
        for(iter = employeesInfo.begin(); iter != employeesInfo.end(); ++iter){
            if(iter->idNumber == idNumber){
                iter->hoursWorked += hoursWorked;
                idFound = true;
            }

        }
        if(!idFound){
            employeesInfo.push_back(Employees(idNumber, "Unregistered Employee", 0.00, hoursWorked));
        }

    }

    inputFile.close();

    sortEmployeesPerIncome();


}



void Employees::sortEmployeesPerIncome(){

    bool swapped;
    list <Employees>::iterator iter;

    do{

        auto it = employeesInfo.begin();
        auto next = std::next(it, 1);
        swapped = false;

        for(iter = employeesInfo.begin(); next != employeesInfo.end(); ++iter, ++next){
            if(((iter->hoursWorked) * (iter->hourlyPayRate)) < ((next->hoursWorked) * (next->hourlyPayRate))){
                swap(*iter, *next);
                swapped = true;
            }

        }
    }while(swapped);
}


void Employees::displayPayrollInfo() {

    list <Employees>::iterator iter;
    cout << "*********Payroll Information********" << endl;
    for(iter = employeesInfo.begin(); iter != employeesInfo.end(); ++iter){
        if(iter->name == "Unregistered Employee"){
            cout << iter->name << "(s) with " << iter->hoursWorked << " unassigned hours" << endl;
        }
        else{
            cout << iter->name << ", $";
            cout << (iter->hoursWorked * iter->hourlyPayRate) << endl;
        }
    }
    cout << "*********End payroll**************" << endl;
}


int main(){

    Employees e;
    e.readFile();
    e.displayPayrollInfo();

    return 0;
}
