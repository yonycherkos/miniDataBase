#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <boost/foreach.hpp>

using namespace std;

void display_element(set<vector<string>> table){
  // select all elements
  // set<vector<string>>::iterator itr1;
  int count = 1;
  for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
    // vector<string>::iterator itr2;
    cout << count << " ";
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
      cout << *itr2 << "    ";
    }
    count++;
    cout <<"\n-----------------------------\n";
  }
  cout << endl;
}

void select_element(set<vector<string>> table, string name){
  // select specific element
  for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
      if( *itr1->begin() == name){
        cout << *itr2 << endl;
      }
    }
  }
  cout << endl;
}

set<vector<string>> delete_element(set<vector<string>> table, string name){
  // delete elements from the table
  for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
      if( *itr1->begin() == name){
        table.erase(itr1);
        break;
      }
    }
  }
  return table;
}

set<vector<string>> update_element(set<vector<string>> table, vector<string> column){
  // update elements of the table
  for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
      if( *itr1->begin() == column.at(0)){
        table.erase(itr1);
        table.insert(column);
        break;
      }
    }
    cout << endl;
  }
  return table;
}

set<vector<string>> insert_element(set<vector<string>> table, vector<string> column){
  // insert element into the table
  table.insert(column);
  return table;
}

int main(int argc, char const *argv[]) {

  set<vector<string>> table;

  vector<string> column = {"name", "age", "gender"};
  vector<string> yonathan = {"yonathan", "23", "male"};
  vector<string> daniel = {"daniel", "20", "male"};
  vector<string> ephrame = {"ephrame", "24", "male"};

  table = insert_element(table, column);
  table = insert_element(table, yonathan);
  table = insert_element(table, daniel);
  table = insert_element(table, ephrame);

  display_element(table);
  string name = "yonathan";
  select_element(table, name);
  table = delete_element(table, name);
  cout << "after deletion" << endl;
  display_element(table);

  vector<string> daniel_update = {"daniel", "21", "female"};
  table = update_element(table, daniel_update);
  cout << "after updating" << endl;
  display_element(table);

  return 0;
}
