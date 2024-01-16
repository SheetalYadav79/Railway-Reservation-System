#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Train
{
public:
    char train_name[50];
    char boarding_point[50];
    char destination_point[50];
    char date[50];
    int train_no;
    int sleeper_class_fare;
    int ac_class_fare;

    //                ================ add train ==================
    void add_train()
    {
        cout << "\nADD TRAIN DETAILS\n";
        cout << "ENTER TRAIN NAME         : ";
        // cin.ignore();
        cin >> train_name;
        cout << "ENTER TRAIN NO           : ";
        cin >> train_no;
        cout << "ENTER BOARDING POINT     : ";
        // cin.ignore();
        cin >> boarding_point;
        cout << "ENTER DESTINATION POINT  : ";
        cin >> destination_point;
        cout << "ENTER SLEEPER CLASS FARE : ";
        cin >> sleeper_class_fare;
        cout << "ENTER AC CLASS FARE      : ";
        cin >> ac_class_fare;
        cout << "ENTER DATE (dd/mm/yyyy)  : ";
        cin >> date;
    }

    //             ================ display train =======================

    void display_train()
    {
        cout << "\nTrain No.           : " << train_no;
        cout << "\nTrain Name          : " << train_name;
        cout << "\nBoarding Point      : " << boarding_point;
        cout << "\nDestination Point   : " << destination_point;
        cout << "\nSleeper Class Fare  : " << sleeper_class_fare;
        cout << "\nAC Class Fare       : " << ac_class_fare;
        cout << "\nDate                : " << date;
        cout << "\n---------------------------------------------";
        // cout << train_no << "\t\t" << train_name << "\t" << boarding_point << "\t\t" << destination_point << "\t\t" << sleeper_class_fare << "\t\t" << ac_class_fare << "\t\t" << date << endl;
    }
};

class passenger
{
public:
    char name[50];
    string date;
    long mob_no;
    int age;
    int train_no;

    //                =================== book ticket ======================

    void book_ticket()
    {
        cout << "\nADD PASSENGER DETAILS\n";
        cout << "ENTER NAME          : ";
        cin >> name;
        cout << "ENTER MOBILE NO     : ";
        cin >> mob_no;
        cout << "ENTER AGE           : ";
        cin >> age;
        cout << "ENTER TRAIN NO.     : ";
        cin >> train_no;
    }

    void display_ticket()
    {

        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nMobile Number: " << mob_no;
        cout << "\n--------------------------------------\n";
    }
};

void add_train()
{
    Train t;
    fstream file;
    file.open("trains.txt", ios::app | ios::binary);

    t.add_train();
    file.write((char *)&t, sizeof(t));
    file.close();
}

void display_train()
{
    Train t;
    fstream file;
    file.open("trains.txt", ios::in | ios::binary);

    while (file.read((char *)&t, sizeof(t)))
    {
        t.display_train();
    }
    file.close();
}

void update_train()
{
    int no;
    int flag = 0;
    Train t;
    fstream file;
    fstream file1;
    cout << "Enter the train no. you want to update record";
    cin >> no;
    cout << "enter new data";

    file.open("trains.txt", ios::in | ios::binary);
    file1.open("temp.txt", ios::out | ios::binary);

    while (file.read((char *)&t, sizeof(t)))
    {
        if (t.train_no == no)
        {
            flag = 1;
            t.add_train();
            cout << "<< Updated >>" << endl;
        }
        file1.write((char *)&t, sizeof(t));
    }
    file.close();
    file1.close();

    if (flag == 1)
    {
        file1.open("temp.txt", ios::in | ios::binary);
        file.open("trains.txt", ios::out | ios::binary);

        while (file1.read((char *)&t, sizeof(t)))
        {
            file.write((char *)&t, sizeof(t));
        }
        file.close();
        file1.close();
    }
}

