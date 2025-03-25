#include <iostream>
#include <string>

class SList {
 public:
  struct Obj {
    std::string s;
    int i;
    double d;
  };

  SList() : head_(nullptr) {}
  ~SList() {
    while (head_) {
      Node* tmp = head_;
      head_ = head_->next;
      delete tmp;
    }
  }

  void PushBack(const Obj &o) {
    Node* n = new Node{o, nullptr};
    if (!head_) {
      head_ = n;
      return;
    }
    Node* cur = head_;
    while (cur->next)
      cur = cur->next;
    cur->next = n;
  }

  void InsertAfter(int index, const Obj &o) {
    Node* cur = head_;
    for (int i = 0; cur && i < index; ++i)
      cur = cur->next;
    if (!cur)
      return;
    Node* n = new Node{o, cur->next};
    cur->next = n;
  }

  void InsertBefore(int index, const Obj &o) {
    if (index <= 0 || !head_) {
      head_ = new Node{o, head_};
      return;
    }
    Node* cur = head_;
    for (int i = 0; cur->next && i < index - 1; ++i)
      cur = cur->next;
    Node* n = new Node{o, cur->next};
    cur->next = n;
  }

  void RemoveAt(int index) {
    if (!head_)
      return;
    if (index == 0) {
      Node* tmp = head_;
      head_ = head_->next;
      delete tmp;
      return;
    }
    Node* cur = head_;
    for (int i = 0; cur->next && i < index - 1; ++i)
      cur = cur->next;
    if (!cur->next)
      return;
    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
  }

  void Print() const {
    for (Node* cur = head_; cur; cur = cur->next)
      std::cout << cur->data.s << " " << cur->data.i << " " << cur->data.d << "\n";
  }

 private:
  struct Node {
    Obj data;
    Node* next;
  };

  Node* head_;
};

int main() {
  SList list;
  list.PushBack({"one", 1, 1.1});
  list.PushBack({"two", 2, 2.2});
  list.PushBack({"three", 3, 3.3});
  list.InsertAfter(1, {"after_two", 22, 22.22});
  list.InsertBefore(0, {"before_one", 0, 0.0});
  list.RemoveAt(2);
  list.Print();
  return 0;
}

/*

before_one 0 0
one 1 1.1
after_two 22 22.22
three 3 3.3

*/