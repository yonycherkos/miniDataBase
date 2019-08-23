#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

map<string, set<vector<string>>> database;

void create_table(string table_name, vector<string> column_names){
  set<vector<string>> table;
  table.insert(column_names);
  database.insert(pair<string, set<vector<string>>> (table_name, table));
}

void drop_table(string table_name){
  auto itr = database.find(table_name);
  if(itr != database.end()){
    database.erase(table_name);
    cout << table_name << " has been deleted successfuly. \n";
  }
}

void display_element(string table_name){
  // select all elements
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    int count = 1;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      cout << count << " ";
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        cout << *itr3 << "\t";
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
int find_column_name_index( set<vector<string>> table, string column_name){
  for(auto itr1 = table.begin(); itr1 != table.end(); itr1++){
    int index = 0;
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); itr2++){
      string column = *itr2;
      if(column == column_name){
         return index;
      }
      index++;
    }
  }
}

void select_element(string table_name, string column_name, string key, string value){
  // select specific element
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    int index = find_column_name_index(table, key);
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      vector<string> row = *itr2;
      if(row[index] == value){ // if the column name matchs
        vector<string> desired_row = *itr2;
        if (column_name == "*"){
          for(auto itr3 = desired_row.begin(); itr3 != desired_row.end(); ++itr3){
            cout << *itr3 << "\t";
          }
          cout << endl;
        }else{
          int index = find_column_name_index(table, column_name);
          cout << desired_row[index] << endl;
        }
      }
    }
  }
}

void update_element(string table_name, vector<string> updated_row, string key, string value){
  // update elements of the table
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    int index = find_column_name_index(table, key);
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      vector<string> row = *itr2;
      if(row[index] == value){
        table.erase(itr2);
        table.insert(updated_row);
        database[table_name] = table; // update database with key table_name
        break;
      }
      cout << endl;
    }
  }
}

void delete_element(string table_name, string key, string value){
  // delete elements from the table
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    int index = find_column_name_index(table, key);
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      vector<string> row = *itr2;
      if(row[index] == value){
        table.erase(itr2);
        database[table_name] = table; // update database with key table_name
        break;
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

vector<string> parse_string(string str, string separator){
  typedef tokenizer<char_separator<char>> tokenizer;
  vector<string> string_segment;
  if (separator == "comma"){
    char_separator<char> sep{","};
    tokenizer tok{str, sep};
    for (auto itr = tok.begin(); itr != tok.end(); ++itr){
      string_segment.push_back(*itr);
    }
  }else if(separator == "equal"){
    char_separator<char> sep{"="};
    tokenizer tok{str, sep};
    for (auto itr = tok.begin(); itr != tok.end(); ++itr){
      string_segment.push_back(*itr);
    }
  }else{
    char_separator<char> sep{" "};
    tokenizer tok{str, sep};
    for (auto itr = tok.begin(); itr != tok.end(); ++itr){
      string_segment.push_back(*itr);
    }
  }
  return string_segment;
}

void query(string query){
  string separator = "space";
  vector<string> query_segment = parse_string(query, separator);
  // 1 - creation queries
  if (query_segment[0] == "create") {
      string table_name = query_segment[2];
      cout << "---------created " + table_name + "-------" << endl;
      string sub_separator = "comma";
      vector<string> sub_query_segment = parse_string(query_segment[3], sub_separator);
      create_table(table_name, sub_query_segment);
      display_element(table_name);
  // 2 - insertion queries
}else if (query_segment[0] == "insert") {
    string table_name = query_segment[2];
    cout << "---------inserted element into " + table_name + "-------" << endl;
    string sub_separator = "comma";
    vector<string> column = parse_string(query_segment[3], sub_separator);
    insert_element(table_name, column);
    display_element(table_name);
  // 3 - selection queries
}else if (query_segment[0] == "select"){
    string column_name = query_segment[1];
    string table_name = query_segment[3];
    cout << "---------selected element from " + table_name + "-------" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_string(query_segment[5], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  // 4 - updating queries
}else if (query_segment[0] == "update") {
    string table_name = query_segment[1];
    cout << "---------updated " + table_name + "-------" << endl;
    string sub_separator = "equal";
    vector<string> sub_query_segment = parse_string(query_segment[2], sub_separator);
    string sub_sub_separator = "comma";
    vector<string> column = parse_string(sub_query_segment[1], sub_sub_separator);
    vector<string> where_condition = parse_string(query_segment[4], sub_separator);
    update_element(table_name, column, where_condition[0], where_condition[1]);
    display_element(table_name);
  // 5 - deletion queries
}else if (query_segment[0] == "delete"){
    string table_name = query_segment[2];
    cout << "---------" + table_name + " after element deletion-------" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_string(query_segment[4], sub_separator);
    delete_element(table_name, where_condition[0], where_condition[1]);
    display_element(table_name);
  // 6 - drop queries
}else if (query_segment[0] == "drop"){
    string table_name = query_segment[2];
    drop_table(table_name);
  // 7 - invalid query
}else if (query_segment[0] == "show"){
    string table_name = query_segment[2];
    display_element(table_name);
}else {
    cout << "please, Enter valued query. " << endl;
  }
}

void display_query_syntax(){
  cout << "=====================================================================================================\n";
  cout << "\t\t sample query syntax example\n";
  cout << "\t1) create table table_name firstname,lastname,age\n";
  cout << "\t2) insert into table_name name,age,gender\n";
  cout << "\t3) select * from table_name where firstname=firstname\n";
  cout << "\t4) update table_name values=name,age,gender where firstname=firstname\n";
  cout << "\t5) delete from table_name where firstname=firstname\n";
  cout << "\t6) select * from table1_name inner_join table2_name on table1_name.firstname=table2_name.firstname\n";
  cout << "\t7) show table table_name\n";
  cout << "\t8) drop table table_name\n";
  cout << "\t\t Enter quite or q to quite. ";
  cout << "=====================================================================================================\n\n";
}

int main(int argc, char const *argv[]) {

  // operations
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
