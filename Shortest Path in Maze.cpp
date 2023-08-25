#include<iostream>
#include <windows.h>
using namespace std;
#define maxQue 100
//===========================================================
struct Node
{
int row, col;
};
//===========================================================
struct treeNode
{
Node pathn;
treeNode* left, * parent, * right;
};
typedef treeNode* Nodeptr;
//===========================================================
template <class itemType>
class Tree
{
//tree class
private:
int count;
public:
Tree();
bool isEmpty();
Nodeptr makeTree(itemType val1, itemType val2);
int calculateNodes();
Nodeptr setLeft(Nodeptr temp, itemType value1, itemType value2);
Nodeptr setRight(Nodeptr temp, itemType value1, itemType value2);
bool isLeft(Nodeptr np);
bool isRight(Nodeptr np);
Nodeptr sibling(Nodeptr np);
void preOrder(Nodeptr tree);
void inOrder(Nodeptr tree);
void postOrder(Nodeptr tree);
};
//------------------------------------------------------------------------
template <class itemType>
Tree<itemType>::Tree()
{
count = 0;
}
//------------------------------------------------------------------------
template <class itemType>
bool Tree<itemType>::isEmpty()
{
if (count == 0) return true;
else return false;
}
//------------------------------------------------------------------------
template <class itemType>
Nodeptr Tree<itemType>::makeTree(itemType val1, itemType val2)
{
Nodeptr newtree = new treeNode;
newtree->pathn.row = val1;
newtree->pathn.col = val2;
newtree->left = NULL;
newtree->right = NULL;
newtree->parent = NULL;
count++;
return newtree;
}
//------------------------------------------------------------------------
template <class itemType>
int Tree<itemType>::calculateNodes()
{
return count;
}
//------------------------------------------------------------------------
template <class itemType>
Nodeptr Tree<itemType>::setLeft(Nodeptr temp, itemType value1, itemType value2)
{
//setting left node
if (temp == NULL)
cout << "void insertion." << endl;
else if (temp->left != NULL)
cout << "invalid insertion ." << endl;
else
{
temp->left = makeTree(value1, value2);
temp->left->parent = temp;
}
return temp->left;
}
//------------------------------------------------------------------------
template <class itemType>
Nodeptr Tree<itemType>::setRight(Nodeptr temp, itemType value1, itemType value2)
{
//setting right node
if (temp == NULL)
cout << "Void Insertion ";
else if (temp->right != NULL)
cout << "Invalid Insertion working ";
else
{
temp->right = makeTree(value1, value2);
temp->right->parent = temp;
}
return temp->right;
}
//------------------------------------------------------------------------
template <class itemType>
bool Tree<itemType>::isLeft(Nodeptr np)
{
//checking the left node if exits
Nodeptr q;
q = np->parent;
if (q == NULL)
return false;
if (q->left == np)
return true;
return false;
}
//------------------------------------------------------------------------
template <class itemType>
bool Tree<itemType>::isRight(Nodeptr np)
{
//checking the right node if exits
Nodeptr q;
q = np->parent;
if (q == NULL)
return false;
if (q->right == np)
return true;
return false;
}
//------------------------------------------------------------------------
template <class itemType>
Nodeptr Tree<itemType>::sibling(Nodeptr np)
{
//detect the sibling node and return
Nodeptr q = np->parent;
if (q == NULL) return NULL;
if (isLeft(np)) return (q->right);
return (q->left);
}
//------------------------------------------------------------------------
template <class itemType>
void Tree<itemType>::preOrder(Nodeptr tree)
{
//tree pre order traversal
if (tree != NULL)
{
cout << tree->pathn.row << " " << tree->pathn.col << "\n";
preOrder(tree->left);
preOrder(tree->right);
}
}
//------------------------------------------------------------------------
template <class itemType>
void Tree<itemType>::inOrder(Nodeptr tree)
{
//tree in order traversal
if (tree != NULL)
{
inOrder(tree->left);
cout << tree->pathn.row << " " << tree->pathn.col << "\n";
inOrder(tree->right);
}
}
//------------------------------------------------------------------------
template <class itemType>
void Tree<itemType>::postOrder(Nodeptr tree)
{
//tree post order traversal
if (tree != NULL)
{
postOrder(tree->left);
postOrder(tree->right);
cout << tree->pathn.row << " " << tree->pathn.col << " ";
}
}
//===========================================================
typedef Nodeptr itemType;
class que
{
//queue class
private:
itemType items[maxQue];
int front, rear, count;
public:
que();
int isempty();
int isfull();
void insert(itemType newitem);
void remove(itemType& item);
};
//------------------------------------------------------------------------
que::que()
{
count = front = rear = 0;
}
//------------------------------------------------------------------------
int que::isempty()
{
return(count == 0);
}
//------------------------------------------------------------------------
int que::isfull()
{
return(count == maxQue);
}
//------------------------------------------------------------------------
void que::insert(itemType newitem)
{
//insert item in que
if (isfull())
{
cout << "Overflow";
}
else
{
items[rear] = newitem;
rear = (rear + 1) % maxQue;
++count;
}
}
//------------------------------------------------------------------------
void que::remove(itemType& item)
{
//removing items from que
if (isempty())
{
cout << "Under Flow";
}
else
{
item = items[front];
front = (front + 1) % maxQue;
--count;
}
}
//===========================================================
template <class itemType>
class PathDetect
{
itemType pathRow, pathCol;
Tree <itemType>obj1;
bool** visited;
Nodeptr nodeleft, noderight, newnode, temp;
public:
PathDetect(itemType ro, itemType co);
void consoleColor(itemType color);
void shortestPathFind(itemType mat[12][12], itemType s_row, itemType s_col, itemType d_row,
itemType d_col);
void slotInTree(itemType s_row, itemType s_col, Nodeptr n, itemType mat[12][12]);
bool ValidMove(int row, int col, itemType mat[12][12]);
Nodeptr BreadthFirstSearch(int row, int col);
int displayPath(Nodeptr temp, int m[12][12]);
void displayMaze(int m[12][12], int r, int c, PathDetect p);
};
//------------------------------------------------------------------------
template <class itemType>
PathDetect<itemType>::PathDetect(itemType ro, itemType co)
{
//parametrized constructor
pathRow = ro;
pathCol = co;
visited = new bool* [ro];
for (int i = 0; i < co; i++)
{
visited[i] = new bool[co];
}
for (int i = 0; i < ro; i++)
for (int j = 0; j < co; j++)
visited[i][j] = false;
}
//------------------------------------------------------------------------
template <class itemType>
void PathDetect<itemType>::consoleColor(itemType color)
{
//setting console color
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//------------------------------------------------------------------------
template <class itemType>
void PathDetect<itemType>::shortestPathFind(itemType mat[12][12], itemType s_row, itemType s_col,
itemType d_row, itemType d_col)
{
int n;
newnode = new treeNode;
newnode = obj1.makeTree(s_row, s_col);//initialize tree
slotInTree(s_row, s_col, newnode, mat);//inserting the shortest path nodes in tree
temp = BreadthFirstSearch(d_row, d_col);
cout << "\n\tShortest Path is as follows :" << endl;
n = displayPath(temp, mat);//printing the path found
cout << "\n\tLength : " << n << endl;
}
//------------------------------------------------------------------------
template <class itemType>
void PathDetect<itemType>::slotInTree(itemType s_row, itemType s_col, Nodeptr n, itemType
mat[12][12])
{
//getting valid moves and setting the direction accordingly
//meanwhile inserting th nodes in the tree
temp = new treeNode;
if (ValidMove(s_row, s_col + 1, mat))
{
temp = obj1.setLeft(n, s_row, s_col + 1);
slotInTree(s_row, s_col + 1, temp, mat);
}
if (ValidMove(s_row + 1, s_col, mat))
{
temp = obj1.setRight(n, s_row + 1, s_col);
slotInTree(s_row + 1, s_col, temp, mat);
}
}
//------------------------------------------------------------------------
template <class itemType>
bool PathDetect<itemType>::ValidMove(int row, int col, itemType mat[12][12])
{
//detecting weather the point lies within the maze or not
if (row<0 || col<0 || row>pathRow || col>pathCol)
return false;
else if (mat[row][col] == 1)
return true;
else
return false;
}
//------------------------------------------------------------------------
template <class itemType>
Nodeptr PathDetect<itemType>::BreadthFirstSearch(int row, int col)
{
//doing breath first search for finding the path(using queue)
que q;
temp = new treeNode;
temp = newnode;
q.insert(temp);
while (!q.isempty())
{
q.remove(temp);
if (temp->pathn.row == row && temp->pathn.col == col)
{
break;
}
if (temp->left != NULL) q.insert(temp->left);
if (temp->right != NULL) q.insert(temp->right);
}
return temp;
}
//------------------------------------------------------------------------
template <class itemType>
int PathDetect<itemType>::displayPath(Nodeptr temp, int m[12][12])
{
//displaying the shortest path
Nodeptr arr[50];
int inum = 0;
while (temp->parent != NULL)
{
arr[inum] = temp;
++inum;//initializing the array for found path
temp = temp->parent;
}
int k = inum - 1;
cout << "\n(" << temp->pathn.row << "," << temp->pathn.col;
for (int j = inum - 1; j >= 0; j--)
{
temp = arr[j];
m[temp->pathn.row][temp->pathn.col] = 3;//setting the display
cout << ") -> (" << temp->pathn.row << "," << temp->pathn.col;
}
cout << ")";
consoleColor(13);
cout << endl;
cout << endl;
//display the final matrix with shortest path
for (int i = 0; i < 9; i++)
{
cout << "\t ";
for (int j = 0; j < 10; j++)
{
if (m[i][j] == 3)
{
consoleColor(11);
cout << "# ";
}
else {
consoleColor(14);
cout << m[i][j] << " ";
}
}
cout << endl;
}
cout << endl;
consoleColor(7);
return ++inum;
}
//------------------------------------------------------------------------
template <class itemType>
void PathDetect<itemType>::displayMaze(int m[12][12], int r, int c, PathDetect p)
{
//initial display of maze
cout << "\n\n\t===========MAZE===========\n\n";
consoleColor(15);
for (int i = 0; i < r; i++)
{
cout << "\t ";
for (int j = 0; j < c; j++)
{
cout << m[i][j] << " ";
}
cout << endl;
}
cout << endl;
int s_row, s_col, d_row, d_col;
cout << "\tEnter start points (row,column) : ";
cin >> s_row >> s_col;//get the start point from user
cout << "\tEnter End points (row,column) : ";
cin >> d_row >> d_col;//get end points from the user
if (m[s_row][s_col] == 1)
{
if (m[d_row][d_col] == 1)
{
//find shortest path between points
p.shortestPathFind(m, s_row, s_col, d_row, d_col);
}
else
cout << "Path Does not Exists";
}
else
cout << "Path Does not Exists";
}
//===========================================================
int main()
{
//main driver program
int rownum = 12, colnum = 12;
int matrix[12][12] =
{//matrix definition
1,1,0,1,0,1,0,1,1,1,0,1,
0,1,0,1,1,1,0,0,1,1,1,1,
0,1,1,0,1,0,1,1,1,1,0,0,
1,0,1,1,0,0,1,1,0,1,1,0,
0,1,0,1,0,0,1,1,0,1,0,1,
1,0,1,1,1,0,0,1,1,0,1,1,
0,0,0,0,1,0,0,1,0,1,1,1,
0,1,1,1,1,0,1,1,0,0,0,0,
1,1,0,1,1,0,0,1,1,1,0,0,
0,0,0,0,1,0,0,1,0,1,1,1,
0,1,0,1,1,1,1,1,0,0,0,0,
1,1,0,1,1,0,0,1,1,1,0,1
};
PathDetect<int> pathN(rownum, colnum);
pathN.displayMaze(matrix, rownum, colnum, pathN);//initial display of the matrix
}
//===========================================================