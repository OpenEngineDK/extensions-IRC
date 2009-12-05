//
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "IRCClient.h"
#include <Logging/Logger.h>
#include <Network/IRCChannel.h>

namespace OpenEngine {
namespace Network {


    std::ostream& operator<<(std::ostream& os, IRCLine l) {
        os << l.ToString();
        return os;
    }


    IRCClient::IRCClient(string host, string nick, string user) :
        host(host),
        nick(nick),
        user(user),
        isOnline(false) {

        sock = new TCPSocket(6667);
        sock->Connect(host);
        run = true;


        IRCLine nl("NICK",nick);
        IRCLine ul("USER","OE-client");
        ul.params.push_back(nick);
        ul.params.push_back(".");
        ul.params.push_back(".");

        SendIRCLine(nl,true);
        SendIRCLine(ul,true);
        
    }

    IRCClient::~IRCClient() {
        delete sock;
    }

    void IRCClient::SendIRCLine(IRCLine l, bool force) {        
        if (force || isOnline) {
            logger.info << "Send: " << l << logger.end;        
            sock->SendLine(l.Encode());
        } else {
            queuedLines.push_back(l);
        }
    }

    void IRCClient::Run() {
        while (run && sock->IsOpen()) {
            string line = sock->ReadLine();
            if (line == "")
                continue;
            // Parse the line!
            //logger.info << "RECV: " << line << logger.end;
            IRCLine l;
            l.Decode(line);

            HandleIRCLine(l);
            
            //logger.info << l.Encode() << logger.end;
            logger.info << l << logger.end;
        }
    }

    void IRCClient::Join(string ch) {
        SendIRCLine(IRCLine("JOIN",ch));
    }

    void IRCClient::EmptyQueue() {
        for (list<IRCLine>::iterator itr = queuedLines.begin();
             itr != queuedLines.end();
             itr++) {
            SendIRCLine(*itr);
        }
        queuedLines.empty();
    }

    void IRCClient::HandleIRCLine(IRCLine line) {
        if (line.cmd == "001") {
            isOnline = true;
            EmptyQueue();
        } else if (line.cmd == "PING") {
            SendIRCLine(IRCLine("PONG",line.tail));
        }  else if (line.cmd == "JOIN") {
            IRCChannel* ch =new IRCChannel(*this,line.tail);
            channels.insert(make_pair<>(line.tail,ch));
            JoinedChannelArg arg(*ch);
            joinEvent.Notify(arg);
        }
            
    }

    void IRCClient::Handle(ProcessEventArg arg) {
        joinEvent.Release();
    }

    void IRCClient::Handle(DeinitializeEventArg arg) {

    }

    void IRCClient::Stop() {
        sock->Close();
        run = false;
    }

} // NS Network
} // NS OpenEngine
