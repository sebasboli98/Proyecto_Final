#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <array>
#include <map>
#include <vector>



namespace gvr{

    typedef unsigned int uint;

    typedef std::pair<std::array<std::string, 3>, std::array<uint, 3>> udpair;
    typedef std::map<std::string, udpair> udat;

}
//using namespace gvr;
//udpair x;

#endif // UTILITIES_H
