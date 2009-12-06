#ifndef _IRC_CHANNEL_H_
#define _IRC_CHANNEL_H_
// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Network/IRCClient.h>

namespace OpenEngine {
namespace Network {

    struct User {
        
        string nick;

        User(string n) : nick(n) {}

        User(Prefix p) : nick(p.Nick()) {}

        //Prefix prefix;
        
    };


    struct MessageEventArg {
        User* user;
        IRCChannel* channel;
        string message;
    };

    struct UserArg {
        User* user;

    };
    struct UserJoinedArg : UserArg {};
    struct UserPartedArg : UserArg {};

/**
 * Short description.
 *
 * @class IRCChannel IRCChannel.h ons/IRC/Network/IRCChannel.h
 */
class IRCChannel {
private:
    IRCClient& client;
    string name;
    
    LockedQueuedEvent<UserJoinedArg> joinEvent;
    LockedQueuedEvent<UserPartedArg> partEvent;
    
    LockedQueuedEvent<MessageEventArg> msgEvent;

    list<User*> users;

    User* FindUser(string nick);
    
    void AddUser(User*);

protected:
    friend class IRCClient;
    IRCChannel(IRCClient& client, string name);    
public:
    ~IRCChannel();
    
    void SendMsg(string msg);

    void HandleIRCLine(IRCLine l);

    IEvent<UserJoinedArg>& UserJoinedEvent() {return joinEvent;}
    IEvent<UserPartedArg>& UserPartedEvent() {return partEvent;}

    IEvent<MessageEventArg>& ChannelMessageEvent() {return msgEvent;}
};

} // NS Network
} // NS OpenEngine

#endif
