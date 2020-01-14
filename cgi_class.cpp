#include "cgi_class.h"
	CGI::CGI(string Data, string Cookies)
	{
		data = split(Data, '&', '=');
		cookies = split(Cookies, ';','=');
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
			trim(key);
			trim(value);
			result.insert(make_pair(key,value));
		}
		return result;
	}
 
	string CGI::httpGet(string name)
	{
		if(data.find(name)==data.end())
			return "";
		else
			return data[name];
	}
 
	string CGI::httpPost(string name)
	{
		if(data.find(name)==data.end())
			return "";
		else
			return data[name];
	}
	
	string CGI::getCookie(string name)
	{
		if(cookies.find(name)==data.end())
			return "";
		else
			return cookies[name];
	}
	
	string CGI::setCookie(string name, string value)
	{
		return "Set-Cookie: " + name + "=" + value + "\n";
	}
    
    // trim from start (in place)
	void CGI::ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
	void CGI::rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
}

	// trim from both ends (in place)
	void CGI::trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

