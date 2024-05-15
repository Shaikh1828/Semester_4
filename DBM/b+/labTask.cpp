#include <bits/stdc++.h>
using namespace std;

int numberOfPointer, key, hopsize = 0;

struct Node {
    int totalKeys;
    Node *parentNode, *nextNode;
    Node **nodePointers;
    bool isLeaf;
    int *numbers;
};

Node *root;

Node *createNewNode() {
    Node *newnode = new Node();
    newnode->totalKeys = 0;
    newnode->parentNode = NULL;
    newnode->nextNode = NULL;
    newnode->nodePointers = new Node *[numberOfPointer + 1];
    for (int i = 0; i <= numberOfPointer; i++) {
        newnode->nodePointers[i] = nullptr;
    }
    newnode->isLeaf = true;
    newnode->numbers = new int[key + 1];
    return newnode;
}

void createNewRoot(Node *node, int value, Node *leftChild, Node *rightChild) {
    node = createNewNode();
    node->isLeaf = false;
    node->numbers[0] = value;
    node->totalKeys++;
    node->nodePointers[0] = rightChild; //changes
    node->nodePointers[1] = leftChild;  //changes
    rightChild->parentNode = node;     //changes
    leftChild->parentNode = node;       //changes
    root = node;
}

Node *searchPlace(Node *node, int num) {
    while (node->isLeaf == false) {
        int i;
        for (i = 0; i < node->totalKeys; i++) {
            if (num > node->numbers[i]) {         //changes
                break;
            }
        }
        node = node->nodePointers[i];
        hopsize++;
    }
    return node;
}

void addWithParent(Node *parent, int value, Node *rightChild) {
    int track = parent->totalKeys;
    track--;

    if (track > -1) {
        for (; track > -1; track--) {
            if (parent->numbers[track] <= value)
                break;
            else {
                parent->numbers[track + 1] = parent->numbers[track];
                parent->nodePointers[track + 2] = parent->nodePointers[track + 1];
            }
        }
    }
    parent->numbers[track + 1] = value;
    parent->nodePointers[track + 2] = rightChild;
    parent->totalKeys++;
}

void moveUp(Node *parent, int value, Node *leftChild, Node *rightChild) {
    if (parent == NULL) {
        createNewRoot(parent, value, leftChild, rightChild);
        return;
    }

    // parent exists, then add to the parent
    rightChild->parentNode = parent;
    addWithParent(parent, value, rightChild);

    // balancing in the parent node
    if (parent->totalKeys == numberOfPointer) {
        Node *secondNode = createNewNode(); // second node
        secondNode->isLeaf = false;

        int mark = parent->totalKeys, j = 0;

        for (int i = mark - (numberOfPointer / 2); i < numberOfPointer; i++) {
            secondNode->numbers[j] = parent->numbers[i];
            if (j == 0) {
                secondNode->nodePointers[0] = parent->nodePointers[i]; // look up later
                secondNode->nodePointers[0]->parentNode = secondNode;
            }

            secondNode->nodePointers[j + 1] = parent->nodePointers[i + 1];
            secondNode->nodePointers[j + 1]->parentNode = secondNode;
            j++;
        }

        parent->totalKeys -= (mark / 2 + 1);
        secondNode->totalKeys = (mark / 2);

        // move up recursively
        moveUp(parent->parentNode, parent->numbers[parent->totalKeys], parent, secondNode);
    }
}

void addToLeaf(int num) {
    // searching for an appropriate place
    Node *leaf = searchPlace(root, num);

    // sorting and insertion
    int track = leaf->totalKeys;
    track--;

    if (track > -1) {
        for (; track > -1; track--) {
            if (num > leaf->numbers[track]) {                   // changes
                leaf->numbers[track + 1] = leaf->numbers[track];
            } else
                break;
        }
    }
    leaf->numbers[track + 1] = num;
    leaf->totalKeys++;

    // balancing
    if (leaf->totalKeys == numberOfPointer) {
        Node *secondNode = createNewNode(); // second node

        int mark = leaf->totalKeys, j = 0;
        for (int i = mark - (numberOfPointer / 2); i < numberOfPointer; i++) {
            secondNode->numbers[j] = leaf->numbers[i];
            j++;
        }

        leaf->totalKeys -= (numberOfPointer / 2);
        secondNode->totalKeys = (numberOfPointer / 2);
        secondNode->nextNode = leaf->nextNode;
        leaf->nextNode = secondNode;

        // move up
        moveUp(leaf->parentNode, secondNode->numbers[0], leaf, secondNode);
    }
}

