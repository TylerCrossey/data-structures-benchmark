#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "DLL.h"
using namespace std;


int main(int argc, char* argv[]){
  clock_t start, end;
  double duration;

  if (argc < 2) {
    cerr << "usage: " << argv[0] << " <input-file>\n";
    return 1;
  }
  fstream input(argv[1]);
  if (!input) {
      cerr << "could not open " << argv[1] << "\n";
      return 1;
  }
  

  start = clock();

  DLL myList;

  int insCount = 0, delCount = 0, retCount = 0;
  char x;
  string social;
  string first;
  string last;

  while (input >> x >> social >> first >> last){
    string name = first + " " + last;

    switch(x){
      case 'i':
        myList.insert(social, name, insCount);
        break;

      case 'd':
        myList.remove(social, delCount);
        break;
      
      case 'r':
        if (myList.search(social) != -1) retCount++;
        break;

      default:
        cout << "Unknown command: " << x << endl;
        break;
    }
  }


  input.close();

  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;
  cout<<"The Number of Valid Insertion: " << insCount << endl;
  cout<<"The Number of Valid Deletion: " << delCount << endl;
  cout<<"The Number of Valid Retrieval: " << retCount << endl;
  cout<<"Number of Items in the List: " << myList.size() << endl;
  cout<<"elapsed time: "<< duration <<'\n';

}