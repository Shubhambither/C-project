#include <iostream>
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
        cout << "Enter Guide Name: ";
        cin >> name;
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

    inline void display()
    {
        cout << "\n       GUIDE DETAILS        ";
        cout << "\nGuide ID: " << id;
        cout << "\nGuide Name: " << name;
        cout << "\nLanguage : ";
        for (int i = 0; i < n; i++)
        {
            cout << languages[i];
            if (i < 3)
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

int main()
{
    guide guides[2];
    for (int i = 0; i < 2; i++)
    {
        cout << "\nEnter Details of Guide " << i + 1 << endl;
        guides[i].input();
    }
    cout << "\n~~ ALL GUIDES ~~\n";

    for (int i = 0; i < 2; i++)
    {

        guides[i].display();
    }
    tour tours[2];

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
    tickets tkt[2];
    int group;
    cout << "\nEnter number of group : ";
    cin >> group;
    for (int i = 0; i < group; i++)
    {
        string destination;
        cout << "\nEnter Ticket Details for Booking " << i + 1 << endl;
        cout << "\nEnter Destination (Kashmir/Jammu): ";
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
            cout << "\nInvalid Destination!";
        }
        tkt[i].input(*ptr);
    }
    cout << "\n~~ ALL TICKET DETAILS ~~\n";

    for (int i = 0; i < group; i++)
    {
        tkt[i].display();
    }
    return 0;
}