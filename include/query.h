#include <iostream>
#include <string>
#include <vector>
#include "operation.h"

using namespace std;

void create_query(vector<string> query_segment){
  string table_name = query_segment[2];
  cout << "\t\t =========created " + table_name + "=======" << endl;
  string sub_separator = "comma";
  vector<string> sub_query_segment = parse_query(query_segment[3], sub_separator);
  create_table(table_name, sub_query_segment);
  show_table(table_name);
}

void insert_query(vector<string> query_segment){
  string table_name = query_segment[2];
  cout << "\t\t =========inserted element into " + table_name + "=======" << endl;
  string sub_separator = "comma";
  vector<string> column = parse_query(query_segment[3], sub_separator);
  insert_element(table_name, column);
  show_table(table_name);
}

void select_query(vector<string> query_segment){
  // select from inner joined table
  string join_connector = query_segment[4];
  if (join_connector == "inner_join"){
    string column_name = query_segment[1];
    string table1_name = query_segment[3];
    string table2_name = query_segment[5];
    string table_name = inner_join(table1_name, table2_name);
    cout << "\t\t =========selected element from " + table_name + "=======" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_query(query_segment[7], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  // select from outter joined table
  } else if (join_connector == "outter_join"){
    string column_name = query_segment[1];
    string table1_name = query_segment[3];
    string table2_name = query_segment[5];
    string table_name = outter_join(table1_name, table2_name);
    cout << "\t\t =========selected element from " + table_name + "=======" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_query(query_segment[7], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  // select from left joined table
  } else if (join_connector == "left_join"){
    string column_name = query_segment[1];
    string table1_name = query_segment[3];
    string table2_name = query_segment[5];
    string table_name = left_join(table1_name, table2_name);
    cout << "\t\t =========selected element from " + table_name + "=======" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_query(query_segment[7], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  // select from right joined table
  } else if(join_connector == "right_join"){
    string column_name = query_segment[1];
    string table1_name = query_segment[3];
    string table2_name = query_segment[5];
    string table_name = right_join(table1_name, table2_name);
    cout << "\t\t =========selected element from " + table_name + "=======" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_query(query_segment[7], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  // select from a single table
  }else{
    string column_name = query_segment[1];
    string table_name = query_segment[3];
    cout << "\t\t =========selected element from " + table_name + "=======" << endl;
    string sub_separator = "equal";
    vector<string> where_condition = parse_query(query_segment[5], sub_separator);
    select_element(table_name, column_name, where_condition[0], where_condition[1]);
  }
}

void update_query(vector<string> query_segment){
  string table_name = query_segment[1];
  cout << "\t\t =========updated " + table_name + "=======" << endl;
  string sub_separator = "equal";
  vector<string> sub_query_segment = parse_query(query_segment[2], sub_separator);
  string sub_sub_separator = "comma";
  vector<string> column = parse_query(sub_query_segment[1], sub_sub_separator);
  vector<string> where_condition = parse_query(query_segment[4], sub_separator);
  update_element(table_name, column, where_condition[0], where_condition[1]);
  show_table(table_name);
}

void delete_query(vector<string> query_segment){
  string table_name = query_segment[2];
  cout << "\t\t =========" + table_name + " after element deletion=======" << endl;
  string sub_separator = "equal";
  vector<string> where_condition = parse_query(query_segment[4], sub_separator);
  delete_element(table_name, where_condition[0], where_condition[1]);
  show_table(table_name);
}

bool validate_query(vector<string> query_segment){

}

void query(string query){
  string separator = "space";
  vector<string> query_segment = parse_query(query, separator);
  int query_lenght = query_segment.size();
  // 1 - creation queries
  if (query_segment[0] == "create") {
      if (query_lenght < 4){
        cout << "\t\t invalid create table query, Enter valued query \n";
      }else{
        create_query(query_segment);
      }
  // 2 - insertion queries
  }else if (query_segment[0] == "insert") {
      if (query_lenght < 4){
        cout << "\t\t invalid insert elements into table query, Enter valued query \n";
      }else{
        insert_query(query_segment);
      }
    // 3 - selection queries
  }else if (query_segment[0] == "select"){
      if (query_lenght < 6){
        cout << "\t\t invalid select elements from table query, Enter valued query \n";
      }else{
        select_query(query_segment);
      }
    // 4 - updating queries
  }else if (query_segment[0] == "update") {
      if (query_lenght < 5){
        cout << "\t\t invalid update table elements query, Enter valued query \n";
      }else{
        update_query(query_segment);
      }
    // 5 - deletion queries
  }else if (query_segment[0] == "delete"){
      if (query_lenght < 5){
        cout << "\t\t invalid delete elements from table query, Enter valued query \n";
      }else{
        delete_query(query_segment);
      }
    // 6 - drop queries
  }else if (query_segment[0] == "drop"){
      if (query_lenght < 3){
        cout << "\t\t invalid table create query \n";
      }else{
        string table_name = query_segment[2];
        drop_table(table_name);
      }
    // 7 - invalid query
  }else if (query_segment[0] == "show"){
      if (query_lenght < 3){
        cout << "\t\t invalid table create query, Enter valued query \n";
      }else{
        string table_name = query_segment[2];
        show_table(table_name);
      }
  }else {
      cout << "\t\t please, Enter valued query. " << endl;
  }
}
