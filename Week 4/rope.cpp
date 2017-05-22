#include <cstdio>
#include <string>
#include <iostream>
#include <stack>
#include <cstdio>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  char key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long size;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, int size, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), size(size), left(left), right(right), parent(parent) {}
};

class Rope {
	std::string s;
	Vertex* root = NULL;
	void update(Vertex* v) {
	  if (v == NULL) return;
	  v->size = 1 + (v->left != NULL ? v->left->size : 0ll) + (v->right != NULL ? v->right->size : 0ll);
	  if (v->left != NULL) {
	    v->left->parent = v;
	  }
	  if (v->right != NULL) {
	    v->right->parent = v;
	  }
	}

	void small_rotation(Vertex* v) {
	  Vertex* parent = v->parent;
	  if (parent == NULL) {
	    return;
	  }
	  Vertex* grandparent = v->parent->parent;
	  if (parent->left == v) {
	    Vertex* m = v->right;
	    v->right = parent;
	    parent->left = m;
	  } else {
	    Vertex* m = v->left;
	    v->left = parent;
	    parent->right = m;
	  }
	  update(parent);
	  update(v);
	  v->parent = grandparent;
	  if (grandparent != NULL) {
	    if (grandparent->left == parent) {
	      grandparent->left = v;
	    } else {
	      grandparent->right = v;
	    }
	  }
	}

	void big_rotation(Vertex* v) {
	  if (v->parent->left == v && v->parent->parent->left == v->parent) {
	    // Zig-zig
	    small_rotation(v->parent);
	    small_rotation(v);
	  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
	    // Zig-zig
	    small_rotation(v->parent);
	    small_rotation(v);
	  } else {
	    // Zig-zag
	    small_rotation(v);
	    small_rotation(v);
	  }  
	}

	// Makes splay of the given vertex and makes
	// it the new root.
	void splay(Vertex*& root, Vertex* v) {
	  if (v == NULL) return;
	  while (v->parent != NULL) {
	    if (v->parent->parent == NULL) {
	      small_rotation(v);
	      break;
	    }
	    big_rotation(v);
	  }
	  root = v;
	}
	// Utilizes size property to find 
	Vertex* find(Vertex*& root, int i) {
	  Vertex* v = root;
	  while (v != NULL) {
		  long long size;
		  if (v->left != NULL) {
			size = v->left->size;
		  } else {
			size = 0;
		  }
		  if (i == size) {
			break;
		  } else if (i < size) { // if item is on left
		  	v = v->left;
		  } else { // if item is on right
		  	i -= (size+1); // update i to fit the size on the right correctly
		  	v = v->right;
		  }
	  }
	  splay(root, v);
	  return v;
	}

	void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
	  right = find(root, key);
	  splay(root, right);
	  if (right == NULL) {
	    left = root;
	    return;
	  }
	  left = right->left;
	  right->left = NULL;
	  if (left != NULL) {
	    left->parent = NULL;
	  }
	  update(left);
	  update(right);
	}

	Vertex* merge(Vertex* left, Vertex* right) {
	  if (left == NULL) return right;
	  if (right == NULL) return left;
	  Vertex* min_right = right;
	  while (min_right->left != NULL) {
	    min_right = min_right->left;
	  }
	  splay(right, min_right);
	  right->left = left;
	  update(right);
	  return right;
	}
	std::string in_order() {
        std::string result;
        if (root == NULL) {
            return "";
        }
        std::stack<Vertex*> S;
        Vertex* p = root;

        while (p != NULL) {
            S.push(p);
            p = p->left;
        }

        while (!S.empty()) {
            p = S.top();
            result.push_back(p->key);
            S.pop();
            p = p->right;
            while (p != NULL) {
                S.push(p);
                p = p->left;
            }
        }
        return result;
    }
public:
	Rope(const std::string &s) : s(s) { 
		for (int i = 0; i < s.length(); i++) {
			root = merge(root, new Vertex(s[i], 1, NULL, NULL, NULL));
		}
	}

	void process(int i, int j, int k) {
       Vertex* left = NULL;
	   Vertex* middle = NULL; // what is moved around
	   Vertex* right = NULL;
	   split(root, i, left, right);
	   split(right, j - i + 1, middle, right);
	   Vertex* temp = merge(left, right);
	   split(temp, k, left, right);
	   root = merge(merge(left, middle), right);
	}

	std::string result() {
		return in_order();
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	std::cout << rope.result() << std::endl;
}
