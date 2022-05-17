#include <bits/stdc++.h>
using namespace std;
enum Color {RED, BLACK};

class Node
{
public:
    int data;
    Node *right, *left, *parent;
    bool color;
    Node(int x)
    {
        right=left=parent=NULL;
        data=x;
        color = RED;
    }
};

class RBTree
{
private:
    Node* root;
public:
    RBTree()
    {
        root=NULL;
    }
    RBTree(Node* nod)
    {
        root=nod;
    }
    void insert(int );
    void Delete(int );
    void inorder();
    void levelOrder();
    bool search(int );
};

//Search
Node* searchHelper(Node* root, int val)
{
    if(root == NULL || root->data == val)
        return root;
    if(root->data < val)
        return searchHelper(root->right,val);
    else
        return searchHelper(root->left, val);
}
bool RBTree::search(int val)
{
  if(searchHelper(root, val))
    return true;
  else return false;
}

//Tools
void rotateLeft(Node*& root, Node*& nod)
{
    Node *nod_right = nod->right;
    nod->right = nod_right->left;

    if (nod->right != NULL)
        nod->right->parent = nod;

    nod_right->parent = nod->parent;

    if (nod->parent == NULL)
        root = nod_right;
    else if (nod == nod->parent->left)
        nod->parent->left = nod_right;
    else
        nod->parent->right = nod_right;

    nod_right->left = nod;
    nod->parent = nod_right;
}
void rotateRight(Node *&root, Node *&nod)
{
    Node *nod_left = nod->left;
    nod->left = nod_left->right;

    if (nod->left != NULL)
        nod->left->parent = nod;

    nod_left->parent = nod->parent;

    if (nod->parent == NULL)
        root = nod_left;
    else if (nod == nod->parent->left)
        nod->parent->left = nod_left;
    else
        nod->parent->right = nod_left;

    nod_left->right = nod;
    nod->parent = nod_left;
}
Node* get_sibling(Node* nod)
{
    if(nod->parent!= NULL)
    {
        if(nod->parent->right == nod)
            return nod->parent->left;
        else return nod->parent->right;
    }
    else return NULL;
}

//Insert:
Node* BasicInsert(Node*& root, Node* nod)
{
    if(root==NULL)
        return nod;
    if(nod->data > root->data)
    {
        root->right = BasicInsert(root->right, nod);
        root->right->parent = root;
    }
    else
    {
        root->left = BasicInsert(root->left, nod);
        root->left->parent = root;
    }
    return root;
}
void fixInsertion(Node *&root, Node *&nod)
{
    Node *parent = NULL;
    Node *grandParent = NULL;
    Node *uncle = NULL;

    while(nod!=root && nod->color != BLACK && nod->parent->color == RED)
    {
        parent = nod->parent;
        grandParent = nod->parent->parent;

        if(parent == grandParent->left)
        {
            uncle = grandParent->right;
            if(uncle!=NULL && uncle->color==RED)
            {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                nod = grandParent;
            }
            else
            {
                if(nod == parent->right)
                {
                    rotateLeft(root, parent);
                    nod = parent;
                    parent = nod->parent;
                }
                rotateRight(root, grandParent);
                swap(parent->color, grandParent->color);
                nod = parent;
            }
        }
        else
        {
            uncle = grandParent->left;
            if(uncle!=NULL && uncle->color==RED)
            {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                nod = grandParent;
            }
            else
            {
                if(nod == parent->left)
                {
                    rotateRight(root, parent);
                    nod = parent;
                    parent = nod->parent;
                }
                rotateLeft(root, grandParent);
                swap(parent->color, grandParent->color);
                nod = parent;
            }
        }
    }
    root->color = BLACK;
}
void RBTree::insert(int x)
{
    Node* node = new Node(x);
    root = BasicInsert(root, node);
    fixInsertion(root, node);
}