void searchNumber() {
    int num;
    cout << "Enter the number to search: ";
    cin >> num;

    hopsize = 0;
    Node *leaf = searchPlace(root, num);
    for (int i = 0; i < leaf->totalKeys; i++) {
        if (leaf->numbers[i] == num) {
            cout << "Number " << num << " found." << endl;
            return;
        }
    }
    cout << "Number " << num << " not found." << endl;
}

void printNode(Node *node, int depth) {
    for (int i = 0; i < depth; i++)
        cout << "  "<< depth << " ";
    cout << "[";
    for (int i = 0; i < node->totalKeys; i++) {
        cout << node->numbers[i];
        if (i < node->totalKeys - 1)
            cout << " ";
    }
    cout << "]" << endl;
}

void printBPlusTree(Node *node, int depth) {
    if (node->isLeaf) {
        printNode(node, depth);
        return;
    }
    for (int i = 0; i < node->totalKeys; i++) {
        printBPlusTree(node->nodePointers[i], depth + 1);
        if (i < node->totalKeys - 1)
            printNode(node, depth);
    }
    printBPlusTree(node->nodePointers[node->totalKeys], depth + 1);
}

bool buildBPlusTree() {
    int words;
    root = createNewNode();

    ifstream filePtr;
    filePtr.open("input.txt");

    if(!filePtr)
    {
        puts("File couldn't be opened");
        return false;
    }
    else
    {
        while( filePtr >> words )
        {
            //getline( filePtr, meaning );
            addToLeaf( words );
        }
        filePtr.close();
    }

    return true;
}

int main() {
    puts("Enter the number of pointers: ");
    cin >> numberOfPointer;
    key = numberOfPointer - 1;

    if (buildBPlusTree())
        puts("Tree has been built successfully.");
    else
        puts("Sorry. Tree couldn't be built");
    
    cout << "B+ Tree:" << endl;
    printBPlusTree(root, 0);

 //   searchNumber();
}




















// #include<bits/stdc++.h>
// using namespace std;

// int numberOfPointer, key;
// int hopsize = 0;

// struct Node
// {
//     int totalKeys;
//     Node *parentNode, *nextNode;
//     Node **nodePointers;
//     bool isLeaf;
//     string *words;
// };

// Node *root;

// Node *createNewNode()
// {
//     Node *newnode = new Node();

//     newnode->totalKeys = 0;
//     newnode->parentNode = NULL;
//     newnode->nextNode = NULL;
//     newnode->nodePointers = new Node *[numberOfPointer+1];
//     for ( int i = 0; i <= numberOfPointer; i++ )
//     {
//         newnode->nodePointers[i] = nullptr;
//     }
//     newnode->isLeaf = true;
//     newnode->words = new string[numberOfPointer];
//     //newnode->meaning = new string[numberOfPointer];
//     return newnode;
// }

// void createNewRoot(Node *node,string value,Node *leftChild,Node *rightChild)
// {
//     node = createNewNode(); // node
//     node->isLeaf=false; 
//     node->words[0]=value; //
//     node->totalKeys++;
//     node->nodePointers[0]=leftChild;
//     node->nodePointers[1]=rightChild;
//     leftChild->parentNode=node;
//     rightChild->parentNode=node;
//     root=node;
// }   

// Node *searchPlace(Node *node, string words)
// {
//     while( node->isLeaf == false )
//     {
//         int i;
//         for( i = 0; i < node->totalKeys; i++ )
//         {
//             if(words < node->words[i] )
//             {
//                 break;
//             }
//         }
//         node = node->nodePointers[i];
//         hopsize++;
//     }

//     return node;
// }


// void addWithParent(Node *parent,string value,Node *rightChild)
// {
//     int track=parent->totalKeys;
//     track--;

//     if(track>-1)
//     {
//         for(;track>-1;track--)
//         {
//             if (parent->words[track] <= value)
//             break;
//             else
//             {
//                 parent->words[track+1]=parent->words[track];
//                 parent->nodePointers[track+2]=parent->nodePointers[track+1];
//             }
//         }
//     }
//     parent->words[track+1]=value;
//     parent->nodePointers[track+2]=rightChild;
//     parent->totalKeys++;
// }

// void moveUp(Node *parent, string value, Node *leftChild, Node *rightChild)
// {
//     if(parent == NULL)
//     {
//         createNewRoot(parent, value, leftChild, rightChild);
//         return;
//     }

//     rightChild->parentNode = parent;
//     addWithParent(parent, value, rightChild);

//     // spliting parent node
//     if(parent->totalKeys == numberOfPointer)
//     {
//         Node *secondNode = createNewNode();   
//         secondNode->isLeaf = false;

//         int mark = parent->totalKeys, j = 0;
       
