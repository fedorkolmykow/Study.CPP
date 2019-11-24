 /* File cgi_class.h */
 #ifndef CGI_CLASS_H
 #define CGI_CLASS_H
#include <string>
#include <map>
#include <sstream>
using namespace std;
class CGI
{
	public :
		CGI(string Data);
		string httpGet(string name);
		string httpPost(string name);
		string getCookie(string name);
		string setCookie(string name, string value);
		istringstream Stream();
		~CGI() {}
	private:
		map <string, string> split(string s, char delimiter1, char delimetr2);
		map <string, string> data;
} ;
 
 #endif /* CGI_CLASS_H */
