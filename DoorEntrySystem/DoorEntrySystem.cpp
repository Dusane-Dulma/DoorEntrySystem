//Door entry system
//Philip monk
//21/11/2024

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;

#define DEBUG 0
#define ESC 27
#define MAXROOMS 20
#define MAXUSERS 100


//observer setup (Not working)
class Observer
{
public:
    virtual void update(BOOL emstate) = 0;
};

class emergencystate
{
private:
    BOOL emstate;
    vector<Observer*> observers;
public:
    void registerObs(Observer* obs)
    {
        observers.push_back(obs);
    }
    void notify()
    {
        for (Observer* observer : observers)
        {
            observer->update(emstate);
        }
    }
    void setstate(BOOL state)
    {
        emstate = state;
    }
    BOOL getstate()
    {
        return emstate;
    }
};
//room setup
class room : public Observer
{
private:
    
    string roomName;
    

public: 
    bool inEmergency = false;
    int accesslevel;
    
    virtual void update(BOOL emstate) override
    {
        inEmergency = emstate;
    }

    void setAccessLevel(int y);

    void setRoomname(string x)
    {
        roomName = x;
    }
    void updateRoomEmerStat()
    {
        if (inEmergency == false)
        {
            inEmergency = true;
        }
        else
            inEmergency = false;
    }

    bool isEmergency()
    {
        if (inEmergency == true)
            cout << "room in emergency";
        _getch();
        return inEmergency;
    }

    bool allClear()
    {}

