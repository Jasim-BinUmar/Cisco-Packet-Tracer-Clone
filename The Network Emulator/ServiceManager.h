#include"router.h"
#include"machine.h"
#include"Dijkstra.h"
#include "List.h"
#include <fstream>
using namespace std;
class ServiceManager {
	int routCount;
	int machineCount;
	Router* r;
	Machine* m;
	Dijkstra dijkstra;
	char* devices;
	int** network = NULL;
public:
	ServiceManager();
	void startupConfiguration();
	void startupConfiguration(string fileName);
	int* populateCommaDelimited(string myText, int size);
	void commaDelimitedRow(string myText, char devices[], int size);
};
ServiceManager::ServiceManager() {
	routCount = 0;
	machineCount = 0;
}
void ServiceManager::startupConfiguration() {
	///////////////////////////////////////////////////Reading from File///////////////////////////////////
	int size = 0;
	string myText;
	ifstream MyReadFile("Network.txt");
	int rowCounter = 0;
	int index = 0;
	while (getline(MyReadFile, myText)) {
		if (rowCounter == 0)
		{
			size = stoi(myText);
			network = new int* [size];
		}
		else if (rowCounter == 1)
		{
			devices = new char[size];
			commaDelimitedRow(myText, devices, size);
			for (int i = 0; i < size; i++) {
				cout << devices[i] << "\t";
			}
		}
		else if (rowCounter >= 2) {
			network[index++] = populateCommaDelimited(myText, size);
		}
		rowCounter++;

	}
	if (network != NULL) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << network[i][j] << "\t";
			}
			cout << endl;
		}
	}
	MyReadFile.close();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'R') {
			routCount++;
		}
		else {
			machineCount++;
		}
	}
	r = new Router[routCount];
	m = new Machine[machineCount];
	int tempMachineCount = 0, tempRouterCount = 0;
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'M') {
			string tempMachineName = to_string(i);
			m[tempMachineCount++].setIdentifier(tempMachineName);
		}
		if (devices[i] == 'R') {
			string tempRouterName = to_string(i);
			r[tempRouterCount++].setIdentifier(tempRouterName);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'M') {
			dijkstra.runDijkstra(network, i);
			Path* p = dijkstra.getPath();
			//get connected router with machine
			int tempNeighbour = p[0].getNeighbour();
			//find actual machine from m (array) on basis of machine identifier i.e. i
			for (int machIndex = 0; machIndex < tempMachineCount; machIndex++) {
				if (m[machIndex].getIdentifier() == to_string(i))
				{
					//find actual router from r (array) on basis of router identifier i.e. r[tempNeighbour]
					//call machine.connectedRouter to connect machine with router
					m[machIndex].setConnectedRouter(&r[tempNeighbour]);
				}
			}
		}
		if (devices[i] == 'R') {
			dijkstra.runDijkstra(network, i);
			Path* p = dijkstra.getPath();
			cout << "vertix" << "\t" << "Dist" << "\t" << "Trace" << "\t" << "Neighbour" << endl;
			for (int i = 0; i < 8; i++) {
				cout << p[i].getVertix() << "\t" << p[i].getDistance() << "\t";
				vector<int> tempTracePath = p[i].getTrace();
				for (int pt = 0; pt < tempTracePath.size();  pt++)
				{
					cout << tempTracePath[pt];
				}
				cout << "\t" << p[i].getNeighbour() << endl;
			}
			//Path* p = dijkstra.getPath();
			//Loop
			RoutTable<Machine, Router> rTable;
			for (int j = 0; j < 8; j++) {
				if (devices[p[j].getVertix()] == 'M') {
					//I have a machine in my list
					int neighbour = p[j].getNeighbour();
					int neighbourIndex = neighbour;
					char deviceType = devices[neighbourIndex];
					if (neighbour >-1 && deviceType == 'R')
					{
						//if my neighbour is not null and my neighbour is a router
						int machineIdex, routerIndex = 0;
						for (machineIdex = 0; machineIdex < machineCount; machineIdex++)
						{
							string tempMachineIdentifier = to_string(p[j].getVertix());
							string machineInstance = m[machineIdex].getIdentifier();
							if (machineInstance == tempMachineIdentifier)
								break;//machine found and index noted
						}
						for (routerIndex = 0; routerIndex < routCount; routerIndex++)
						{
							string tempNeigh = to_string(p[j].getNeighbour());
							if (r[routerIndex].getIdentifier() == tempNeigh)
								break;//router found and index noted
						}
						rTable.add(&m[machineIdex], &r[routerIndex]);
					}
					else if (p[j].getNeighbour() != -1 && deviceType == 'M')
					{
						//if my neighbour is not null and my neighbour is a machine
						int machineIdex, routerIndex = 0;
						for (machineIdex = 0; machineIdex < machineCount; machineIdex++)
						{
							if (m[machineIdex].getIdentifier() == to_string(p[j].getVertix()))
								break;//machine found and index noted
						}
						//add machine and myself (router)
						rTable.add(&m[machineIdex], &r[i]);
					}
					
				}
			}
			r[i].configureRouter(rTable);
		}//end if
		
	}//end for loop
	Message msg1(101, 8, "M1", "7", " toward machine 07 ");
	Message msg2(102, 4, "M1", "6", " I am also toward machine 06");
	Message msg3(103, 2, "M1", "7", " But me toward machine 07");
	Message msg4(104, 1, "M1", "7", " And me too, toward machine 07");
	vector<Message> msgList;
	msgList.push_back(msg1);
	m[0].dispatchMessage(msgList);
	/*
	r[0].sendMessage(msgList);
	msgList.clear();
	msgList.push_back(msg2);
	r[0].sendMessage(msgList);
	msgList.clear();
	msgList.push_back(msg3);
	r[0].sendMessage(msgList);
	msgList.clear();
	msgList.push_back(msg4);
	r[0].sendMessage(msgList);*/
}//end configuration
void ServiceManager::startupConfiguration(string fileName) {
/////////////////////////////////////////////////////////////Read from file///////////////////////////
	int size = 0;
	string myText;
	ifstream MyReadFile(fileName);
	int rowCounter = 0;
	int index = 0;
	while (getline(MyReadFile, myText)) {
		if (rowCounter == 0)
		{
			size = stoi(myText);
			network = new int* [size];
		}
		else if (rowCounter == 1)
		{
			devices = new char[size];
			commaDelimitedRow(myText, devices, size);
			cout << endl;
			for (int i = 0; i < size; i++) {
				cout << devices[i] << "\t";
			}
		}
		else if (rowCounter >= 2) {
			network[index++] = populateCommaDelimited(myText, size);
		}
		rowCounter++;

	}
	cout << endl;
	if (network != NULL) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << network[i][j] << "\t";
			}
			cout << endl;
		}
	}
	MyReadFile.close();
	cout << "\npress any key to run shortest path algorithm by using Dijkstra\n";
	system("pause>null");
	system("CLS");
	//////////////////////////////////////////////////////////////////////////////////////////////////
	/*Identifying Routers and Machines from file and placing them in an array: devices*/
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'R') {
			routCount++;
		}
		else {
			machineCount++;
		}
	}
	/*creating actual Router and Machine array on basis of their numbers as identified above*/
	r = new Router[routCount];
	m = new Machine[machineCount];
	int tempMachineCount = 0, tempRouterCount = 0;
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'M') {
			//assign name or identifier to machine. Machine index from device array is actually representing name of machine
			string tempMachineName = to_string(i);
			m[tempMachineCount++].setIdentifier(tempMachineName);
		}
		if (devices[i] == 'R') {
			//assign name or identifier to router. Router index from device array is actually representing name of router
			string tempRouterName = to_string(i);
			r[tempRouterCount++].setIdentifier(tempRouterName);
		}
	}
	/*Now, identify shortest path from each machine and each router to all other connected nodes*/
	for (int i = 0; i < 8; i++) {
		if (devices[i] == 'M') {
			cout << "\n\t\t\tShortest paths from Machine "<<i<<endl;
			dijkstra.runDijkstra(network, i);
			Path* p = dijkstra.getPath();
			//get connected router with machine
			int tempNeighbour = p[0].getNeighbour();
			//find actual machine from m (array) on basis of machine identifier i.e. i
			for (int machIndex = 0; machIndex < tempMachineCount; machIndex++) {
				if (m[machIndex].getIdentifier() == to_string(i))
				{
					//find actual router from r (array) on basis of router identifier i.e. r[tempNeighbour]
					//call machine.connectedRouter to connect machine with router
					m[machIndex].setConnectedRouter(&r[tempNeighbour]);
				}
			}
		}
		if (devices[i] == 'R') {
			cout << "\n\t\t\tShortest paths from Router " << i << endl;
			dijkstra.runDijkstra(network, i);
			Path* p = dijkstra.getPath();
			cout << "vertix" << "\t" << "Dist" << "\t" << "Trace" << "\t" << "Neighbour" << endl;
			for (int i = 0; i < 8; i++) {
				cout << p[i].getVertix() << "\t" << p[i].getDistance() << "\t";
				vector<int> tempTracePath = p[i].getTrace();
				for (int pt = 0; pt < tempTracePath.size(); pt++)
				{
					cout << tempTracePath[pt];
				}
				cout << "\t" << p[i].getNeighbour() << endl;
			}
			//Path* p = dijkstra.getPath();
			//Loop
			RoutTable<Machine, Router> rTable;
			for (int j = 0; j < 8; j++) {
				if (devices[p[j].getVertix()] == 'M') {
					//I have a machine in my list
					int neighbour = p[j].getNeighbour();
					int neighbourIndex = neighbour;
					char deviceType = devices[neighbourIndex];
					if (neighbour > -1 && deviceType == 'R')
					{
						//if my neighbour is not null and my neighbour is a router
						int machineIdex, routerIndex = 0;
						for (machineIdex = 0; machineIdex < machineCount; machineIdex++)
						{
							string tempMachineIdentifier = to_string(p[j].getVertix());
							string machineInstance = m[machineIdex].getIdentifier();
							if (machineInstance == tempMachineIdentifier)
								break;//machine found and index noted
						}
						for (routerIndex = 0; routerIndex < routCount; routerIndex++)
						{
							string tempNeigh = to_string(p[j].getNeighbour());
							if (r[routerIndex].getIdentifier() == tempNeigh)
								break;//router found and index noted
						}
						rTable.add(&m[machineIdex], &r[routerIndex]);
					}
					else if (p[j].getNeighbour() != -1 && deviceType == 'M')
					{
						//if my neighbour is not null and my neighbour is a machine
						int machineIdex, routerIndex = 0;
						for (machineIdex = 0; machineIdex < machineCount; machineIdex++)
						{
							if (m[machineIdex].getIdentifier() == to_string(p[j].getVertix()))
								break;//machine found and index noted
						}
						//add machine and myself (router)
						rTable.add(&m[machineIdex], &r[i]);
					}

				}
			}
			r[i].configureRouter(rTable);
		}//end if

	}//end for loop
	system("pause>null");
	system("CLS");
	cout << "\n===========Write Message to demonstrate Path Traversal in Network===========\n";
	int msgId=0, msgPriority=0;
	string sourceMachine="", destMachine="", payload="";
	cout << "\n Enter message ID\n";
	cin >> msgId;
	cout << "\nSet message priority\n";
	cin >> msgPriority;
	cout << "\n specify source machine from following\n";
	for (int machCounter = 0; machCounter < machineCount; machCounter++) {
		cout << m[machCounter].getIdentifier() << endl;
	}
	cin >> sourceMachine; 
	cout << "\n specify destination machine from following\n";
	for (int machCounter = 0; machCounter < machineCount; machCounter++) {
		cout << m[machCounter].getIdentifier() << endl;
	}
	cin >> destMachine;
	cout << "\nType your message\n";
	cin.ignore();
	getline(cin, payload);
	//cin >> payload;
	cout << "\nWe are about to send your message to destination through shortest path\n";
	Message msgInstance(msgId, msgPriority, sourceMachine, destMachine, payload);
	vector<Message> msgList;
	msgList.push_back(msgInstance);
	for (int machCounter = 0; machCounter < machineCount; machCounter++) {
		if (m[machCounter].getIdentifier() == msgInstance.getSourceAddress())
		{
			m[machCounter].dispatchMessage(msgList);
		}
	}
}
int* ServiceManager:: populateCommaDelimited(string myText, int size) {
	string subStr = "";
	vector<string> v;
	for (int i = 0; i < myText.size(); i++) {
		if (myText[i] != ',')
		{
			subStr += myText[i];
		}
		else {/*
			cout << subStr << "\t";*/
			v.push_back(subStr);
			subStr = "";
		}
	}
	if (subStr != "") {
		//cout << subStr;
		v.push_back(subStr);
	}
	//cout << endl;
	int* arr = new int[v.size()];
	for (int i = 0; i < v.size(); i++) {
		arr[i] = stoi(v[i]);
	}
	return arr;
}
void ServiceManager:: commaDelimitedRow(string myText, char devices[], int size) {
	string subStr = "";
	int counter = 0;
	for (int i = 0; i < myText.size(); i++) {
		if (myText[i] != ',')
		{
			subStr += myText[i];
		}
		else {
			if (counter < size)
				devices[counter++] = subStr[0];// << "\t";
			subStr = "";
		}
	}
	if (subStr != "") {
		if (counter < size)
			devices[counter++] = subStr[0];
	}
}