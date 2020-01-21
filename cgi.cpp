#include <iostream>
#include "cgi_class.h"
#include "DB.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
void Send(CGI* cgi, DB* db);
void Delete(CGI* cgi, DB* db);
string Show(DB* db);
string readFile(const string& fileName);


int main()
{
	CGI *cgi;
	DB *db;   
	cgi = new CGI();
    db = new DB("DB_records.txt"); 
    
    cout << "Content-Type: text/html; charset=utf-8"<< endl;

	if (cgi->httpPost("send")=="send")
		{
			Send(cgi,db);
			cout << cgi->setCookie("Name", cgi->httpPost("Name"));
			cout << cgi->setCookie("FamilyName", cgi->httpPost("FamilyName"));
			cout << endl;
			cout << readFile("index.html");
			cout << "В Базу данных добавлено: " << cgi->httpPost("Name") << "  " << cgi->httpPost("FamilyName");
		}
		
	if (cgi->httpPost("show")=="show")
		{
			cout << endl;
			cout <<  Show(db) << endl;
			return 0;
		}
		
	if (cgi->httpPost("delete")=="delete")
		{
			Delete(cgi, db);
			cout << endl;
			cout <<  Show(db) << endl;
		}
	if (cgi->httpPost("back")=="back")
		{
			cout << endl;
			cout << readFile("index.html");
			return 0;
		}
	delete db;
    return 0;
}

void Send(CGI* cgi, DB* db)
{
	string record = cgi->httpPost("Name") + " " 
										+ cgi->httpPost("FamilyName");
	db->WriteRecord(record);
}
	
string Show(DB* db)
{
	list<string> Page;
	list<string> :: iterator it;
	string Output;
	istringstream Stream(readFile("blank.html"));
	while(getline(Stream, Output))
	{
		Page.push_back(Output);
	}
	it = Page.begin();
	it++;
	it++;
	it++;
	for(int i = 0; i < db->RecordsCount(); i++)
	{
		Output = "<li><p>"  +  db->ReadRecord(i) + "\t<input name=\"check" + to_string(i) +"\" type=\"checkbox\"></p></li>";
		Page.insert(it, Output);
	}
	Output = "";
	for (it=Page.begin(); it!=Page.end(); ++it)
		Output = Output + *it + "\n";
	return Output;
}

void Delete(CGI* cgi, DB* db)
{
	string name;
	for(int i = 0; i < db->RecordsCount(); i++)
	{
		name = "check" + to_string(i);
		if (cgi->httpPost(name) == "on")
		{
				db->DeleteRecord(i);
				i--;
		}
	}
	
	
}

string readFile(const string& fileName) {
    ifstream f(fileName);
    stringstream ss;
    ss << f.rdbuf();
    f.close();
    return ss.str();
}
