#ifndef Node_H
#define Node_H
#include"message.h"
class Node
{
public:
	virtual void sendMessage(vector<Message> msgList) = 0;

};
#endif