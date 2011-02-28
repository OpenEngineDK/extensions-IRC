
# Create the extension library
ADD_LIBRARY(Extensions_IRC
  Network/IRCClient.cpp
  Network/IRCClient.h
  Network/IRCChannel.cpp
  Network/IRCChannel.h
  Logging/IRCLogger.cpp
  Logging/IRCLogger.h
)
