//
// Created by roey on 11/2/18.
//

#ifndef EX1AP_INFINT_H
#define EX1AP_INFINT_H


#include <string>


class InfInt {
    std::string num;
public:
    InfInt(std::string str);

    InfInt(const char *array);

    InfInt(int number);

    InfInt(long number);

    InfInt();

    char GetBit(unsigned long c) const;

    InfInt operator+(const InfInt &number2) const;

    InfInt operator-(const InfInt &number2) const;

    InfInt operator*(const InfInt &number2) const;

    InfInt operator/(const InfInt &ob) const;

    InfInt operator%(const InfInt &ob) const;

    InfInt operator+=(const InfInt &number2);

    InfInt operator*=(const InfInt &number2);

    InfInt operator-=(const InfInt &number2);

    InfInt &operator=(const InfInt &number2);

    bool operator!=(const InfInt &number2) const ;

    bool operator==(const InfInt &number2) const;

    InfInt operator~() const;

    InfInt operator|(const InfInt &number2) const;

    InfInt operator&(const InfInt &number2) const;

    InfInt operator&=(const InfInt &number2);

    InfInt operator^(const InfInt &number2) const;

    bool operator>(const InfInt &number2) const;

    bool operator<(const InfInt &number2) const;

    bool operator<=(const InfInt &number2) const;

    bool operator>=(const InfInt &number2) const;

    InfInt operator<<=(int x);

    InfInt operator<<(int x) const;

    InfInt operator>>(int x) const;

    InfInt operator>>=(int x);

    InfInt operator++();

    InfInt operator++(int);

    InfInt operator--();

    InfInt operator--(int);

    explicit operator int() const;

    InfInt DivAndMod(const InfInt &ob, bool x) const;

    void SetBinary(std::string str);

    InfInt GetAbs() const;

    std::string GetNum() const;

    bool isNeg() const;

    bool isZero() const;

    void SetBit(long bitNum, char bitValue);


    unsigned long NumOfBits();

    std::string Calc() const;

    friend std::ostream &operator<<(std::ostream &stream, const InfInt &A);


};


#endif //EX1AP_INFINT_H
