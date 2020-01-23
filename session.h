/* File session.h */
 #ifndef SESSION_H
 #define SESSION_H
#include <string>
#include <cpp_redis/cpp_redis>
using namespace std;
const std::string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
class Session
{
	public :
		Session(string _uid);
        bool CheckUID(string name);
        string getvar(string key, string varname);
        void setvar(string key, string var, string val);
        string getUID() {return uid;};
        bool getNewSes() {return new_session;};
		~Session () {};
	private:
        string generateUUID();
		cpp_redis::client client;
        string uid;
        bool new_session;
} ;
 
#endif /* SESSION_H */
