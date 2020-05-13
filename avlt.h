/*avlt.h*/

//Nisarg Thakkar
//CS 251 Project 5
// Threaded AVL tree
//Self balancing threaded AVL tree

#pragma once

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename KeyT, typename ValueT>
class avlt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded; // true => Right is a thread, false => non-threaded
    int    Height;     // height of tree rooted at this node
  };
  NODE* LeftMost;
  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  
  void _insert(KeyT key, ValueT value)  //helper insert function for copy constructor, without rotation
  { 
    NODE* prev = nullptr;
	NODE* cur = Root;
	stack<NODE*> nodes;     //to update height
	
	while (cur != nullptr)
    {
	  if (key == cur->Key)  // already in tree
        return;             //return without doing anything
	
	  nodes.push(cur);       
      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;  //prev is gonna be parent of inserted node
      }
      else  //search right
      {
		if (!(cur->isThreaded))
		{
			prev = cur;
			cur = cur->Right;
		}
		else   //if threaded, is like nullptr sets cur to nullptr
		{
			prev = cur;
			cur = nullptr;
		}
      }
    }//while
	
	//2. allocate memory	
	//if not found assigns new node
	NODE* n = new NODE();
	n->Key = key;
	n->Value = value;
	n->Left =nullptr;
	n->Right = nullptr;
	n->isThreaded = true;           //always inserted at leaf, will be threaded.
	n->Height = 0;                 //inserted at leaf, height is 0
	
	//3. Link in with parent
	if (prev == nullptr)
	{	
		Root = n;   //if first node entered, becomes Root
	}
		
	else if (key < prev->Key)  //if inserted to left, link in with existing structure
	{
		prev->Left = n;   
		n->Right = prev;  //threaded
	}
	else             //if inserted to right, link in with existing tree
	{
		n->Right = prev->Right;    //inherets threaded pointer from previous
		prev->Right = n;
		
		prev->isThreaded = false;    //previous is no longer threaded
	}
	
	//4. update size
	Size++;   //add size
	
	//5. walk back up and update height
	//
	while(!nodes.empty())
	{   
		cur = nodes.top();
		nodes.pop();
		
		int HL, HR, newH;
		
		if(cur->Left == nullptr)
			HL = -1;                //if no childern, height is -1
		else
			HL = cur->Left->Height;
			
		if(cur->isThreaded)
			HR = -1;
		else
			HR = cur->Right->Height;
			
		newH = 1 + std::max(HL, HR);      
		
		if (newH == cur->Height)
			break;                 //when height doesn't change, we can stop; no need to keep going up
		
		cur->Height = newH;
	}	
 }
  void _preorder(NODE* cur)  //pre_order do the thing (insert in this case, helps making deep copy, go to left, go to right
  {	  
	  if (cur == nullptr)             //base case
	  {  return;}
	 
	_insert(cur->Key, cur->Value);
	
	
	_preorder(cur->Left);    //recursively left and right
	
	if (!(cur->isThreaded))
	{		
	  _preorder(cur->Right);    
	 }
  
  }
  
  
  void _inorder(NODE* cur, ostream& output) const  //go to left, do the thing, go to right (recursive)
  {
	  if (cur == nullptr)    //base case
		  return;
	  
	  else    //prints in order
	  {
	  	  _inorder(cur->Left, output);
		  if ((!(cur->isThreaded)) || (cur->isThreaded && cur->Right == nullptr))
			  output << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << endl;
		  else
			  output << "(" << cur->Key << "," << cur->Value << "," << cur->Height << "," << cur->Right->Key << ")" << endl;
		  if (!(cur->isThreaded))
			  _inorder(cur->Right, output);
	  }
  }
  
  void _des(NODE* cur)  //destructor helper function, go to left, go to right, start deleting (bottom up)
  {
	  if (cur == nullptr)
		  return;
	  _des(cur->Left);  //to left
	  if (!(cur->isThreaded))  //to right, if not threaded
		_des(cur->Right);
	  delete(cur);   //delete
  }
  
  void _RightRotate(NODE* Parent, NODE* N)
  {
	  
	 //Label
     NODE* L = N->Left;
     NODE* A = L->Left;
	 NODE* B;
	 NODE* C;
	 
	 if (!L->isThreaded)
		 B = L->Right;
	 else
		 B = nullptr;
	 
	 if (!N->isThreaded)
		C = N->Right;
	 else
		C = nullptr;
     
     //rotate
     L->Right = N;
	 L->isThreaded = false;
     N->Left = B;
     
     //update parent to link to L
     
     if (Parent == nullptr)
     { Root = L;  }
     else if (Parent->Left == N)
      Parent->Left = L;
     else
      Parent->Right = L;
      
    // update N's height
    
    int HA, HB, HC;
    
   if(A != nullptr)
      HA = A->Height;
   else
      HA = -1;
      
   if(B != nullptr)
      HB = B->Height;
   else
      HB = -1;
      
   if(C != nullptr)
      HC = C->Height;
   else
      HC = -1;
      
      
    N->Height = 1 + max(HB, HC);
    L->Height = 1 + max(HA, N->Height);
	
	
    return;
  }
  
  void _LeftRotate(NODE* Parent, NODE* N)
  {
	 //Label
     NODE* R = N->Right;
     NODE* B = R->Left;
	 NODE* C = R->Right;  //Lefr rotate, right pointer can't be nullptr; no need to check for it
	 NODE* A = N->Left;
	 
	      
     //rotate
     R->Left = N;
	 
	 if(B == nullptr)
	 {
		 N->Right = R; //threaded
		 N->isThreaded = true;
	 }
	 else
		 N->Right = B;
     
     //update parent to link to L
     
     if (Parent == nullptr)
     { Root = R;}
     else if (Parent->Left == N)
      Parent->Left = R;
     else
      Parent->Right = R;
      
    // update N's height
    
    int HA, HB, HC;
    
   if(A != nullptr)
      HA = A->Height;
   else
      HA = -1;
      
   if(B != nullptr)
      HB = B->Height;
   else
      HB = -1;
      
   if(C != nullptr)
      HC = C->Height;
   else
      HC = -1;
      
     
    N->Height = 1 + max(HB, HA);
    R->Height = 1 + max(HC, N->Height);
	
	
    return;
  }

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avlt()
  {
    Root = nullptr;
	LeftMost = nullptr;
    Size = 0;
  }

  //
  // copy constructor
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt (const avlt& other)
  {
    Root = nullptr;
	LeftMost = nullptr;
    Size = 0;
	_preorder(other.Root);
  }

	//
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~avlt()
  {
    _des(Root);
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt& operator=(const avlt& other)
  {
    clear();
    
	_preorder(other.Root);
    return *this;
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    if (Root != nullptr)
		_des(Root);
    Size = 0;
	Root = nullptr;
	LeftMost = nullptr;
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  // Time complexity:  O(1) 
  //
  int size() const
  {
    return Size;
  }

  // 
  // height:
  //
  // Returns the height of the tree, -1 if empty.
  //
  // Time complexity:  O(1) 
  //
  int height() const
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) worst-case
  //
  bool search(KeyT key, ValueT& value) const
  {
    NODE* cur = Root;
	
	while(cur != nullptr)
	{
		if(key == cur->Key)
		{
			value = cur->Value;  //if key found, returned
			return true;
		}
			
		if(key < cur->Key)     //otherwise go to left node recursively
			cur = cur->Left;
		else
		{
			if (cur->isThreaded)     
				cur = nullptr;
			else
				cur = cur->Right;   //and go to right
		}
	}
    
		return false; //if here, no keys found
  }

  //
  // range_search
  //
  // Searches the tree for all keys in the range [lower..upper], inclusive.
  // It is assumed that lower <= upper.  The keys are returned in a vector;
  // if no keys are found, then the returned vector is empty.
  //
  // Time complexity: O(lgN + M), where M is the # of keys in the range
  // [lower..upper], inclusive.
  //
  // NOTE: do not simply traverse the entire tree and select the keys
  // that fall within the range.  That would be O(N), and thus invalid.
  // Be smarter, you have the technology.
  //
  vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
	 //search on lower
    vector<KeyT>  keys;
	NODE* prev = nullptr;
	NODE* cur = Root;
	KeyT key;
	bool there;
	
	//if upper is lower than lower, or tree doesn't exist
	if(upper < lower || Root == nullptr)
		  return keys;
	
	while(cur != nullptr)
	{
		if(lower == cur->Key)
		{
			break;  //if lower found
		}
			
		if(lower < cur->Key)    //go left
		{
			prev = cur;
			cur = cur->Left;
		}
		else
		{
			if (cur->isThreaded)  
			{
				prev = cur;
				cur = nullptr;
			}
			else
			{
				prev = cur;
				cur = cur->Right;   //and go to right
			}
		}
	}
	
	if(cur == nullptr) // lower not found
	{
		if (lower < prev->Key)    //if lower is less than prev, then start internal state from previous
			LeftMost = prev;
		else if(prev->Right != nullptr)    //if lower is higher than prev's key, then start internal state from prev's threaded node
			LeftMost = prev->Right;
	}
	
	if(cur != nullptr)	 //if lower found, start internal state from there
		LeftMost = cur;
	there = next(key);    //get key for from next function with boolean
		
	while(there && ((lower <= key) && (key <= upper)))     //if key in range, and returned successfully from next
	{
		keys.push_back(key);                              //push in vector
		
		if(LeftMost == nullptr)                          //if internal state is set to null from next, return that vector, no next
			return keys;                               //key exists
		
		there = next(key);                      //if internal state not null, get the next key, reset internal state to next inorder node
				
	}
    
	return keys;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.  Rotations are performed
  // as necessary to keep the tree balanced according to AVL definition.
  //
  // Time complexity:  O(lgN) worst-case
  //
  void insert(KeyT key, ValueT value)
  { //1. search
    NODE* prev = nullptr;
	NODE* cur = Root;
	stack<NODE*> nodes;
	NODE* broken = nullptr;
	NODE* broken_parent = nullptr;
	
	while (cur != nullptr)
    {
	  if (key == cur->Key)  // already in tree
        return;             //return without doing anything
	
	  nodes.push(cur);
      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;  //cout << "here fine" << endl;
      }
      else  //search right
      {
		if (!(cur->isThreaded))
		{
			prev = cur;
			cur = cur->Right;
		}
		else   //if threaded, is like nullptr sets cur to nullptr
		{
			prev = cur;
			cur = nullptr;
		}
      }
    }//while
	
	//2. allocate memory	
	//if not found assigns new node
	NODE* n = new NODE();
	n->Key = key;
	n->Value = value;
	n->Left =nullptr;
	n->Right = nullptr;
	n->isThreaded = true;           //always inserted at leaf, will be threaded.
	n->Height = 0;                 //
	
	//3. Link in with parent
	if (prev == nullptr)
	{	
		Root = n;   //if first node entered, becomes Root
	}
		
	else if (key < prev->Key)  //if inserted to left, link in with existing structure
	{
		prev->Left = n;   
		n->Right = prev;  //threaded
	}
	else             //if inserted to right, link in with existing tree
	{
		n->Right = prev->Right;    //inherets threaded pointer from previous
		prev->Right = n;
		
		prev->isThreaded = false;    //previous is no longer threaded
	}
	
	//4. update size
	Size++;   //add size
	
	//5. walk back up and update height
	//
	while(!nodes.empty())
	{   
		int BH = 0;             //balance factor for current node 
		cur = nodes.top();
		nodes.pop();
		
		int HL, HR, newH;
		
		if(cur->Left == nullptr)
			HL = -1;
		else
			HL = cur->Left->Height;
			
		if(cur->isThreaded)
			HR = -1;
		else
			HR = cur->Right->Height;
			
		newH = 1 + std::max(HL, HR);
		
		if (newH == cur->Height)         //breaks if heights deosn't change, no need to go up
			break;
		
		cur->Height = newH;
			
		BH = HL - HR;                //balance factor , height of left childern - height of right childern
		
		if (BH > 1 || BH < -1)       // if needs rotation, sets where broken and it's parent
		{
			broken = cur;			
			
			if (nodes.empty())  //  broken at root
				broken_parent = nullptr;
			else
				broken_parent = nodes.top();   //
			
		}
		
		if (BH > 1) //case 1 or 2
		{
			if (key > cur->Left->Key) //case 2
			{
				_LeftRotate(broken, cur->Left);
			}
			
			_RightRotate(broken_parent, broken);
		}
		
		if (BH < -1) //case 3 or 4
		{
			if (key < cur->Right->Key) //case 3
			{
				
				_RightRotate(broken, broken->Right);
			}
			
			_LeftRotate(broken_parent, broken);
		}
  }//while
		
	}
	

  
  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) worst-case
  //
  ValueT operator[](KeyT key) const
  {
    bool temp;
	ValueT val;
	
	temp = search(key, val);   //if key exist, temp will be true and value returned
	if(temp)
		return val;

    return ValueT{ };

  }

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) worst-case
  //
  KeyT operator()(KeyT key) const
  {
    NODE* cur = Root;
	NODE* temp = nullptr;
	
	while(cur != nullptr)  //searches if key exists
	{
		if(key == cur->Key)   //key found
		{
			temp = cur;
			cur = nullptr;
		}
			
		else if(key < cur->Key)
			cur = cur->Left;
			
		else
		{
			if (cur->isThreaded)
				cur = nullptr;				
			else
				cur = cur->Right;
		}
	}
	if(temp != nullptr) // key found
	{
		if((temp->isThreaded && temp->Right != nullptr) || (!(temp->isThreaded))) //threaded and not at end (pointing to null) or not threaded
			return temp->Right->Key;				 //returns right inorder key
	}

    return KeyT{ };
  }

  //
  // %
  //
  // Returns the height stored in the node that contains key; if key is
  // not found, -1 is returned.
  //
  // Example:  cout << tree%12345 << endl;
  //
  // Time complexity:  O(lgN) worst-case
  //
  int operator%(KeyT key) const
  {
    NODE* cur = Root;
	
	while(cur != nullptr)
	{
		if(key == cur->Key)
		{
			return cur->Height;
		}
			
		if(key < cur->Key)     //otherwise go to left node recursively
			cur = cur->Left;
		else
		{
			if (cur->isThreaded)     
				cur = nullptr;
			else
				cur = cur->Right;   //and go to right
		}
	}

    return -1;
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) worst-case
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  {
    if(this->Root == nullptr)
	{	
		LeftMost = nullptr;
		return; 
	}
	
	NODE* cur = this->Root;
	
	while(cur->Left != nullptr)   //sets the smallest, leftmost pointer to leftmost to start inorder traversal
	{
		cur = cur->Left;
	}
	
	LeftMost = cur;
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) worst-case
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    if(LeftMost != nullptr)
	{ 
		key = LeftMost->Key;
		if(LeftMost->isThreaded)    //takes care of leaf nodes, sets leftmost to its next inorder node
		{
			LeftMost = LeftMost->Right;
		}
		else     //takes care of internal nodes
		{
			LeftMost = LeftMost->Right;      //going to non threaded right and going its extreme left
			while (LeftMost->Left != nullptr)
			{
				LeftMost = LeftMost->Left;
			}
		}
		return true;
		
	}
	
    return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* AVLT ***********************" << endl;

    output << "** size: " << this->size() << endl;
    output << "** height: " << this->height() << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value,height) or (key,value,height,THREAD)
    //
    // (key,value,height) if the node is not threaded OR thread==nullptr
    // (key,value,height,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
	_inorder(Root, output);   //calls helper function to print inorder with ostream type
    output << "**************************************************" << endl;
  }
	
};

