#ifndef Queue_H
#define Queue_H

#include<string>
#include"message.h"
using namespace std;

class Queue
{
public:
	Queue();
	Queue(int maxCap, string name);
	~Queue();
	bool isFull();
	bool isEmpty();
	bool insert(Message item);
	void remove(Message& item);
	Message* deQueue();
	string getDestination();

	int front, rear, cap;
	Message* q;
	string destinationRouter;
};

Queue::Queue()
{
	front = -1;
	rear = -1;
	cap = 5;
	q = new Message[cap];
}
/*name represents destination router*/
Queue::Queue(int maxCap, string name)
{
	front = -1;
	rear = -1;
	cap = maxCap;
	q = new Message[cap];
	destinationRouter = name;	
}

Queue::~Queue()
{
	delete[] q;
}

bool Queue::isFull()
{
	if (front == 0 && rear == cap - 1)
	{
		return true;
	}
	else if (rear + 1 == front)
	{
		return true;
	}
	return false;
}

bool Queue::isEmpty()
{
	if (front == -1)
	{
		return true;
	}
	return false;
}

 bool Queue::insert(Message item)
{
	if (!isFull())
	{
		if (front == -1)
		{
			front = 0;
		}
		rear = (rear + 1) % cap;
		q[rear] = item;

	}
	else
	{
		cout << "Queue is Full";
		return 0;
	}
}

void Queue::remove(Message& item)
{
	if (!isEmpty())
	{
		item = q[front];
		if (front == rear)
		{
			front = -1;
			rear = -1;
		}
		else
		{
			front = (front + 1) % cap;
		}
	}
}
Message* Queue::deQueue()
{
	Message* m=NULL;
	if (!isEmpty())
	{
		if (front == rear)
		{
			m = &q[front];
			front = -1;
			rear = -1;
			
		}
		else
		{
			m = &q[front];
			front = (front + 1) % cap;
		}
		
	}
	return m;
}
string Queue::getDestination()
{
	return destinationRouter;
}

#endif 