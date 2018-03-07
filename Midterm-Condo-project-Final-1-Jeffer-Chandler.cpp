/*****************************************
Computer science midterm project Condo data base
Jeffer Jingfei P
ICS4U1
Dr.N
Jan.11th, 2017
Condo Data Base:
This is simple information system project to keep track of current occupants in a building. It
requires nice UI and the following functions:
1. Add Records
2. List Records
3. Modify Records
4. Delete Records
5. Exit Program
******************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>


using namespace std;

//a function to check if an input is an integer
int checkint(){
    int a;
    cin >> a;
    while(cin.fail()){
        cout<<"\tPlease enter an integer: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> a;
        cout<<endl;
    }
    return a;
}

class Condo{
	public:
	int **roomMatrix;
	//boolean variable to keep track of if the record has been deleted
	bool record;
	string name;
	int floor,room, beds;
    float cost;
    string enterDate;

    Condo();
    //a method to add records
	void addRecord(int f, int r);
	void listRecord(int a);
	void modifyRecord(int num, int f, int r);
	void deleteRecord();
	//use pass by reference to pass the text file to method
	void printText(ofstream *file, int a);
	void printText2(ofstream *file, int floor,int room);
};

//constructer of the class to set the record variable to false.
Condo::Condo(){
    record = false;
}

//this method set the delete status to true when the user delete an occupant
void Condo::deleteRecord(){
    record = false;
}

//Method to print occupant's information on a text file
void Condo::printText(ofstream *file,int a){
	*file<<setw(3)<<a<<setw(20)<<name<<setw(8)<<floor<<setw(8)<<room<<setw(20)<<enterDate<<setw(8)<<cost<<setw(8)<<beds<<endl;
}

//method to print the avaliability matrix
void Condo::printText2(ofstream *file, int floor, int room){
	*file<<"\n\nCurrent Avalibility (\"1\" represents occuiped \"0\" represents vacant:"")"<<endl;
	for (int a=0;a<floor;a++){
		*file<<setw(10)<<"Floor "<<(a+1)<<": ";
    	for (int b=0;b<room;b++){
    		*file<<roomMatrix[a][b]<<" | ";
		}
    *file<<"\n";
    }
}
//a method to modify record
void Condo::modifyRecord(int num, int f, int r){
	int option=-1;

	//use a while loop to loop through the options
	if (record = true){
        while (option != 7){
            system("cls");
            cout<<"\n\tPlease indicate which information do you want to change"<<endl;
            cout<<"\n\t1:Name\n\t2:Floor\n\t3:Room\n\t4:Enter Date\n\t5:Bills\n\t6:Beds\n\t7:Finish modification"<<endl;
            option = checkint();

            switch(option){
                case 1:
                    cin.ignore();
                    cout<<"\twhat is the new name of occupant: "<<num<<endl;
                    getline(cin,name);
                    break;

                //modify floor
                case 2:
                    cout<<"\tFloor:"<<endl;
                    floor = checkint();
                    while(floor < 0 || floor > f){
                        cout<<"\tInvalid Input; Please enter a valid floor: ";
                        floor = checkint();
                    }
                    break;

                //modify Room
                case 3:
                    cout<<"\tRoom:"<<endl;
                    room= checkint();
                    while(room < 0 || room > r){
                        cout<<"\tInvalid Input; Please enter a valid room: ";
                        room = checkint();
                    }
                    break;

                //modify Enter Date
                case 4:
                    cout<<"\tEnter date:"<<endl;
                    cin.ignore();
                    getline(cin,enterDate);
                    break;

                //modify bills
                case 5:
                    cout<<"\tAmount to pay:"<<endl;
                    cost = checkint();
                    break;

                //modify the number of beds in the room
                case 6:
                    cout<<"\tNumber of beds:";
                    beds = checkint();
                    break;

                case 7:
                    break;

                default:
                    cout<<"\tInvalid Choice. Please choose one of the options listed above";
                    Sleep(3000);
                    break;
            }
        }
	}
	else{
        cout<<"\tThis user does not exist";
	}
}
//a method to add records using provided floor and room number
void Condo::addRecord(int f, int r){
	string user;
    floor=f;
	room=r;
	cin.ignore();

	cout<<"\tWhat is the name of the occupant"<<endl;
	getline (cin,user);
	name=user;
	cout<<"\tEnter date:\n";
	getline (cin,enterDate);
	cout<<"\tHow much does this occupant need to pay?"<<endl;
	cost = checkint();
	cout<<"\tHow many beds in this room?"<<endl;
	beds = checkint();
	record = true;
	}

//a method to list the records
void Condo::listRecord(int a){
    if (record == true){
        cout<<setw(3)<<a<<setw(20)<<name<<setw(8)<<floor<<setw(8)<<room<<setw(20)<<enterDate<<setw(8)<<cost<<setw(8)<<beds<<endl;
    }
}

//create a room subclass to Condo
class Room: public Condo{
	public:
	bool checkAva(int f,int r);
	void set(int floor,int room);
	void show(int floorNum, int roomNum);
};

//to show the occupancy of the condo
void Room::show(int floorNum, int roomNum){
	for (int a=0;a<floorNum;a++){
		cout<<"Floor "<<(a+1)<<": ";
		for (int b=0;b<roomNum;b++){
		cout<<roomMatrix[a][b]<<" | ";
		}
	cout<<"\n";
	}

}
//to setup the avalibility matrix
void Room::set(int floorNum, int roomNum){
	roomMatrix = new int *[floorNum];
	for (int a=0;a<floorNum;a++)
	roomMatrix[a] = new int [roomNum];

	//set the martix to 0 for rooms that haven't been occupied
	for (int a=0;a<floorNum;a++){
		roomMatrix[a][0]=0;
		for (int b=0;b<roomNum;b++)
		roomMatrix[a][b]=0;
	}
}

//checks if a room is occupied
bool Room::checkAva(int f,int r){
	bool occupied;
	int check=roomMatrix[f-1][r-1];
	if(check==1)occupied=true;
	if (check==0)occupied=false;
	return occupied;
}

//functions:
//this function is created to ask for a input in order to prevent clear screen from skipping any important screens.
void pause(void){
	string anykey;
	cout<<"\n\nPRESS ANY KEY TO CONTINUE:"<<endl;
	cin.ignore();
	getline(cin,anykey);
}

//a function to set up the condo
void setup(int *f, int *r){
	cout<<"\tHello user, welcome to the menu of Condo infomation system\n\n";
    cout<<"\tHow many floors are in the condo?\n";
    *f = checkint();
    cout<<"\tHow many rooms in a floor;\n";
    *r = checkint();
    system("cls");
    cout<<"\tNow the system is set. You have a few options\n\n";
}

//a function to prepare for adding records. Error checking
void preAdd(int *f,int *r,int pointer,int floor,int room){
	cout<<"\n\tThis is the "<<pointer<<" th person you are adding"<<endl;
			cout<<"\n\tWhich floor would you like to book?"<<endl;
			*f = checkint();
			cout<<"\tWhich room on this floor"<<endl;
			*r = checkint();

			//check if the room and floor number are within range
			if (*f>floor or *r>room){
				cout<<"\tThe floor and room number you entered do not exist"<<endl;
				pause();
			}
}

int main(void){
    //create a int variable to let user select options
    int floor, room, userFloor,userRoom, length, option=1;
    int pointer=1;

    //using passing by reference to set up the condo system
	setup(&floor,&room);
    pause();

	//create the class variables
	length = 2*floor*room;
	Room Rooms[length];
	Room Standard;
	Standard.set(floor,room);


    while(option != 5){
    	system("cls");
    	cout<<setw(45)<<"Management Menu"<<endl;
        cout<<"\t1. Add Records\n\t2. List Records\n\t3. Modify Records\n\t4. Delete Records\n\t5. Exit Program and create a text file of the record"<<endl;
        option = checkint();
        cout<<endl;
        switch(option){
        case 1:
            {
        	system("cls");
			preAdd(&userFloor,&userRoom,pointer,floor,room);

			if (userFloor<(floor+1) && userRoom<(room+1)){
			//checks if this room is already occupied
			if (Standard.checkAva(userFloor,userRoom)==true){
				cout << "\tThis room is already occupied. This is the avalibility of Rooms\n" << endl;
				Standard.show(floor,room);
				cout<<endl;
				pause();
				break;
			}

			//update the info if the room is not occupied
			if ((Standard.checkAva(userFloor,userRoom)==false) || (Rooms[pointer].record == false)){
			//set the variables
                Rooms[pointer].addRecord(userFloor,userRoom);
                //save record on the room matrix
                Standard.roomMatrix[userFloor-1][userRoom-1]=1;

                //increase the pointer for the number of occupants
                pointer++;
			}}
			break;
            }

		//option to list record
		case 2:
		    {
			system("cls");
			cout<<setw(45)<<"Record Table"<<endl;
			//formatted output
			cout<<setw(3)<<"#:"<<setw(20)<<"Name:"<<setw(8)<<"Floor:"<<setw(8)<<"Room:"<<setw(20)<<"Enter Date:"<<setw(8)<<"Bills:"<<setw(8)<<"Beds:"<<endl;
			cout<<string(75,'-')<<endl;
			for (int a = 1;a <pointer;a++){
                Rooms[a].listRecord(a);
			}
            cout<<endl;
            //display the avalibility of Condo
            Standard.show(floor,room);
            cout<<endl;
            pause();
            break;

		    }
		//to modify an record
		case 3:
		    {
			system("cls");
			int which;

			cout<<"\twhich occupant do you wish to modify?\n"<<endl;
			//display all the occupants
			for (int a=1;a<pointer;a++){
            	Rooms[a].listRecord(a);
			}

			which = checkint();
			//checks if the occupant already exist:
			if(Rooms[which].record == true){
                    if(Standard.checkAva(Rooms[which].floor,Rooms[which].room)==true){
                        Standard.roomMatrix[Rooms[which].floor-1][Rooms[which].room-1]=0;
                        Rooms[which].modifyRecord(which, floor, room);}
                //update standard

                Standard.roomMatrix[Rooms[which].floor-1][Rooms[which].room-1]=1;
			}
			break;
		    }
		//to delete an record
		case 4:
		    {
		    system("cls");
			int which,delF,delR;
			cout<<"Which occupant do you wish to delete?\n"<<endl;

			//display all the occupants
			for (int a=1;a<pointer;a++){
            	Rooms[a].listRecord(a);
			}
			which = checkint();
			if (Rooms[which].record == true){
                delF=Rooms[which].floor;
                delR=Rooms[which].room;
                Standard.roomMatrix[delF-1][delR-1]=0;
                Rooms[which].deleteRecord();
			}
			else{
			    cout<<"\tThis user does not exist.";
			}
			break;
		    }
		//handle quitting program and printing a text file
		case 5:
		    {
            ofstream myfile;
            myfile.open ("CondoRecord.txt");
            myfile << setw(3)<<"#:"<<setw(20)<<"Name:"<<setw(8)<<"Floor:"<<setw(8)<<"Room:"<<setw(20)<<"Enter Date:"<<setw(8)<<"Bills:"<<setw(8)<<"Beds:"<<endl;
            for (int a = 1; a < pointer;a++){
            		//checks if the object has been deleted
                    if (Rooms[a].record = true){
                        Rooms[a].printText(&myfile,a);
                    }
            }
			Standard.printText2(&myfile,floor,room);
            myfile.close();
            break;
		    }
        default:
            {
            cout<<"\tInvalid Choice. Please choose one of the options listed above";
            Sleep(3000);
            break;
            }
        }
    }

		return 0;
    }

