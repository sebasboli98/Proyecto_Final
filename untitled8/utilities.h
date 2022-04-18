#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <array>
#include <map>
#include <vector>

namespace gvr{

    typedef unsigned int uint;
    typedef long long int llint;

    typedef std::pair<std::array<std::string, 3>, std::array<uint, 3>> udpair;//Pareja de datos(Arreglo de 3 string y arrgelo 3 enteros sin signos)
    typedef std::map<std::string, udpair> udat; // mapa que tiene una llave string y contiene una pareja de datos

    typedef std::pair<float, float> vec2d;//Vector 2D

}

namespace mo{//Matematica operacional
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

    inline float invSqrt(float n){ // Inv raiz cuadrada(Salio del algoritmo de QuakeIII)
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

    inline float oneOver(float num) {return num > 0? invSqrt(num * num) : invSqrt(num * num) * -1;}//1/numero
    inline float Sqrt(float n){return oneOver(invSqrt(n));}//Raiz cuadrada

    template <typename T>
    T exp(T base, int exponent){//Potencia
        T Ans = 1;
        for(; exponent > 0; exponent--){
            Ans *= base;
        }
        return Ans;
    }

    template<typename T>
    T abs(T Num){   //Absoluto
        return Num >= 0? Num : Num * -1;
    }

}
#endif // UTILITIES_H
