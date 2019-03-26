//
// Created by roey on 11/2/18.
//

#include <iostream>
#include <climits>
#include <sstream>

#include "InfInt.h"
#include "SupportFunc.h"


#define ASCCI_VALUE 48

//constructor (with string of number)
InfInt::InfInt(std::string str) {

    //for a negative number
    if (str.at(0) == '-') {
        //remove the "-"
        str = str.substr(1, str.length());
        //convert the decimal reviced number to binary.
        str = FromCharsToBinary(ConvertStringToBinary(str));
        //make is negative (2`s complement)
        str = DoNeg(str);

    } else {
        if (str.at(0) == '0') {
            str = (char) 0;
        } else {
            str = FromCharsToBinary(ConvertStringToBinary(str));
        }
    }

    this->num = str;
}

InfInt::InfInt(const char *array) {
    std::string str = array;
    InfInt A(str);
    this->num = A.GetNum();

}

InfInt::InfInt(int number) {
    std::ostringstream stream;
    stream << number;
    std::string str = stream.str();

    InfInt A(str);
    this->num = A.GetNum();
}

InfInt::InfInt(long number) {
    std::ostringstream stream;
    stream << number;
    std::string str = stream.str();

    InfInt A(str);
    this->num = A.GetNum();
}

//default constructor
InfInt::InfInt() {
    char c = 0;
    this->num = c;
}

//get the string of the number
std::string InfInt::GetNum() const {
    return this->num;
}

//set the number (in binary)
void InfInt::SetBinary(std::string str) {
    this->num = str;
}

//check if the number is negative
bool InfInt::isNeg() const {
    char mask = -128; //1000 0000
    if (this->GetNum().length() == 0) {
        return false;
    }
    //check if the MSB is on or off

    if ((this->num.at(0) & mask) != 0) {
        return true;
    }
    return false;
}

char InfInt::GetBit(unsigned long in) const {
    char mask = 1;
    unsigned long byte;
    if (in == 0) {
        byte = 0;
    } else {
        byte = in / CHAR_BIT;
    }
    if (byte > (this->GetNum().length() - 1)) {
        std::cout << "Error" << std::endl;
        return -1;
    }
    unsigned long bit = in % CHAR_BIT;
    char c;
    if (this->GetNum().length() == 0) {
        c = 0;
    } else {
        c = this->GetNum().at(this->GetNum().length() - byte - 1);
    }

    return (c >> bit) & mask;
}


InfInt InfInt::operator+(const InfInt &number2) const {


    std::string str1;
    std::string str2;
    //make the strings in the same size (add zero`s)
    MakeStringSameSize(str1, str2, *this, number2);


    std::string result;
    char carry = 0;
    //add byte by byte
    for (long i = str1.length() - 1; i >= 0; i--) {

        unsigned char first = str1.at(i);
        unsigned char sec = str2.at(i);
        unsigned char bit1;
        unsigned char bit2;
        int tempSum = 0;
        char sum = 0;
        unsigned char mask = 1; //0000 0001

        //add bit by bit
        for (int j = 0; j < CHAR_BIT; j++) {
            if (j != 0) {
                //let the 1 of the mask be in the correct postion
                mask <<= 1;
            }
            bit1 = first & mask;
            bit2 = sec & mask;
            //add the 2 bits together.
            tempSum = bit1 + bit2;
            //move them to the correct location of th bit
            tempSum >>= j;

            //check the summary with the carry
            if ((tempSum == 1 && carry == 0) || (tempSum == 0 && carry == 1)) {
                sum = sum | mask;
                carry = 0;
                continue;
            } else if ((tempSum == 2 && carry == 0) || (tempSum == 1 && carry == 1)) {
                carry = 1;
                continue;
            } else if ((tempSum == 2 && carry == 1)) {
                sum = sum | mask;
                carry = 1;
            }

        }
        result = sum + result;
    }


    //check if we need to add 1 (or not, in case we want to use it for adding negative number with positive)
    if (carry == 1) {
        char c = ChecksForCarry(*this, number2);
        if (c != 0) {
            result = c + result;
        }
    }

    InfInt A;
    A.SetBinary(result);
    return A;
}

