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
#include <algorithm>
#include <sstream>

using namespace std;

#define DEBUG 0
#define ESC 27
#define MAXROOMS 20
#define MAXUSERS 100

//function to get current date
string currentDate()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t in_time_t = chrono::system_clock::to_time_t(now);
    tm local_tm;
    localtime_s(&local_tm, &in_time_t); char buffer[11]; // Buffer to hold the date string 
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local_tm);
    return string(buffer);
}

//observer setup (Not working)
class Observer
{
public:
    virtual void update(BOOL emstate) = 0;
};
//emergencystate (Not working)
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
    
   
    
public: 
    string roomName;
    string cleanstart = "";
    string cleanend = "";
    bool inEmergency = false;
    int accesslevel;
    string roomtype;
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
    string getRoomtype()
    {
        return roomtype;
    }
    string getcleaningstime()
    {
        return cleanstart;
    }
    string getcleaningetime()
    {
        return  cleanend;
    }
};

//lecture hall
 class lectureHall : public room 
 {


 public:
     string cleanstart = "07:00 AM";
     string cleanend = "08:00 AM";
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
     void setRoomtype()
     {
         roomtype = "Lecture Hall";
     }
 };
 //lecture hall constructor
 lectureHall::lectureHall(string x, int y)
 {
     setRoomtype();
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
      string cleanstart = "07:00 AM";
      string cleanend = "08:00 AM";
      void setAccessLevel(int y) 
      {
          accesslevel = y;
      }

     void cleaningTime()
     {

     }
     void setRoomtype()
     {
         roomtype = "Staff room";
     }
     staffRoom(string x, int y);
 };
 //staffroom constructor
 staffRoom::staffRoom(string x, int y)
 {
     setRoomtype();
     setRoomname(x);
     setAccessLevel(y);
 }
 //teaching room 
 class teachingRoom : public room
 { public:
     
     string cleanstart = "07:00 AM";
     string cleanend = "08:00 AM";
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
     void setRoomtype()
     {
         roomtype = "Teaching room";
     }
     teachingRoom(string x, int y);
 };
 //teaching room constructor
 teachingRoom::teachingRoom( string x, int y)
 {
     setRoomtype();
     setRoomname(x);
     setAccessLevel(y);
 }
 //secure room 
 class secureRoom : public room
 { public:
     string cleanstart = "";
     string cleanend = "";
     void update(BOOL emstate) override
     {
         inEmergency = emstate;
     }
     void setAccessLevel(int y) 
     {
         accesslevel = y;
     }
     void setRoomtype()
     {
         roomtype = "Secure Room";
     }
     secureRoom(string x, int y);
 };
 //secure room constructor
 secureRoom :: secureRoom(string x, int y)
 {
     setRoomtype();
     setRoomname(x);
     setAccessLevel(y);
 }



 // cardholder setup
 

class cardHolder
{

private:
    string fname;
    string sname;
    
    int accessLevel;

public:
int collegeID;
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
    string getSName()
    {
        return sname;
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
    bool Cleaningtime(const string& startTimeStr, const string& endTimeStr)
    {
        tm startTime = {};
        tm endTime = {};
        istringstream ssStartTime(startTimeStr);
        istringstream ssEndTime(endTimeStr);
        ssStartTime >> get_time(&startTime, "%I:%M %p");
        ssEndTime >> get_time(&endTime, "%I:%M %p");
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        tm now_tm; 
        localtime_s(&now_tm, &now_time);
        return mktime(&now_tm) >= mktime(&startTime) && mktime(&now_tm) <= mktime(&endTime);
    }

};
// manager
class manager : public cardHolder 
{
    public:
        void addUser(string name,int accesslevel, int id)
        {
            fstream userfile;
            userfile.open("ID_Card_List.txt", ios::app);
            userfile << name << " "<< accesslevel << " " << id ;
            userfile.close();


        }

        void writerooms(string name, int access)
        {
            fstream roomfile;
            roomfile.open("rooms.txt", ios::app); //append to file 

            if (roomfile.is_open())
            {
                roomfile  << name << " " << access ;
            }
            else
            {
                cerr << "File not found";
                _getch();
            }

            roomfile.close();
        }

