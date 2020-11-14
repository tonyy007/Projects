// header file for the templated DLList=

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e = T(), DLListNode *p = nullptr, DLListNode *n = nullptr)
    : obj(e), prev(p), next(n) {}
};

struct Record{
		string title;
		string name;
		string ISBN;
		int year;
		string edition;
		Record(string title = "", string name = "",string ISBN = "",int year = 0,string edition ="") : title(title), name(name), ISBN(ISBN), year(year), edition(edition){}
		string getTitle()const {return title;} 
		string getName()const {return name;}
		string getISBN()const{return ISBN;} 
		int getYear()const{return year;}
		string getEdition()const{return edition;}
};

ostream& operator << (ostream& out, Record r){ //O(1)
	out << r.getTitle() << std::endl;
	out << r.getName() << std::endl;
	out << r.getISBN() << std::endl;
	out << r.getYear() << std::endl;
	out << r.getEdition() << std::endl << std::endl;
	return out;
}

bool operator<(const Record& left, const Record& right){
	if(left.getTitle() == right.getTitle()){
		if(left.getName() == right.getName()){
				return left.getISBN() < right.getISBN(); //O(1)
		}else{
			return left.getName() < right.getName();
		}
	}else{
		return left.getTitle() < right.getTitle();
	}
}

template<typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList() : header(T()), trailer(T()) // default constructor O(1)
  { header.next = &trailer; trailer.prev = &header; } 
  DLList(const DLList<T>& dll); // copy constructor O(n)
  DLList(DLList<T>&& dll); // move constructor O(1)
  ~DLList(); // destructor O(n)
  DLList<T>& operator=(const DLList<T>& dll);
  DLList<T>& operator=(DLList<T>&& dll); 
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  const DLListNode<T> *after_last_node() const { return &trailer; } 
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; } //O(1)
  T first() const; // return the first book O(1)
  T last() const; // return the last book O(1)
  void insert_first(T obj); // insert to the first book O(1)
  T remove_first(); // remove the first book O(1)
  void insert_last(T obj); // insert to the last book O(1)
  T remove_last(); // remove the last book O(1)
  void insert_after(int up, T obj); //O(n)
  void insert_before(int up, T obj); //O(n)
  T remove_after(int up); //O(n)
  T remove_before(int up); //O(n)
  int search(string title); 
  void display(int element, int same = 0);
  int searchSame(int element); 
  void sort(); 
};

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll);



// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
template<typename T>
DLList<T>::DLList(const DLList<T>& dll)
{	
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  DLListNode<T>* Next = dll.header.next;
  
  while(Next != &dll.trailer){
	  insert_last(Next->obj);
	  Next = Next->next;
  }

}
// move constructor
template<typename T>
DLList<T>::DLList(DLList<T>&& dll)
{
	DLListNode<T>* last = dll.trailer.prev;
	DLListNode<T>* first = dll.header.next;
	header.next = first;
	trailer.prev = last;
	first->prev = &header;
	last->next = &trailer;
	dll.trailer.prev = &(dll.header);
	dll.header.next = &(dll.trailer);
}

template<typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll)
{
	if(this != &dll){
	  DLListNode<T>* Next = header.next;
	  if(!is_empty()){
		  while(Next != &trailer){
			  remove_first();
			  Next = Next->next;
		  }
	  }
	  header.next = &trailer;
	  trailer.prev = &header;
	  
	  Next = dll.header.next;
	  
	  while(Next != &dll.trailer){
		  insert_last(Next->obj);
		  Next = Next->next;
	  }
	}
  return *this;
}

// move assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll)
{	
	if(this != &dll){
		DLListNode<T>* Next = header.next;
		if(!is_empty()){
		  while(Next != &trailer){
				  remove_first();
				  Next = Next->next;
			}
		}
		DLListNode<T>* last = dll.trailer.prev;
		DLListNode<T>* first = dll.header.next;
		header.next = first;
		trailer.prev = last;
		first->prev = &header;
		last->next = &trailer;
		dll.trailer.prev = &(dll.header);
		dll.header.next = &(dll.trailer);
	}
  return *this;
}

