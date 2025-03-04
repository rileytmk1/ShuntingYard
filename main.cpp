#include <iostream>
#include <cstring>
#include <vector>
#include <map>
//#include "binarytree.h"

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
  // set precedence of operators through map
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
  vector<char> postfix;
  while(peek(stackHead) != '\0'){
    char p = peek(stackHead);
    pop(stackHead);
    enqueue(queueHead, p, tail);
  }
  while(peekq(queueHead) != '\0'){
    postfix.push_back(peekq(queueHead));
    dequeue(queueHead);
  }
  cout << "Postfix Expression: ";
  for (int i = 0; i < postfix.size(); i++){
    cout << postfix[i];
  }
  cout << endl;
  
  char input2 [50];
  cout << "Print infix, postfix, or prefix? ";
  cin.get(input2, 50);
  cin.get();

  if (strcmp(input2, "prefix") == 0){
    cout << "Prefix: ";
  }
  else if (strcmp(input2, "postfix") == 0) {
    cout << "Postfix: ";
  }
  else if (strcmp(input2, "infix") == 0){
    cout << "Infix: ";
  }

  
  /*
  for (int i = 0; i < postfix.size(); i++){
    binarytree* node, l, r;
    if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^'){
      binarytree
    }
  }
  */
  
  
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
