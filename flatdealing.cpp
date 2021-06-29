#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<map>
#include<cstdlib>

using namespace std;
int count_1 = 10;
int count_2 = 10;
int count_3 = 10;
int chance = 1;


class flat
{
private:
    int room_no;
    string fname;
    string lname;
    string address;
    string phone;


public:
    flat() {}
    flat(int room_no, string fname, string lname, string address, string phone)
    {
        this->room_no = room_no;
        this->fname = fname;
        this->lname = lname;
        this->address = address;
        this->phone = phone;
    }

    int get_room_no() { return room_no; }
    string getfirstname() { return fname; }
    string getlastname() { return lname; }
    string getaddress() { return address; }
    string getphone() { return phone; }


    friend ofstream& operator<< (ofstream& ofs, flat& fl);
    friend ifstream& operator>> (ifstream& ifs, flat& fl);
    friend ostream& operator<< (ostream& os, flat& fl);
};
class owner
{
private:
    map<int, flat> flatss;
public:
    owner();

    flat add();          //to book a room
    void displayvac();   //to display vacant flats
    void display();      //to display the particular customer record
    void rooms();        //to display alloted rooms
    void edit();         //to edit the customer record
    int check(int);      //to check room status
    void modify(int);    //to modify the record
    int delete_rec(int); //to delete the record
    void pricelist();
    void displaybooked();
    ~owner();
};

void owner::displayvac()
{
    system("cls");
    cout << "\n\t\t SOCIETY - DWARKA ENCLAVES \nADDRESS - DWARKA SECTOR  -24" << endl;
    cout << "\n\t" << "Available 1 BHK flats = " << count_1;
    cout << "\n\t" << "Available 2 BHK flats = " << count_2;
    cout << "\n\t" << "Available 3 BHK flats = " << count_3 << endl;
}
void owner::pricelist()
{
    cout << "\nHere's the menu of flats we are offering you : ";
    cout << "\n  Room No.\tCategory\t   Type   \t  Area(sq. ft)\tPrice(Rs.)";
    cout << "\n  100-102\t1 BHK\t\tFront Facing\t   683\t\t30 Lac";
    cout << "\n  103-105\t1 BHK\t\tBack Facing\t   683\t\t28 Lac";
    cout << "\n  106-109\t1 BHK Corner\t 2 side open\t   703\t\t32 Lac";
    cout << "\n  200-202\t2 BHK\t\tFront Facing\t   875\t\t40 Lac";
    cout << "\n  203-205\t2 BHK\t\tBack Facing\t   875\t\t38 Lac";
    cout << "\n  206-209\t2 BHK Corner\t 2 side open\t   959\t\t45 Lac";
    cout << "\n  300-302\t3 BHK\t\tFront Facing\t   1314\t\t55 Lac";
    cout << "\n  303-305\t3 BHK\t\tBack Facing\t   1314\t\t53 Lac";
    cout << "\n  306-309\t3 BHK Corner\t 2 side open\t   1398\t\t60 Lac";
    getch();

}


flat owner::add()
{
    system("cls");
    int r, flag;
    string fn, ln, adrs, phn;
    ofstream fout;
label:
    cout << "\n Enter Customer Details to Book a flat";
    cout << "\n **";
    cout << "\n\nRoom no:\n from 100-109 for 1 bhk flats \n from 200-209 for 2 bhk flats \n from 300-309 for 3 bhk flats : \n";
    cin >> r;
    if ((r >= 100 && r <= 109) || (r >= 200 && r <= 209) || (r >= 300 && r <= 309))
    {

        flag = check(r);

        if (flag == 1)
        {
            cout << "\n Sorry..!!!Flat is already booked";
            cout << "\n\Try for other vacant flats!\n\n";
            goto label;
        }

        else
        {
            if (r >= 100 && r <= 109)
            {
                count_1 -= 1;
            }
            if (r >= 200 && r <= 209)
            {
                count_2 -= 1;
            }
            if (r >= 300 && r <= 309)
            {
                count_3 -= 1;
            }
            cout << "First Name: ";
            cin >> fn;
            cout << "Last Name: ";
            cin >> ln;
            cout << " Address: ";
            cin >> adrs;
            cout << " Phone No: ";
            cin >> phn;
            flat acc(r, fn, ln, adrs, phn);
            flatss.insert(pair<int, flat>(acc.get_room_no(), acc));
            fout.open("Record.dat", ios::app);

            map<int, flat>::iterator itr;
            for (itr = flatss.begin(); itr != flatss.end(); itr++)
            {
                fout << itr->second;
            }
            fout.close();
            system("cls");
            cout << "\n CONGRATS !!! Room is put on hold !!!\n\n<---Holder Details --->\n";
            return acc;
        }

        cout << "\n Press any key to continue!!";
        getch();

    }
    else
    {
        cout << "\n Wrong room number entered !!\n";
        getch();
    }

}

