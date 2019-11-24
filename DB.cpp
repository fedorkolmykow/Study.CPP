#include "DB.h"
#include <iostream>
DB::DB(string path)
{
	string temp;
	Path=path;
	ifstream infile(Path, ios_base::in | ios_base::app);
	
	while(getline(infile,temp))
	{
		Data.push_front(temp);	
	}
	infile.close();
}

string DB::ReadRecord(int id)
{
	list<string> :: iterator it = Data.begin();
	for(int j = 0; j < id; j++)
		it++;
	return *it;
}

void DB::WriteRecord(string record)
{
	Data.push_back(record);

}

void DB::DeleteRecord(int id)
{
	list<string>  :: iterator it;
	it = Data.begin(); 
	advance(it,id);
	Data.erase(it);
}

int DB::RecordsCount() { return Data.size();}

DB::~DB()
{
	ofstream ofile(Path, ios_base::out| ios_base::trunc);
	for(list<string> :: iterator it = Data.begin(); it!=Data.end(); it++)
	{
		ofile << (*it + "\n");
		cout << (*it + "\n");
	}
	ofile.close();
}
