#ifndef BTNODE_H
#define BTNODE_H

// combined linkedlist node functionality into this binary tree node
class btNode {
 public:
  btNode(char data); //constructor
  char value;
  btNode* left;
  btNode* right;
  btNode* next;
};
#endif
