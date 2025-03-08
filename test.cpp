#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "btnode.h"

using namespace std;

// function prototypes for stack functionality
void push(btNode* & stackHead, btNode* newNode);
void pop(btNode* & stackHead);
char peek(btNode* &stackHead);

//function prototypes for queue functionality
void enqueue(btNode* &queueHead, btNode* newNode, btNode* &tail); //char data
void dequeue(btNode* &queueHead);
char peekq(btNode* & queueHead);

//function prototypes for outputting from expression tree
void prefix(btNode* root);
void infix(btNode* root);
void postfix(btNode* root);

int main()
{
  // set head nodes of stack and queue to be used for the shuntig yard algorithm
  btNode* stackHead = NULL;
  btNode* queueHead = NULL;
  map<char, int> m;
  // set precedence of operators through map (higher value = higher precedence)
  m['+'] = 0;
  m['-'] = 0;
  m['/'] = 1;
  m['*'] = 1;
  m['^'] = 2;
  //tail node for queue functionality
  btNode* tail = queueHead;
  char input[100];
  cout << "Enter a mathematical expression in infix notation: ";
  cin.get(input, 100);
  cin.get();

  //perform shunting yard algorithm
  for (int i = 0; i < strlen(input); i++){
    if (input[i] != ' '){
      //if digit, send to ouput queue
      if (isdigit(input[i])){
	btNode* newNode = new btNode(input[i]);
        enqueue(queueHead, newNode, tail);
      }
      //if left parentheses push to operator stack
      else if (input[i] == '(') {
	btNode* newNode = new btNode(input[i]);
        push(stackHead, newNode);
      }
      else if (input[i] == ')'){
	// if right parentheses send everything from operator stack to output queue until matching left parentheses is seen
        while(peek(stackHead) != '(' && peek(stackHead) != '\0'){
          btNode* p = new btNode(peek(stackHead));
          pop(stackHead);
          enqueue(queueHead, p, tail);
        }
        pop(stackHead);
      }
      //if operator
      else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^'){
	// while top of operator stack isn't ( and top of operator stack has higher precedence than current operator or same precedence but left associative
        while (peek(stackHead) != '(' && peek(stackHead) != '\0' && (m[input[i]] < m[peek(stackHead)] || (m[input[i]] == m[peek(stackHead)] && input[i] != '^'))){ // ( '^' is the only right associative operator)
	  //pop from operator stack and send to output queue
          btNode* p1 = new btNode(peek(stackHead));
          pop(stackHead);
          enqueue(queueHead, p1, tail);
        }
	//push current operator to stack
	btNode* newNode = new btNode(input[i]);
        push(stackHead, newNode);

      }
      
    }

  }
  //vector to store the postfix expression
  vector<char> postfixExpression;
  //while there are still things in the operator stack pop them all and send them to the output queue
  while(peek(stackHead) != '\0'){
    btNode* p = new btNode(peek(stackHead));
    pop(stackHead);
    enqueue(queueHead, p, tail);
  }

  //transfer postfix expression from queue to the vector
  while(peekq(queueHead) != '\0'){
    postfixExpression.push_back(peekq(queueHead));
    dequeue(queueHead);
  }
  
  cout << "Postfix Expression: ";
  for (int i = 0; i < postfixExpression.size(); i++){
    cout << postfixExpression[i];
  }
  cout << endl;

  // building binary expression tree

  btNode* treeStack = NULL;
  for (int i = 0; i < postfixExpression.size(); i++) {
    // if current token is a digit push to stack
    if (isdigit(postfixExpression[i])){
      btNode* digit = new btNode(postfixExpression[i]);
      push(treeStack, digit);
    }

    //if current token is a operator
    else{
      // first two operators on the top of the stack become right and left child
      btNode* r = treeStack;
      pop(treeStack);

      btNode* l = treeStack;
      pop(treeStack);

      // create new operator node with popped operands as children
      btNode* opNode = new btNode(postfixExpression[i]);
      opNode->left = l;

          
      opNode->right = r;

      // pushed new node back into stack
      push(treeStack, opNode);
    }
    
  }

    
  char input2 [50];
  cout << "Print infix, postfix, or prefix? ";
  cin.get(input2, 50);
  cin.get();

  if (strcmp(input2, "prefix") == 0){
    cout << "Prefix Expression: ";
    prefix(treeStack);
  }
  else if (strcmp(input2, "postfix") == 0) {
    cout << "Postfix Expression: ";
    postfix(treeStack);
  }
  else if (strcmp(input2, "infix") == 0){
    cout << "Infix Expression: ";
    infix(treeStack);
  }

}

void prefix(btNode* root)
{
  //base case: return when current node is null
  if (root == NULL){
    return;
  }

  cout << root->value; //ouput current node value
  prefix(root->left); //recursively traverse left subtree
  prefix(root->right); //recursively traverse right subtree
}

void postfix(btNode* root)
{
  //base case: return when current node is null 
  if (root == NULL){
    return;
  }
  postfix(root->left); //recursviely traverse left subtree
  postfix(root->right); //recursively traverse right subtree
  cout << root->value; //output current node value
}

void infix(btNode* root)
{
  // base case: return when current node is null
  if (root == NULL){
    return;
  }

  infix(root->left); // recursively traverse left subtree

  cout << root->value; //ouput current node value

  infix(root->right); // recursively traverse right subtree
}



void push(btNode* & stackHead, btNode* data)
{
  //push at the front of the stack
  btNode* temp = stackHead;
  stackHead = data;
  stackHead->next = temp;
}

void pop(btNode* & stackHead)
{
  //delete from front of stack (LIFO)
  btNode* temp = stackHead;
  stackHead = stackHead->next;
  
  //delete temp; ---------> don't delete the pointer here since when building the expression tree after I pop I still need to access the pointer. Don't need to delete to pop, still has the same functionality since head pointer gets moved.
}

//return value of node at the top of the stack
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
  //add data to the end of the queue
  tail->next = data;
  tail = data;

}


void dequeue(btNode* &queueHead)
{
  //delete from the front of the queue
  btNode* temp = queueHead;
  queueHead = queueHead->next;
  delete temp;
}

//get the value of node at the top of the queue
char peekq(btNode* &queueHead)
{
  if (queueHead != NULL){
    return queueHead->value;
  }
  else{
    return '\0';
  }
}




 
