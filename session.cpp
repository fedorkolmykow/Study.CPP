#include "session.h"

bool Session::CheckUID(string cookieuid)
    {
        if(cookieuid.empty())
            return false;
        string uid;
        client.get(cookieuid, [&uid, &cookieuid](cpp_redis::reply& reply){
            if(reply.is_string())
                if(reply.as_string() == "1")
                    uid = cookieuid;
        });
        client.sync_commit();
        return uid == cookieuid && !uid.empty();
    }
    
string Session::getvar(string key, string varname)
    {
        string resp;
        client.get(key + varname, [&resp](cpp_redis::reply& reply){
            if(reply.is_string())
                resp = reply.as_string();
            else
                resp = "";
        });
        client.sync_commit();
        return resp;
    }
    
void Session::setvar(string key, string var, string val)
    {
        client.set(key + var, val);
        client.sync_commit();
    }
    
Session::Session(string _uid)
    {
        client.connect("127.0.0.1", 6379);
        if (!CheckUID(_uid))
        {
			new_session=true;
            uid = generateUUID();
            setvar(uid, "", "1");
        }
        else 
            uid = _uid;
    }
    
string Session::generateUUID() 
{
        std::srand(time(nullptr));
        std::string uuid = std::string(36, ' ');
        int rnd = 0;
        int r = 0;

        uuid[8] = '-';
        uuid[13] = '-';
        uuid[18] = '-';
        uuid[23] = '-';

        uuid[14] = '4';

        for (int i = 0; i < 36; i++) {
            if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) {
                if (rnd <= 0x02) {
                    rnd = 0x2000000 + (std::rand() * 0x1000000) | 0;
                }
                rnd >>= 4;
                uuid[i] = CHARS[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
            }
        }
        return uuid;
}
