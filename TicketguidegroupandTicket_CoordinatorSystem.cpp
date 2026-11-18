#include <iostream>
#include <fstream>
using namespace std;
class tour
{
public:
    static int tourid;
    int id;
    string destination;
    int duration;
    string vehicle[4] = {"Taxi", "Train", "Plane", "Bus"};
    double price;
    int available_seats;
    friend class tickets;
    void input(tour tours[], int index)
    {
        bool duplicate;

        do
        {
            duplicate = false;

            cout << "\nEnter destination: ";
            cin >> destination;

            for (int i = 0; i < index; i++)
            {
                if (tours[i].destination == destination)
                {
                    cout << "\nDestination already exists! Enter another destination.\n";
                    duplicate = true;
                    break;
                }
            }

        } while (duplicate);

        id = tourid++;

        cout << "\nEnter duration of tour: ";
        cin >> duration;

        cout << "\nEnter price: ";
        cin >> price;

        cout << "\nEnter available seats: ";
        cin >> available_seats;
    }
    inline void display()
    {
        cout << "\n       TOUR DETAILS        ";
        cout << "\nTour ID          : " << id + 1;
        cout << "\nDestination      : " << destination;
        cout << "\nDuration         : " << duration << " days";
        cout << "\nAvailable Options: ";
        for (int i = 0; i < 4; i++)
        {
            cout << vehicle[i];
            if (i < 3)
                cout << ", ";
        }
        cout << "\nPrice           : " << price;
        cout << "\nAvailable Seats : " << available_seats;
    }
};
int tour::tourid;
class guide
{
public:
    static int guideid;
    int id;
    string name;
    int n;
    string languages[5];
    int experience;
    int age;
    string birthplace;

    void input()
    {
        id = guideid++;
        cin.ignore();
        cout << "Enter Guide Name: ";
        getline(cin, name);
        cout << "Enter number of languages guide speak : ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter Language " << i + 1 << " : ";
            cin >> languages[i];
        }
        cout << "\nEnter Experience : ";
        cin >> experience;
        cout << "\nEnter age : ";
        cin >> age;
        cout << "\nEnter birthplace : ";
        cin >> birthplace;
    }
    void saveGuide()//make save for file for tickets and tours
    {
        ofstream out("guides.txt", ios::app);

        out << "Guide ID: " << id << endl;
        out << "Guide Name: " << name << endl;
        for (int i = 0; i < n; i++)
        {
            out << "Language " << i + 1 << ": " << languages[i] << endl;
        }
        out << "Age: " << age << " years" << endl;
        out << "Experience: " << experience << " years" << endl;
        out << "--------------------------" << endl;

        out.close();

        cout << "\nGuide saved successfully!";
    }
    inline void display()
    {
        cout << "\n       GUIDE DETAILS        ";
        cout << "\nGuide ID: " << id;
        cout << "\nGuide Name: " << name;
        cout << "\nLanguage : ";
        for (int i = 0; i < n; i++)
        {
            cout << languages[i];
            if (i < n)
                cout << ", ";
        }
        cout << "\nExperience: " << experience << " years";
        cout << "\nAge: " << age;
        cout << "\nBirthplace: " << birthplace;
        cout << "\n----------------------";
    }
};
int guide::guideid = 1;
class tickets
{
public:
    int tkt;
    double total;
    int left;
    string mode;
    void input(tour &t)
    {

        cout << "\nEnter number of tickets: ";
        cin >> tkt;

        if (tkt <= 0)
        {
            cout << "Invalid number of tickets!\n";
            tkt = 0;
            left = t.available_seats;
            total = 0;
            return;
        }

        if (tkt > t.available_seats)
        {
            cout << "Not enough seats available!\n";
            tkt = 0;
            left = t.available_seats;
            total = 0;
            return;
        }

        t.available_seats -= tkt;
        left = t.available_seats;

        cout << "Select transport (1. Taxi, 2. Train, 3. Plane, 4. Bus): ";

        int ch;
        cin >> ch;

        if (ch >= 1 && ch <= 4)
        {
            mode = t.vehicle[ch - 1];
        }
        else
        {
            mode = "Bus";
        }

        double mult = 1.0;

        if (mode == "Taxi")
        {
            mult = 1.5;
        }
        else if (mode == "Train")
        {
            mult = 1.0;
        }
        else if (mode == "Plane")
        {
            mult = 2.5;
        }
        else if (mode == "Bus")
        {
            mult = 1.0;
        }

        total = (t.price * mult) * tkt;
    }

