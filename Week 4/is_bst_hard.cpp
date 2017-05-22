#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};
bool RecurIsBinarySearchTreeLeft(const vector<Node>& tree, int id, long long upper);
bool RecurIsBinarySearchTreeRight(const vector<Node>& tree, int id, long long lower);


bool RecurIsBinarySearchTreeLeft(const vector<Node>& tree, int id, long long upper) {
  if (tree[id].left != -1) {
    if (tree[tree[id].left].key >= tree[id].key) {
      return false;
    }
    if (!RecurIsBinarySearchTreeLeft(tree, tree[id].left, tree[id].key)) {
      return false;
    }
  }
  if (tree[id].right != -1) {
    if ((tree[tree[id].right].key < tree[id].key) || (tree[tree[id].right].key >= upper)) {
      return false;
    }
    if (!RecurIsBinarySearchTreeRight(tree, tree[id].right, tree[id].key)) {
      return false;
    }
  }
  return true;
}
bool RecurIsBinarySearchTreeRight(const vector<Node>& tree, int id, long long lower) {
  if (tree[id].left != -1) {
    if ((tree[tree[id].left].key >= tree[id].key) || (tree[tree[id].left].key < lower)) {
      return false;
    }
    if (!RecurIsBinarySearchTreeLeft(tree, tree[id].left, tree[id].key)) {
      return false;
    }
  }
  if (tree[id].right != -1) {
    if (tree[tree[id].right].key < tree[id].key) {
      return false;
    }
    if (!RecurIsBinarySearchTreeRight(tree, tree[id].right, tree[id].key)) {
      return false;
    }
  }
  return true;
}
bool IsBinarySearchTree(const vector<Node>& tree) {
  // Find root node first
  vector<int> parents;
  parents.resize(tree.size(), -1);
  for (int i = 0; i < tree.size(); i++) {
    if (tree[i].left != -1) 
      parents[tree[i].left] = i;
    if (tree[i].right != -1)
      parents[tree[i].right] = i;
  }
  //for (int i = 0; i < parents.size(); i++) {
  //  std::cout << i << ": " << parents[i] << std::endl;
  //}
  int root = -1;
  for (int i = 0; i < parents.size(); i++) {
    if (parents[i] == -1) {
      root = i;
      break;
    }
  }
  if (root == -1) // empty tree
    return true;
  //std::cout << "Root: " << root << std::endl;
  return ((RecurIsBinarySearchTreeLeft(tree, root, std::numeric_limits<long long>::max())) && (RecurIsBinarySearchTreeRight(tree, root, std::numeric_limits<long long>::min())));
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
