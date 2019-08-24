#include <iostream>
#include <string>
#include "../include/query.h"

using namespace std;

int main(int argc, char const *argv[]) {

  display_query_syntax();
  bool terminate = false;
  while(!terminate){
    string input_query;
    cout << "Enter query: ";
    getline(cin, input_query);
    if (input_query == "quite" || input_query == "q"){
      terminate = true;
    }else{
      query(input_query);
    }
  }

  return 0;
}