//         for( int i = mark-(numberOfPointer/2); i < numberOfPointer; i++ )
//         {
//             secondNode->words[j] = parent->words[i];
//             if( j == 0 )
//             {
//                 secondNode->nodePointers[0] = parent->nodePointers[i];
//                 secondNode->nodePointers[0]->parentNode = secondNode;
//             }

//             secondNode->nodePointers[j+1] = parent->nodePointers[i+1];
//             secondNode->nodePointers[j+1]->parentNode = secondNode;
//             j ++;
//         }
        
//         parent->totalKeys -= (mark/2+1); 
//         secondNode->totalKeys = (mark/2); 

//         // move up recursively
//         moveUp(parent->parentNode,parent->words[parent->totalKeys],parent,secondNode);
//     }
// }

// void addToLeaf(string words)
// {
//     Node *leaf = searchPlace(root, words);

//     // sorting and insertion
//     int track = leaf->totalKeys;
//     track --;

//     if(track >= 0)
//     {
//         for( ; track > -1; track-- )
//         {
//             if( words > leaf->words[track] )
//             {
//                 leaf->words[track+1] = leaf->words[track];
//                 //leaf->meaning[track+1] = leaf->meaning[track];
//             }
//             else break;
//         }
//     }
//     leaf->words[track+1] = words;
//     //leaf->meaning[track+1] = meaning;
//     leaf->totalKeys ++;

//     // leaf node spliting
//     if(leaf->totalKeys == numberOfPointer)
//     {
//         Node *secondNode = createNewNode();   

//         int mark = leaf->totalKeys, j = 0;
        
//         for(int i = mark-(numberOfPointer/2); i < numberOfPointer; i++ )
//         {
//             secondNode->words[j] = leaf->words[i];
//             //secondNode->meaning[j] = leaf->meaning[i];
//             j ++;
//         }

//         leaf->totalKeys -= (numberOfPointer / 2);
//         secondNode->totalKeys = numberOfPointer/2;
//         secondNode->nextNode = leaf->nextNode;
//         leaf->nextNode = secondNode;

//         // move up
//         moveUp(leaf->parentNode, secondNode->words[0], leaf, secondNode);
//     }
// }

// void searchWord()
// {
//     int i;
//     puts("enter the word:");
//     string word;
//     cin >> word;
//     // for (auto &a : word )
//     // {
//     //     a = tolower(a);
//     // }
//     //transform(word.begin(), word.end(), word.begin(), ::tolower);

//     hopsize = 0;
//     Node *leaf = searchPlace(root, word);
//     for( i = 0; i < leaf->totalKeys; i++ )
//     {
//         if(leaf->words[i] == word) break;
//     }
//     //freopen("ans.txt","w",stdout);

//     if(i == leaf->totalKeys) cout << "Sorry. Word not found";
//     else
//     {
//         cout << word << " is found.\n";
//     }
//     cout << "Hop Size " << hopsize <<"\n";
// }

// bool buildBPlusTree()
// {
//     string words;
//     root = createNewNode();

//     ifstream filePtr;
//     filePtr.open("input.txt");

//     if(!filePtr)
//     {
//         puts("File couldn't be opened");
//         return false;
//     }
//     else
//     {
//         while( filePtr >> words )
//         {
//             //getline( filePtr, meaning );
//             addToLeaf( words );
//         }
//         filePtr.close();
//     }

//     return true;
// }

// // void printTree( Node *node )
// // {   
// //     while( node->isLeaf == false)
// //     {
// //         node = node.n
        
// //     }

    
// // }

// void printNode(Node *node, int depth) 
// {
//     for ( int i = 0; i < depth; i++ ) ;
//     cout << "[";
//     for (int i = 0; i < node->totalKeys; i++) 
//     {
//         cout << node->words[i];
//         if (i < node->totalKeys - 1)
//             cout << " ";
//     }
//     cout << "]" ;
// }


// void printBPlusTree( Node *node, int depth ) 
// {
//     if ( node->isLeaf ) 
//     {
//         printNode(node, depth);
//         return;
//     }

//     for (int i = 0; i < node->totalKeys; i++) 
//     {
//         printBPlusTree(node->nodePointers[i], depth + 1);
//         if ( i < node->totalKeys - 1 )
//             printNode(node, depth);
//     }
//     printBPlusTree( node->nodePointers[node->totalKeys], depth + 1 );
// }



// int main()
// {
//     cout << "Number of pointers : ";
//     cin >> numberOfPointer;
//     key = numberOfPointer - 1;

//     if(buildBPlusTree()) puts("Tree has been built successfully.");
//     else puts("Sorry. Tree couldn't be built.");

//     //searchWord();

//     printBPlusTree( root, 0);
// }