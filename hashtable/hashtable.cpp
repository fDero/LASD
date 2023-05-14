
#pragma once

#include "hashtable.hpp"
#include <string>
#include <concepts>

namespace lasd {

    /******************************************** HASH-FUNCTIONS **************************************/
    // without loss of generality, every template-type is treated as a string, this allows for this
    // one definition wich covers every use-case needed for this library without need for template-specialization

    template<typename Data> sizetype HashTable<Data>::HashFunction(const Data& object) const noexcept {
        std::string string;
        if constexpr (std::same_as<Data, std::string>){ string = object; }
        else { string = std::to_string(object); } 
        sizetype encoding = seed;
        for (const char letter : string) encoding = (encoding * 54059) ^ (76963 * (int)letter);
        return (encoding % 86969) % buckets;
    }




    /********************************** GET THE LOWEST POWER OF 2 BIGGER THAN nx *****************************/
    // this algorithms is based on the low level rappresentation of a numerical integral type in modern CPUs
    // and archieves a O(1) time-complexity computation of the lowest power of 2 bigger than a given number

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