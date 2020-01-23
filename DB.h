/* File DB.h */
 #ifndef DB_H
 #define DB_H
#include <string>
#include <list>
#include <fstream>
#include <iterator>
using namespace std;
class DB
{
	public :
		DB(string path);
		string ReadRecord(int id);
		void WriteRecord(string record);
		void DeleteRecord(int id);
		int RecordsCount();
		~DB();
	private:
		//void SetPosition(int id);
		list<string> Data;
		string Path;
} ;
 
#endif /* CGI_CLASS_H */
