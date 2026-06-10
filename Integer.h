#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>

class Integer
{
private:
    std::vector<char> integer;
    char sign;
    void InitFromString(const char *stevilo); // funkcija, ki se uporabi v 2 constructorjih

    Integer DelnoSestej(const Integer &ref, char predznak);                          // assumes both numbers are positive; 
    //predznak -1 for subraction, 1 for adition
public:
    Integer();                      // default constructor
    Integer(const char *stevilo);   // construct with char array
    Integer(long long int stevilo); // construct with integer
    Integer(const Integer &ref);    // copy constructor

    // std::vector function wrapers
    int size() const;
    void push_back(int stevka);
    char back();

    // operators
    Integer operator++(int);
    Integer operator+(const Integer &other);
    Integer operator-(const Integer &other);
    Integer operator*(Integer const &other);

    void print();
};