#include "cgi_class.h"
	CGI::CGI()
	{
		//if (getenv("CONTENT_TYPE")=="application/x-www-form-urlencoded")
		//{
			string Data;
			cin >> Data;
			Data = rawURLDecode(Data);
			
			data = split(Data, '&', '=');
			cookies = split(headers["cookies"], ';','=');
			
		//}
	}
	
	void CGI::parseHeaders()
	{
		if (getenv("CONTENT_TYPE") != nullptr)
			headers.insert(pair<string, string>("type", getenv("CONTENT_TYPE")));
        if (getenv("CONTENT_LENGTH") != nullptr)
			headers.insert(pair<string, string>("length", getenv("CONTENT_LENGTH")));
        if (getenv("HTTP_COOKIE") != nullptr)
			headers.insert(pair<string, string>("cookies", getenv("HTTP_COOKIE")));
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
			value = Replace(value);
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

	char CGI::from_hex(char ch) 
	{
		return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
	}

	string CGI::rawURLDecode(string text)
	{
		char h;
		ostringstream escaped;
		escaped.fill('0');

		for (auto i = text.begin(), n = text.end(); i != n; ++i) {
			string::value_type c = (*i);

			if (c == '%') {
				if (i[1] && i[2]) {
					h = from_hex(i[1]) << 4 | from_hex(i[2]);
					escaped << h;
					i += 2;
				}
			} else if (c == '+') {
				escaped << ' ';
			} else {
				escaped << c;
			}
		}

		return escaped.str();
	}

	string CGI::Replace(string text)
	{
		
		for (auto i = text.begin(); i != text.end(); ++i) 
		{
			if (*i == '<')
			{
				i = text.erase(i);
				i = text.insert(i, 't');
				i = text.insert(i, 'l');
				i = text.insert(i, '&');
			}
			if (*i == '>')
			{
				i = text.erase(i);
				i = text.insert(i, 't');
				i = text.insert(i, 'g');
				i = text.insert(i, '&');		
			}
		}
		return text;
	}
