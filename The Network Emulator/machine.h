#ifndef Machine_H
#define Machine_H
#include"message.h"
#include<vector>
#include"node.h"
using namespace std;
class Machine
{
public:
	Machine();
	Machine(string name);
	~Machine(); 
	void setIdentifier(string name);
	string getIdentifier();
	string getRecievedMessage();
	string getSentMessage();
	void sendMessage(Message* m);
	void setConnectedRouter(Node*);
	void dispatchMessage(vector<Message>);
private:
	string recievedMessage, sentMessage, identifier;
	Node* connectedRouter;
};

Machine::Machine()
{
	recievedMessage = "";
	sentMessage = "";
}
Machine::Machine(string name) {
	this->identifier = name;
}
Machine::~Machine()
{
}
void Machine::setIdentifier(string identifier) {
	this->identifier = identifier;
}
string Machine::getIdentifier() {
	return identifier;
}
string Machine::getRecievedMessage()
{
	return recievedMessage;
}
string Machine::getSentMessage()
{
	return sentMessage;
}
void Machine::sendMessage(Message* message) {
	cout << "Message received by "<<this->getIdentifier() << endl;
	cout << message->getPayload() << endl;
}
void Machine::setConnectedRouter(Node* router) {
	connectedRouter = router;
}

void Machine::dispatchMessage(vector<Message> list){
	connectedRouter->sendMessage(list);
}
#endif