void search_train()
{
    int no;
    Train t;
    fstream file;
    cout << "Enter the train no. you want to Search";
    cin >> no;
    file.open("trains.txt", ios::in | ios::binary);

    while (file.read((char *)&t, sizeof(t)))
    {
        if (t.train_no == no)
        {
            t.display_train();
        }
    }
}

void delete_train()
{
    int no;
    int flag = 0;
    Train t;
    fstream file;
    fstream file1;
    cout << "Enter the train no. you want to Delete";
    cin >> no;

    file.open("trains.txt", ios::in | ios::binary);
    file1.open("temp.txt", ios::out | ios::binary);

    while (file.read((char *)&t, sizeof(t)))
    {
        if (t.train_no == no)
        {
            flag = 1;
        }
        else
        {
            file1.write((char *)&t, sizeof(t));
        }
    }
    file.close();
    file1.close();

    if (flag == 1)
    {
        file1.open("temp.txt", ios::in | ios::binary);
        file.open("trains.txt", ios::out | ios::binary);

        while (file1.read((char *)&t, sizeof(t)))
        {
            file.write((char *)&t, sizeof(t));
        }
        file.close();
        file1.close();
    }
}

void display_passenger_ticket()
{
    passenger p;
    fstream file;
    file.open("passenger_data.txt", ios::in | ios::binary);

    cout << "Passenger Details:\n";
    cout << "--------------------------------------";
    while (file.read((char *)&p, sizeof(p)))
    {
        p.display_ticket();
    }
    file.close();
}

void book_ticket()
{
    passenger p;
    fstream file;
    file.open("passenger_data.txt", ios::app | ios::binary);

    p.book_ticket();
    file.write((char *)&p, sizeof(p));
    cout << "<< Ticket booked >>";
    file.close();
}

void display_ticket()
{
    long no;
    passenger p;
    fstream file;
    cout << "Enter the Mob no. you want to Search : ";
    cin >> no;
    file.open("passenger_data.txt", ios::in | ios::binary);

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.mob_no == no)
        {
            cout << "\nName          : " << p.name;
            cout << "\nAge           : " << p.age;
            cout << "\nMobile Number : " << p.mob_no;
            cout << "\nTrain No      : " << p.train_no;
        
            // cout << "\nYOUR DETAILS";
            // p.display_ticket();
            // cout << "\nYOUR TRAIN DETAILS";
            search_train();
        }
        else
        {
            cout << "Don't find any travel details";
        }
    }
}

void cancel_ticket()
{
    long no;
    int flag = 0;
    passenger p;
    fstream file;
    fstream file1;
    cout << "Enter the Mob no. you want to Delete";
    cin >> no;

    file.open("passenger_data.txt", ios::in | ios::binary);
    file1.open("temp.txt", ios::out | ios::binary);

    while (file.read((char *)&p, sizeof(p)))
    {
        if (p.mob_no == no)
        {
            flag = 1;
        }
        else
        {
            file1.write((char *)&p, sizeof(p));
        }
    }
    file.close();
    file1.close();

    if (flag == 1)
    {
        file1.open("temp.txt", ios::in | ios::binary);
        file.open("passenger_data.txt", ios::out | ios::binary);

        while (file1.read((char *)&p, sizeof(p)))
        {
            file.write((char *)&p, sizeof(p));
        }
        file.close();
        file1.close();

        cout << "<< Ticket Cancelled >>";
    }
}

