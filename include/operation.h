#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include "utils.h"

using namespace std;
using namespace boost;

map<string, set<vector<string>>> database;

void create_table(string table_name, vector<string> column_names){
  set<vector<string>> table;
  table.insert(column_names);
  database.insert(pair<string, set<vector<string>>> (table_name, table));
}

void show_table(string table_name){
  // select all elements
  auto itr1 = database.find(table_name);
  if(itr1 != database.end()){
    set<vector<string>> table = itr1->second;
    for(auto itr2 = table.begin(); itr2 != table.end(); ++itr2){
      for(auto itr3 = itr2->begin(); itr3 != itr2->end(); ++itr3){
        cout << "\t\t" << *itr3 << "\t";
      }
      cout <<"\n\t\t-----------------------------------------------------------------------------------------------\n";
    }
    cout << endl;
  }
}

void drop_table(string table_name){
  auto itr = database.find(table_name);
  if(itr != database.end()){
    database.erase(table_name);
    cout <<"\t\t" << table_name << " has been deleted successfuly. \n";
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
            cout << "\t\t" << *itr3 << "\t";
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


string inner_join(string table1_name, string table2_name){
  // find intersection of two tables
  string inner_join_table_name = "inner_join_" + table1_name + "_and_" + table2_name;
  set<vector<string>> inner_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_intersection(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(inner_join_table, inner_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (inner_join_table_name, inner_join_table));
  }
  return inner_join_table_name;
}

string outter_join(string table1_name, string table2_name){
  // find intersection of two tables
  string outter_join_table_name = "outter_join_" + table1_name + "_and_" + table2_name;
  set<vector<string>> outter_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_union(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(outter_join_table, outter_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (outter_join_table_name, outter_join_table));
  }
  return outter_join_table_name;
}

string left_join(string table1_name, string table2_name){
  // find intersection of two tables
  string left_join_table_name = "left_join_" + table1_name + "_and_" + table2_name;
  set<vector<string>> left_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(left_join_table, left_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (left_join_table_name, left_join_table));
  }
  return left_join_table_name;
}

string right_join(string table1_name, string table2_name){
  // find intersection of two tables
  string right_join_table_name = "right_join_" + table1_name + "_and_" + table2_name;
  set<vector<string>> right_join_table;
  auto itr1 = database.find(table1_name);
  auto itr2 = database.find(table2_name);
  if(itr1 != database.end() && itr2 != database.end()){
    set<vector<string>> table1 = itr1->second;
    set<vector<string>> table2 = itr2->second;
    set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(right_join_table, right_join_table.begin()));
    database.insert(pair<string, set<vector<string>>> (right_join_table_name, right_join_table));
  }
  return right_join_table_name;
}
