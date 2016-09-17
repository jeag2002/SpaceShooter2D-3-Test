//clase de utilidades, gestion de strings


#pragma once
#ifndef CORESTRING_HPP
#define CORESTRING_HPP

#include "Stdafx.h"

namespace CoreString{

    inline std::string copySafetyString(std::string input){
        char* input_str_to_char_cpy = new char[input.length()+1];
        for(unsigned int i=0; i<(input.length()+1); i++){input_str_to_char_cpy[i] = input.c_str()[i];}
        std::string cpyInput(input_str_to_char_cpy);
        return cpyInput;
    }
};


#endif // CORESTRING_H_INCLUDED
