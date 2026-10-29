#include <iostream>
#include <fstream>
#include "hashTable.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){

  if (argc < 2) {
    cerr << "usage: " << argv[0] << " <input-file>\n";
    return 1;
  }
  fstream input(argv[1]);
  if (!input) {
      cerr << "could not open " << argv[1] << "\n";
      return 1;
  }
  
  clock_t start, end;
  double duration;

  start = clock();

  // make the array size inside the hash table is 10007
  HashTable<int> ht(10007);

  //operation counters for output
  int insCount = 0, delCount = 0, retCount = 0;

  //temp variables for operating on current input
  int social;
  string first;
  string last;
  char x;
  
  //switch statement grabbed from linked list file, uses i d r for insert delete retrieve
  while (input >> x >> social >> first >> last){

    switch(x){
      case 'i':
        if(ht.insert(social, social)) insCount++;
        break;

      case 'd':
        if(ht.erase(social)) delCount++;
        break;
      
      case 'r':
        if(ht.find(social)) retCount++;
        break;

      default:
        cout << "Unknown command: " << x << endl;
        break;
    }
  }
  
  
  
  
  
  
  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;

 
  cout << "The Number of Valid Insertation :" << insCount << endl;
  cout << "The Number of Valid Deletion :"    << delCount << endl;
  cout << "The Number of Valid Retrieval :"   << retCount << endl;
  cout << "Item numbers in the list :"        << ht.getSize() << endl;
  cout<<"elapsed time: "<< duration <<'\n';
}
