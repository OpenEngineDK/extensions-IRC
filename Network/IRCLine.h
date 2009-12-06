// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace OpenEngine {
namespace Network {

    struct Prefix {
        string raw;

        string Nick() {            
            vector<string> parts;
            boost::split(parts, raw, boost::is_any_of("!@"));
            
            return parts[0];

        }

        
    };

    struct IRCLine {
        Prefix prefix;
        string cmd;
        vector<string> params;
        string tail;

        IRCLine() {}

        IRCLine(string c, string t) : cmd(c), tail(t) {

        }

        
        string Encode() {
            ostringstream out;

            if (prefix.raw != "")
                out << ":" << prefix.raw << " ";
            out << cmd << " ";

            for (vector<string>::iterator itr = params.begin();
                 itr != params.end();
                 itr++) {
                out << *itr << " ";
            }

            out << ":" << tail;
            out << endl;
            return out.str();

        }

        void Decode(string line) {
            istringstream iss(line);

            if (line[0] == ':') {
                iss.get(); // remove :
                iss >> prefix.raw;
            }
            iss >> cmd;

            string n;
            while (iss >> n && (n[0] != ':')) {
                params.push_back(n);
                //iss >> n;
            }
            tail = n.substr(1,n.length()-1);

            while (iss >> n) {
                tail += " ";
                tail += n;
            }

        }

        string ToString() {
            ostringstream out;

            out << "IRC:" << endl
                << " prefix( " << prefix.raw << " )" << endl
                << "    cmd( " <<    cmd << " )" << endl;

            for (vector<string>::iterator itr = params.begin();
                 itr != params.end();
                 itr++) {
                out << " param ( " << *itr << " )" << endl;

            }

            out << "   tail( " <<   tail << " )" << endl;

            return out.str();
        }


    };


} // NS Network
} // NS OpenEngine
