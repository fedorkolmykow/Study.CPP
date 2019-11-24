#include <iostream>
#include "cgi_class.h"
#include "DB.h"
#include <fstream>
#include <iostream>

using namespace std;
void Send(CGI* cgi, DB* db);
void Delete(DB* db, int id);
string Show(DB* db);
string readFile(const string& fileName);


int main()
{
	string PostData;
    cin>>PostData;
    CGI *cgi = new CGI(PostData);
    DB *db = new DB("DB_records.txt"); 
    cout << "Content-Type: text/html; charset=utf-8"<< endl << endl;

	if (cgi->httpPost("send")=="send")
		{
			Send(cgi,db);
			cout << readFile("start.html");
		}
	if (cgi->httpPost("show")=="show")
		{
			cout << "Data:  " << Show(db) << endl;
			return 0;
		}
	if (cgi->httpPost("delete")=="delete")
		Delete(db, 0);
	delete db;
    return 0;
}
//send=send&Name=Lech&FamilyName=Walensa
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
	for(int i = 0; i < db->RecordsCount(); i++)
	{
		Output = db->ReadRecord(i) + 
		"<p><input name=\"delete\"  type=\"submit\" value=\"" + 
		to_string(i) + "\"></p>";
		Page.insert(it, Output);
	}
	Output = "";
	for (it=Page.begin(); it!=Page.end(); ++it)
		Output = Output + *it + "\n";
	return Output;
}

void Delete(DB* db, int id)
{}

string readFile(const string& fileName) {
    ifstream f(fileName);
    stringstream ss;
    ss << f.rdbuf();
    f.close();
    return ss.str();
}
