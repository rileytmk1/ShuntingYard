#include <iostream>
#include <cstring>

using namespace std;

struct Node{
  char value;
  Node* next;
};


void push(Node* & stackHead, char data);
void pop(Node* & stackHead);
void peek(Node* &stackHead);
void enqueue(Node* &queueHead, char data, Node* &tail);
void dequeue(Node* &queueHead);
void peekq(Node* & queueHead);

int main()
{
  Node* stackHead = NULL;
  Node* queueHead = NULL;
  Node* tail = queueHead;
  enqueue(queueHead, '1', tail);
  enqueue(queueHead, '2', tail);
  enqueue(queueHead, '3', tail);
  dequeue(queueHead);
  peekq(queueHead);
  push(stackHead, '1');
  push(stackHead, '2');
  push(stackHead, '3');
  pop(stackHead);
  peek(stackHead);
}

void push(Node* & stackHead, char data)
{
  Node* temp = stackHead;
  stackHead = new Node();
  stackHead->value = data;
  stackHead->next = temp;
}

void pop(Node* & stackHead)
{
  Node* temp = stackHead;
  stackHead = stackHead->next;
  delete temp;
}

void peek(Node* & stackHead)
{
  cout << stackHead->value << endl;
}

void enqueue(Node* &queueHead, char data, Node* &tail)
{
  Node* newNode = new Node();
  newNode->value = data;
  if (tail == NULL){
    queueHead = newNode;
    tail = newNode;
    return;
  }
  tail->next = newNode;
  tail = newNode;
  
}


void dequeue(Node* &queueHead)
{
  Node* temp = queueHead;
  queueHead = queueHead->next;
  delete temp;
}

void peekq(Node* &queueHead)
{
  cout << queueHead->value << endl;
}
