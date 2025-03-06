#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "btnode.h"

using namespace std;


void push(btNode* & stackHead, btNode* newNode); //char data
void pop(btNode* & stackHead);
char peek(btNode* &stackHead);
void enqueue(btNode* &queueHead, btNode* newNode, btNode* &tail); //char data
void dequeue(btNode* &queueHead);
char peekq(btNode* & queueHead);
void prefix(btNode* root);
void print(btNode* root);

int main()
{
  btNode* stackHead = NULL;
  btNode* queueHead = NULL;
  map<char, int> m;
  // set precedence of operators through map
  m['+'] = 0;
  m['-'] = 0;
  m['/'] = 1;
  m['*'] = 1;
  m['^'] = 2;
  btNode* tail = queueHead;
  char input[100];
  cout << "Enter a mathematical expression in infix notation: ";
  cin.get(input, 100);
  cin.get();
  for (int i = 0; i < strlen(input); i++){
    if (input[i] != ' '){
      if (isdigit(input[i])){
	btNode* newNode = new btNode(input[i]);
        enqueue(queueHead, newNode, tail);
      }
      else if (input[i] == '(') {
	btNode* newNode = new btNode(input[i]);
        push(stackHead, newNode);
      }
      else if (input[i] == ')'){
        while(peek(stackHead) != '(' && peek(stackHead) != '\0'){
          btNode* p = new btNode(peek(stackHead));
          pop(stackHead);
          enqueue(queueHead, p, tail);
        }
        pop(stackHead);
      }
      else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^'){
        while (peek(stackHead) != '(' && peek(stackHead) != '\0' && (m[input[i]] < m[peek(stackHead)] || (m[input[i]] == m[peek(stackHead)] && input[i] != '^'))){
          btNode* p1 = new btNode(peek(stackHead));
          pop(stackHead);
          enqueue(queueHead, p1, tail);
        }
	btNode* newNode = new btNode(input[i]);
        push(stackHead, newNode);

      }
      //cout << peek(stackHead) << endl;

    }

  }
  vector<char> postfix;
  while(peek(stackHead) != '\0'){
    btNode* p = new btNode(peek(stackHead));
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

  // need to change push function so it pushes nodes instead of chars
  
  btNode* treeStack = NULL;
  for (int i = 0; i < postfix.size(); i++) {
    if (isdigit(postfix[i])){
      btNode* digit = new btNode(postfix[i]);
      push(treeStack, digit);
      cout << "test" << endl;
    }
    
    else{
      btNode* r = treeStack;
      pop(treeStack);
      btNode* l = treeStack;
      pop(treeStack);

      btNode* opNode = new btNode(postfix[i]);
      opNode->left = l;
    
      opNode->right = r;
    
      push(treeStack, opNode);
    }
    
  }

  cout << "hi " << treeStack->left->value << endl;
  
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

void prefix(btNode* root)
{
  if (root == NULL){
    return;
  }

  cout << root->value;
  prefix(root->left);
  cout << "test" << endl;
  prefix(root->right);
}


void push(btNode* & stackHead, btNode* data)
{
  btNode* temp = stackHead;
  stackHead = data;
  stackHead->next = temp;
}

void pop(btNode* & stackHead)
{
  btNode* temp = stackHead;
  stackHead = stackHead->next;
  delete temp;
}

char peek(btNode* & stackHead)
{
  if (stackHead != NULL){
    return stackHead->value;
  }
  else{
    return '\0';
  }

}

void enqueue(btNode* &queueHead, btNode* data, btNode* &tail)
{
    
  if (tail == NULL){
    queueHead = data;
    tail = data;
    return;
  }
  tail->next = data;
  tail = data;

}


void dequeue(btNode* &queueHead)
{
  btNode* temp = queueHead;
  queueHead = queueHead->next;
  delete temp;
}

char peekq(btNode* &queueHead)
{
  if (queueHead != NULL){
    return queueHead->value;
  }
  else{
    return '\0';
  }
}




 
