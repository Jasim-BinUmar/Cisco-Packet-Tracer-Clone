#include "List.h"
#include"router.h"
#include"machine.h"
#include"ServiceManager.h"
#include<conio.h>
#include<string>
using namespace std;
int main()
{
	ServiceManager manager;
	cout << "\n\n\n"
		<< "\t\t=================================================================== \n"
		<< "\t\t=================================================================== \n"
		<< "\t				    THE NETWORK EMULATOR							    \n"
		<< "\t\t=================================================================== \n"
		<< "\t\t=================================================================== \n"
		<< "\t				    Major Features									    \n"
		<< "\t\t=================================================================== \n"
		<< "\t\t	1. Persistant Storage using Filing 								\n"
		<< "\t\t	2. Graph Data Structure											\n"
		<< "\t\t	3. Priority Queue												\n"
		<< "\t\t	4. Linked List													\n"
		<< "\t\t	5. Dijkstra Algorithm to find shortest path						\n"
		<< "\t\t	6. Routers Configuration										\n"
		<< "\t\t	7. Trace Message Path a.k.a Shortest Path						\n"
		<< "\t\t=================================================================== \n";
	/*out << "\nPress any key to proceed toward demo\n";
	char opt = 'a';*/
	char networkOpt;
	do
	{
		cout << "\nChoose Network\n";
		cout << "\t\t 1. Network Demo 01\n";
		cout << "\t\t 2. Network Demo 02\n";
		cout << "\t\t 3. Network Demo 03\n";
		cout << "\t\t 4. Default demo for beginner\n";
		cout << "You can alter file contents for further networks demos\n";
		cout << "\t\t Press E to exit.\n";
		cin >> networkOpt;
		if (networkOpt == '1')
		{
			manager.startupConfiguration("Network01.txt");
		}
		else if (networkOpt == '2')
		{

			manager.startupConfiguration("Network02.txt");
		}
		else if (networkOpt == '3')
		{

			manager.startupConfiguration("Network03.txt");
		}
		else if (networkOpt == '4')
		{

			manager.startupConfiguration("Network01.txt");
		}
	} 
	while (networkOpt =='e'&& networkOpt == 'E');
	
	/*while (opt != 'z') 
	{
		cout << "\nPress n to visit network emulator\n";
		cin >> opt;
		if (opt == 'n') 
		{
			cout << "\nChoose Network\n";
			cout << "\t\t 1. Network Demo 01\n";
			cout << "\t\t 2. Network Demo 02\n";
			cout << "\t\t 3. Network Demo 03\n";
			cout << "\t\t 4. Default demo for beginner\n";
			cout << "You can alter file contents for further networks demos\n";
			cin >> networkOpt;
			if (networkOpt == '1') 
			{
				manager.startupConfiguration("Network01.txt");
			}
			else if (networkOpt == '2') 
			{

				manager.startupConfiguration("Network02.txt");
			}
			else if (networkOpt == '3') 
			{

				manager.startupConfiguration("Network03.txt");
			}
			else if (networkOpt == '4') 
			{

				manager.startupConfiguration();
			}
		}

		else 
		{
			cout << "\nchoose z to exit or any option to continue\n";
		}
	}*/
		/*ServiceManager manager;
		manager.startupConfiguration();*/
		return 0;
}
