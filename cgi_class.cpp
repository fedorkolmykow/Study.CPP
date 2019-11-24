#include "cgi_class.h"
	CGI::CGI(string Data)
	{
		data = split(Data, '&', '=');
	}
 
	map <string, string> CGI::split(string s,char delimiter1,char delimiter2)
	{
		map <string, string> result;
		string str;
		istringstream Stream1(s);
		while(getline(Stream1, str, delimiter1))
		{
			string key;
			string value;
			istringstream Stream2(str);
			getline(Stream2, key, delimiter2);
			getline(Stream2, value);
			result.insert(make_pair(key,value));
		}
		return result;
	}
 
	string CGI::httpGet(string name)
	{
		return data[name];
	}
 
	string CGI::httpPost(string name)
	{
		return data[name];
	}
	
	string CGI::getCookie(string name)
	{
		return "0";
	}
	
	string CGI::setCookie(string name, string value)
	{
		return "0";
	}
    