void owner::display()
{
    system("cls");
    int r, flag = 0;
    cout << "\n Enter room no: ";
    cin >> r;

    map<int, flat>::iterator itr = flatss.find(r);
    if (itr != flatss.end())
    {
        flag = 1;
        cout << "Details of the room holder: \n" << itr->second;
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant!!";

    cout << "\n\n Press any key to continue!!";
    getch();
}

void owner::rooms()
{
    system("cls");

    map<int, flat>::iterator itr;
    cout << "All Flats Holder Details: " << "\n\n";
    for (itr = flatss.begin(); itr != flatss.end(); itr++)
    {
        cout << itr->second << "\n";
        cout << "\n-----------------------------------------------------\n";
    }
    getch();
}

int owner::check(int r)
{
    map<int, flat>::iterator itr = flatss.find(r);
    if (itr != flatss.end())
    {
        return 1;
    }
    return 0;
}

void owner::edit()
{
    system("cls");
    int choice, r;

    cout << "\n EDIT MENU";
    cout << "\n *";
    cout << "\n\n  1.Modify Customer Record";
    cout << "\n  2.Delete Customer Record";
    cout << "\n  3.Exit";

    cout << "\n Enter your choice: ";
    cin >> choice;

    system("cls");


    switch (choice)
    {
    case 1:cout << "\n Enter room no: ";
        cin >> r;
        modify(r);
        break;
    case 2:cout << "\n Enter room no: ";
        cin >> r;
        int c;
        c = delete_rec(r);
        if (c == 1)
        {
            cout << "\nRecord has been successfully deleted !!\n";
        }
        break;
    case 3: break;
    default: cout << "\n Wrong Choice!!";
    }

    cout << "\n Press any key to continue!!!";
    getch();
}

void owner::modify(int r)
{
    string fn, ln, add, phn;
    int flag = 0;
    map<int, flat>::iterator itr = flatss.find(r);
    if (itr != flatss.end())
    {
        cout << "\n Enter New Details";
        cout << "\n *";
        cout << "\n First Name: ";
        cin >> fn;
        cout << "\n Last Name: ";
        cin >> ln;
        cout << " Address: ";
        cin >> add;
        cout << " Phone no: ";
        cin >> phn;

        flat acc(r, fn, ln, add, phn);
        itr->second = acc;
        cout << "\n Record is modified!!\n With new holder details as -->\n";
        flag = 1;
        cout << acc;
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant!!";
}

int owner::delete_rec(int r)
{
    int flag = 0;
    char ch;
    map<int, flat>::iterator itr = flatss.find(r);
    if (itr != flatss.end())
    {
        cout << endl << "Details for Flat no. " << itr->first << " :\n" << itr->second;
        flag = 1;
    }

    if (flag == 1)
    {
        cout << "\n\n Do you want to delete this record(y/n): ";
        cin >> ch;

        if (ch == 'n' || ch == 'N')
        {
            cout << "Okay!Exiting..... ";
            return 0;
        }
        else if (ch == 'y' || ch == 'Y')
        {
            flatss.erase(r);
            if (r >= 100 && r <= 109)
            {
                count_1 += 1;
            }
            if (r >= 200 && r <= 209)
            {
                count_2 += 1;
            }
            if (r >= 300 && r <= 309)
            {
                count_3 += 1;
            }
            return 1;
        }
    }
    else
    {
        cout << "Flat is vaccant till now! ";
    }

}
void owner::displaybooked()
{
    int ch_1 = 0, ch_2 = 0, ch_3 = 0;
    int checkk_1 = 0, checkk_2 = 0, checkk_3 = 0;

    map<int, flat>::iterator itr;
    for (itr = flatss.begin(); itr != flatss.end(); itr++)
    {
        if (itr->second.get_room_no() >= 100 && itr->second.get_room_no() <= 109)
        {
            if (ch_1 == 0)
            {
                cout << "\n 1 BHK Booked Flats:";
                ch_1 = 1;
            }
            cout << " " << itr->second.get_room_no() << " ";
            checkk_1++;
        }
        if (itr->second.get_room_no() >= 200 && itr->second.get_room_no() <= 209)
        {
            if (ch_2 == 0)
            {
                cout << "\n 2 BHK Booked Flats:";
                ch_2 = 1;
            }
            cout << " " << itr->second.get_room_no() << " ";
            checkk_2++;
        }
        if (itr->second.get_room_no() >= 300 && itr->second.get_room_no() <= 309)
        {
            if (ch_3 == 0)
            {
                cout << "\n 3 BHK Booked Flats:";
                ch_3 = 1;
            }
            cout << " " << itr->second.get_room_no() << " ";
            checkk_3++;
        }

    }

    if (checkk_1 == 0)cout << "\n ALL 1 BHK FLATS ARE AVAIALABLE";
    if (checkk_2 == 0)cout << "\n ALL 2 BHK FLATS ARE AVAIALABLE";
    if (checkk_3 == 0)cout << "\n ALL 3 BHK FLATS ARE AVAIALABLE\n";
    cout << "\n Press enter to continue...\n";
    getch();

}


ofstream& operator<<(ofstream& ofs, flat& fl)
{
    ofs << fl.room_no << endl;
    ofs << fl.fname << endl;
    ofs << fl.lname << endl;
    ofs << fl.address << endl;
    ofs << fl.phone << endl;
    return ofs;
}
ifstream& operator>>(ifstream& ifs, flat& fl)
{
    ifs >> fl.room_no;
    ifs >> fl.fname;
    ifs >> fl.lname;
    ifs >> fl.address;
    ifs >> fl.phone;
    return ifs;

}
ostream& operator<<(ostream& os, flat& fl)
{
    os << "Flat Number :" << fl.get_room_no() << endl;
    os << "First name :" << fl.getfirstname() << endl;
    os << "Last name :" << fl.getlastname() << endl;
    os << "Address :" << fl.getaddress() << endl;
    os << "Phone number :" << fl.getphone() << endl;
    return os;
}


owner::owner()
{
    flat acc;
    ifstream infile("Record.dat", ios::in);
    if (!infile)
    {
        //cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while (!infile.eof())
    {
        infile >> acc;
        flatss.insert(pair<int, flat>(acc.get_room_no(), acc));
    }
    infile.close();
}

owner::~owner()
{
    ofstream outfile;
    outfile.open("Record.dat", ios::trunc);
    map<int, flat>::iterator itr;
    for (itr = flatss.begin(); itr != flatss.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}


int main()
{
    flat f;
    owner own;
    system("cls");
    cout << "\n\t\t\t************************";
    cout << "\n\t\t\t* FLAT DEALING PROJECT *";
    cout << "\n\t\t\t************************";

    cout << "\n\n\n\n\t\tMade By:";
    cout << "\n\t\t Shivam Bharti -  2k19/SE/115 ";
    cout << "\n\t\t Pawan         -  2k19/SE/083 ";
    cout << "\n\n\n\n\n\t\t\t\tPress any key to continue!!";
    getch();
    system("cls");
    cout << endl << endl << "\t \t |*WELCOME TO SB&P FLAT DEALERS*|" << endl << endl;
    cout << endl;
    int n, p, re, o;
    while (n != 4)
    {
        cout << "  Please tell us about yourself:\n 1.NEW USER \n 2.REGISTERED USER  \n 3.OWNER \n 4.QUIT" << endl;
        cin >> n;
        switch (n)
        {
        case 1: 	system("cls");
            cout << "\t WELCOME SIR/MAM" << endl;
            cout << "\n  HOW CAN WE HELP YOU " << endl;

            do
            {
                cout << "\n\n\t PLEASE SELECT AMONG THESE :" << endl << endl;
                cout << "\n  1.DISPLAY VACANT FLAT INFORMATION";
                cout << "\n  2.DISPLAY PRICE MENU OF ALL FLATS";
                cout << "\n  3.BOOK AN AVAILABLE FLAT";
                cout << "\n  4.EXIT" << endl;
                cout << "  ";
                cin >> p;
                cout << endl;
                switch (p)
                {
                case 1: own.displayvac();
                    cout << "\n Press any key to continue!!";
                    getch();
                    break;
                case 2: own.pricelist();
                    break;
                case 3: f = own.add();
                    cout << f;
                    break;
                case 4: cout << "\n  THANKS FOR VISITING\n" << endl;
                    break;
                default: cout << "SORRY !, YOU MADE A WRONNG CHOICE " << endl;
                    break;

                }

            } while (p != 4);

            break;
        case 2: 	system("cls");
            cout << "\n  WELCOME AGAIN SIR/MAM" << endl;
            cout << "\n GLAD TO SEE YOU" << endl;
            do
            {
                cout << "\n\n\t Please select your choice" << endl << endl;
                cout << "  1.Edit Details";
                cout << "\n  2.Display Details";
                cout << "\n  3.Book A New Flat";
                cout << "\n  4.Exit";
                cout << "\n  ";
                cin >> re;
                switch (re)
                {
                case 1: own.edit();
                    break;
                case 2: own.display();
                    break;
                case 3: f = own.add();
                    cout << f;
                    break;
                case 4: cout << "\n  THANKS FOR VISITING" << endl;
                    break;
                default: cout << "SORRY !, YOU MADE A WRONNG CHOICE " << endl;
                    break;
                }
            } while (re != 4);
            break;
        case 3: {system("cls");
            int i;
            char ch1, password[10];
            cout << "Enter your password : ";
            for (i = 0; i < 10; i++)
            {
                ch1 = getch();
                password[i] = ch1;

                if (ch1 != 13)      //13 is ASCII of Enter key
                    printf("*");
                if (ch1 == 13)
                    break;
            }
            password[i] = '\0';
            if ((strcmp(password, "031929")) == 0)
            {
                system("cls");
                cout << "Password matched :)";
                cout << "\n\n\tWHAT DO YOU WANT SIR ? " << endl << endl;
                do
                {
                    cout << "\n  1.Show all flats status";
                    cout << "\n  2.Show a particular record";
                    cout << "\n  3.Delete or modify a record";
                    cout << "\n  4.Show available flats";
                    cout << "\n  5.Show booked flats ";
                    cout << "\n  6.Exit";
                    cout << "\n  ";
                    cin >> o;
                    switch (o)
                    {
                    case 1: own.rooms();
                        break;
                    case 2: own.display();
                        break;
                    case 3: own.edit();
                        break;
                    case 4: own.displayvac();
                        break;
                    case 5: own.displaybooked();
                        break;
                    case 6: break;
                    default: cout << "\n SORRY, YOU MADE A WRONG CHOICE!!";
                        break;
                    }
                } while (o != 6);

            }
            else
                cout << "\n Wrong password Entered! ";
            break;
        }
        case 4: cout << "\n  THANKS FOR VISITING " << endl;
            break;
        default: cout << "SORRY !, YOU MADE A WRONG CHOICE " << endl;
            break;
 }
 }
     getch();
    return 0;
}
