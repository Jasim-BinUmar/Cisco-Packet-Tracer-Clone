#ifndef Message_H
#define Message_H
#include<string>
using namespace std;
class Message
{
public:
	Message();
	Message(int id, int p, string sAddress, string dAddress, string pLoad);
	~Message();
	void setMessageId(int id);
	void setPriority(int p);
	void setSourceAddress(string sAddress);
	void setDestinationAddress(string dAddress);
	void setPayload(string pL);
	void setTrace(string t);
	int getMessageId();
	int getPriority();
	string getSourceAddress();
	string getDestinationAddress();
	string getPayload();
	string getTrace();

private:
	int messageId;
	int priority;
	string sourceAddress, destinationAddress, payload, trace;
};
Message::Message()
{
	messageId = NULL;
	priority = NULL;
	sourceAddress = "";
	destinationAddress = "";
	payload = "";
	trace = "";
}
Message::Message(int id ,int p,string sAddress, string dAddress, string pLoad)
{
	messageId = id;
	priority = p;
	sourceAddress = sAddress;
	destinationAddress = dAddress;
	payload = pLoad;
	trace = "";
}

Message::~Message()
{
}
void Message::setMessageId(int id)
{
	messageId = id;
}
void Message::setPriority(int p)
{
	priority = p;
}
void Message::setSourceAddress(string sAddress)
{
	sourceAddress = sAddress;
}
void Message::setDestinationAddress(string dAddress)
{
	destinationAddress = dAddress;
}
void Message::setPayload(string pL)
{
	payload = pL;
}
void Message::setTrace(string t)
{
	trace = t;
}
int Message::getMessageId()
{
	return messageId;
}
int Message::getPriority()
{
	return priority;
}
string Message::getSourceAddress()
{
	return sourceAddress;
}
string Message::getDestinationAddress()
{
	return destinationAddress;
}
string Message::getPayload()
{
	return payload;
}
string Message::getTrace()
{
	return trace;
}
#endif