//Delete:
Node* succesor(Node* nod)
{
    Node* temp = nod;

    while(temp->left!=NULL)
        temp=temp->left;
    return temp;
}
Node* Replacement(Node* nod)
{
    if(!nod->left && !nod->right)
        return NULL;
    else if(!nod->left)
        return nod->right;
    else if(!nod->right)
        return nod->left;
    else return succesor(nod->right);
}
void fixDoubleBlack(Node* root, Node* x)
{
    if(x==root) return;
    Node* sibling = get_sibling(x);
    Node* parent = x->parent;
    if(!sibling) fixDoubleBlack(root, parent);
    else
    {
        if(sibling->color == RED)
        {
            parent->color = RED;
            sibling->color = BLACK;
            if(sibling -> parent -> left == sibling)
                rotateRight(root, parent);
            else
                rotateLeft(root, parent);

            fixDoubleBlack(root, x);
        }
        else
        {
            if((sibling->left&&sibling->left->color == RED) || (sibling->right&&sibling->right->color == RED))
            {
                //macar unu rosu
                if(sibling->left && sibling->left->color == RED)
                {
                    //LEFT LEFT
                    if(sibling -> parent -> left == sibling)
                    {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(root, parent);
                    }
                    //RIGHT LEFT
                    else
                    {
                        sibling->left->color = parent->color;
                        rotateRight(root, sibling);
                        rotateLeft(root, parent);
                    }
                }
                else
                {
                    //LEFT RIGHT
                    if(sibling -> parent -> left == sibling)
                    {
                        sibling->right->color = parent->color;
                        rotateLeft(root, sibling);
                        rotateRight(root, parent);
                    }
                    //RIGHT RIGHT
                    else
                    {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(root, parent);
                    }
                }
                parent->color = BLACK;
            }
            else
            {
                //amandoi negrii
                sibling->color = RED;
                if(parent->color == BLACK)
                    fixDoubleBlack(root, parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}
void DeleteHelp(Node* root, Node* v)
{
    Node *u = Replacement(v);
    bool uvBlack = false;
    if((u==NULL||u->color == BLACK)&&(v->color==BLACK))
        uvBlack = true;

    Node* parent = v->parent;

    if(u==NULL) //v leaf
    {
        if(v==root)
            root=NULL;
        else
        {
            if(uvBlack)
                fixDoubleBlack(root, v);
            else
            {
                Node* s = get_sibling(v);
                if(s != NULL)
                    s->color = RED;
            }
            if(v == parent->left)
                parent->left = NULL;
            else parent->right = NULL;
        }
        delete v;
        return;
    }

    if(v->left == NULL || v->right == NULL)
    {
        if(v==root)
        {
            v->data = u->data;
            v->left = v->right = NULL;
            delete u;
        }
        else
        {
            if(parent->left == v)
                parent->left = u;
            else
                parent->right = u;
            delete v;
            u->parent = parent;
            if(uvBlack)
                fixDoubleBlack(root, u);
            else
                u->color = BLACK;
        }
        return;
    }

    swap(u->data, v->data);
    DeleteHelp(root,u);
}
void RBTree::Delete(int x)
{
    Node* nod = searchHelper(root, x);
    DeleteHelp(root, nod);
}


//Afisare :
void inorderHelper(Node* root)
{
    if(root==NULL)
        return;
    inorderHelper(root->left);

   cout<<root->data<<' ';
    inorderHelper(root->right);
}
void levelOrderHelper(Node* root)
{
    if(!root) return;
    queue<Node*> Q;
    Q.push(root);
    while(!Q.empty())
    {
        Node* nod = Q.front();

        Q.pop();
        cout<<nod->data<<' ';
        if(nod->left)
            Q.push(nod->left);
        if(nod->right)
            Q.push(nod->right);
    }
}
void RBTree::levelOrder()
{
    levelOrderHelper(root);
    cout<<'\n';
}
void RBTree::inorder()
{
    inorderHelper(root);
    cout<<'\n';
}
