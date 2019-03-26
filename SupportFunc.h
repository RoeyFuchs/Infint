//
// Created by roey on 11/2/18.
//

#ifndef EX1AP_SUPPORTFUNC_H
#define EX1AP_SUPPORTFUNC_H

#include "InfInt.h"


#include <string>


std::string FromCharsToBinary(std::string str);
int FromBinaryToInt(std::string str);
std::string SetStringSize(std::string str, long size);
std::string DivideInTwo(std::string num);
std::string ConvertStringToBinary(std::string num);
std::string ReverseString(std::string str);
std::string DoNeg(std::string str);
std::string NotString(std::string str);
char GetBitStr(unsigned long in, std::string str);
void MakeStringSameSize(std::string &str1, std::string &str2, const InfInt &A, const InfInt &B);
char ChecksForCarry(const InfInt &A, const InfInt &B);
std::string ClearLeadingZero(std::string);

#endif //EX1AP_SUPPORTFUNC_H
