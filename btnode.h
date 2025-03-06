#ifndef BTNODE_H
#define BTNODE_H

class btNode {
 public:
  btNode(char data);
  char value;
  btNode* left;
  btNode* right;
  btNode* next;
};
#endif
