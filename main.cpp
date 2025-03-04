#include <iostream>
#include <cstring>
#include <map>

using namespace std;

struct Node{
  char value;
  Node* next;
};


void push(Node* & stackHead, char data);
void pop(Node* & stackHead);
char peek(Node* &stackHead);
void enqueue(Node* &queueHead, char data, Node* &tail);
void dequeue(Node* &queueHead);
char peekq(Node* & queueHead);

int main()
{
  Node* stackHead = NULL;
  Node* queueHead = NULL;
  map<char, int> m;
  m['+'] = 0;
  m['-'] = 0;
  m['/'] = 1;
  m['*'] = 1;
  m['^'] = 2;
  Node* tail = queueHead;
  char input[100];
  cout << "Enter a mathematical expression in infix notation: ";
  cin.get(input, 100);
  cin.get();
  for (int i = 0; i < strlen(input); i++){
    if (input[i] != ' '){
      if (isdigit(input[i])){
	enqueue(queueHead, input[i], tail);
      }
      
      else if (input[i] == '(') {
	push(stackHead, input[i]);
      }
      else if (input[i] == ')'){
	while(peek(stackHead) != '(' && peek(stackHead) != '\0'){
	  char p = peek(stackHead);
	  pop(stackHead);
	  enqueue(queueHead, p, tail);
	}
	pop(stackHead);
      }
      else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^'){
	while (peek(stackHead) != '(' && peek(stackHead) != '\0' && (m[input[i]] < m[peek(stackHead)] || (m[input[i]] == m[peek(stackHead)] && input[i] != '^'))){
	  char p1 = peek(stackHead);
	  pop(stackHead);
	  enqueue(queueHead, p1, tail);
	}
	
	push(stackHead, input[i]);

      }
      //cout << peek(stackHead) << endl;
      
    }
      
  }
  
  while(peek(stackHead) != '\0'){
    char p = peek(stackHead);
    pop(stackHead);
    enqueue(queueHead, p, tail);
  }
  while(peekq(queueHead) != '\0'){
    cout << peekq(queueHead);
    dequeue(queueHead);
  }
  
  
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

char peek(Node* & stackHead)
{
  if (stackHead != NULL){
    return stackHead->value;
  }
  else{
    return '\0';
  }
  
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

char peekq(Node* &queueHead)
{
  if (queueHead != NULL){
    return queueHead->value;
  }
  else{
    return '\0';
  }
}
