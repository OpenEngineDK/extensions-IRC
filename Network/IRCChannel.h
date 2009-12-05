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

/**
 * Short description.
 *
 * @class IRCChannel IRCChannel.h ons/IRC/Network/IRCChannel.h
 */
class IRCChannel {
private:
    IRCClient& client;
    string name;
protected:
    friend class IRCClient;
    IRCChannel(IRCClient& client, string name);
public:
    void SendMsg(string msg);
    
};

} // NS Network
} // NS OpenEngine

#endif
