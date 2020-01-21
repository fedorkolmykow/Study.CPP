 /* File cgi_class.h */
 #ifndef CGI_CLASS_H
 #define CGI_CLASS_H
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
class CGI
{
	public :
		CGI();
		string httpGet(string name);
		string httpPost(string name);
		string getCookie(string name);
		string setCookie(string name, string value);
		istringstream Stream();
		map <string, string> cookies;
		~CGI() {}
	private:
		map <string, string> split(string s, char delimiter1, char delimetr2);
		map <string, string> data;
		map <string,string> headers;
		//map <string, string> cookies;
		void ltrim(std::string &s);
		void rtrim(std::string &s);
		void trim(std::string &s);
		void parseHeaders();
		char from_hex(char ch);
		string getHeader(string);
		string rawURLDecode(string text);
		string Replace(string text);
} ;
 
 #endif /* CGI_CLASS_H */
