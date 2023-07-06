#ifndef Router_H
#define Router_H

#include"List.h"
#include"priorityQueue.h"
#include"queue.h"
#include"machine.h"
#include"node.h"
#include<vector>
using namespace std;
class Router:public Node
{
public:

	Router();
	Router(string identifier);
	~Router();
	void setIdentifier(string name);
	string getIdentifier();
	void configureRouter(RoutTable<Machine,Router> routingTable);
	void sendMessage(vector<Message> msgList);
	void dispatchMessage();
	RoutTable<Machine, Router> getRoutingTable();
private:
	string identifier;
	PriorityQueue* incomingQueue;
	RoutTable<Machine, Router> routingTable;
	//Queue outgoingQueue;
	vector<Queue*> outgoingQueue;
	/*This function will be called locally therefore it is kept private. This function is responsable to dispatch a 
	message to another router.*/
};

Router::Router()
{
}

Router::Router(string identifier) {
	this->identifier = identifier;
}
Router::~Router()
{
}

void Router::setIdentifier(string identifier) {
	this->identifier = identifier;
}
string Router::getIdentifier() {
	return identifier;
}

void Router::configureRouter(RoutTable<Machine, Router> routingTable)
{
	
		this->routingTable = routingTable;
		RoutEntry<Machine, Router>* rEntry = routingTable.getHead();
		while (rEntry!=NULL)
		{
			// do not create queue for a router if that queue is already created
			Router* r = rEntry->route;
			bool queueExist = false;
			for (int i = 0; i < outgoingQueue.size(); i++)
			{
				if (outgoingQueue[i]->getDestination() == r->getIdentifier())
					queueExist = true;
			}
			if (!queueExist)
			{
				Queue* queue = new Queue(4, r->getIdentifier());
				outgoingQueue.push_back(queue);
			}
			rEntry = rEntry->next;
		}
}

void Router::sendMessage(vector<Message> msgList)
{
	cout << "\n Inside Router \t" << this->getIdentifier() << endl;

	incomingQueue = new PriorityQueue(msgList.size());
	for (int i = 0; i < msgList.size(); i++)
	{
		incomingQueue->insert(msgList[i]);
	}

	for (int i = 0; i < msgList.size(); i++)
	{
		RoutEntry<Machine,Router>* rEntry = routingTable.getHead();

		Message* m = incomingQueue->deQueue();
		while (rEntry != NULL)
		{
			if (m->getDestinationAddress() == rEntry->machine->getIdentifier())
			{
				if (rEntry->route->getIdentifier() == this->getIdentifier())
				{
					/*cout << "machine is connected with me" << endl;*/
					rEntry->machine->sendMessage(m);
				}
				 else {
					// Machine is not connected with me.Search for outgoing Queue.
						for (int i = 0; i < outgoingQueue.size(); i++)
						{
							Queue* q = outgoingQueue[i];
							if (q->getDestination() == (rEntry->route->getIdentifier()))
							{
								q->insert((*m));
								break;
							}
						}
				}
				break;
			}
			rEntry = rEntry->next;
		}
		if (rEntry == NULL)
		{
			cout << "\nPath not found\n";
		}
	}
	this->dispatchMessage();

}

void Router::dispatchMessage()
{
	for (int i = 0; i < outgoingQueue.size(); i++)
	{
		while (!outgoingQueue[i]->isEmpty())
		{
			Message* m = outgoingQueue[i]->deQueue();
			cout << "\n Message to be entertained is " << m->getPayload() << "\t" << m->getMessageId() << endl;
			string destinationRouterName = outgoingQueue[i]->getDestination();
			//RoutingEntry* entry = routingTable.searchRoutingEntry(nextRouterName);
			for (int i = 0; i < routingTable.size; i++) {
				RoutEntry<Machine, Router>* tempRouter = routingTable.get(i);
				if (tempRouter->route->getIdentifier() == destinationRouterName)
				{
					Message tempMessage;
					tempMessage.setMessageId(m->getMessageId());
					tempMessage.setPayload(m->getPayload());
					tempMessage.setPriority(m->getPriority());
					tempMessage.setDestinationAddress(m->getDestinationAddress());
					tempMessage.setSourceAddress(m->getSourceAddress());
					vector<Message> msg;
					msg.push_back(tempMessage);
					//tempRouter->route->routingTable = routingTable;
					tempRouter->route->sendMessage(msg);
					break;
				}
			}
		}
	}
}

RoutTable<Machine, Router> Router::getRoutingTable() {
	return this->routingTable;
}
#endif