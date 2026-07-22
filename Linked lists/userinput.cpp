#include <bits/stdc++.h>
using namespace std;
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

int main() {

    int n;
    cin >> n;

    Node* head = nullptr;
    Node* tail = nullptr;

    while (n--) {
        int x;
        cin >> x;

        Node* node = new Node(x);

        if (!head)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
}