#include <iostream>
#include "btnode.h"

using namespace std;

btNode::btNode(char data){
  value = data;
  left = NULL;
  right = NULL;
  next = NULL;
}