template<typename T>
DLList<T>::~DLList()
{
  DLListNode<T>* Next = header.next;
	while(Next != &trailer){
	  remove_first();
	  Next = Next->next;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new book as the first one
template<typename T>
void DLList<T>::insert_first(T obj)
{ 
	DLListNode<T>* insert = new DLListNode<T>(obj);
	DLListNode<T>* second = header.next;
	header.next = insert;
	second->prev = insert;
	insert->prev =  &header;
	insert->next = second;
}

// insert a new book as the last one
template<typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T>* insert = new DLListNode<T>(obj);
  DLListNode<T>* secondToLast = trailer.prev;
  secondToLast->next = insert;
  trailer.prev = insert;
  insert->next = &trailer;
  insert->prev = secondToLast;
}

// remove the first book from the list
template<typename T>
T DLList<T>::remove_first()
{ 
	DLListNode<T>* remove = header.next;
	DLListNode<T>* keep = remove->next;
	header.next = keep;
	keep->prev = &header;
	T objRemove = remove->obj;
	delete remove;
	return objRemove;
}

// remove the last book from the list
template<typename T>
T DLList<T>::remove_last()
{
	DLListNode<T>* remove = trailer.prev;
	DLListNode<T>* keep = remove->prev;
	trailer.prev = keep;
	keep->next = &trailer;
	T objRemove = remove->obj;
	delete remove;
	return objRemove;
}

// return the first book (do not remove)
template<typename T>
T DLList<T>::first() const
{ 
	return ((header.next)->obj);
}

// return the last book (do not remove)
template<typename T>
T DLList<T>::last() const
{
	return ((trailer.prev)->obj);
}

// insert a new book after the book p
template<typename T>
void DLList<T>::insert_after(int up, T obj)
{
	DLListNode<T>* Next = header.next;
	int count = 0;
	  while(count < up - 1){
		  count++;
		  Next = Next->next;
	 }
	 DLListNode<T>* insert = new DLListNode<T>(obj);
	 DLListNode<T>* follow = Next->next;
	 insert->prev = Next;
	 insert->next = follow;
	 Next->next = insert;
	 follow->prev = insert;
}

// insert a new book before the book p
template<typename T>
void DLList<T>::insert_before(int up, T obj)
{
  	DLListNode<T>* Next = header.next;
	int count = 0;
	  while(count < up - 1){
		  count++;
		  Next = Next->next;
	 }
	 DLListNode<T>* insert = new DLListNode<T>(obj);
	 DLListNode<T>* before = Next->prev;
	 insert->prev = before;
	 insert->next = Next;
	 before->next = insert;
	 Next->prev = insert;
}

// remove the book after the book p
template<typename T>
T DLList<T>::remove_after(int up)
{
	DLListNode<T>* Next = header.next;
	int count = 0;
	  while(count < up - 1){
		  count++;
		  Next = Next->next;
	 }
	DLListNode<T>* remove = Next->next;
	DLListNode<T>* keep = remove->next;
	remove->next = nullptr;
	remove->prev = nullptr;
	T ret = remove->obj;
	delete remove;
	Next->next = keep;
	keep->prev = Next;
	return ret;
}

// remove the book before the book p
template<typename T>
T DLList<T>::remove_before(int up)
{
	DLListNode<T>* Next = header.next;
	int count = 0;
	  while(count < up - 1){
		  count++;
		  Next = Next->next;
	 }
	DLListNode<T>* remove = Next->prev;
	DLListNode<T>* keep = remove->prev;
	remove->next = nullptr;
	remove->prev = nullptr;
	T ret = remove->obj;
	delete remove;
	keep->next = Next;
	Next->prev = keep;
	return ret;
}

template<typename T>
int DLList<T>::search(string title){
	int index = 0;
	DLListNode<T>* Next = header.next;
	while(Next != &trailer){
		  index++;
		  if((title == Next->obj.title)){
			return index;
		  }
		  Next = Next->next;
	 }
	 return -1; //book not found
}
template<typename T>
void DLList<T>::display(int element, int same){
	int count = 1;
	DLListNode<T>* Next = header.next;
	while(count < element){
		Next = Next->next;
		count++;
	}
	count = 0;
	while(count <= same){
		cout << endl << Next->obj;
		count++;
		Next = Next->next;	
	}
}


template<typename T>
int DLList<T>::searchSame(int element){
	int count = 1;
	int same = 0;
	DLListNode<T>* Next = header.next;
	while(count < element){
		Next = Next->next;
		count++;
	}	
	while((Next != &trailer)){
		if((Next->obj.title == Next->next->obj.title) && (Next->obj.name == Next->next->obj.name)){
			same++;
		}
		Next = Next->next;
	}
	return same;
}

template<typename T>
void DLList<T>::sort(){
	DLListNode<T>* Next = header.next;
	while(Next->next != &trailer){
		if(!(Next->obj < Next->next->obj)){
			DLListNode<T>* old = Next -> prev;
			DLListNode<T>* swap = Next -> next;
			DLListNode<T>* keep = Next->next->next;
			Next->next = keep;
			keep->prev = Next;
			swap->next = Next;
			swap->prev = old;
			old->next = swap;
			Next->prev = swap;
		}else{
			Next = Next->next;
		}
	}
	
}

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll)
{  
  DLListNode<T>* current = dll.first_node();
  while(current != dll.after_last_node()){
		out << current->obj << " ";
		current = current->next;
  }
  return out;
}

#endif