InfInt InfInt::operator-(const InfInt &number2) const {
    //create number 2 with minus, and add them using the + operator
    InfInt num2;
    num2.SetBinary(DoNeg(number2.GetNum()));
    return (*this + num2);

}

InfInt InfInt::operator*(const InfInt &number2) const {
    std::string str1;
    std::string str2;

    InfInt temp1;
    InfInt temp2;

    //make the strings in the same size (add zero`s)
    MakeStringSameSize(str1, str2, this->GetAbs(), number2.GetAbs());

    std::string result;

    char bit2;


    for (unsigned long i = 0; i < str2.length() * CHAR_BIT; i++) {
        bit2 = GetBitStr(i, str2);
        result.clear();
        for (unsigned long k = 0; k < i; k++) {
            result = '0' + result;
        }
        for (unsigned long j = 0; j < str1.length() * CHAR_BIT; j++) {
            result = (char) ((bit2 * GetBitStr(j, str1)) + ASCCI_VALUE) + result;
        }

        temp2.SetBinary(FromCharsToBinary(result));

        if (temp2.isZero()) {
            continue;
        }

        temp1 += temp2;
    }
    //check if one of the number is negative, and remove leading zeros
    if (this->isNeg() ^ number2.isNeg()) {
        temp1.SetBinary(ClearLeadingZero(temp1.GetNum()));
        temp1.SetBinary(DoNeg(temp1.GetNum()));
    }

    return temp1;
}

InfInt InfInt::operator*=(const InfInt &number2) {
    InfInt C = *this * number2;
    this->SetBinary(C.GetNum());
    return *this;
}

InfInt InfInt::operator+=(const InfInt &number2) {
    InfInt C = *this + number2;
    this->SetBinary(C.GetNum());
    return *this;
}

InfInt InfInt::operator-=(const InfInt &number2) {
    InfInt C = *this - number2;

    this->SetBinary(C.GetNum());
    return *this;
}

InfInt InfInt::operator~() const {
    InfInt A;
    A.SetBinary(NotString(this->GetNum()));
    return A;
}

InfInt InfInt::operator^(const InfInt &number2) const {
    std::string str1;
    std::string str2;
    //make the 2 strings in the same size
    MakeStringSameSize(str1, str2, *this, number2);
    std::string result;
    char c;
    //do xor byte by byte.
    for (unsigned long i = 0; i < str1.length(); i++) {
        c = str1.at(i) ^ str2.at(i);
        result.push_back(c);
    }
    InfInt A;
    A.SetBinary(result);
    return A;
}

bool InfInt::operator==(const InfInt &number2) const {
    if ((*this - number2).isZero()) {
        return true;
    }
    return false;
}

bool InfInt::operator!=(const InfInt &number2) const {
    return !(*this == number2);
}

bool InfInt::operator>(const InfInt &number2) const {
    InfInt A = *this - number2;


    if (A.isNeg() || A.isZero()) {
        return false;
    }
    return true;
}

bool InfInt::operator<(const InfInt &number2) const {

    InfInt A = *this - number2;

    if (!A.isNeg() || A.isZero()) {
        return false;
    }
    return true;
}

bool InfInt::isZero() const {
    //check if the all bit/byte are zero.
    bool x = true;
    for (long i = 0; i < this->num.length(); i++) {
        if (this->num.at(i) != 0) {
            x = false;
        }
    }
    return x;
}

bool InfInt::operator<=(const InfInt &number2) const {
    return ((*this < number2) | (*this == number2));

}

bool InfInt::operator>=(const InfInt &number2) const {
    return ((*this > number2) | (*this == number2));

}

InfInt InfInt::operator<<=(int x) {
    InfInt A = *this << x;
    this->SetBinary(A.GetNum());
    return *this;
}

