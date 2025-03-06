#ifndef BTNODE_H
#define BTNODE_H

class btNode {
 public:
  btNode(char data);
  char value;
  btNode* node;
  btNode* left;
  btNode* right;
  btNode* next;
};
#endif