    void display()
    {

        cout << "   TICKET RECEIPT   \n";
        cout << "--------------------\n";
        cout << "Tickets Booked: " << tkt << "\n";
        cout << "Transport Mode: " << mode << "\n";
        cout << "Total Price   : " << total << "\n";
        cout << "Seats Left    : " << left << "\n";
    }
};
class loader
{
    //make more loader constructor with parameter 
    public:
    loader()
    {
        ifstream in("guides.txt");

        if (!in)
        {
            cout << "\nNo saved guide records found!\n";
            return;
        }

        cout << "\n========== LOADED GUIDES FROM FILE ==========\n";
        string line;
        while (getline(in, line))
        {
            cout << line << endl;
        }
        cout << "=============================================\n";

        in.close();
    }
};
class QuickTour
{
public:
    string destination;
    int duration;
    double price;
    int available_seats;

    // Parameterized Constructor that prints details immediately upon creation
    QuickTour(string dest, int dur, double p, int seats)
    {
        destination = dest;
        duration = dur;
        price = p;
        available_seats = seats;

        cout << "\n--- QUICK DEBUG TOUR CREATED ---";
        cout << "\nDestination      : " << destination;
        cout << "\nDuration         : " << duration << " days";
        cout << "\nPrice            : " << price;
        cout << "\nAvailable Seats  : " << available_seats << "\n";
    }
};
int main()
{
    tickets tkt[2];
    cout << "\nLoading system...";
    loader load;
    QuickTour debugPackage("Kashmir", 5, 12000.0, 20);
    guide guides[5];
    tour tours[2];
    int choice;
    do
    {
        cout << "\n==============================\n";
        cout << "      TOUR MANAGEMENT SYSTEM    \n";
        cout << "================================\n";
        cout << "1. Manage Guides\n";
        cout << "2. Manage Tours\n";
        cout << "3. Book Tickets\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\n--- GUIDE MANAGEMENT ---\n";
            int g;
            cout << "Enter number of guides you want to enter : ";
            cin >> g;
            if (g >= 5)
            {
                cout << "Maximum capacity is 5. Setting count to 5.\n";
                g = 5;
            }
            for (int i = 0; i < g; i++)
            {
                cout << "\nEnter Details of Guide " << i + 1 << endl;
                guides[i].input();
                guides[i].saveGuide(); // for future in inheritance all classes will call this function
            }
            cout << "\n~~ ALL GUIDES ~~\n";
            for (int i = 0; i < g; i++)
            {
                guides[i].display();
            }
            break;
        }
        case 2:
        {
            cout << "\n--- TOUR MANAGEMENT ---\n";
            for (int i = 0; i < 2; i++)
            {
                cout << "\nEnter Details of Tour " << i + 1 << endl;
                tours[i].input(tours, i);
            }
            cout << "\n~~ ALL TOURS ~~\n";
            for (int i = 0; i < 2; i++)
            {
                tours[i].display();
            }
            break;
        }
        case 3:
        {
            int group;
            cout << "\nEnter number of bookings: ";
            cin >> group;

            for (int i = 0; i < group; i++)
            {
                string destination;
                cout << "\nEnter Ticket Details for Booking " << i + 1 << endl;
                cout << "Enter Destination (Kashmir/Jammu): ";
                cin >> destination;

                tour *ptr = nullptr;
                if (destination == "Kashmir")
                {
                    ptr = &tours[0];
                }
                else if (destination == "Jammu")
                {
                    ptr = &tours[1];
                }
                else
                {
                    cout << "\nInvalid Destination! Skipping...\n";
                    continue;
                }
                tkt[i].input(*ptr);
            }
            cout << "\n~~ ALL TICKET DETAILS ~~\n";
            for (int i = 0; i < group; i++)
            {
                if (tkt[i].tkt > 0)
                {
                    tkt[i].display();
                }
            }
            break;
        }
        case 4:
        {
            cout << "\nExiting Program. Goodbye!\n";
            break;
        }
        default:
        {
            cout << "\nInvalid choice! Please choose between 1 and 4.\n";
        }
        }
    } while (choice != 4);
    return 0;
}