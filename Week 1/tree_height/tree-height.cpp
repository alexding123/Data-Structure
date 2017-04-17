#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};
class IndexDepth; 
class IndexDepth {
  public: 
    int index;
    int depth;
    IndexDepth(int index, int depth) : index(index), depth(depth) {}
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  int root; 
  std::vector<int> tree[n];
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index == -1) {
      root = child_index;
    } else {
      tree[parent_index].push_back(child_index);
    }
  }
  int maxDepth = 0;
  std::deque<IndexDepth> q;
  q.push_back(IndexDepth(root, 1));

  while (!q.empty()) {
    IndexDepth num = q.front();
    q.pop_front();
    int size = tree[num.index].size();
    if (size != 0) {
      for (int i = 0; i < size; i++) {
        q.push_back(IndexDepth(tree[num.index][i], num.depth+1));
      }
    }
    maxDepth = std::max(maxDepth, num.depth);
  }
  std::cout << maxDepth << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
