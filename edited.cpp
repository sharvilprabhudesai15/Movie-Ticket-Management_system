#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>    //all libraries plus system commands eg:cls,pause
#include <cstring>
#include <ctype.h>  // for isdigit()
const int len = 300;
using namespace std;
bool isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}
int main();
class Cinema
{
public:
    void viewTime();
    int selectCinema();
    void bookTicket(int CinemaType, int CinematNo, int cust);
    int seatDisp(int SeatNo);
    int findRecord(int SeatNo);
    //reserves the seats with showing empty seats as 0
    Cinema()
    {
        int a, b, c;
        for (c = 0; c < 4; c++) // represents the seat number time
        {
            for (a = 0; a < 6; a++) // represents row ------
            {
                for (b = 0; b < 10; b++) // represents column  ||||||||||
                {
                    CinemaSeatNo[a][b][c] = 0;
                }
            }
        }
    }

private:
    int CinemaSeatNo[6][10][4];
    int CinemaType;
    int CinemaNo;     // to choose cinema
    int totalTicBook; // number of seats you want to reserve 1,2,3....
    int cust;
};
class customer : public Cinema
{
public:
    void addCustomer();
    void dispCustomer();

private:
    char name[len];
    char address[len];
    char telNo[len];

    int payment;
};
//------------------------------View Time---------------------------------------
// to show the cinama names
void viewTime()
{
    int back;
    system("cls");
    cout << "\n\t^^^^^^^^^^^^^^^^^^^^ Available Cinema ^^^^^^^^^^^^^^^^^\n";
    cout << "\n\n\t\t 1.Spiderman No Way Home \n";
    cout << "\t\t 2.Sooryavanshi \n";
    cout << "\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "\n\tEnter 0 to Exit From This Menu : ";
    cin >> back;
    system("cls");
}
// --------------------------------insert cinema data---------------------------------
int Cinema::selectCinema()
{
    int menu1 = 0, menu2 = 0, CinemaNo;
    // cinemaSeatNo[a][b][x]
    system("cls");
    // to show the timing of the cinema Morning Evening
    do
    {
        cout << "\n\t*************** Please Enter Reservation Detail. ***************"
             << "\n\nEnter Time Of Cinema.."
             << "\n\t[1] : For Morning  Cinema" // cinemaSeatNo[x][x][0 to 1]
             << "\n\t[2] : For Evening Cinema"  // cinemaSeatNo[x][x][2 to 3]
             << "\n\t[0] : To Quit From Reservation Menu\nEnter choice: ";
        cin >> CinemaType; // 1= Spiderman No Way Home, 2=Sooryavanshi//
        //------Check Type Of Cinema------
        switch (CinemaType)
        {
        //case1 to show which movie you want to select  morning one
        case 1:
            do
            {
                cout << "\n--- Morning Show Ticket Reservation ---"
                     << "\nEnter Cinema.."
                     << "\n\t[1] For Spiderman No Way Home"
                     << "\n\t[2] For Sooryavanshi"
                     << "\n\t[0] For Quit Menu\nEnter choice: ";
                cin >> CinemaNo;
                switch (CinemaNo)
                {
                case 1:
                case 2:
                    //case 3:
                    //put any cinema it will store into only 1 array
                    //menu1 and menu 2 made to make code work incase of an invalid state  and exit state respectively
                    CinemaNo = CinemaNo - 1;
                    cust = seatDisp(CinemaNo);
                    bookTicket(CinemaType, CinemaNo, cust);
                    menu2 = 1;
                    menu1 = 2;
                    break;
                case 0:
                    menu2 = 1;
                    break;
                default:
                    cerr << "Invalid choice" << endl
                         << endl;
                    system("pause");
                    system("cls");
                }
            } while (menu2 != 1);
            break;
        //case 2 is made to store the evening movie tickets
        case 2:
            do
            {
                cout << "\n--- Evening Show Ticket Reservation ---"
                     << "\nEnter Seat.."
                     << "\n\t[3] For Spiderman No Way Home"
                     << "\n\t[4] For Sooryavanshi"
                     << "\n\t[0] For Quit Menu\nEnter choice: ";
                cin >> CinemaNo;
                //made similar cases as case 1  but to select evening shows
                switch (CinemaNo)
                {
                case 3:
                case 4:
                    // case 6:
                    CinemaNo = CinemaNo - 1;
                    cust = seatDisp(CinemaNo);
                    bookTicket(CinemaType, CinemaNo, cust);
                    menu2 = 1;
                    menu1 = 2;
                    break;
                case 0:
                    menu2 = 1;
                    break;
                default:
                    cerr << "Invalid choice" << endl
                         << endl;
                    system("pause");
                    system("cls");
                }
            } while (menu2 != 1);
            break;
        // to come outside the loop it has been made
        case 0:
            menu1 = 1;
            break;
        default:
            cerr << "Invalid choice" << endl
                 << endl;
            system("pause");
            system("cls");
        }
    } while (menu1 == 0);
    return (menu1);
} // -------------------------------- booking ticket function --------------------------------
void Cinema::bookTicket(int CinemaType, int CinemaNo, int customer)
{
    // p has been made to keep counter of the seats
    int seatNo, seatCheck = 0, temp, a, b, p;
    string FType;
    p = 60 - cust;
    cout << "\nHow Many Ticket Do You Want?[ticket available:(" << p << ")]: ";
    cin >> totalTicBook;
    if (totalTicBook > p || totalTicBook < 1)
    {
        do
        {
            cout << "\nSorry!! Seat Available Not Enough Or Invalid Input...";
            cout << "\nHow Many Ticket Do You Want?[ticket available:(" << p << ")]: ";
            cin >> totalTicBook;
        } while (totalTicBook > p || totalTicBook < 1);
    }
    for (int i = 1; i <= totalTicBook; i++)
    {
        system("cls");
        seatDisp(CinemaNo);
    seat:
    line:
        cout << "\nBooking[" << i << "/" << totalTicBook << "]."
             << "\nEnter The Seat Number(1 to 60): ";
        try
        {
            cin >> seatNo;
            if (seatNo > 60 || seatNo < 1)
                throw 0;
        }
        catch (int)
        {
            cout << endl
                 << "Enter valid seat number" << endl;
            goto line;
        }
        if (seatNo <= 60)
        {
            // made to select seats row wise

            // the seat number is (-) by number  to get actual array index where you want to enter

            if (seatNo <= 10) // Ticket between 1 to 10
            {
                a = 0;
                b = seatNo - 1;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;

                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";

                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else if (seatNo > 10 && seatNo <= 20) // Ticket between 11 to 20
            {
                a = 1;
                b = seatNo - 11;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;
                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";
                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else if (seatNo > 20 && seatNo <= 30) // Ticket between 21 to 30
            {
                a = 2;
                b = seatNo - 21;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;
                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";
                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else if (seatNo > 30 && seatNo <= 40) // Ticket between 31 to 40
            {
                a = 3;
                b = seatNo - 31;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;
                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";
                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else if (seatNo > 40 && seatNo <= 50) // Ticket between 41 to 50
            {
                a = 4;
                b = seatNo - 41;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;
                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";
                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else if (seatNo > 50 && seatNo <= 60) // Ticket between 51 to 60
            {
                a = 5;
                b = seatNo - 51;
                if (CinemaSeatNo[a][b][CinemaNo] == 1)
                {
                    seatCheck = 1;
                    i--;
                    cout << "\nSorry...Ticket# " << seatNo << " booked!!\n";
                    system("pause");
                }
                else
                {
                    seatCheck = 0;
                    CinemaSeatNo[a][b][CinemaNo] = 1;
                }
            }
            else
            {
                cout << "enter valid seat number \n";
                seatCheck = 0;
                CinemaSeatNo[a][b][CinemaNo] = 1;
                goto seat;
            }
        }

        // ------------- saving cinemaseat --------------
        //spiderman morning
        if (CinemaNo == 0 && seatCheck == 0)
        {
            ofstream fileout("Cinema1", ios::out | ios::binary);
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    temp = CinemaSeatNo[a][b][CinemaNo];
                    fileout << temp << " ";
                }
            }
        }
        //sooryavanshi
        else if (CinemaNo == 1 && seatCheck == 0)
        {
            ofstream fileout("Cinema2", ios::out | ios::binary);
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    temp = CinemaSeatNo[a][b][CinemaNo];
                    fileout << temp << " ";
                }
            }
        }
        //spiderman evening
        else if (CinemaNo == 2 && seatCheck == 0)
        {
            ofstream fileout("Cinema3", ios::out | ios::binary);
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    temp = CinemaSeatNo[a][b][CinemaNo];
                    fileout << temp << " ";
                }
            }
        }
        //sooryavanshi evening
        else if (CinemaNo == 3 && seatCheck == 0)
        {
            ofstream fileout("Cinema4", ios::out | ios::binary);
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    temp = CinemaSeatNo[a][b][CinemaNo];
                    fileout << temp << " ";
                }
            }
        }
    }

    system("cls");
    seatDisp(CinemaNo); // -------------saving customer data--------------
    if (CinemaType == 1 && CinemaNo == 0)
        FType = "Morning - Spiderman No Way Home";
    if (CinemaType == 1 && CinemaNo == 1)
        FType = "Morning - Sooryavanshi";
    if (CinemaType == 2 && CinemaNo == 2)
        FType = "Evening-Spiderman No Way Home";
    if (CinemaType == 2 && CinemaNo == 3)
        FType = "Evening - Sooryavanshi";
    ofstream fout("customer", ios::out | ios::app | ios::binary);
    fout << "Cinema : " << FType << endl
         << "Total ticket(s) Booked: " << totalTicBook << endl;
}
//-------------------------------Find Record----------------------------------------
int Cinema::findRecord(int CinemaNo)
{
    int a, b, temp;
    cust = 0;
    //since cinemas screens are decremented by 1 so cinema is staring  from 0 and not 1 
    if (CinemaNo == 0)
    {
        ifstream fin("Cinema1", ios::in | ios::binary);
        while (fin)
        {
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    fin >> temp;
                    //the output statement is executed even when the input operation fails.
                    //  And when it fails, it doesn't update x.
                    // EOF causes the repetition of last character of the file twice so to that alternative i have used .Fail
                    // Instead of testing .eof(), test .fail().
                    if (!fin.fail()) // avoid displaying the last char twice
                        CinemaSeatNo[a][b][CinemaNo] = temp;
                    if (temp == 1)
                        cust++;
                }
            }
        }
    }
    if (CinemaNo == 1)
    {
        ifstream fin("Cinema2", ios::in | ios::binary);
        while (fin)
        {
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    fin >> temp;
                    if (!fin.fail()) // avoid displaying the last char twice
                        CinemaSeatNo[a][b][CinemaNo] = temp;
                    if (temp == 1)
                        cust++;
                }
            }
        }
    }
    if (CinemaNo == 2)
    {
        ifstream fin("Cinema3", ios::in | ios::binary);
        while (fin)
        {
            for (a = 0; a < 6; a++)
            // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    fin >> temp;
                    if (!fin.fail()) // avoid displaying the last char twice
                        CinemaSeatNo[a][b][CinemaNo] = temp;
                    if (temp == 1)
                        cust++;
                }
            }
        }
    }
    if (CinemaNo == 3)
    {
        ifstream fin("cinema4", ios::in | ios::binary);
        while (fin)
        {
            for (a = 0; a < 6; a++) // represents row
            {
                for (b = 0; b < 10; b++) // represents column
                {
                    fin >> temp;
                    if (!fin.fail()) // avoid displaying the last char twice
                        CinemaSeatNo[a][b][CinemaNo] = temp;
                    if (temp == 1)
                        cust++;
                }
            }
        }
    }
    // ---- statement to solve the counting of customer ----
    if (cust > 60)
        cust = cust - 60;
    return (cust);
}
void customer::addCustomer()
{
    //ignore that many size before storing the data 
    string P;
    cin.ignore(len, '\n'); // leaves that many spaces
    cout << "\nEnter Customer Name: ";
    cin.getline(name, len);
    cout << "Enter Customer Address: ";
    cin.getline(address, len);
phone:
    try
    {
        cout << "Enter Customer Contact Number: ";
        cin.getline(telNo, len);
        if ((strlen(telNo) == 10))
        {
            for (int i = 0; i < 10; i++)
            {
                if (isalpha(telNo[i]))
                    throw 1;
            }
        }
        else
            throw 'a';
    }
    catch (int n)
    {
        cout << "Enter mobile number in digits don't use characters !! " << endl;
        goto phone;
    }
    catch (char k)
    {
        cout << "Enter 10 Digit Mobile Number  !! " << endl;
        goto phone;
    }

pay:

    cout << "Enter Type Of Payment"
         << "\n[1] : Cash"
         << "\n[2] : Credit Card\nChoice: ";
    cin >> payment;
    try
    {
        if (payment > 2 || payment < 1)
            throw 0;
    }
    catch (int)
    {
        cout << "Enter valid option \n";
        goto pay;
    }
    // ----------- saving customer details -----------
    if (payment == 1)
        P = "CASH";
    if (payment == 2)
        P = "CREDIT CARD";
        //fout is the file object/variable to accept or print things in a file format
        // since in this case we are writing so ofstream is used
    ofstream fout("customer", ios::out | ios::app | ios::binary);
    fout << "Customer Name: " << name << endl
         << "Customer Address: " << address << endl
         << "Customer Contact Number: " << telNo << endl
         << " Type Of Payment: " << P << endl
         << endl;
    cout << "\nBooking Process Is Done..\n";
    system("pause");
    system("cls");
}
// ------------------Displaying available seat[0] or booked seat[1] -------------------
int Cinema::seatDisp(int CinemaNo)
{
    string title;
    if (CinemaNo == 0)
        title = " Morning::Spiderman No Way Home";
    else if (CinemaNo == 1)
        title = "Morning::Sooryavanshi";
    else if (CinemaNo == 2)
        title = "Evening::Spiderman No Way Home";
    else if (CinemaNo == 3)
        title = "Evening::Sooryavanshi";
    cust = Cinema::findRecord(CinemaNo);
    cout << "\n\n\tDisplaying Seat For " << title;
    cout << "\n\t--------------------------------------------------------------------\n";
    for (int a = 0; a < 6; a++)
    {
        cout << "\t";
        for (int b = 0; b < 10; b++)
        {
            if (CinemaSeatNo[a][b][CinemaNo] == 0)
            {
                if (a == 0)
                    cout << setw(2) << b + 1 << "[0] ";
                else if (a == 1)
                    cout << b + 11 << "[0] ";
                else if (a == 2)
                    cout << b + 21 << "[0] ";
                else if (a == 3)
                    cout << b + 31 << "[0] ";
                else if (a == 4)
                    cout << b + 41 << "[0] ";
                else if (a == 5)
                    cout << b + 51 << "[0] ";
            }
            else if (CinemaSeatNo[a][b][CinemaNo] == 1)
            {
                if (a == 0)
                    cout << setw(2) << b + 1 << "[1] ";
                else if (a == 1)
                    cout << b + 11 << "[1] ";
                else if (a == 2)
                    cout << b + 21 << "[1] ";
                else if (a == 3)
                    cout << b + 31 << "[1] ";
                else if (a == 4)
                    cout << b + 41 << "[1] ";
                else if (a == 5)
                    cout << b + 51 << "[1] ";
            }
            if (CinemaSeatNo[a][b][CinemaNo] == 2)
            {
                if (a == 0)
                    cout << setw(2) << b + 1 << "[0] ";
                else if (a == 1)
                    cout << b + 11 << "[0] ";
                else if (a == 2)
                    cout << b + 21 << "[0] ";
                else if (a == 3)
                    cout << b + 31 << "[0] ";
                else if (a == 4)
                    cout << b + 41 << "[0] ";
                else if (a == 5)
                    cout << b + 51 << "[0] ";
            }
            if (CinemaSeatNo[a][b][CinemaNo] == 3)
            {
                if (a == 0)
                    cout << setw(2) << b + 1 << "[0] ";
                else if (a == 1)
                    cout << b + 11 << "[0] ";
                else if (a == 2)
                    cout << b + 21 << "[0] ";
                else if (a == 3)
                    cout << b + 31 << "[0] ";
                else if (a == 4)
                    cout << b + 41 << "[0] ";
                else if (a == 5)
                    cout << b + 51 << "[0] ";
            }
        }
        cout << "\n\n";
    }
    cout << "\t--------------------------------------------------------------------"
         << "\n\tTotal Booked Seat: " << cust;
    return (cust);
}
//------------------ Display/View Customer -----------------------
void customer::dispCustomer()
{
    char ch;
    system("cls");
    //since we are reading from the file so i have used fstream and fin is the file object 
    ifstream fin("customer", ios::in | ios::binary);
    cout << "\n\t******************* Customer Details.. *******************\n\n\n";

    //if file doesn't get 
    if (!fin)
    {
        //cerr is used in case of the error contition for file so that it will give immediate statement and not wait at the last moment to do so
        cerr << "\nError opening the file..!!\n";
    }
    while (fin)
    {
        fin.get(ch);
        if (!fin.fail()) // avoid displaying the last char twice
            cout << ch;
    }
    system("pause");
    system("cls");
}
int main()
{
    int choice, seatchoice;
    int menu = 0;
    // int CinemaMenu=0;
    int cinMenu = 0;
    // ||||class objects ||||
    Cinema F;
    customer C;
    system("cls");
    cout << "\t=========================================================\n";
    cout << "\t*********************************************************\n";
    cout << "\t*                                                       *\n";
    cout << "\t*                    Welcome To                         *\n";
    cout << "\t*              __Movie Ticket System__                  *\n";
    cout << "\t*                                                       *\n";
    cout << "\t*********************************************************\n";
    cout << "\t==========================================================";
    do
    {
        cout << "\n\n\t^^^^^^^^^^^^^^^^^^^^^ MAIN MENU ^^^^^^^^^^^^^^^^^^^^^\n\n";
        cout << "\t1. View Available Cinema\n";
        cout << "\t2. Check Available Seats\n";
        cout << "\t3. Book Ticket(s)\n";
        cout << "\t4. View Customer Bookings\n\n";
        cout << "\t0. Quit From System\n";
        cout << "\n\n\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
        cout << "\n\n\tEnter your option : ";
        cin >> choice;
        switch (choice)
        {

        case 1:
            viewTime();
            break;
        case 2:
            system("cls");
            do
            {
                cout << "\n\t^^^^^^^^^^^^^^^^^^^^^ AVAILABLE SEATS ^^^^^^^^^^^^^^^^^^^^^^^^^\n\n"
                     << "\t1. Available Seat For Morning Spiderman No Way Home\n"
                     << "\t2. Available Seat For Morning Sooryavanshi\n"
                     << "\t3. Available Seat For Evening Spiderman No Way Home\n"
                     << "\t4. Available Seat For Evening Sooryavanshi\n"
                     << "\t0. To Quit From Available Seats Menu\n"
                     << "\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
                     << "\tEnter Your Option : ";
                cin >> seatchoice;
                switch (seatchoice)
                {
                case 1:
                    F.seatDisp(seatchoice - 1);
                    break;
                case 2:
                    F.seatDisp(seatchoice - 1);
                    break;
                case 3:
                    F.seatDisp(seatchoice - 1);
                    break;
                case 4:
                    F.seatDisp(seatchoice - 1);
                    break;
                case 0:
                    cinMenu = 1;
                    system("cls");
                    break;
                default:
                    cerr << "Invalid choice" << endl
                         << endl;
                    system("pause");
                }
            } while (cinMenu != 1);
            break;
        case 3:
            if (C.selectCinema() == 2)
                C.addCustomer();
            break;
        case 4:
            C.dispCustomer();
            break;

        case 0:
            menu = 1;
            system("cls");
            cout << "\n\t__________________________________________________________________\n\n\n";
            cout << "\t(:(:(:(:(:(: Thank you for using Movie Ticket System :):):):):):) \n\n";
            cout << "\t(:(:(:(:(:(:\t\t  See You Again\t\t     :):):):):):) \n\n";
            cout << "\n\t__________________________________________________________________\n\n";
            break;
        default:
            cerr << "Invalid choice" << endl
                 << endl;
            system("pause");
            system("cls");
        }
    } while (menu != 1);
    system("pause");
    return 0;
}