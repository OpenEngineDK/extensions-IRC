// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#include <Network/IRCChannel.h>
#include <boost/algorithm/string.hpp>


namespace OpenEngine {
namespace Network {

    IRCChannel::IRCChannel(IRCClient& c, string n) : client(c),name(n) {
        client.events.push_back(&joinEvent);
        client.events.push_back(&partEvent);
        client.events.push_back(&msgEvent);
    }

    IRCChannel::~IRCChannel() {
        client.events.remove(&joinEvent);
        client.events.remove(&partEvent);
        client.events.remove(&msgEvent);

    }

    void IRCChannel::SendMsg(string m) {
        IRCLine l("PRIVMSG",m);
        l.params.push_back(name);
      
        client.SendIRCLine(l);

        MessageEventArg arg;
        arg.user = FindUser(client.GetNick());
        arg.channel = this;
        arg.message = m;

        msgEvent.Notify(arg);
    }

    User* IRCChannel::FindUser(string nick) {
        for (list<User*>::iterator itr = users.begin();
             itr != users.end();
             itr++) {
            User *u = *itr;
            if (u->nick == nick)
                return u;
        }
        return NULL;
    }

    void IRCChannel::AddUser(User* u) {
        users.push_back(u);
        UserJoinedArg a;
        a.user = u;
        joinEvent.Notify(a);
    }

    void IRCChannel::HandleIRCLine(IRCLine line) {
        // Lets assume that IRCClient are only sending us stuff for this channel!
        if (line.cmd == "JOIN") {
            AddUser(new User(line.prefix));
            
        } else if (line.cmd == "353") {
            vector<string> names;
            boost::split(names, line.tail, boost::is_any_of(" "));
            for (vector<string>::iterator itr = names.begin();
                 itr != names.end();
                 itr++) {
                
                string n = *itr;
                
                if (n[0] == '@' ||
                    n[0] == '+')
                    n = n.substr(1,n.length()-1);

                AddUser(new User(n));
                

            }
        } else if (line.cmd == "PRIVMSG") {
            string nick = line.prefix.Nick();
            User* user = FindUser(nick);
            if (!user)
                throw "user not found on channel";

            MessageEventArg arg;
            arg.user = user;
            arg.channel = this;
            arg.message = line.tail;

            msgEvent.Notify(arg);
        }
    }

} // NS Network
} // NS OpenEngine