        void updateUser(string olduser, string filename, string newuser, int accesslevel,int id)
        {
            removeUser(filename, olduser);
            addUser(newuser,accesslevel,id);
        }

        void updateRoom(string oldroom, string filename, string newroom, int access)
        {
            removeRoom(filename,oldroom);
            writerooms(newroom,access);
        }

        void removeUser(const string& filename, const string user)
        {
            ifstream infile(filename);
            ofstream tempfile("temp.txt");
            string line;

            if (infile.is_open() && tempfile.is_open())
            {
                while (getline(infile, line))
                {
                    if (line.find(user) == string::npos) 
                    {
                        tempfile << line << endl;
                    }
                }
                infile.close();
                tempfile.close();

                remove(filename.c_str());
                rename("temp.txt", filename.c_str());
            }
            else
            {
                cerr << "File not found" << endl;
            }

        }

        void removeRoom(const string& filename, const string room)
        {
            ifstream infile(filename);
            ofstream tempfile("temp.txt");
            string line;

            if (infile.is_open() && tempfile.is_open())
            {
                while (getline(infile, line))
                {
                    if (line.find(room) == string::npos)
                    {
                        tempfile << line << endl;
                    }
                }
                infile.close();
                tempfile.close();

                remove(filename.c_str());
                rename("temp.txt", filename.c_str());
            }
            else
            {
                cerr << "File not found" << endl;
            }

        }

        void viewLog()
        {
            string fileName = "room_access_log_"+ currentDate() + ".txt";
            ifstream inFile(fileName); 
            string line; 
            if (inFile.is_open()) 
            { 
                while (getline(inFile, line)) 
                { 
                    cout << line << std::endl; 
                } 
                inFile.close(); 
            }
            else { cerr << "Unable to open file." << std::endl; }
        }

