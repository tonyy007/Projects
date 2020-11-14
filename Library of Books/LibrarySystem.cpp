#include <vector>
#include <iostream>
#include "functions.h"


using namespace std;


int main(){
	vector<DLList<Record>> library(26);
	string title;
	cout <<"Please enter the title of the book to enter into database: ";
	getline(cin, title);
	char first = title.at(0);
	int index = first - 'A';
	while(title != "q"){
		string ISBN, edition, year,author;
		cout <<	"Please enter the name of the author of the book: ";
		getline(cin, author);
		cout << "Please enter the ISBN:";
		getline(cin, ISBN);
		cout <<	"Please enter the edition:";
		getline(cin, edition);
		cout <<	"Please enter the year:";
		getline(cin, year);
		Record in(title, author, ISBN, stoi(year), edition);
		library.at(index).insert_first(in);
		library.at(index).sort();
		cout <<"Please enter the title of another book to continiue entering or type 'q' to quit: ";
		getline(cin, title);
		first = title.at(0);
		index = first - 'A';
	}
	cout << endl;
	cout <<"Please enter the title of the book to search: ";
	getline(cin, title);
	first = title.at(0);
	index = first - 'A';
	while(title != "q"){
		int element = library.at(index).search(title);
		int same = library.at(index).searchSame(element);
		if(element == -1){
			string ISBN, edition, year,author;
			cout <<	"Book not found. Please enter the name of the author of the book: ";
			getline(cin, author);
			cout << "Please enter the ISBN:";
			getline(cin, ISBN);
			cout <<	"Please enter the edition:";
			getline(cin, edition);
			cout <<	"Please enter the year:";
			getline(cin, year);
			Record in(title, author, ISBN, stoi(year), edition);
			library.at(index).insert_first(in);
			library.at(index).sort();
		}else if(same > 0){
			string edition;
			library.at(index).display(element,same);
			cout <<	"Please enter the edition:";
			getline(cin, edition);
			int editionNum = edition.at(0) - 49;
			library.at(index).display(element + editionNum);
		}else{
			library.at(index).display(element);
		}
		cout <<"Please enter the title of another book to search or type 'q' to quit: ";
		getline(cin, title);
		first = title.at(0);
		index = first - 'A';
	}
}

