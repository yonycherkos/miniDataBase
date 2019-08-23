#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/foreach.hpp>

using namespace std;

map<string, set<vector<string>>> database;

void create_table(string table_name, vector<string> column_names){
  set<vector<string>> table;
  table.insert(column_names);
  database.insert(pair<string, set<vector<string>>> (table_name, table));
}

void display_element(string table_name){
  // select all elements
  // set<set<vector<string>>>::iterator itr = database.find(table);
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    int count = 1;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      cout << count << " ";
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        cout << *itr3 << "    ";
      }
      count++;
      cout <<"\n-----------------------------\n";
    }
    cout << endl;
  }
}

void insert_element(string table_name, vector<string> column){
  // insert element into the table
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    table.insert(column);
    database[table_name] = table; // update database with key table_name
  }
}

void select_element(string table_name, string primery_key){
  // select specific element
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        if( *itr2->begin() == primery_key){
          cout << *itr3 << endl;
        }
      }
    }
  }
  cout << endl;
}

void update_element(string table_name, vector<string> updated_row){
  // update elements of the table
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        if( *itr2->begin() == updated_row[0]){
          table.erase(itr2);
          table.insert(updated_row);
          database[table_name] = table; // update database with key table_name
          break;
        }
      }
      cout << endl;
    }
  }
}

void delete_element(string table_name, string name){
  // delete elements from the table
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        if( *itr2->begin() == name){
          table.erase(itr2);
          database[table_name] = table; // update database with key table_name
          break;
        }
      }
    }
  }
}

void inner_join(string table1_name, string table2_name, string inner_join_table_name){
  // find intersection of two tables
  set<vector<string>> inner_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_intersection(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(inner_join_table, inner_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (inner_join_table_name, inner_join_table));
  }
}

void outter_join(string table1_name, string table2_name, string outter_join_table_name){
  // find intersection of two tables
  set<vector<string>> outter_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_union(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(outter_join_table, outter_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (outter_join_table_name, outter_join_table));
  }
}

void left_join(string table1_name, string table2_name, string left_join_table_name){
  // find intersection of two tables
  set<vector<string>> left_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(left_join_table, left_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (left_join_table_name, left_join_table));
  }
}

void right_join(string table1_name, string table2_name, string right_join_table_name){
  // find intersection of two tables
  set<vector<string>> right_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(right_join_table, right_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (right_join_table_name, right_join_table));
  }
}

int main(int argc, char const *argv[]) {

  // operations
  // 1) create table
  string table1_name = "table1";
  vector<string> table1_column_names = {"name", "age", "gender"};
  create_table(table1_name, table1_column_names);
  string table2_name = "table2";
  vector<string> table2_column_names = {"name", "age", "gender"};
  create_table(table2_name, table2_column_names);

  // 2) insert element
  // columnts to be inserted to table1
  vector<string> yonathan = {"yonathan", "23", "male"};
  vector<string> daniel = {"daniel", "20", "male"};
  vector<string> ephrame = {"ephrame", "24", "male"};

  // columns to be inserted to table2
  vector<string> eleny = {"eleny", "5", "female"};
  vector<string> lidya = {"daniel", "18", "female"};
  vector<string> betty = {"ephrame", "13", "female"};

  // insert the elements to table1
  insert_element(table1_name, yonathan);
  insert_element(table1_name, daniel);
  insert_element(table1_name, ephrame);

  // insert the elements to table2
  insert_element(table2_name, yonathan);
  insert_element(table2_name, daniel);
  insert_element(table2_name, ephrame);

  // 3) display element
  cout << "---------Table1------------\n";
  display_element(table1_name);
  cout << "---------Table2------------\n";
  display_element(table2_name);

  // 4) select element
  string table1_primary_key = "yonathan";
  select_element(table1_name, table1_primary_key);

  // 5) delete element
  delete_element(table1_name, table1_primary_key);
  cout << "------after deleting-------" << endl;
  display_element(table1_name);

  // 6) update element
  vector<string> updated_row = {"daniel", "21", "female"};
  update_element(table1_name, updated_row);
  cout << "------after updating------" << endl;
  display_element(table1_name);

  // 7) inner join
  string inner_join_table_name = "inner_join_table";
  inner_join(table1_name, table2_name, inner_join_table_name);
  cout << "------Inner joining--------" << endl;
  display_element(inner_join_table_name);

  // 8) outter join
  string outter_join_table_name = "outter_join_table";
  outter_join(table1_name, table2_name, outter_join_table_name);
  cout << "------outter joining--------" << endl;
  display_element(outter_join_table_name);

  // 9) left join
  string left_join_table_name = "left_join_table";
  left_join(table1_name, table2_name, left_join_table_name);
  cout << "------left joining--------" << endl;
  display_element(left_join_table_name);

  // 10) right join
  string right_join_table_name = "right_join_table";
  right_join(table1_name, table2_name, right_join_table_name);
  cout << "------right joining--------" << endl;
  display_element(right_join_table_name);

  return 0;
}
