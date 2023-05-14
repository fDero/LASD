
#pragma once

#include "hashtable.hpp"
#include <string>

namespace lasd {

    /******************************************** HASH-FUNCTIONS **************************************/
    // notice that the hash function is a template method of the template class HashTable, it is instaciatied
    // and specialized for types such as int, double and std::string, but it actually can be as generic as 
    // needed with the use of a reinterpret cast wich is capable of reading the bytes of the spceific object
    // passed as parameter and it treats them as if they were a string of character (each byte as a char)

    template<typename Data> inline sizetype HashTable<Data>::HashFunction(const Data& object) const noexcept {
        auto ptr = reinterpret_cast<char const* const>(&object);
        sizetype encoding = seed;
        for (auto addresscursor = ptr; addresscursor - ptr < sizeof(Data); addresscursor++){
            encoding = (encoding * 54059) ^ (*addresscursor * 76963);
        }
        return (encoding % 86969) % buckets;
    }

    template<> inline sizetype HashTable<std::string>::HashFunction(const std::string& string) const noexcept {
        sizetype encoding = seed;
        for (const char letter : string) encoding = (encoding * 54059) ^ (76963 * (int)letter);
        return (encoding % 86969) % buckets;
    }

    template<> inline sizetype HashTable<int>::HashFunction(const int& integer) const noexcept {
        return (integer * integer + seed) % buckets;
    }

    template<> inline sizetype HashTable<double>::HashFunction(const double& decimal_floating_point_value) const noexcept {
        double square = (decimal_floating_point_value * decimal_floating_point_value);
        sizetype encoding = ((sizetype)square + seed) % buckets;
        return encoding;
    }




    /********************************** GET THE LOWEST POWER OF 2 BIGGER THAN nx *****************************/
    // this algorithms is based on the low level rappresentation of a numerical integral type in modern CPUs
    // and archieves a constant-time-complexity computation of the lowest power of 2 bigger than a given number

    template <typename Data> sizetype HashTable<Data>::RoundupPower2(sizetype nx) const noexcept {
        nx -= 0x00001;
        nx |= nx >> 1;
        nx |= nx >> 2;
        nx |= nx >> 4;
        nx |= nx >> 8;
        nx |= nx >> 16;
        nx |= nx >> 32;
        return ++nx;
    }
}