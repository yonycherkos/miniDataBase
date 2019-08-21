#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>

using namespace std;

// void create_database(string database_name){
//   return set<set<vector<string>>> database_name;
// }
//
// void create_table(string table_name){
//   return set<vector<string>> table_name;
// }

void display_element(set<set<vector<string>>> database, set<vector<string>> table){
  // select all elements
  // set<set<vector<string>>>::iterator itr = database.find(table);
  auto itr = database.find(table);
  if(itr != database.end()){
    int count = 1;
    for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
      cout << count << " ";
      for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
        cout << *itr2 << "    ";
      }
      count++;
      cout <<"\n-----------------------------\n";
    }
    cout << endl;
  }else{
    cout << "table to be display doesn't found!" << endl;
  }
}

set<vector<string>> insert_element(set<vector<string>> table, vector<string> column){
  // insert element into the table
  table.insert(column);
  return table;
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

set<vector<string>> update_element(set<vector<string>> table, vector<string> column){
  // update elements of the table
  for(auto itr1 = table.begin(); itr1 != table.end(); ++itr1){
    for(auto itr2 = itr1->begin(); itr2 != itr1->end(); ++itr2){
      if( *itr1->begin() == column[0]){
        table.erase(itr1);
        table.insert(column);
        break;
      }
    }
    cout << endl;
  }
  return table;
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

set<vector<string>> inner_join(set<vector<string>> table1, set<vector<string>> table2){
  // find intersection of two tables
  set<vector<string>> inner_join_table;
  set_intersection(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(inner_join_table, inner_join_table.begin()));
  return inner_join_table;
}

set<vector<string>> outter_join(set<vector<string>> table1, set<vector<string>> table2){
  // find union of two tables
  set<vector<string>> outter_join_table;
  set_union(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(outter_join_table, outter_join_table.begin()));
  return outter_join_table;
}

set<vector<string>> left_join(set<vector<string>> table1, set<vector<string>> table2){
  // find left_join of two tables
  set<vector<string>> left_join_table;
  set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(left_join_table, left_join_table.begin()));
  return left_join_table;
}

set<vector<string>> right_join(set<vector<string>> table1, set<vector<string>> table2){
  // find write join of two tables
  set<vector<string>> right_join_table;
  set_difference(table1.begin(), table1.end(), table2.begin(), table2.end(), inserter(right_join_table, right_join_table.begin()));
  return right_join_table;
}

int main(int argc, char const *argv[]) {

  set<set<vector<string>>> database;
  set<vector<string>> table1;
  set<vector<string>> table2;

  // column to be inserted to both tables
  vector<string> column = {"name", "age", "gender"};

  // columns to be inserted to table1
  vector<string> yonathan = {"yonathan", "23", "male"};
  vector<string> daniel = {"daniel", "20", "male"};
  vector<string> ephrame = {"ephrame", "24", "male"};

  // columns to be inserted to table2
  vector<string> eleny = {"yonathan", "5", "female"};
  vector<string> lidya = {"daniel", "18", "female"};
  vector<string> betty = {"ephrame", "13", "female"};

  // insert the elements to table1
  table1 = insert_element(table1, column);
  table1 = insert_element(table1, yonathan);
  table1 = insert_element(table1, daniel);
  table1 = insert_element(table1, ephrame);

  // insert the elements to table2
  table2 = insert_element(table2, column);
  table2 = insert_element(table2, yonathan);
  table2 = insert_element(table2, daniel);
  table2 = insert_element(table2, ephrame);

  // insert the tables to the databse
  database.insert(table1);
  database.insert(table2);

  display_element(database, table1);
  string name = "yonathan";
  select_element(table1, name);
  table1 = delete_element(table1, name);
  database.insert(table1);
  cout << "after deleting " << endl;
  display_element(database, table1);

  vector<string> daniel_update = {"daniel", "21", "female"};
  table1 = update_element(table1, daniel_update);
  database.insert(table1);
  cout << "after updating " << endl;
  display_element(database, table1);

  // test inner join
  set<vector<string>> inner_join_table;
  inner_join_table = inner_join(table1, table2);
  database.insert(inner_join_table);
  cout << "Table1" << endl;
  display_element(database, table1);
  cout << "Table2" << endl;
  display_element(database, table2);
  cout << "Inner joining" << endl;
  display_element(database, inner_join_table);

  // testing outer join
  set<vector<string>> outter_join_table;
  outter_join_table = outter_join(table1, table2);
  database.insert(outter_join_table);
  cout << "Outter joining" << endl;
  display_element(database, outter_join_table);

  // tesing left join
  set<vector<string>> left_join_table;
  left_join_table = left_join(table1, table2);
  database.insert(left_join_table);
  cout << "Left joining" << endl;
  display_element(database, left_join_table);

  // testing right join
  set<vector<string>> right_join_table;
  right_join_table = right_join(table1, table2);
  database.insert(right_join_table);
  cout << "Right joining" << endl;
  display_element(database, right_join_table);

  return 0;
}
