//Door entry system
//Philip monk
//21/11/2024

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>


using namespace std;

#define DEBUG 0
#define ESC 27
#define MAXROOMS 20
#define MAXUSERS 100

 class room
{
private:
    bool inEmergency = false;
    string roomName;
    

public: 

    int accesslevel;

    void setAccessLevel(int y);

    void setRoomname(string x)
    {
        roomName = x;
    }
    bool updateRoomEmerStat()
    {
        if (inEmergency == false)
        {
            inEmergency = true;
        }
        else
            inEmergency = false;
    }
    void roomAccessed()
    {};

    bool isEmergency()
    {}

    bool allClear()
    {}

    void grantAccess()
    {
        cout << "Access to " << getroomName();
    }
    string getroomName()
    {
        return roomName;
    }
    int getRoomAccess()
    {
        return accesslevel;
    }
    



};
 class lectureHall : public room
 {


 public:

     void setAccessLevel(int y)  
     {
         accesslevel = y;
         
     }

     void cleaningTime()
     {

     }
     lectureHall(string x,int y);
 };
 lectureHall::lectureHall(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }


 class staffRoom : public room
 {
  public:
      void setAccessLevel(int y) 
      {
          accesslevel = y;
      }

     void cleaningTime()
     {

     }
     staffRoom(string x, int y);
 };
 staffRoom::staffRoom(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }

 class teachingRoom : public room
 { public:
     void setAccessLevel(int y) 
     {
         accesslevel = y;
     }

     void cleaningTime()
     {

     }
     teachingRoom(string x, int y);
 };
 teachingRoom::teachingRoom( string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }

 class secureRoom : public room
 { public:
     void setAccessLevel(int y) 
     {
         accesslevel = y;
     }

     secureRoom(string x, int y);
 };
 secureRoom :: secureRoom(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }



 class Observer {
 public :
     virtual void update(const string& msg) = 0;
 };

 class emergencystate
 {
     vector<Observer*> observers;
 public:
     void attach(Observer* obs)
     {
         observers.push_back(obs);
     }
     void notify(const string& msg)
     {

     }
 };

class cardHolder
{

private:
    string fname;
    string sname;
    int collegeID;
    int accessLevel;

public:
    void setName(string x, string y)
    {
        fname = x;
        sname = y;
    }

    void setCollegeID(int y)
    {
        collegeID = y;
    }

    void setAccessLevel(int z)
    {
        accessLevel = z;
    }
    string getName()
    {
        return fname;
    }
    string getfullName()
    {
        string fullName = fname + " " + sname;
        return fullName;
    }
    int getAccessLevel()
    {
        return accessLevel;
    }

};

class manager : public cardHolder
{
    public:
        void addUser(string name,int accesslevel)
        {
            fstream userfile;
            userfile.open("user.txt", ios::app);
            userfile << name << " "<< accesslevel <<"\n";
            userfile.close();


        }

        void updateUser()
        {

        }

        void removeUser()
        {
        
        }

        void updateRoom()
        {
        
        }
        void viewLog()
        {
        
        }


};
class student : public cardHolder
{  
};

class staffMember : public cardHolder
{};
class visitor : public cardHolder
{};
class cleaner : public cardHolder
{};
class security : public cardHolder
{};
class EResponer : public cardHolder
{};
void gotoxy(int x, int y)         //define gotoxy function
{
    static HANDLE hStdout = NULL;
    COORD coord;

    coord.X = x;
    coord.Y = y;
    if (!hStdout) { hStdout = GetStdHandle(STD_OUTPUT_HANDLE); }
    SetConsoleCursorPosition(hStdout, coord);
}


void clrscr(void) //clear screen function
{
    static HANDLE hStdout = NULL;
    static CONSOLE_SCREEN_BUFFER_INFO csbi;
    const COORD startCoords = { 0,0 }; // defines starting coordinates of clear screen 
    DWORD dummy;

    if (!hStdout)
    {
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdout, &csbi);
    }
    FillConsoleOutputCharacter(hStdout, ' ', csbi.dwSize.X * csbi.dwSize.Y, startCoords, &dummy);
    gotoxy(0, 0); //returns cursor to top left of screen for next output
}

vector <room> rooms[MAXROOMS];
vector <cardHolder> cards[MAXUSERS];
fstream roomfile;


void refreshfile() {
    roomfile.open("rooms.txt"); // open file

    if (roomfile.is_open())
    {
        string tempname;
        int tempaccess;
        int currentcase;
        do
        {
            roomfile >> tempname;
            roomfile >> tempaccess;
            currentcase = tempaccess;
            //cout << tempname << " " << tempaccess;
            if (currentcase == 1)
            {

                lectureHall lecturehall(tempname, tempaccess);
                rooms->push_back(lecturehall);

            }
            else if (currentcase == 2)
            {
                staffRoom staffroom(tempname, tempaccess);
                rooms->push_back(staffroom);

            }
            else if (currentcase == 3)
            {
                teachingRoom teachingroom(tempname, tempaccess);
                rooms->push_back(teachingroom);

            }
            else if (currentcase == 4)
            {
                secureRoom secureroom(tempname, tempaccess);
                rooms->push_back(secureroom);

            }

        } while (!roomfile.eof());
        roomfile.close(); //close file
        for (int i = 0; i < rooms->size(); i++)
        {
            cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
        }
        _getch();
    }
    else
    {
        cerr << "File not found";
        _getch();
    }
}

