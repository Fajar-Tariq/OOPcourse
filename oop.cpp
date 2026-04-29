#include<iostream> 
#include<fstream>
using namespace std;
class Device {     //FIRST CLASS
	string name;
	bool isOn;
	int brightness;
public:
	Device()  //CONTRUCTOR
	{
		name = "unknown";
		isOn = false;
		brightness = 50;
    }
	Device(string n, bool on, int light)   //OVERLOADED CONTRUCTOR
	{
		name = n;
		isOn = on;
		if (light >= 0 && light <= 100)
			brightness = light;
		else
			brightness = 50;
	}
	~Device()  //DESTRUCTOR
	{
		cout << " device " << name << " is being removed" << endl;
	}
	void setname(string n) //FOR SETTING THE NAME OF THE DEVICE
	{
		name = n;
	}
	string getname() //FOR GETTING THE NAME OF THE DEVICE
	{
		return name;
	}
	void setbrightness(int b) //SETTING THE BRIGHTNESS OF THE DEVICE
	{
		if (b >= 1 && b <= 100)
			brightness = b;
		else
			cout << "invalid brightness entry" << endl;
	}
	int getbrightness()  //GETTING THE BRIGHTNESS OF THE DEVICE
	{
		return brightness;
	}
	void turnOn() //TURNING THE DEVICE ON
	{
		isOn = true;
	}
	void turnOff() //TURNING THE DEVICE OFF
	{
		isOn =false;
	}
	bool getstatus()const //STATUS OF THE DEVICE WHETHER IT IS ON OR OFF
	{
		return isOn;
	} 
	void showinfo()  //DISPLAY INFO
	{
	   cout << "name:" << name << " status:" << (isOn ? "on" : "off") << " brightness:" << brightness << endl;
	}
	void saveToFile(ofstream& out)
	{
			out << name << " " << isOn << " " << brightness << endl;
	}

	void loadFromFile(ifstream& in) 
	{
			in >> name >> isOn >> brightness;
	}
};
class Room //SECOND CLASS
{
	string roomName;
	Device devices[5];
	int count;
public:
	Room(string n) //CONSTRUCTOR
	{
		roomName = n;
		count = 0;
    }
	~Room() //DESTRUCTOR
	{
		cout << "room " <<roomName << "manager closed" << endl;
    }
	void addDevice(Device d)  //ADDING A DEVICE TO THE ROOM
	{
		if (count < 5)
		{
			devices[count] = d;
			count++;
			ofstream out("devices.txt", ios::app); // append mode
			d.saveToFile(out);
			out.close();

			cout << "device added successfully" << endl;
		}
		else
		{
			cout << "no space avaliable" << endl;
		}
	}
	void showDevices() //SHOW ALL DEVICES IN THE ROOM
	{
		if (count == 0)
		{
			cout << "no devices avaliable" << endl;
			return;
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				devices[i].showinfo();
			}
		}

	}
	int findDevice(string n)   //FINDING ANY DEVICE IN THE ROOM
	{
		for (int i = 0; i < count; i++)
		{
			if (devices[i].getname() == n)
				return i;
		}
		return -1;
	}
	void toggledevice(string name) //CHANGING THE STATUS OF THE DEVICE
	{
		int index = findDevice(name);
		if (index != -1) {
			if (devices[index].getstatus())
				devices[index].turnOff();
			else
				devices[index].turnOn();
			cout << "Device toggled successfully!" << endl;
		}
		else {
			cout << "Device not found!" << endl;
		}
	}
	void setdevicebrightness(string n, int b) //SETTER FUNCTION FOR THE BRIGHTNESS
	{
		int index = findDevice(n);
		if (index != -1)
		{
			devices[index].setbrightness(b);
        }
		else
		{
			cout << "device not found" << endl;
		}
	}
	void loadRoom() //FILE HANDLING
	{
		ifstream in("devices.txt");
		if (!in)
			return;

		string n;
		bool status;
		int b;

		while (in >> n >> status >> b)
		{
			if (count < 5)
			{
				devices[count] = Device(n, status, b);
				count++;
			}
		}

		in.close();
	}
};
int main() //MAIN FUNCTION
{
	Room room("living room");
	room.loadRoom();
	int choice;
	do { //MAIN MENU
		cout << "SMART ROOM MANAGER" << endl;
		cout << "1.Add a device" << endl;
		cout << "2.Show all devices" << endl;
		cout << "3.turn device on and off" << endl;
		cout << "4.Changes brightness" << endl;
		cout << "5.exit" << endl;
		cout << "enter your choice" << endl;
		cin >> choice;
		if (choice == 1) {
			string name;
			bool status;
			int brightness;

			cout << "Enter device name: ";
			cin >> name;
			cout << "Is device ON? (1 for Yes, 0 for No): ";
			cin >> status;
			cout << "Enter brightness (0-100): ";
			cin >> brightness;

			Device d(name, status, brightness);
			room.addDevice(d);
		}
		else if (choice == 2)
		{
			room.showDevices();
		}
		else if (choice == 3) {
			string name;
			cout << "Enter device name: ";
			cin >> name;
			room.toggledevice(name);
		}
		else if (choice == 4) {
			string name;
			int b;
			cout << "Enter device name: ";
			cin >> name;
			cout << "Enter new brightness: ";
			cin >> b;
			room.setdevicebrightness(name, b);
		}
		else if (choice == 5)
		{
			return 0;
		}
		else {
			cout << "invalid choice" << endl;
		}
	    } 
	while (choice != 5);
		
		return 0;
	}