//             ===================== admin mode =======================
void admin_mode()
{
    string admin_pass = "r123";
    string entered_pass;

    cout << endl
         << "Enter Password: ";
    cin >> entered_pass;

    if (entered_pass == admin_pass)
    {
        while (1)
        {
            int choice;

            cout << "\n===========================";
            cout << "\n>> WELCOME TO ADMIN MODE <<";
            cout << "\n===========================";
            cout << "\n1. ADD TRAIN";
            cout << "\n2. DISPLAY TRAIN";
            cout << "\n3. UPDATE TRAIN";
            cout << "\n4. SEARCH TRAIN";
            cout << "\n5. DELETE TRAIN";
            cout << "\n6. DISPLAY PASSENGER DETAILS";
            cout << "\n7. BACK TO MAIN MENU";
            cout << "\nENTER YOUR CHOICE: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                add_train();
                break;
            case 2:
                display_train();
                break;
            case 3:
                update_train();
                break;
            case 4:
                search_train();
                break;
            case 5:
                delete_train();
                break;
            case 6:
                display_passenger_ticket();
                break;
            case 7:
                return;
            default:
                cout << "Enter a valid choice" << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Wrong password!!!, Try Again." << endl;
        admin_mode();
    }
}

//               ================= check username exist or not ==================
bool isUsernameTaken(const string &username)
{
    ifstream file("username_pass.txt");
    string line;

    while (getline(file, line))
    {
        if (line.find(username) == 0)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

//                   =================== user login =======================
void user_login()
{
    string username, password;

    cout << "Enter your username: ";
    cin >> username;

    if (!isUsernameTaken(username))
    {
        cout << "Username not found. Please sign up first.\n";
        return;
    }

    cout << "Enter your password: ";
    cin >> password;

    ifstream file("username_pass.txt");
    string line;
    bool loggedIn = false;

    while (getline(file, line))
    {
        if (line.find(username) == 0 && line.find(password) != string::npos)
        {
            loggedIn = true;
            break;
        }
    }
    file.close();

    if (loggedIn)
    {
        cout << "Login successful!\n";

        while (1)
        {
            int choice;

            cout << "\n1. BOOK TICKET";
            cout << "\n2. DISPLAY TICKET";
            cout << "\n3. CANCEL TICKET";
            cout << "\n4. DISPLAY TRAINS";
            cout << "\n5. BACK TO MAIN MENU";
            cout << "\nENTER YOUR CHOICE :";
            cin >> choice;
            switch (choice)
            {
            case 1:
                book_ticket();
                break;
            case 2:
                display_ticket();
                break;
            case 3:
                cancel_ticket();
                break;
            case 4:
                display_train();
                break;
            case 5:
                return;
            default:
                cout << "Enter a valid choice!!! Try Again.";
                break;
            }
        }
    }
    else
    {
        cout << "Invalid username or password.\n";
    }
}

//              ================== user signup =====================
void user_signUp()
{
    string username, password;

    cout << "Create a username: ";
    cin >> username;

    if (isUsernameTaken(username))
    {
        cout << "Username is already taken. Please choose a different one.\n";
        return;
    }

    cout << "Create a password: ";
    cin >> password;

    ofstream file("username_pass.txt", ios::app);
    file << username << " " << password << "\n";
    file.close();

    cout << "Account created successfully!\n";
}

//                 ================== user mode =====================
void user_mode()
{
    int choice;
    while (1)
    {
        cout << "\n==========================";
        cout << "\n>> WELCOME TO USER MODE <<";
        cout << "\n==========================";
        cout << "\n1. LOGIN";
        cout << "\n2. SIGN UP";
        cout << "\n3. BACK TO MAIN MENU";
        cout << "\nENTER YOUR CHOICE :";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user_login();
            break;
        case 2:
            user_signUp();
            break;
        case 3:
            return;

        default:
            cout << "Enter valid choice!!! Try Again.";
            break;
        }
    }
}

//                ================ main code ===================
int main()
{
    int choice;
    while (1)
    {
        cout << "\n================================";
        cout << "\n>> WELCOME TO INDIAN RAILWAYS <<";
        cout << "\n================================";

        cout << "\n1. ADMIN MODE";
        cout << "\n2. USER MODE";
        cout << "\n3. EXIT";
        cout << "\nENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            admin_mode();
            break;
        case 2:
            user_mode();
            break;
        case 3:
            exit(0);
        default:
            cout << "Enter a valid choice" << endl;
            break;
        }
    }
    return 0;
}