void writerooms(string x,int y)
{
    roomfile.open("rooms.txt",ios::app); //append to file 

    if (roomfile.is_open())
    {
        roomfile << x << " " << y << "\n";
    }
    else
    {
        cerr << "File not found";
        _getch();
    }

    roomfile.close();
}



string login;

manager mainman;
student stu;
staffMember staff;
cleaner cClean;
security secGuard;
EResponer emerGuest;
visitor guest;


int roomtype = 0;
string roomname;
int type;
string roomlookup;

int main()
{ 


    refreshfile();
    mainman.setName("Phil","Monk");

    

    // user chooses function 

    
    do
    {
        clrscr();
        cout << "welcome to the college door entry system system" << endl;
        cout << "Select function: (1) Enter room, (2) Login to setup or (0) to exit: ";
       // cout << "Currently logged in as: " << login; //test login status
        cin >> type;
        if (type == 1)
        {
            cout << "Enter room number: (ks225)";
            cin >> roomlookup;
            for (int i = 0; i < rooms->size(); i++)
            {   
                string currentRoom = rooms->at(i).getroomName();
                if (roomlookup == currentRoom)
                {
                    cout << "Access granted to " << currentRoom;
                    _getch();
                }
                else
                    cout << "Room does not exist";
                _getch();
            }
            
        }
        if (type == 2) // setup new rooms to txt file 
        {
            clrscr();
            cout << "Enter login name: " << endl;
            cin >> login;
            if (login == mainman.getName())  // login required
            {   cout << "Access granted " << endl;
            
                while (login == mainman.getName())
                {
                    int choice;
                    string tempfname;
                    string tempsname;
                    cout << "1 user, 2 room";
                    cin >> choice;
                    clrscr();
                    if (choice == 1) 
                    {
                        cout << "New cardholder type"; //expand menu 
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            stu.setName(tempfname, tempsname);
                            stu.setAccessLevel(choice);
                            mainman.addUser(stu.getfullName(), stu.getAccessLevel());
                            break;

                        case 2:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            staff.setName(tempfname, tempsname);
                            staff.setAccessLevel(choice);
                            mainman.addUser(staff.getfullName(), staff.getAccessLevel());
                            break;

                        case 3:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            cClean.setName(tempfname, tempsname);
                            cClean.setAccessLevel(choice);
                            mainman.addUser(cClean.getfullName(), cClean.getAccessLevel());
                            break;

                        case 4:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            secGuard.setName(tempfname, tempsname);
                            secGuard.setAccessLevel(choice);
                            mainman.addUser(secGuard.getfullName(), secGuard.getAccessLevel());
                            break;
                        case 5:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            emerGuest.setName(tempfname, tempsname);
                            emerGuest.setAccessLevel(choice);
                            mainman.addUser(emerGuest.getfullName(), emerGuest.getAccessLevel());
                            break;
                        case 6:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            guest.setName(tempfname, tempsname);
                            guest.setAccessLevel(choice);
                            mainman.addUser(guest.getfullName(), guest.getAccessLevel());
                            break;
                        }
                    }

                    else
                    cout << "enter room type: ";
                    cin >> roomtype; // roomtype will determine which kind of room will be created
                    
                    if (roomtype == 1)
                    {
                        cout << "enter room name: ";
                        cin >> roomname;
                        lectureHall lecturehall(roomname, roomtype);

                        rooms->push_back(lecturehall);
                        writerooms(roomname, roomtype);
                        if (DEBUG == 1)
                        {
                            for (int i = 0; i < rooms->size(); i++)
                            {
                                cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
                            }
                        }
                        
                    }
                    else if (roomtype == 2)
                    {
                        cout << "enter room name: ";
                        cin >> roomname;
                        staffRoom staffroom(roomname, roomtype);
                        rooms->push_back(staffroom);
                        writerooms(roomname, roomtype);
                        if (DEBUG == 1)
                        {
                            for (int i = 0; i < rooms->size(); i++)
                            {
                                cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
                            }
                        }
                        
                    }
                    else if (roomtype == 3)
                    {
                        cout << "enter room name: ";
                        cin >> roomname;
                        teachingRoom teachingroom(roomname, roomtype);
                        rooms->push_back(teachingroom);
                        writerooms(roomname, roomtype);
                        if (DEBUG == 1)
                        {
                            for (int i = 0; i < rooms->size(); i++)
                            {
                                cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
                            }
                        }
                        
                    }
                    else if (roomtype == 4)
                    {
                        cout << "enter room name: ";
                        cin >> roomname;
                        secureRoom secureroom(roomname, roomtype);
                        rooms->push_back(secureroom);
                        writerooms(roomname, roomtype);
                        if (DEBUG == 1)
                        {
                            for (int i = 0; i < rooms->size(); i++)
                            {
                                cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
                            }
                        }
                       
                    }
                    else if (roomtype == 0)
                    {

                        login = "Logged out";
                        break;

                    }
                    
                }

            }
            else
                cout << "access denied";
        
           

            
        }

    } while (type != 0);
}
