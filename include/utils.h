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
  cout << "\t1) create table student id,name,age,gender\n";
  cout << "\t2) insert into student 1,danny,21,male\n";
  cout << "\t3) select * from student where name=danny\n";
  cout << "\t4) update student values=1,danny,25,male where name=danny\n";
  cout << "\t5) delete from student where id=1\n";
  cout << "\t6) select * from student inner_join teacher where name=danny\n";
  cout << "\t7) show table student\n";
  cout << "\t8) drop table student\n";
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
