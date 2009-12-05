// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#include <Network/IRCChannel.h>

namespace OpenEngine {
namespace Network {

    IRCChannel::IRCChannel(IRCClient& c, string n) : client(c),name(n) {
        
    }

    void IRCChannel::SendMsg(string m) {
        IRCLine l("PRIVMSG",m);
        l.params.push_back(name);
      
        client.SendIRCLine(l);
    }

} // NS Network
} // NS OpenEngine
