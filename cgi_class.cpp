#include "cgi_class.h"
CGI::CGI()
{
    string Data;
    parseHeaders();

    if (headers["type"]=="application/x-www-form-urlencoded")
    {
		cin >> Data;
        Data = rawURLDecode(Data);
        data = split(Data, '&', '=');
        for (auto i = data.begin(); i != data.end(); ++i) 
        {
            i->second = Replace(i->second, "<", "&lt");
            i->second = Replace(i->second, ">", "&gt");
        }
        cookies = split(headers["cookies"], ';','=');
    }
    if ((headers["type"]=="multipart/form-data"))
    {
		int length = stoi(headers["length"]);
		char tempc[length];
		cin.read(tempc, length);
		string temp(tempc, length);
        vector<string> form_data;
        form_data = split(temp, headers["boundary"]);
        form_data.erase(form_data.begin());
        form_data.erase(form_data.end()-1);
        for (auto it=form_data.begin(); it!=form_data.end(); it++)
        {
            string str = *it;
            size_t pos = str.find("\n\r"); 
            string head = str.substr(0, pos);
            map<string,string> subheaders = split(head, '\n',':');
            map<string,string> disposition = split(subheaders["Content-Disposition"], ';','=');
            str.erase(0, pos);
            trim(str);
            
            subheaders.erase(subheaders.begin());
            if (disposition["filename"]=="")
            {
                data.insert(pair<string, string>(disposition["name"], str));
            }
            else
            {
                UploadedFile upFile;
                upFile.filename = disposition["filename"];
                upFile.type = subheaders["Content-Type"];
                upFile.size = str.size();
                upFile.tmp_name = tmpnam(nullptr);
                ofstream fout(upFile.tmp_name,  ios::out|ios::binary);
                if(!fout.is_open()) 
                    upFile.error = 1;
                else
                {
                    upFile.error = 0;
                    fout.write(str.c_str(),upFile.size);
                    fout.close();
                }
                if (upFile.size > 0)
                Files.push_back(upFile);
                
            }
        }
    }
}

	void CGI::parseHeaders()
	{
        if (getenv("CONTENT_TYPE") != nullptr)
        {
			string boundary;
            map <string, string> temp = split(getenv("CONTENT_TYPE"),';','=');
            boundary = temp.find("boundary")->second;
			
			if (boundary!="")
				{
					headers.insert(pair<string, string>("type",  "multipart/form-data"));
					boundary = "--" + boundary;
					headers.insert(pair<string, string>("boundary", boundary ));
				}
			else
				headers.insert(pair<string, string>("type",  "application/x-www-form-urlencoded"));
        }
        if (getenv("CONTENT_LENGTH") != nullptr)
			headers.insert(pair<string, string>("length", getenv("CONTENT_LENGTH")));
        if (getenv("HTTP_COOKIE") != nullptr)
			headers.insert(pair<string, string>("cookies", getenv("HTTP_COOKIE")));
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
		if(cookies.find(name)==cookies.end())
			return "";
		else
			return cookies[name];
	}
	
	string CGI::setCookie(string name, string value)
	{
		return "Set-Cookie: " + name + "=" + value + "\n";
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
	
	string CGI:: getHeader(string name)
    {
        if(headers.find(name)==headers.end())
			return "";
		else
            return headers[name];
    }
    
    UploadedFile* CGI::getFile(string name)
    {
        for (auto it=Files.begin(); it!=Files.end(); it++)
            if ((*it).filename == name)
                return &(*it);
        return nullptr;
    }
	
	int CGI::move_uploaded_file(UploadedFile tmpFile, string path)
    {
        if (tmpFile.error == 0)
            {
                int len;
                char * buffer;
 
                ifstream  infile(tmpFile.tmp_name, ios::binary);
                ofstream outfile(path + tmpFile.filename, ios::binary);
                infile.seekg (0, ios::end);
                len = infile.tellg();
                infile.seekg (0, ios::beg);
                buffer = new char [len];
                infile.read   (buffer,len);
                outfile.write (buffer,len);
                delete[] buffer;
                infile.close();
                outfile.close();
                remove((tmpFile.tmp_name).c_str());
                return 0;
            }
            else
            {
                remove((tmpFile.tmp_name).c_str());
                return 1;
            }
            
    }
	
	CGI::~CGI()
    {
		if(!Files.empty())
		cout << "На сервер закачены следующие файлы:" << "<br>";
        for (auto it=Files.begin(); it!=Files.end(); it++) 
        {
			cout << "Имя: "<<(*it).filename 
			<< " MIME-тип: " << (*it).type 
			<< " Размер :" <<  (*it).size 
			<< " Временное имя: " << (*it).tmp_name 
			<< " Код ошибки: " <<  (*it).error << "<br>";
            move_uploaded_file(*it, "/home/fakolmykow/www/fakolmykow.mati.su/files/");
        }
        
    }
