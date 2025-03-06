#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "btnode.h"

using namespace std;


void push(btNode* & stackHead, char data);
void pop(btNode* & stackHead);
char peek(btNode* &stackHead);
void enqueue(btNode* &queueHead, char data, btNode* &tail);
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

  // need to change push function so it pushes nodes instead of chars
  
  btNode* treeStack = NULL;
  for (int i = 0; i < postfix.size(); i++) {
    if (isdigit(postfix[i])){
      push(treeStack, postfix[i]);
    }
    else{
      btNode* right = treeStack;
      pop(treeStack);
      btNode* left = treeStack;
      pop(treeStack);

      btNode* opNode = new btNode(postfix[i]);
      opNode->left = left;
      opNode->right = right;
      push(treeStack, postfix[i]);
    }
  }
  
  prefix(treeStack);
 
  char input2 [50];
  cout << "Print infix, postfix, or prefix? ";
  cin.get(input2, 50);
  cin.get();

  if (strcmp(input2, "prefix") == 0){
    cout << "Prefix: ";
    prefix(treeStack);
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

void print(btNode* root) {
    if (root == nullptr) return;
    cout << "(" << root->value;
    print(root->left);
    print(root->right);
    cout << ")";
}

void push(btNode* & stackHead, char data)
{
  btNode* temp = stackHead;
  stackHead = new btNode(data);
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

void enqueue(btNode* &queueHead, char data, btNode* &tail)
{
  btNode* newNode = new btNode(data);
  
  if (tail == NULL){
    queueHead = newNode;
    tail = newNode;
    return;
  }
  tail->next = newNode;
  tail = newNode;

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




 
