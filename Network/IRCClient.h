// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _IRC_CLIENT_H_
#define _IRC_CLIENT_H_

#include <Network/TCPSocket.h>
#include <Core/Thread.h>
#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Network/IRCLine.h>
#include <Core/LockedQueuedEvent.h>

#include <map>

namespace OpenEngine {
namespace Network {

    using namespace OpenEngine::Core;


    class IRCChannel;

    struct JoinedChannelArg {
        IRCChannel& channel;
        JoinedChannelArg(IRCChannel& c) : channel(c) {}
    };



/**
 * Short description.
 *
 * @class IRCClient IRCClient.h ons/IRC/Network/IRCClient.h
 */
class IRCClient : public Thread,
                  public IListener<ProcessEventArg>, 
                  public IListener<DeinitializeEventArg> {
private:
    TCPSocket* sock;

    string host,nick,user;
    bool run;



    LockedQueuedEvent<JoinedChannelArg> joinEvent;

    bool isOnline;

    list<IRCLine> queuedLines;
    map<string,IRCChannel*> channels;

    void EmptyQueue();

protected:
    friend class IRCChannel;
    void SendIRCLine(IRCLine l, bool force=false);

public:
    IRCClient(string host, string nick, string user);
    ~IRCClient();

    void Stop();
    
    void Run();

    void HandleIRCLine(IRCLine l);

    void Join(string ch );

    void Handle(ProcessEventArg arg);
    void Handle(DeinitializeEventArg arg);

    IEvent<JoinedChannelArg>& JoinedChannelEvent() {return joinEvent;}
};

} // NS Network
} // NS OpenEngine

#endif
