#include<bits/stdc++.h>
using namespace std;

int numberOfPointer,key;

struct Node{
    int totalKeys;
    Node *parentNode,*nextNode;
    Node **nodePointers;
    bool isLeaf;
    string *english,*meaning;
};

Node *root;

Node *createNewNode()
{
    Node *newnode=new Node();

    newnode->totalKeys=0;
    newnode->parentNode=NULL;
    newnode->nextNode=NULL;
    newnode->nodePointers=new Node *[numberOfPointer+1];
    for (int i = 0; i < numberOfPointer; i++)
    {
        newnode->nodePointers[i] = nullptr;
    }
    newnode->isLeaf=true;
    newnode->english=new string[key+1];
    newnode->meaning=new string[key+1];

    return newnode;
}

void createNewRoot(Node *node,string value,Node *leftChild,Node *rightChild)
{
    node=createNewNode();
    node->isLeaf=false;
    node->english[0]=value;
    node->totalKeys++;
    node->nodePointers[0]=leftChild;
    node->nodePointers[1]=rightChild;
    leftChild->parentNode=node;
    rightChild->parentNode=node;
    root=node;
}

Node *searchPlace(Node *node,string english)
{
    while(node->isLeaf==false)
    {
        int i;
        for( i=0;i<node->totalKeys;i++)
        {
            if(english<node->english[i])
            {
                break;
            }
        }
        node=node->nodePointers[i];
    }

    return node;
}


void addWithParent(Node *parent,string value,Node *rightChild)
{
    int track=parent->totalKeys;
    track--;

    if(track>-1)
    {
        for(;track>-1;track--)
        {
            if (parent->english[track] <= value)
            break;
            else
            {
                parent->english[track+1]=parent->english[track];
                parent->nodePointers[track+2]=parent->nodePointers[track+1];
            }
        }
    }
    parent->english[track+1]=value;
    parent->nodePointers[track+2]=rightChild;
    parent->totalKeys++;
}

void moveUp(Node *parent,string value,Node *leftChild,Node *rightChild)
{
    if(parent==NULL)
    {
        createNewRoot(parent,value,leftChild,rightChild);
        return;
    }

    // parent exists, then add to the parent
    rightChild->parentNode = parent;
    addWithParent(parent,value,rightChild);

    // balancing in the parent node
    if(parent->totalKeys==numberOfPointer)
    {
        Node *secondNode=createNewNode();    // second node
        secondNode->isLeaf=false;

        int mark=parent->totalKeys,j=0;

        for(int i=mark/2;i<mark;i++)
        {
            if(j==0)
            {
                secondNode->nodePointers[0]=parent->nodePointers[i];   // look up later
                secondNode->nodePointers[0]->parentNode=secondNode;
            }

            secondNode->nodePointers[j+1]=parent->nodePointers[i+1];
            secondNode->nodePointers[j+1]->parentNode=secondNode;
            j++;
        }

        parent->totalKeys=mark/2;
        secondNode->totalKeys=mark-(mark/2);
        //secondNode->nextNode=parent->nextNode;
       // parent->nextNode=secondNode;

        // move up recursively
        moveUp(parent->parentNode,parent->english[parent->totalKeys],parent,secondNode);
    }
}

void addToLeaf(string english,string meaning)
{
    // searching for an appropriate place
    Node *leaf=searchPlace(root,english);

    // sorting and insertion
    int track=leaf->totalKeys;
    track--;

    if(track>-1)
    {
        for(;track>-1;track--)
        {
            if(english<leaf->english[track])
            {
                leaf->english[track+1]=leaf->english[track];
                leaf->meaning[track+1]=leaf->meaning[track];
            }
            else break;
        }
    }
    leaf->english[track+1]=english;
    leaf->meaning[track+1]=meaning;
    leaf->totalKeys++;

    // balancing
    if(leaf->totalKeys==numberOfPointer)
    {
        Node *secondNode=createNewNode();    // second node

        int mark=leaf->totalKeys,j=0;
        for(int i=mark/2;i<mark;i++)
        {
            secondNode->english[j]=leaf->english[i];
            secondNode->meaning[j]=leaf->meaning[i];
            j++;
        }

        leaf->totalKeys=mark/2;
        secondNode->totalKeys=mark-(mark/2);
        secondNode->nextNode=leaf->nextNode;
        leaf->nextNode=secondNode;

        // move up
        moveUp(leaf->parentNode,secondNode->english[0],leaf,secondNode);
    }
}

void searchMeaning()
{
    int i;
    puts("enter the word:");
    string word;
    cin>>word;

    Node *leaf=searchPlace(root,word);
    for(i=0;i<leaf->totalKeys;i++)
    {
        if(leaf->english[i]==word) break;
    }
    freopen("ans.txt","w",stdout);
    if(i==leaf->totalKeys) puts("sorry. no word found");
    else
    {
        cout<<word<<" means "<<leaf->meaning[i]<<"\n";
    }
}

bool buildBPlusTree()
{
    string english,meaning;
    root=createNewNode();

    ifstream filePtr;
    filePtr.open("dictionary.txt");

    if(!filePtr)
    {
        puts("file couldn't be opened");
        return false;
    }
    else
    {
        while(filePtr>>english)
        {
            getline(filePtr,meaning);
            addToLeaf(english,meaning);
        }
    }
    return true;
}

int main()
{
    puts("enter the number of pointers: ");
    cin>>numberOfPointer;
    key=numberOfPointer-1;

    if(buildBPlusTree()) puts("tree has been built successfully.");
    else puts("sorry. tree couldn't be built");

    searchMeaning();
}