    void grantAccess()
    {
        cout << "Access to " << getroomName() << " Granted";
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

//lecture hall
 class lectureHall : public room 
 {


 public:

     void update(BOOL emstate) override
     {
         inEmergency = emstate;
     }
     void setAccessLevel(int y)  
     {
         accesslevel = y;
         
     }

     void cleaningTime()
     {

     }
     lectureHall(const string x,int y);
 };
 //lecture hall constructor
 lectureHall::lectureHall(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }

 //staffroom 
 class staffRoom : public room
 {
     void update(BOOL emstate) override
     {
         inEmergency = emstate;
     }
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
 //staffroom constructor
 staffRoom::staffRoom(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }
 //teaching room 
 class teachingRoom : public room
 { public:
     void update(BOOL emstate) override
     {
         inEmergency = emstate;
     }
     void setAccessLevel(int y) 
     {
         accesslevel = y;
     }

     void cleaningTime()
     {

     }
     teachingRoom(string x, int y);
 };
 //teaching room constructor
 teachingRoom::teachingRoom( string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }
 //secure room 
 class secureRoom : public room
 { public:
     void update(BOOL emstate) override
     {
         inEmergency = emstate;
     }
     void setAccessLevel(int y) 
     {
         accesslevel = y;
     }

     secureRoom(string x, int y);
 };
 //secure room constructor
 secureRoom :: secureRoom(string x, int y)
 {
     setRoomname(x);
     setAccessLevel(y);
 }



 // cardholder setup
 

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
    int getcollegeID()
    {
        return collegeID;
    }

};
// manager
class manager : public cardHolder 
{
    public:
        void addUser(string name,int accesslevel, int id)
        {
            fstream userfile;
            userfile.open("user.txt", ios::app);
            userfile << name << " "<< accesslevel << " " << id <<"\n";
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

//student
class student : public cardHolder 
{  
public:
    student();
    student(string fname, string sname, int accesslevel, int colID);
    
};
//student constructor
student :: student(string fname, string sname, int accesslevel, int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}
//staff member
class staffMember : public cardHolder
{
public:
    staffMember();
    staffMember(string fname, string sname, int accesslevel, int colID);
    
};
//staffmember constructor
staffMember :: staffMember(string fname, string sname, int accesslevel, int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}
//visitor
class visitor : public cardHolder
{
public:
    visitor();
    visitor(string fname, string sname, int accesslevel, int colID);
    
};
//visitor constructor
visitor::visitor(string fname, string sname, int accesslevel, int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}

//cleaner
class cleaner : public cardHolder
{
public:
    cleaner();
    cleaner(string fname, string sname, int accesslevel, int colID);
    
};
//cleaner constructor
cleaner :: cleaner(string fname, string sname, int accesslevel, int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}

//security
class security : public cardHolder
{
public:
    security();
    security(string fname, string sname, int accesslevel, int colID);
   
};
//security constructor
security:: security(string fname, string sname, int accesslevel, int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}
//emergency responder
class EResponer : public cardHolder
{
public:
    EResponer();
    EResponer(string fname, string sname, int accesslevel,int colID);
};
//emergency responder constructor
EResponer::EResponer(string fname, string sname, int accesslevel,int colID)
{
    setName(fname, sname);
    setAccessLevel(accesslevel);
    setCollegeID(colID);
}



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

vector <room> rooms[MAXROOMS]; // vector of room on system
vector <cardHolder> cards[MAXUSERS]; //vector of cardholders on system
fstream userfile;
fstream roomfile;

emergencystate ems;
void refreshusers()
{

    userfile.open("ID_Card_List.txt");

    if (userfile.is_open())
    {
        cout << "userfile open";
        string tempfname;
        string tempsname;
        int tempaccess;
        int tempcid;

        do
        {
            userfile >> tempfname;
            userfile >> tempsname;
            userfile >> tempaccess;
            userfile >> tempcid;
            cout << tempfname << tempsname << tempaccess << tempcid<<endl;
            int currentcase = tempaccess;
            if (currentcase == 1)
            {

                student student(tempfname, tempsname, tempaccess, tempcid);
                cards->push_back(student);

            }
            else if (currentcase == 2)
            {
                staffMember staffMember(tempfname, tempsname, tempaccess, tempcid);
                cards->push_back(staffMember);

            }
            else if (currentcase == 3)
            {
                cleaner cleaner(tempfname, tempsname, tempaccess, tempcid);
                cards->push_back(cleaner);

            }
            else if (currentcase == 4)
            {
                security security(tempfname, tempsname, tempaccess, tempcid);
                cards->push_back(security);

            }
            else if (currentcase == 5)
            {
                EResponer EResponer(tempfname, tempsname, tempaccess,tempcid);
                cards->push_back(EResponer);
            }
            else if (currentcase == 6)
            {
                visitor visitor(tempfname, tempsname, tempaccess, tempcid);
                cards->push_back(visitor);
            }
            currentcase = 0;
        } while (!userfile.eof());
        userfile.close(); //close file
        if (DEBUG == 1)
        {
            for (int j = 0; j < cards->size(); j++)
            {
                cout << cards->at(j).getName() << cards->at(j).getcollegeID() << endl;
            }
            _getch();
        }
    }
    else
    {
        cerr << "File not found";
        _getch();
    }
}
       

 
void refreshfile() {
   
    roomfile.open("rooms.txt"); // open file

    if (roomfile.is_open())
    {
        cout << "roomfile open";
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
                //ems.registerObs(&lecturehall);
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

        if (DEBUG == 1) 
        {
            for (int i = 0; i < rooms->size(); i++)
            {
                cout << rooms->at(i).getroomName() << " " << rooms->at(i).getRoomAccess() << endl;
            }
            _getch();
        }
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

string currentDate()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t in_time_t = chrono::system_clock::to_time_t(now);
    tm local_tm; 
    localtime_s(&local_tm, &in_time_t); char buffer[11]; // Buffer to hold the date string 
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local_tm); 
    return string(buffer);
}

void writeAccesslog(string roomname, string accessedby, string result, bool state)
{
    string date = currentDate();
    string logfileName = "room_access_log_" + date + ".txt";

    string emstate;
    if (state == true)
    {
        emstate = " Emergency";
    }
    else
    {
        emstate = " All clear";
    }

    fstream log;
    log.open(logfileName, ios_base::app);
    if (log.is_open())
    {
        log << "Room: " << roomname << " Accessed by: " << accessedby << " on " << currentDate() << " Access: " << result << " State:" << emstate << endl;
        if (DEBUG == 1)
        {
            cout << "Log has been written";
            _getch();
        }
        log.close();
    }
    else
    {
        cerr << "unable to open log";
    }
}

string login;
// objects
manager mainman;
student stu("", "", 0, 0);
staffMember staff("", "", 0,0);
cleaner cClean("", "", 0,0);
security secGuard("", "", 0,0);
EResponer emerGuest("", "", 0,0);
visitor guest("", "", 0,0);


int roomtype = 0;
string roomname;
int type;
string roomlookup;
 

int main()
{ 
    srand(time(0));
    int newcollegeID = rand() % 900000 + 100000;// generate random 6 digit number
    refreshfile();
    refreshusers();
    mainman.setName("Phil","Monk"); // first name is login
   
    
    
    

    // user chooses function 

    
    do
    { HOME:
        clrscr();
        cout << "welcome to the college door entry system system" << endl;
        cout << "Select function: (1) Enter room, (2) Login to setup or (0) to exit: ";
       // cout << "Currently logged in as: " << login; //test login status
        cin >> type;
        if (type == 1)
        {
            cout << "Enter college id";
            int idattempt;
            cin >> idattempt;
            bool idfound = false;
            for (int num = 0; num < cards->size(); num++)
            {
                //cout << endl << idattempt;
                int currentcard = cards->at(num).getcollegeID();
                while (idattempt == currentcard)
                {
                    idfound = true;
                    cout << "Enter room number: (ks225)";
                    cin >> roomlookup;

                    bool roomfound = false;
                    for (int i = 0; i < rooms->size(); i++)
                    {

                        string currentRoom = rooms->at(i).getroomName();                  
                        
                       
                        if (roomlookup == currentRoom)
                        {
                            bool currentstate = rooms->at(i).isEmergency();
                            

                            roomfound = true;
                            //cout << "loop " << i;
                           
                             if(currentstate == true && cards->at(num).getAccessLevel() != 6 || currentstate == false && cards->at(num).getAccessLevel() == 6)
                            {
                                cout << "Access denied";
                                writeAccesslog(roomlookup, cards->at(num).getfullName(), " Denied ",rooms->at(i).isEmergency());
                                idattempt = 0;
                                roomlookup = "";
                                _getch();
                                goto HOME;
                            }
                             else if (cards->at(num).getAccessLevel() >= rooms->at(i).getRoomAccess())
                            {
                                rooms->at(i).grantAccess();
                                writeAccesslog(roomlookup, cards->at(num).getfullName(), " Granted ",rooms->at(i).isEmergency());
                                idattempt = 0;
                                roomlookup = "";
                                _getch();
                                break;
                            }


                        }
                        else
                            continue;


                    }
                    //room not found
                    if (!roomfound)
                    {
                        try {
                            throw runtime_error("Room not found");
                        }
                        catch (const runtime_error& e)
                        {
                            cerr << "Caught exception: " << e.what() << endl;
                        }
                    }


                }
                
            }
                // id not found
                if (!idfound)
                {
                    try {
                        throw runtime_error("ID not found");
                    }
                    catch (const runtime_error& e)
                    {
                        cerr << "Caught exception: " << e.what() << endl;
                        _getch();
                    }
                }
        }           
    
        else if (type == 2) // setup new rooms, students or set emergency state to txt file 
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
                    cout << "1 user setup, 2 emergency, 3 room setup, 0 to go back";
                    cin >> choice;
                    clrscr();
                    //new cardholder
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
                            stu.setCollegeID(newcollegeID);
                            mainman.addUser(stu.getfullName(), stu.getAccessLevel(),stu.getcollegeID());
                            cards->push_back(stu);
                            break;

                        case 2:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            staff.setName(tempfname, tempsname);
                            staff.setAccessLevel(choice);
                            staff.setCollegeID(newcollegeID);
                            mainman.addUser(staff.getfullName(), staff.getAccessLevel(),staff.getcollegeID());
                            cards->push_back(staff);
                            break;

                        case 3:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            cClean.setName(tempfname, tempsname);
                            cClean.setAccessLevel(choice);
                            cClean.setCollegeID(newcollegeID);
                            mainman.addUser(cClean.getfullName(), cClean.getAccessLevel(),cClean.getcollegeID());
                            cards->push_back(cClean);
                            break;

                        case 4:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            secGuard.setName(tempfname, tempsname);
                            secGuard.setAccessLevel(choice);
                            secGuard.setCollegeID(newcollegeID);
                            mainman.addUser(secGuard.getfullName(), secGuard.getAccessLevel(),secGuard.getcollegeID());
                            cards->push_back(secGuard);
                            break;
                        case 5:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            guest.setName(tempfname, tempsname);
                            guest.setAccessLevel(choice);
                            guest.setCollegeID(newcollegeID);
                            mainman.addUser(guest.getfullName(), guest.getAccessLevel(),guest.getcollegeID());
                            break;
                        case 6:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            emerGuest.setName(tempfname, tempsname);
                            emerGuest.setAccessLevel(choice);
                            emerGuest.setCollegeID(1);
                            mainman.addUser(emerGuest.getfullName(), emerGuest.getAccessLevel(),emerGuest.getcollegeID());
                            cards->push_back(emerGuest);
                            break;

                        }
                    }
                    //emergency state
                    else if (choice == 2)
                    {
                        char emergency;
                        cout << "Change emergency State? Y/N";
                        cin >> emergency;
                        //set emergency state
                        if (emergency == 'y')
                            for (int emr = 0; emr < rooms->size(); emr++)
                            {
                                rooms->at(emr).updateRoomEmerStat();
                            }
                        else if (emergency == 'n')
                            goto HOME;


                        /*//trying to use observer but unable to get it to work
                        if (emergency == 'y')
                        ems.setstate(TRUE);
                        else if (emergency == 'n')
                            ems.setstate(FALSE);
                            break;*/
                    }  
                    //new room
                    else if (choice == 3)
                    {
                        cout << "enter room type lecturehall (1), Staffroom (2), Teachingroom (3),Secureroom (4) Go back (0): ";
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
                            
                        }
                    }
                    //log out
                    else if (choice == 0)
                    {
                        login = "Logged out";
                    }
                }

            }
            else
                cout << "access denied";
        
           

            
        }

    } while (type != 0);
}