InfInt InfInt::operator<<(int x) const {
    char temp1 = 0;
    char temp2 = 0;
    char mask = -128; //1000 0000
    char mask2 = 1;   //0000 0001
    bool numberNeg = this->isNeg();
    InfInt A;
    A.SetBinary(this->num);

    //every step of the loop is one shift
    for (unsigned int j = 0; j < x; j++) {
        //moving on every byte
        for (long i = A.num.length() - 1; i >= 0; i--) {
            temp1 = A.num.at(i) & mask;
            temp1 >>= (CHAR_BIT - 1);
            A.num.at(i) <<= 1;
            //copy the left bit of the previous byte
            A.num.at(i) = A.num.at(i) | temp2;
            temp2 = temp1 & mask2;
        }
        //check if need to add one more byte
        if (temp2 != 0) {
            if (numberNeg) {
                A.num = (char) -1 + A.GetNum();

            } else {
                A.num = (char) 1 + A.GetNum();
            }
            temp2 = 0;
        }
    }
    //check if the sign of the number is change
    if (!A.isNeg() && numberNeg) {
        char negMask = -1; // 1111 1111
        int point = -1;
        //find the leftest bit of 1.
        for (int i = CHAR_BIT - 1; i >= 0; i--) {
            if (A.GetNum().at(0) >> i != 0) {
                point = i;
                break;
            }
        }
        if (point >= 0) {
            A.num.at(0) = mask >> (point - 1) | A.GetNum().at(0);
        } else {
            A.num = negMask + A.GetNum();
        }
    }

    if (A.isNeg() && !numberNeg) {
        A.SetBinary((char) 0 + A.GetNum());
    }
    return A;
}


InfInt InfInt::operator>>(int x) const {
    char mask = 1; //0000 0001
    unsigned char mask2 = 127; //0111 1111

    InfInt A;
    A.SetBinary(this->num);
    //every step of the loop is one shift
    for (unsigned j = 0; j < x; j++) {
        char temp1 = 0;
        char temp2 = 0;
        for (unsigned long i = 0; i < A.GetNum().length(); i++) {
            //save the rightest bit
            temp1 = A.GetNum().at(i) & mask;
            //move the byte.
            //mask 2 used to ensure that the leftest bit will be zero.temp2 add the bit from the previous byte.
            A.num.at(i) = ((A.GetNum().at(i) >> 1) & mask2) | temp2;
            temp2 = temp1 << (CHAR_BIT - 1);
        }
    }

    return A;
}

InfInt InfInt::operator>>=(int x) {
    InfInt A = *this >> x;
    this->SetBinary(A.GetNum());
    return *this;
}

InfInt InfInt::GetAbs() const {
    InfInt A;
    if (this->isNeg()) {
        std::string str = DoNeg(this->GetNum());
        A.SetBinary(str);
    } else {
        A.SetBinary(this->GetNum());
    }
    return A;
}

InfInt InfInt::operator&(const InfInt &number2) const {
    std::string str1;
    std::string str2;
    std::string result;
    char c;
    //make the strings in the same size (add zero`s)
    MakeStringSameSize(str1, str2, *this, number2);
    for (unsigned long i = 0; i < str1.length(); i++) {
        c = str1.at(i) & str2.at(i);
        result = result + c;
    }
    InfInt A;
    A.SetBinary(result);
    return A;
}

InfInt InfInt::operator&=(const InfInt &number2) {
    InfInt A = *this & number2;
    this->SetBinary(A.GetNum());
    return *this;
}

InfInt InfInt::operator|(const InfInt &number2) const {
    std::string str1;
    std::string str2;
    std::string result;
    char c;
    //make the strings in the same size (add zero`s)
    MakeStringSameSize(str1, str2, *this, number2);

    InfInt A;
    A.SetBinary(str1);
    for (unsigned long i = 0; i < A.GetNum().length(); i++) {
        A.num.at(i) = str1.at(i) | str2.at(i);
    }
    return A;
}

InfInt InfInt::operator/(const InfInt &ob) const {
    return this->DivAndMod(ob, true);
}

InfInt InfInt::operator%(const InfInt &ob) const {
    return this->DivAndMod(ob, false);
}

int FirstOnBit(char byte) {
    char byteCheck = -128;
    for (int i = CHAR_BIT - 1; i >= 0; i--) {
        char result = byteCheck & byte;
        if (result != 0) {
            return i;
        }
        byteCheck = byteCheck >> 1;
    }
    return -1;
}

unsigned long InfInt::NumOfBits() {
    if (this->GetNum().length() == 0) {
        return 0;
    }
    long size = FirstOnBit(this->GetNum().at(0)) + (this->GetNum().length() - 1) * CHAR_BIT;
    return size;
}


