#include <iostream>
#include <fstream>
#include <map>

using namespace std;

template <typename T>
struct nodeType
{
    nodeType* left;
    nodeType* right;
    T payload;
};

struct linkedListNode
{
    char symbol;
    int count;
    linkedListNode *next;

    linkedListNode() : symbol(0), count(0), next(nullptr) {}

    void put(linkedListNode* newNode) {
        linkedListNode* ptr = this;

        // Find the right place in the list to insert the node
        while (ptr->next != nullptr && ptr->next->count < newNode->count) {
			ptr = ptr->next;
        }

        linkedListNode* tmp = ptr->next;
        ptr->next = newNode;
        newNode->next = tmp;
    }

    void print() {
        cout << symbol << "(" << count << ")";
        if (next) {
            cout << "-> ";
            next->print();
        }
    }
};

void printMap(map<char, int> m);

linkedListNode* convertToLinkedList(map<char, int> charMap) {
	// use the first element of the map to create a 1-item linked list
    linkedListNode* head = new linkedListNode();
    head->symbol = charMap.begin()->first;
    head->count = charMap.begin()->second;

    map<char, int>::iterator it;
    for (it = charMap.begin(); it != charMap.end(); it++)
    {
        if (it == charMap.begin())
            continue;  // first value was already added

        // make a new node and put it into the list
        linkedListNode* newNode = new linkedListNode();
        newNode->symbol = it->first;
        newNode->count = it->second;

        head->put(newNode);
    }

    return head;
}

int main()
{
    /***** TASK ONE- INPUT *****/
    /* OPen file stream */
    ifstream in;
    in.open("input.txt");
    if (!in)
    {
        cout << "ERR: File not found" << endl;
        return 1;
    }

    /* Use a map to count characters */
    char c;
    map<char, int> charMap;
    while (!in.eof())
    {
        in >> c;
        if (in.eof())
            break;

        if (charMap.find(c) == charMap.end())
            charMap.emplace(c, 1);
        else
            charMap.at(c)++;
    }
    printMap(charMap);

    linkedListNode* root = convertToLinkedList(charMap);
    root->print();

    in.close();

    return 0;
}

void printMap(map<char, int> m)
{
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
}
