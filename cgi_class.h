/* File cgi_class.h */
 #ifndef CGI_CLASS_H
 #define CGI_CLASS_H
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <cstdio> 
#include <fstream>
#include "str_methods.h"

using namespace std;

typedef struct {
  std::string filename; 	// реальное имя файла
  std::string type;	// MIME-тип файла
  std::string tmp_name; // временное имя файла
  int error; 	// код ошибки (0, если нет)
  size_t size; 	// размер загружаемого файла
} UploadedFile;

class CGI
{
	public :
		CGI();
        UploadedFile* getFile(string name);
        string getHeader(string);
		string httpGet(string name);
		string httpPost(string name);
		string getCookie(string name);
		string setCookie(string name, string value);
		istringstream Stream();
		~CGI();
	private:
		vector<UploadedFile> Files;
		map <string, string> data;
		map <string,string> headers;
		map <string, string> cookies;
		void parseHeaders();
		char from_hex(char ch);
        int move_uploaded_file(UploadedFile tmpFile, string path);		
		string rawURLDecode(string text);
		
} ;


 
#endif /* CGI_CLASS_H */
