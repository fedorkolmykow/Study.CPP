#include "str_methods.h"
#include <iostream>
//Г***окод. Переписать
string Replace(string text, string cur, string ins)
	{
        bool insert = false;
		for (auto i = text.begin(); i != text.end(); ++i) 
		{
            auto iter = i;
            for (auto it = cur.begin(); it != cur.end(); ++it)
            {
                if (*iter != *it)
                {
                    insert = false;
                    break;
                }
                iter++;
                insert = true;
            }
            if (insert)
            {
                i = text.erase(i, iter);
                for (auto it = ins.rbegin(); it != ins.rend(); ++it)
                {
                    i = text.insert(i, *it);
                }
            }
		}
		return text;
}


//	Hello my name my fedor my friend my my !
vector<string> split(string s, string delimiter)
	{
        size_t found, len;
        vector<string> result;
        len = delimiter.size();
        do
        {
            found = s.find(delimiter);
            result.push_back(s.substr(0,found));
            s.erase(0,found + len);
        }
        while(found != string::npos);
            
		return result;
}

vector <string> split(string s,char delimiter)
	{
		vector <string> result;
		string str;
		istringstream Stream1(s);
		while(getline(Stream1, str, delimiter))
		{
			result.push_back(str);
		}
		return result;
	}


map <string, string> split(string s,char delimiter1,char delimiter2)
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
    // trim from start (in place)
void ltrim(std::string &s) 
    {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
void rtrim(std::string &s) 
    {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
    }

	// trim from both ends (in place)
void trim(std::string &s) 
    {
		ltrim(s);
		rtrim(s);
	}
	
