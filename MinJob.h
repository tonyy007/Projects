#include <vector>
#include <list>
#include <iterator>

using namespace std;

template<typename T>
class Min{ //vector
	private:
		vector<T> data;
	public:
		bool is_empty(){return data.empty();}
		void insert(T info){data.push_back(info);}
		T remove_min();
};

template<typename T>
T Min<T>::remove_min(){
	T min = data.at(0);
	unsigned int index = 0;
	for(size_t i = 0; i < data.size(); ++i){ //looking for minimum in unsorted vector
		if(!(min < data.at(i))){
			min = data.at(i);
			index = i; 
		}
	}
	data.erase(data.begin() + index);
	return min;
}

template<typename T>
class List{ //list class 
	private:
		list<T> data;
	public:
		bool is_empty(){return data.empty();}
		void insert(T info){data.push_back(info);}
		T remove_min();
};

template<typename T>
T List<T>::remove_min(){ //similar to unsorted vector but must be iterated differenrly
	auto it = data.begin();
	T min = *(data.begin());
	unsigned int index = 0;
	unsigned int count = 0;
	for(;it != data.end(); ++it){
		if(!(min < *(it))){
			min = *(it);
			index = count;
		}
		count++;
	}
	it = data.begin();
	for(unsigned int i = 0;i < index; ++i){
		it++;
	}
	data.erase(it);
	return min;
}
