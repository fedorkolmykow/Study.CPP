#include <iostream>
#include "cgi_class.h"
#include "DB.h"
#include "session.h"
#include <fstream>
#include <iostream>
#include <string>
//#include <filesystem>

using namespace std;
void Send(CGI* cgi, DB* db);
void Delete(CGI* cgi, DB* db);
string Show(DB* db);
string readFile(const string& fileName);
string ShowFiles();

int main()
{
	
	cout << "Content-Type: text/html; charset=utf-8"<< endl;
	DB *db;   
    Session *ses;
	CGI *cgi = new CGI();
    db = new DB("DB_records.txt"); 
    ses = new Session(cgi->getCookie("uid"));

    //cout << ses->getUID() << "<br>";
    if (ses->getNewSes())
        cout << cgi->setCookie("uid", ses->getUID());
	if (cgi->httpPost("send")=="send")
		{
			cout << cgi->setCookie("Name", cgi->httpPost("Name"));
			cout << cgi->setCookie("FamilyName", cgi->httpPost("FamilyName"));
		}
	cout << endl;
	if (cgi->httpPost("send")=="send")
		{
			Send(cgi,db);
			cout << readFile("index.html");
			cout << "В Базу данных добавлено: " << cgi->httpPost("Name") << "  " << cgi->httpPost("FamilyName")<< "<br>";
		}
		
	if (cgi->httpPost("show")=="show")
			cout <<  Show(db) << endl;

		
	if (cgi->httpPost("delete")=="delete")
		{

			Delete(cgi, db);
			cout <<  Show(db) << endl;
		}
	if ((cgi->httpPost("back")=="back") || (cgi->httpPost("load")=="load") )
			cout << readFile("index.html");		

	//if (cgi->httpPost("\"show_files\"")=="show_files" )
	//		cout << ShowFiles();	
			
	if ((cgi->httpPost("admin")=="admin"))
	{
		cout << readFile("index.html");		
		ses->setvar(ses->getUID(), "admin", "1");
	}
	if ((cgi->httpPost("user")=="user"))
	{
		cout << readFile("index.html");		
		ses->setvar(ses->getUID(), "admin", "0");
	}

	if (ses->getvar(ses->getUID(), "admin")=="1")
		cout << "Добро пожаловать, администратор"<< "<br>";
	else
		cout << "Добро пожаловать, пользователь"<< "<br>";
    cout << "Current session's UID: " << ses->getUID() << "<br>";
    
    //cout << "Files: <br>";
    //for(auto& p: fs::directory_iterator("files"))
    //    cout << p << "<br>";
	delete db;
	delete cgi;
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

/*string ShowFiles()
{
	list<string> Page;
	list<string> :: iterator it;
	string Output;
	istringstream Stream(readFile("blank1.html"));
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
	
	
}*/

string readFile(const string& fileName) {
    ifstream f(fileName);
    stringstream ss;
    ss << f.rdbuf();
    f.close();
    return ss.str();
}
