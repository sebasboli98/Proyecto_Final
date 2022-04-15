#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <array>
#include <map>
#include <vector>

namespace gvr{

    typedef unsigned int uint;
    typedef long long int llint;

    typedef std::pair<std::array<std::string, 3>, std::array<uint, 3>> udpair;
    typedef std::map<std::string, udpair> udat;

    typedef std::pair<float, float> vec2d;

}

namespace mo{
    //template<typename T>
    //T operator^(T base, int exponent){
    //    T Ans = 1;
    //    for(; exponent > 0; exponent--){
    //        Ans *= base;
    //    }
    //    return Ans;
    //}

    //template<>
    //std::string operator^(std::string b, int e){
    //    std::string a = "";
    //    for(; e > 0; e--)
    //        a += b;
    //    return a;
    //}
    //^
    template <typename T>
    T exp(T base, int exponent){
        T Ans = 1;
        for(; exponent > 0; exponent--){
            Ans *= base;
        }
        return Ans;
    }

    inline float invSqrt(float n){ // Quake III Fast invert Square Root Algorithm
        long i;
        float x2, y;

        x2 = n * 0.5f;
        y = n;
        i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (1.5f - (x2 * y * y));
        y = y * (1.5f - (x2 * y * y));

        return y;
    }

    inline float oneOver(float num) {return invSqrt(num * num);}
    inline float Sqrt(float n){return oneOver(invSqrt(n));}

}
#endif // UTILITIES_H
