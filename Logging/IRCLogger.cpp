#include "IRCLogger.h"

namespace OpenEngine {
namespace Logging {

IRCLogger::IRCLogger(IRCChannel* c) : chan(c) {
}

void IRCLogger::Write(LoggerType type, string msg) {
    chan->SendMsg(msg);
}
        
}
}
