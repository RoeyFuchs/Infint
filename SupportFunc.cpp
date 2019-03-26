//
// Created by roey on 11/2/18.
//

#include <iostream>
#include "SupportFunc.h"
#include <math.h>
#include <climits>


int FromBinaryToInt(std::string str) {
    int sum = 0;
    for (unsigned long i = str.length(); i > 0; i--) {
        if (str.at(i - 1) == '1') {
            //check MSB
            if (i == 1) {
                sum -= (int) pow(2, str.length() - i);
            } else {
                sum += (int) pow(2, str.length() - i);
            }
        }
    }
    return sum;
}

std::string FromCharsToBinary(std::string str) {

    //adding 1 or zero to fit the number into char array
    while (str.length() % 8 != 0 || str.length() < 8) {
        str = str.at(0) + str;
    }
    std::string subString;
    std::string bigNum;
    while (str.length() != 0) {
        subString = str.substr(0, 8);
        char c = (char) FromBinaryToInt(subString);
        bigNum.push_back(c);
        str = str.substr(8, str.length());
    }

    return bigNum;
}


std::string DivideInTwo(std::string number) {
    int divisor = 2;
    // As result can be very large store it in string
    std::string ans;
    //make sure thata the devisor is bigger than the number itself
    if (number.length() == 1 && number.at(number.size() - 1) < '2') {
        return number;
    }
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}

std::string ConvertStringToBinary(std::string num) {
    std::string numberCopy = num;
    std::string binary;
    //Division in two. stop when the number is 0 or 1
    while (numberCopy.length() > 1 || (numberCopy.length() > 0 && (int) numberCopy.at(numberCopy.length() - 1) > '0')) {
        //check if odd or even
        if ((int) numberCopy.at(numberCopy.length() - 1) % 2 == 1) {
            //make the last digit even
            char lastDigit = (char) ((int) numberCopy.at(numberCopy.length() - 1) - 1);
            //substring without the last digit, and put the correct in the new string
            numberCopy = numberCopy.substr(0, numberCopy.length() - 1);
            numberCopy.push_back(lastDigit);
            binary = binary + "1";
        } else {
            binary = binary + "0";
        }
        numberCopy = DivideInTwo(numberCopy);
    }

    if (binary.at(binary.length() - 1) == '1') {
        binary.push_back('0');
    }

    binary = ReverseString(binary);

    return binary;

}

std::string ReverseString(std::string str) {
    std::string revStr;
    for (long i = str.length() - 1; i >= 0; i--) {
        revStr += str.at(i);
    }
    return revStr;
}

//2`s complametion
std::string DoNeg(std::string str) {
    str = NotString(str);
    InfInt A;
    InfInt B("1");
    A.SetBinary(str);
    InfInt C = A + B;
    return C.GetNum();
}

std::string NotString(std::string str) {
    std::string newString;
    char a;
    char mask = -1;
    for (long i = 0; i < str.length(); i++) {
        a = str.at(i) ^ mask;
        newString.push_back(a);
    }

    return newString;
}


char GetBitStr(unsigned long in, std::string str) {
    if (str.empty()) {
        return 0;
    }
    char mask = 1;
    unsigned long byte;
    if (in == 0) {
        byte = 0;
    } else {
        byte = in / CHAR_BIT;
    }
    if (byte > str.length() - 1) {
        std::cout << "Error" << std::endl;
        return -1;
    }
    unsigned long bit = in % CHAR_BIT;
    char c;
    if (str.length() == 0) {
        c = str.at(0);
    } else {

        c = str.at(str.length() - byte - 1);
    }

    c = (c >> bit) & mask;
    return c;
}

std::string SetStringSize(std::string str, long size) {
    char c = str.at(0) >> CHAR_BIT;
    while (str.length() < size) {
        str = c + str;
    }
    return str;
}

void MakeStringSameSize(std::string &str1, std::string &str2, const InfInt &A, const InfInt &B) {
    if (A.GetNum().length() > B.GetNum().length()) {
        str1 = A.GetNum();
        str2 = SetStringSize(B.GetNum(), A.GetNum().length());
    } else if (A.GetNum().length() < B.GetNum().length()) {
        str1 = SetStringSize(A.GetNum(), B.GetNum().length());
        str2 = B.GetNum();
    } else {
        str1 = A.GetNum();
        str2 = B.GetNum();
    }
}

/*addition support function
check if we need to add 1 (or not, in case we want to use it for adding negative number with positive) */
char ChecksForCarry(const InfInt &A, const InfInt &B) {
    char c = 0;
    if (!A.isNeg() && !B.isNeg()) {
        c = 1;
    } else if (A.isNeg() && B.isNeg()) {
        c = -1;
        if (B.GetAbs().GetNum() > A.GetNum()) {
            c = -1;
        } else {
            c = 0;
        }
        if (ClearLeadingZero(B.GetAbs().GetNum()) == ClearLeadingZero(A.GetNum())) {
            return c = 0; //

        }
    } else if (A.isNeg() && !B.isNeg()) {
        if (ClearLeadingZero(A.GetAbs().GetNum()).length() != ClearLeadingZero(B.GetNum()).length()) {
            if (ClearLeadingZero(B.GetNum()).length() > ClearLeadingZero(A.GetAbs().GetNum()).length()) {
                return c = 0;
            } else {
                return c = -1;
            }
        }
        if (A.GetAbs().GetNum() > B.GetNum()) {
            c = -1;
        } else {
            c = 1;
        }
        if (ClearLeadingZero(A.GetAbs().GetNum()) == ClearLeadingZero(B.GetNum())) {
            return c = 0;
        }
    }

    return c;
}

std::string ClearLeadingZero(std::string str) {
    std::string newStr = str;
    char zero = 0;
    long byteToCut = 0;
    for (long i = 0; i < str.length(); i++) {
        if (str.at(i) == zero) {
            byteToCut++;
        }
    }
    newStr = newStr.substr(byteToCut, str.length());
    return newStr;
}


