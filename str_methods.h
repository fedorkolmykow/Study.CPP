/* File str_methods.h */
 #ifndef STR_METHODS_H
 #define STR_METHODS_H
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

map <string, string> split(string s, char delimiter1, char delimetr2);
vector <string> split(string s, string delimiter);
vector <string> split(string s,char delimiter);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
string Replace(string text, string cur, string ins);



#endif /* STR_METHODS_H */
