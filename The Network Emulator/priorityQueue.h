#ifndef PriorityQueue_H
#define PriorityQueue_H

#include"queue.h"
#include"message.h"

class PriorityQueue:public Queue
{
public:
	
	PriorityQueue(int size);
	bool insert(Message m);
	
private:
	/*int front, rear, cap;*/
	/*Message* q;*/
};
PriorityQueue::PriorityQueue(int size):Queue(size,"")
{
	
}
bool PriorityQueue::insert(Message item)
{
	Message key;
	int i = 0;
	if (!isFull())
	{
		if (front == -1) front = 0;
		rear = (rear + 1) % cap;
		q[rear] = item;
		key = q[rear];
		i = rear - 1;
		while (i >= front && q->getPriority() < key.getPriority())
		{
			q[i + 1] = q[i];
			i = i - 1;
		}
		q[i + 1] = key;
	}
	else
	{
		cout << "Queue is Full";
		return 0;
	}
}

#endif 


