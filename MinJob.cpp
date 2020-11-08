#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MinJob.h"
#include <list>
#include <iterator>
#include <ctime>

using namespace std;

struct CPU_Job {
	int ID; // process ID
	int length; // process length
	int prior; // process priority
	CPU_Job(int a=0, int b=0, int c=0) : ID(a), length(b), prior(c) {};
	// compares jobs’ priorities and/or IDs
	bool operator<=(const CPU_Job& job);
	bool operator<(const CPU_Job& job);
};

bool CPU_Job::operator<=(const CPU_Job& job){
	if(prior == job.prior){ //checking for appropriate logic
		if(ID < job.ID){
			return true;
		}else{
			return false;
		}
		return true;
	}else if(prior < job.prior){
		return true;
	}else{
		return false;
	}
}

bool CPU_Job::operator<(const CPU_Job& job){
	if(prior == job.prior){ //same as <= operator because some functions call <= so <= defined.
		if(ID < job.ID){
			return true;
		}else{
			return false;
		}
	}else if(prior < job.prior){ //comparing priorities
		return true;
	}else{
		return false;
	}
}

template<typename T>
class BinaryHeap; //declaration of class

template<typename T>
class Priority{ //defintion of MPQ based off of BinaryHeap
	private:
		BinaryHeap<T> priority;
	public: //all functions call BinaryHeap's functions
		bool is_empty(){return priority.is_empty();}
		T remove_min(){return priority.remove_min();}
		void insert(T element){priority.insert(element);}
};

template<typename T>
class BinaryHeap {
	private: 
		vector<T> heap;
	public: 
		bool is_empty(){return heap.size() == 0;}
		T remove_min();
		void insert(T element);
		void print(); //impleted to test to see if BinaryHeap was implemented correctly
};

template<typename T>
void BinaryHeap<T>::print(){
	for(size_t i = 0; i < heap.size();i++){
		cout << heap.at(i) << " ";
	}
	cout << endl;
}

template<typename T>
void BinaryHeap<T>::insert(T element){
	heap.push_back(element); //insert last
	int childIndex = heap.size() - 1;
	int parentIndex = (childIndex - 1) / 2;
	int lastIndex = childIndex;
	bool move = true;
	while(lastIndex != 0 && move){  //walk up tree if necessary
		if(!(heap.at(parentIndex) < heap.at(childIndex))){
			T temp = heap.at(parentIndex);
			heap.at(parentIndex) = heap.at(childIndex);
			heap.at(childIndex) = temp;
		}else{
			move = false;
		}
		lastIndex = parentIndex; //getting indexes
		childIndex = parentIndex;
		parentIndex = (childIndex - 1) / 2;
	}
}

template<typename T>
T BinaryHeap<T>::remove_min(){
	T temp = heap.at(0); //swap and then remove
	heap.at(0) = heap.at(heap.size() - 1);
	heap.at(heap.size() - 1) = temp;
	T ret = temp; //this is the object to return
	heap.pop_back();
	if(heap.size()  == 1 || heap.size() == 0){ //this is checking for if the heap size is 2 or less so index out of bounds doesn't occur
		return ret;
	}else if(heap.size() == 2){
		if(!(heap.at(0) < heap.at(1))){
			T temp = heap.at(0);
			heap.at(0) = heap.at(heap.size() - 1);
			heap.at(heap.size() - 1) = temp;
		}
		return ret;
	}
	bool walk = true;
	unsigned int indexParent = 0;
	T parent = heap.at(indexParent);
	T left, right;
	if(indexParent * 2 + 2 < heap.size()){
		left = heap.at(2 * indexParent + 1);
		right = heap.at(2 * indexParent + 2);
	}else if(indexParent * 2 + 1 < heap.size()){
		left = heap.at(2 * indexParent + 1);
		right = heap.at(2 * indexParent + 1);
	}
	T min;
	unsigned int indexSwap;
	if(left <= right){ //comparing left and right child
		min = left;
		indexSwap = 2 * indexParent + 1;
	}else{
		min = right;
		indexSwap = 2 * indexParent + 2;
	}	
	while(walk){ //swap until necessary
		if(!(parent < min)){
			temp = parent;
			heap.at(indexParent) = min; 
			if(indexSwap >= heap.size()){
				indexSwap = heap.size() - 1;
			}
			heap.at(indexSwap) = temp;
		}else{ //swap is no longer necessary
			walk = false;
		}
		indexParent = indexSwap;
		if(indexParent >= heap.size()){
			indexParent = heap.size() - 1;
		}
		parent = heap.at(indexParent);
		if(indexParent * 2 + 2 < heap.size()){ //getting left and right child nodes and checking for out of bounds
			left = heap.at(2 * indexParent + 1);
			right = heap.at(2 * indexParent + 2);
		}else if(indexParent * 2 + 1 < heap.size()){
			left = heap.at(2 * indexParent + 1);
			right = heap.at(2 * indexParent + 1);
		}else{
			walk = false;
		}
		if(left <= right){
			min = left;
			indexSwap = 2 * indexParent + 1;
		}else{
			min = right;
			indexSwap = 2 * indexParent + 2;
		}	
	}
	return ret;
}

int main(){
	clock_t t1,t2; // clock declarations
	//MPQ running
	t1 = clock();
	string inputFILE,outputFILE;
	Priority<CPU_Job> job;
	cout << "Welcome to job priority sort." << endl;
	cout << "The job file should be formatted like this" << endl;
	cout << "<JobID>   <length>   <Priority>" << endl << endl;
	cout << "A 'sample.txt' input file is given as an example of how this works. Jobs with lower priority numbers are done first." << endl;
	cout <<"If the priority number is the same, then smaller job ID's are done first." << endl;
	cout << "Please enter the name of the file containing the jobs, its length, and its priority: ";
	getline(cin, inputFILE);
	ifstream list(inputFILE);
	int ID, length, priority;
	while(!list.is_open()){
		cout<<"File not found! Please re-enter file name or type 'EXIT' to terminate:";
		getline(cin, inputFILE);
		if(inputFILE == "EXIT"){
			cout << "Program Terminated!" << endl;
			return 1;
		}
		list.open(inputFILE);
	}
	while(!list.eof()){ //file input
		list >> ID >> length >> priority;
		CPU_Job add(ID, length, priority);
		job.insert(add);
	}
	list.close();
	ofstream output("Joblist.txt");
	while(!job.is_empty()){	 //file output
		CPU_Job print = job.remove_min();
		for(int i = print.length; i > 0;--i){
			output << "Job " << print.ID << " with length " << i << " and priority " << print.prior << endl;
		}
	}
	output << "No more jobs to run" << endl;
	output.close();
	t2 = clock();
	double diff = (double)(t2 - t1)*1000/CLOCKS_PER_SEC; //calculating time
	cout << endl;
	cout <<"Process complete! Your output file is 'Joblist.txt' and shows your jobs running along with the length remaining until complete." << endl;
	cout << "Timing: " << diff << " milisec" << endl; //MPQ stop
	return 0;
}