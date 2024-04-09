#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <ostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <vector>

using namespace std;



class BSTMapNode {
public:
  string key;
  int value;
  BSTMapNode *left;
  BSTMapNode *right;

  BSTMapNode(const string &k, const int &v, BSTMapNode *l = nullptr,
             BSTMapNode *r = nullptr) {
    key = k;
    value = v;
    left = l;
    right = r;
  }
};

//class BSTPrinter;

class BSTMap {
  friend class BSTPrinter;

private:
  BSTMapNode *root; // Root of the BST

  BSTMapNode *putHelp(BSTMapNode *root, const string &ik, const int &val) {
    if (root == nullptr)
      return new BSTMapNode (ik, val);
    if (ik < root->key)
      root->left = putHelp(root->left, ik, val);
    else if (ik > root->key)
      root->right = putHelp(root->right, ik, val);
    return root;
  }

  bool findHelp(const BSTMapNode *root, const string &sk) const {
    if (root == nullptr)
      return false;
    if (sk < root->key)
      return findHelp(root->left, sk);
    if (sk > root->key)
      return findHelp(root->right, sk);
    else
      return true;
  }

public:
  BSTMap() { root = nullptr; }
  ~BSTMap() { clear(root); }

  /** Delete all nodes. */
  void clear(BSTMapNode *root) {
    if (root == nullptr)
      return;
    clear(root->left);
    clear(root->right);
    delete root;
  }

  
  /**
   * Print the BST level by level, from top to bottom and left to right.
   */
  void print(ostream &os) {
    vector<vector<string>> lines;
    vector<BSTMapNode *> level;
    vector<BSTMapNode *> next;

    level.push_back(root);
    int nn = 1;
    size_t widest = 0;

    while (nn != 0) {
      vector<string> line;
      nn = 0;

      for (BSTMapNode *n : level) {
        if (n == nullptr) {
          line.push_back("");

          next.push_back(nullptr);
          next.push_back(nullptr);
        } else {
          std::stringstream ss;
          ss << n->key << ":" << n->value;
          string aa = ss.str();
          line.push_back(aa);
          if (aa.length() > widest)
            widest = aa.length();

          next.push_back(n->left);
          next.push_back(n->right);

          if (n->left != nullptr)
            nn++;
          if (n->right != nullptr)
            nn++;
        }
      }

      if (widest % 2 == 1)
        widest++;

      lines.push_back(line);

      vector<BSTMapNode *> tmp = level;
      level = next;
      next = tmp;
      next.clear();
    }

    int perpiece = lines.at(lines.size() - 1).size() * (widest + 4);
    for (size_t i = 0; i < lines.size(); i++) {
      vector<string> line = lines.at(i);
      int hpw = (int)floor(perpiece / 2.f) - 1;

      if (i > 0) {
        for (size_t j = 0; j < line.size(); j++) {
          // split node
          char c = ' ';
          if (j % 2 == 1) {
            if (line.at(j - 1) != "") {
              c = '+';
            } else if (j < line.size() && line.at(j) != "") {
              c = '+';
            }
          }
          os << c;

          // lines and spaces
          if (line.at(j) == "") {
            for (int k = 0; k < perpiece - 1; k++) {
              os << " ";
            }
          } else {
            for (int k = 0; k < hpw; k++) {
              os << (j % 2 == 0 ? " " : "─");
            }
            os << (j % 2 == 0 ? "┌" : "┐");
            for (int k = 0; k < hpw; k++) {
              os << (j % 2 == 0 ? "─" : " ");
            }
          }
        }
        // os << "\\n\"\n";
        os << "\n";
      }

      for (size_t j = 0; j < line.size(); j++) {
        string f = line.at(j);
        int gap1 = (int)ceil(perpiece / 2.f - f.length() / 2.f);
        int gap2 = (int)floor(perpiece / 2.f - f.length() / 2.f);
        for (int k = 0; k < gap1; k++) {
          os << " ";
        }
        os << f;
        for (int k = 0; k < gap2; k++) {
          os << " ";
        }
      }
      // os << "\\n\"\n";
      os << "\n";

      perpiece /= 2;
    }
  }

  /**
   * Insert the key-value pair `ik` and `val` to the BSTMap.
   *
   * @param ik The key to insert
   * @param val The value corresponding to the key
   */
  void put(const string &ik, const int &val) {
    root = putHelp(root, ik, val);
  }

  /**
   * Search for given key in the BSTMap.
   *
   * @param sk The search key
   * @return true if `sk` is in the BSTMap
   */
  bool find(const string &sk) const { return findHelp(root, sk); }

  int get(const string &sk) const;
  void remove(const string &rk);
};

/**
 * Return the value of the given search key `sk` in the BSTMap.
 */
int BSTMap::get(const string &sk) const {
  // TODO: You may assume that `sk` is in the BSTMap.
   int v;
   return v;
}

/**
 * Remove `rk` and its corresponding value from the BST.
 */
void BSTMap::remove(const string &rk) {
  // TODO: You may assume that `rk` is in the BSTMap.
}



#endif // __BSTMAP_H__
