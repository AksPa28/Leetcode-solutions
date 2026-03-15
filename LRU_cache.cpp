#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
    struct Node {
        int key, value;
        Node *prev, *next;
        Node (int key, int value): key(key), value(value), prev(nullptr), next(nullptr) {}
    };
        int maxSize;
        unordered_map<int, Node*> mp;
        Node *head = new Node(-1, -1), *tail = new Node(-1, -1);

public:
    LRUCache(int capacity): maxSize(capacity) {
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node* newNode){
        Node* nextNode = head->next;
        head->next = newNode;
        nextNode->prev = newNode;
        newNode->next = nextNode;
        newNode->prev = head;
    }

    void deleteNode(Node *node){
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
    
    int get(int key) {
        if(mp.find(key) != mp.end()){
            Node* foundNode = mp[key];
            int ans = foundNode->value;
            mp.erase(key);
            deleteNode(foundNode);
            addNode(foundNode);
            mp[key] = head->next;
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()){
            Node* foundNode = mp[key];
            mp.erase(key);
            deleteNode(foundNode);
        }
        if(mp.size() == maxSize){
            mp.erase(tail->prev->key);
            deleteNode(tail->prev);
        }
        addNode(new Node(key, value));
        mp[key] = head->next;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */