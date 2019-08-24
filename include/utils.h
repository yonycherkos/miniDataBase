#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

void display_query_syntax(){
  cout << "=====================================================================================================\n";
  cout << "\t\t sample query syntax example\n";
  cout << "\t1) create table table_name firstname,lastname,age\n";
  cout << "\t2) insert into table_name name,age,gender\n";
  cout << "\t3) select * from table_name where firstname=firstname\n";
  cout << "\t4) update table_name values=name,age,gender where firstname=firstname\n";
  cout << "\t5) delete from table_name where firstname=firstname\n";
  cout << "\t6) select * from table1_name inner_join table2_name where firstname=firstname\n";
  cout << "\t7) show table table_name\n";
  cout << "\t8) drop table table_name\n";
  cout << "\t\t Enter quite or q to quite.\n";
  cout << "=====================================================================================================\n\n";
}

vector<string> parse_query(string str, string separator){
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