void InfInt::SetBit(long bitNum, char bitValue) {
    long byteNumber = bitNum / CHAR_BIT;
    bitNum %= CHAR_BIT;


    bitValue <<= bitNum;
    long n = this->GetNum().length();
    long x = -(this->GetNum().length() - 1 - byteNumber);
    if (n - byteNumber < 1) {
        char c = 0;
        for (long j = 0; j < x; j++) {
            this->SetBinary(c + this->GetNum());
        }
    }
    long m = this->GetNum().length();
    char currentVal = this->GetNum().at(m - 1 - byteNumber);
    char mask1 = 1;
    //in a case of we want to change the last bit
    if (bitNum == 0) {
        mask1 = 0;
    }
    char temp = 1;
    for (int i = 1; i < bitNum; i++) {
        mask1 = (mask1 | (temp <<= 1));
    }
    char mask2 = -128;
    mask2 >>= CHAR_BIT - 1 - bitNum - 1;
    //in a case of we want to change tha first bit
    if (bitNum == CHAR_BIT - 1) {
        mask2 = 0;
    }

    currentVal = currentVal & (mask1 | mask2);
    currentVal = currentVal | bitValue;
    this->num.at(this->GetNum().length() - 1 - byteNumber) = currentVal;

}

InfInt InfInt::operator++() {
    InfInt A("1");
    *this += A;
    return *this;
}

InfInt InfInt::operator++(int) {
    InfInt temp;
    temp.SetBinary(this->GetNum());
    ++(*this);
    return temp;
}

InfInt InfInt::operator--() {
    InfInt A("1");
    *this -= A;
    return *this;
}

InfInt InfInt::operator--(int) {
    InfInt temp;
    temp.SetBinary(this->GetNum());
    --(*this);
    return temp;
}

InfInt::operator int() const {
    int num = 0;
    std::string result;
    //take the int part from the InfInt
    if (this->GetNum().length() - 1 > sizeof(int)) {
        for (long i = this->GetNum().length() - 1; i <= sizeof(int); i++) {
            result = this->GetNum().at(i) + result;
        }
    } else {
        result = this->GetNum();
    }
    InfInt A;
    A.SetBinary(result);
    result = A.Calc();
    //stream into int
    std::stringstream str(result);
    str >> num;

    return num;

}

InfInt &InfInt::operator=(const InfInt &number2) {
    this->SetBinary(number2.GetNum());
    return *this;
}


//this function divided the number and also have the modulo function.
InfInt InfInt::DivAndMod(const InfInt &ob, bool x) const {
    bool neg = false;
    if (this->isNeg() ^ ob.isNeg()) {
        neg = true;
    }
    InfInt A = this->GetAbs();
    InfInt B = ob.GetAbs();

    InfInt one("1");
    if (ob.isZero()) {
        throw "Cannot divide by zero";
    }
    InfInt q, r;
    std::string reminder = "";
    int n = A.NumOfBits();    // the length of the number in bits
    for (int i = n; i >= 0; --i) {
        r = r << 1;
        if (A.GetBit(i) == 1) {
            r = r + one;
        }
        if (r >= B) {
            r = r - B;
            q.SetBit(i, 1);
        }
    }

    if (neg) {
        q.SetBinary(DoNeg(q.GetNum()));
    } else {
        q.SetBinary((char) 0 + q.GetNum());
    }
    if (x) {
        return q;
    } else {
        return r;
    }

}

std::string InfInt::Calc() const {
    std::string calc = "";
    InfInt Ten("10");
    InfInt Zero(0);
    InfInt A;
    std::string s = this->GetNum();
    if (this->isZero()) {
        calc = "0";
        return calc;
    }
    if (this->isNeg()) {
        s = DoNeg(s);
    }

    A.SetBinary(s);

    while (A > Zero) {
        char c = (A % Ten).GetNum().at(0) + ASCCI_VALUE;
        calc = c + calc;
        A = A / Ten;
    }
    if (this->isNeg()) {
        calc = "-" + calc;
    }
    return calc;


}

std::ostream &operator<<(std::ostream &stream, const InfInt &A) {

    stream << A.Calc();

    return stream;

}












