// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_I_R_C_LOGGER_H_
#define _OE_I_R_C_LOGGER_H_

#include <Logging/ILogger.h>
#include <Network/IRCChannel.h>

namespace OpenEngine {
namespace Logging {
/**
 * Short description.
 *
 * @class IRCLogger IRCLogger.h ons/IRC/Logging/IRCLogger.h
 */

using Network::IRCChannel;

class IRCLogger : public ILogger {
private:
    IRCChannel *chan;
public:
    IRCLogger(IRCChannel* c);
    void Write(LoggerType type, string msg);
};

} // NS Logging
} // NS OpenEngine

#endif // _OE_I_R_C_LOGGER_H_