        bool grantAccess()
        {
            return true;
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

vector <room> rooms; // vector of room on system
vector <room>* ptrrooms = &rooms;
vector <cardHolder> cards; //vector of cardholders on system
vector <cardHolder>* ptrcards = &cards;
fstream userfile;


emergencystate ems;

//function to refresh list of users from file
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
                ptrcards->push_back(student);

            }
            else if (currentcase == 2)
            {
                staffMember staffMember(tempfname, tempsname, tempaccess, tempcid);
                ptrcards->push_back(staffMember);

            }
            else if (currentcase == 3)
            {
                cleaner cleaner(tempfname, tempsname, tempaccess, tempcid);
                ptrcards->push_back(cleaner);

            }
            else if (currentcase == 4)
            {
                security security(tempfname, tempsname, tempaccess, tempcid);
                ptrcards->push_back(security);

            }
            else if (currentcase == 5)
            {
                EResponer EResponer(tempfname, tempsname, tempaccess,tempcid);
                ptrcards->push_back(EResponer);
            }
            else if (currentcase == 6)
            {
                visitor visitor(tempfname, tempsname, tempaccess, tempcid);
                ptrcards->push_back(visitor);
            }
            currentcase = 0;
        } while (!userfile.eof());
        userfile.close(); //close file
        if (DEBUG == 1)
        {
            for (int j = 0; j < ptrcards->size(); j++)
            {
                cout << ptrcards->at(j).getName() << ptrcards->at(j).getcollegeID() << endl;
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
       

 // function to refresh list of rooms from file
void refreshfile() {
    fstream roomfile;
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

            // room assigned by access level
            if (currentcase == 1)
            {

                lectureHall lecturehall(tempname, tempaccess);
                ptrrooms->push_back(lecturehall);
                //ems.registerObs(&lecturehall); // observer function not working 
            }
            else if (currentcase == 2)
            {
                staffRoom staffroom(tempname, tempaccess);
                ptrrooms->push_back(staffroom);

            }
            else if (currentcase == 3)
            {
                teachingRoom teachingroom(tempname, tempaccess);
                ptrrooms->push_back(teachingroom);

            }
            else if (currentcase == 4)
            {
                secureRoom secureroom(tempname, tempaccess);
                ptrrooms->push_back(secureroom);

            }

        } while (!roomfile.eof());
        roomfile.close(); //close file

        if (DEBUG == 1) // print out list of incoming rooms
        {
            for (int i = 0; i < ptrrooms->size(); i++)
            {
                cout << ptrrooms->at(i).getroomName() << " " << ptrrooms->at(i).getRoomAccess() << endl;
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




//function to write to acces log
void writeAccesslog(string roomname, string accessedby, string result, bool state)
{
    string date = currentDate();
    string logfileName = "room_access_log_" + date + ".txt"; // create room access log file

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
    log.open(logfileName, ios_base::app); // open file
    if (log.is_open())
    {
        log << "Room: " << roomname << ", Accessed by: " << accessedby << " on " << currentDate() << ", Access: " << result << ", State:" << emstate << endl; //write line to file
        if (DEBUG == 1)
        {
            cout << "Log has been written"; 
            _getch();
        }
        log.close(); //close file
    }
    else
    {
        cerr << "unable to open log"; //error handle
    }
}

bool compareByName(string a, string  b) { return a < b; }


// objects
manager mainman;
student stu("", "", 0, 0);
staffMember staff("", "", 0,0);
cleaner cClean("", "", 0,0);
security secGuard("", "", 0,0);
EResponer emerGuest("", "", 0,0);
visitor guest("", "", 0,0);
//varibles
int roomtype = 0;
string roomname;
int type;
string roomlookup;
vector <string> persons;
string login;
bool loggingin = false;

int main()
{
    srand(time(0));
    int newcollegeID = rand() % 900000 + 100000;// generate random 6 digit number
    refreshfile();
    refreshusers();
    mainman.setName("Phil", "Monk"); // first name is login
    mainman.setAccessLevel(6);
    mainman.setCollegeID(10);
   //mainman.addUser(mainman.getfullName(), mainman.getAccessLevel(), mainman.getcollegeID()); // run this line of code to add first manager to card id only needed on intial setup.
    ptrcards->push_back(mainman);
    int flag = 0;

    // user chooses function 


    do
    {
    HOME:
        clrscr();
        cout << "welcome to the college door entry system system" << endl;
        cout << "Select function:" << endl<< "(1) Enter room," << endl << "(2) Login to setup," << endl << "(3) View available rooms," << endl << "(4) view current card holders" << endl << "(0) to exit : ";
        // cout << "Currently logged in as: " << login; //test login status
        cin >> type;
        //simulate enter room
        if (type == 1)
        {
            cout << "Enter college id: ";
            int idattempt;
            cin >> idattempt;
            bool idfound = false;
            for (int num = 0; num < ptrcards->size(); num++)
            {
                //cout << endl << idattempt;
                int currentcard = ptrcards->at(num).getcollegeID();
                while (idattempt == currentcard)
                {
                    idfound = true;
                    cout << "Enter room number: (ks225) ";
                    cin >> roomlookup;

                    bool roomfound = false;
                    for (int i = 0; i < ptrrooms->size(); i++)
                    {

                        string currentRoom = ptrrooms->at(i).getroomName();


                        if (roomlookup == currentRoom)
                        {
                            bool currentstate = ptrrooms->at(i).isEmergency();


                            roomfound = true;
                            //cout << "loop " << i;
                            if (ptrcards->at(num).getAccessLevel() == 3 && !ptrcards->at(num).Cleaningtime(ptrrooms->at(i).getcleaningstime(), ptrrooms->at(i).getcleaningetime()))
                            {
                                cout << "Not Cleaning time";
                                writeAccesslog(roomlookup, ptrcards->at(num).getfullName(), " Denied Not Cleaning time", ptrrooms->at(i).isEmergency());
                                _getch();
                                goto HOME;
                            }
                            else
                            {
                                if (currentstate == true && ptrcards->at(num).getAccessLevel() != 7 || currentstate == false && ptrcards->at(num).getAccessLevel() == 7)
                                {
                                    cout << "Access denied";
                                    writeAccesslog(roomlookup, ptrcards->at(num).getfullName(), " Denied ", ptrrooms->at(i).isEmergency());
                                    idattempt = 0;
                                    roomlookup = "";
                                    _getch();
                                    goto HOME;
                                }
                                else if (ptrcards->at(num).getAccessLevel() >= ptrrooms->at(i).getRoomAccess())
                                {
                                    ptrrooms->at(i).grantAccess();
                                    writeAccesslog(roomlookup, ptrcards->at(num).getfullName(), " Granted ", ptrrooms->at(i).isEmergency());
                                    idattempt = 0;
                                    roomlookup = "";
                                    _getch();
                                    break;
                                }
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

        // setup new rooms, students, set emergency state or view daily log
        else if (type == 2)
        {
            clrscr();
            cout << "Enter login name: " << endl;
            cin >> login;
            
            for (int manid = 0; manid < cards.size(); manid++)
            {
                if (login == cards.at(manid).getName() && cards.at(manid).getAccessLevel() == 6)
                {
                    loggingin = mainman.grantAccess();
                    break;
                }
            }
            if (loggingin == true)  // login required
            {
                cout << "Access granted " << endl;

                while (loggingin)
                {
                    int choice;
                    string tempfname;
                    string tempsname;
                    cout << "1 user setup, " << endl <<"2 emergency," << endl << "3 room setup," <<endl << "4 update room," << endl << "5 remove room," << endl << "6 remove user," << endl << "7 update user, " << endl << "8 view daily entry log," << endl << " 0 to go back: ";
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
                            mainman.addUser(stu.getfullName(), stu.getAccessLevel(), stu.getcollegeID());
                            ptrcards->push_back(stu);
                            break;

                        case 2:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            staff.setName(tempfname, tempsname);
                            staff.setAccessLevel(choice);
                            staff.setCollegeID(newcollegeID);
                            mainman.addUser(staff.getfullName(), staff.getAccessLevel(), staff.getcollegeID());
                            ptrcards->push_back(staff);
                            break;

                        case 3:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            cClean.setName(tempfname, tempsname);
                            cClean.setAccessLevel(choice);
                            cClean.setCollegeID(newcollegeID);
                            mainman.addUser(cClean.getfullName(), cClean.getAccessLevel(), cClean.getcollegeID());
                            ptrcards->push_back(cClean);
                            break;

                        case 4:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            secGuard.setName(tempfname, tempsname);
                            secGuard.setAccessLevel(choice);
                            secGuard.setCollegeID(newcollegeID);
                            mainman.addUser(secGuard.getfullName(), secGuard.getAccessLevel(), secGuard.getcollegeID());
                            ptrcards->push_back(secGuard);
                            break;
                        case 5:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            guest.setName(tempfname, tempsname);
                            guest.setAccessLevel(choice);
                            guest.setCollegeID(newcollegeID);
                            mainman.addUser(guest.getfullName(), guest.getAccessLevel(), guest.getcollegeID());
                            break;
                        
                        case 6:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            mainman.setName(tempfname, tempsname);
                            mainman.setAccessLevel(6);
                            mainman.setCollegeID(10);
                            mainman.addUser(mainman.getfullName(), mainman.getAccessLevel(), mainman.getcollegeID());
                            ptrcards->push_back(mainman);
                            break;
                        case 7:
                            cout << "enter new user's name: ";
                            cin >> tempfname >> tempsname;
                            emerGuest.setName(tempfname, tempsname);
                            emerGuest.setAccessLevel(choice);
                            emerGuest.setCollegeID(1);
                            mainman.addUser(emerGuest.getfullName(), emerGuest.getAccessLevel(), emerGuest.getcollegeID());
                            ptrcards->push_back(emerGuest);
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
                            for (int emr = 0; emr < ptrrooms->size(); emr++)
                            {
                                ptrrooms->at(emr).updateRoomEmerStat();
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
                        roomname = "";
                        cout << "enter room type lecturehall (1), Staffroom (2), Teachingroom (3),Secureroom (4) Go back (0): ";
                        cin >> roomtype; // roomtype will determine which kind of room will be created
                        RETRY:
                        cout << "enter room name: ";
                        cin >> roomname;
                        bool roomis = false;
                        for (int roomexists = 0; roomexists < rooms.size(); roomexists++)
                        {
                            if (roomname == rooms.at(roomexists).getroomName())
                            {
                                roomis = true;
                                break;
                            }
                            else
                                roomis = false;

                        }
                        if (roomis == true)
                        {
                            cout << "That room already exists ";
                            _getch();
                            clrscr();
                            goto RETRY;
                        }
                        if (roomtype == 1)
                        {
                            
                            lectureHall lecturehall(roomname, roomtype);
                            ptrrooms->push_back(lecturehall);
                            mainman.writerooms(roomname, roomtype);
                            if (DEBUG == 1)
                            {
                                for (int i = 0; i < ptrrooms->size(); i++)
                                {
                                    cout << ptrrooms->at(i).getroomName() << " " << ptrrooms->at(i).getRoomAccess() << endl;
                                }
                            }

                        }
                        else if (roomtype == 2)
                        {
                            
                            staffRoom staffroom(roomname, roomtype);
                            ptrrooms->push_back(staffroom);
                            mainman.writerooms(roomname, roomtype);
                            if (DEBUG == 1)
                            {
                                for (int i = 0; i < ptrrooms->size(); i++)
                                {
                                    cout << ptrrooms->at(i).getroomName() << " " << ptrrooms->at(i).getRoomAccess() << endl;
                                }
                            }

                        }
                        else if (roomtype == 3)
                        {
                           
                            teachingRoom teachingroom(roomname, roomtype);
                            ptrrooms->push_back(teachingroom);
                            mainman.writerooms(roomname, roomtype);
                            if (DEBUG == 1)
                            {
                                for (int i = 0; i < ptrrooms->size(); i++)
                                {
                                    cout << ptrrooms->at(i).getroomName() << " " << ptrrooms->at(i).getRoomAccess() << endl;
                                }
                            }

                        }
                        else if (roomtype == 4)
                        {
                            
                            secureRoom secureroom(roomname, roomtype);
                            ptrrooms->push_back(secureroom);
                            mainman.writerooms(roomname, roomtype);
                            if (DEBUG == 1)
                            {
                                for (int i = 0; i < ptrrooms->size(); i++)
                                {
                                    cout << ptrrooms->at(i).getroomName() << " " << ptrrooms->at(i).getRoomAccess() << endl;
                                }
                            }

                        }
                        else if (roomtype == 0)
                        {

                            loggingin = false;

                        }
                    }
                    //update room
                    else if (choice == 4)
                    {
                        roomname = "";
                        int roomaccess;
                        cout << "Enter room name to be updated: ";
                        string newroomname;
                        int newaccess;
                        string roomnameup;
                        cin >> roomnameup;
                        for (int rmup = 0; rmup < rooms.size(); rmup++)
                        {
                            if (roomnameup == rooms.at(rmup).getroomName())
                            {
                                roomname = rooms.at(rmup).getroomName();
                                roomaccess = rooms.at(rmup).getRoomAccess();

                            }
                        }

                        cout << "new room name";
                        cin >> newroomname;
                        cout << "new access";
                        cin >> newaccess;

                        if (newroomname != "0")
                        {
                            roomname = newroomname;
                        }
                        
                        if (to_string(newaccess) != "0")
                        {
                            roomaccess = int(newaccess);
                        }


                        
                        mainman.updateRoom(roomnameup, "rooms.txt", roomname, roomaccess);
                        rooms.clear();
                        ptrrooms->clear();
                        refreshfile();

                        goto HOME;
                    }
                    // remove room
                    else if (choice == 5)
                    {
                        cout << "enter room to be removed";
                        string roomremove;
                        cin >> roomremove;
                        mainman.removeRoom("rooms.txt", roomremove);
                        rooms.erase(remove_if(rooms.begin(), rooms.end(), [&roomremove](const room& rooms) {return rooms.roomName == roomremove; }), ptrrooms->end());
                    }
                    //remove user
                    else if (choice == 6)
                    {
                        cout << "Enter user id to be removed: ";
                        int idremove;
                        cin >> idremove;
                        mainman.removeUser("ID_Card_List.txt",to_string(idremove));
                        cards.erase(remove_if(cards.begin(), cards.end(), [&idremove](const cardHolder& cards) {return cards.collegeID == idremove; }),ptrcards->end());
                    }
                    //update users
                    else if (choice == 7)
                    {
                        string userf,users;
                        int userid;
                        int useraccess;
                        cout << "Enter user id to be updated: ";
                        int idupdate;
                        string newfirstname,newsurname;
                        int newid;
                        int newaccess;
                        cin >> idupdate;
                        for (int idup  = 0; idup < cards.size(); idup++)
                        {
                            if (idupdate == cards.at(idup).getcollegeID())
                            {
                                 userf = cards.at(idup).getName();
                                 users = cards.at(idup).getSName();
                                 userid = cards.at(idup).getcollegeID();
                                 useraccess = cards.at(idup).getAccessLevel();

                            }
                        }
                        
                        cout << "new 1st name";
                        cin >> newfirstname;
                        cout << "new 2nd name";
                        cin >> newsurname;
                        cout << "new id";
                        cin >> newid;
                        cout << "new access";
                        cin >> newaccess;

                        if (newfirstname != "0")
                        {
                            userf = newfirstname;
                        }
                        if (newsurname != "0")
                        {
                            users = newsurname;
                        }
                        if (to_string(newid)!= "0")
                        {
                            userid = int(newid);
                        }
                        if (to_string(newaccess) != "0")
                        {
                            useraccess = int(newaccess);
                        }


                        string user = userf + " " + users;
                        mainman.updateUser(to_string(idupdate), "ID_Card_List.txt",user,useraccess,userid);
                        cards.clear();
                        ptrcards->clear();
                        refreshusers();

                        goto HOME;

                    }
                    // view daily entry log
                    else if (choice == 8)
                    {
                        mainman.viewLog();
                        _getch();
                        clrscr();
                        continue;
        }
                    //log out
                    else if (choice == 0)
                    {
                        loggingin = false;
                    }
                }

            }
            else
                cout << "access denied";




        }
        
        //display current rooms
        else if (type == 3)
        {
            cout << "Current rooms:" << endl;// Note: blank line in .txt file will cause last line to be read again
            for (int roominfo = 0; roominfo < ptrrooms->size(); roominfo++)// loop to print out current rooms in college
            {
                cout << "Room: " << ptrrooms->at(roominfo).getroomName() << " " << "\tAccess Required: " << ptrrooms->at(roominfo).getRoomAccess() << "\tRoom type: " << ptrrooms->at(roominfo).getRoomtype() << endl;
            }
            _getch();
        }
        
        //display current cardholders
        else if (type == 4)
        {
            for (int findper = 0; findper < ptrcards->size(); findper++)
            {

                persons.push_back(ptrcards->at(findper).getfullName()); //create vector of fullnames

            }
            {
                sort(persons.begin(), persons.end(), compareByName); // sorting users by name alphabetically
                cout << "Current Members of college " << endl;
                if (DEBUG == 1) {
                    for (int member = 0; member < persons.size(); member++)
                    {
                        cout << persons.at(member) << endl;
                    }
                }
               
                    for (int person = 0; person < ptrcards->size(); person++)
                    {
                        string target = persons.at(person);
                        for (int id = 0; id < ptrcards->size(); id++)
                        {
                            if (ptrcards->at(id).getfullName() == target && ptrcards->at(id).getfullName() != "Emergency responder") //find remaining data to be printed sorted alphabeticly 
                            {
                                cout << "Name: " << ptrcards->at(id).getfullName() << "\t ID: " << ptrcards->at(id).getcollegeID() << "\t Access Level: " << ptrcards->at(id).getAccessLevel() << endl;
                            }
                            else
                                continue;
                        }

                    }
                    persons.clear(); // emptying vector avoids duplication print error

               
                _getch();
            }
        }
        
        
    } while (type != 0);
}
