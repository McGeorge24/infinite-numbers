#include "Integer.h"

void Integer::InitFromString(const char *buffer)
{
    int i = 0;
    int length = strlen(buffer);
    // preverim predznak
    if (buffer[0] == '-')
    {
        sign = -1;
        length--;
        buffer += 1; // premakne pointer do začetka za 1
    }
    else
        sign = 1;

    integer.reserve(length);

    // integer[0] so enice, integer[1] desetice ...
    for (i = 0; i < length; i++)
        integer.push_back(buffer[strlen(buffer) - 1 - i] - 48);
}

Integer Integer::DelnoSestej(const Integer &ref, char predznak)
{
    Integer answer(""); // initialize the return value
    Integer first = *this, second = ref;
    int razlika_dolzine;
    std::vector<char>::const_iterator itr, end;

    razlika_dolzine = first.size() - second.size();
    // da ne pride do memory access violation
    first.push_back(0);
    second.push_back(0);
    if (razlika_dolzine < 0)
    {
        razlika_dolzine *= -1;
        for (int i = 0; i < razlika_dolzine; i++)
            first.push_back(0);
    }
    else
        for (int i = 0; i < razlika_dolzine; i++)
            second.push_back(0);

    int length = first.size();
    if (first.to_int() < second.to_int())
    {
        Integer temp = first;
        first = second;
        second = temp;
    }
    answer.integer.reserve(length);

    // sledi enostavno pisno seštevanje
    char carry = 0;
    for (int i = 0; i < length; i++)
    {
        answer.push_back(first.integer[i] + predznak * second.integer[i] + predznak * carry);
        carry = 0;
        if ((answer.back() < 0) || (answer.back() > 9))
        {
            carry = 1;
            answer.integer.back() -= predznak * 10; // .back() returns a read/write reference to the last element (sm uprasu chatgpt)
        }
    }

    answer.trim();
    return answer;
}

// --------------------- inicializacija --------------------- //
// constructorji
// brez argumentov
Integer::Integer()
{
    integer.push_back(0);
    sign = 1;
}

// iz stringa
Integer::Integer(const char *stevilo)
{
    InitFromString(stevilo);
}

// iz integerja
Integer::Integer(const long long int stevilo)
{
    char buffer[20]; // max velikost int-a je okoli 10^18
    sprintf(buffer, "%lld", stevilo);
    InitFromString(buffer);
}

// copy constructor (tega zares nerabm)
Integer::Integer(const Integer &ref)
{
    integer = ref.integer;
    sign = ref.sign;
}

//--------------------------------------------------------------------------------------------
// wrapperji za std::vector funkcije
int Integer::size() const
{
    return integer.size();
}

void Integer::push_back(int stevka)
{
    integer.push_back(stevka);
}

char Integer::back()
{
    return integer.back();
}

//--------------------------------------------------------------------------------------------
// operatorji

Integer Integer::operator++(int)
{
    // tuki mi je mogu pomagat AI, ne razumem kako deluje ta operator
    Integer temp = *this; // Save the current value
    Integer int1("1");
    *this = *this + int1; // Increment the current object
    return temp;          // Return the original value
}

// seštevanje
Integer Integer::operator+(const Integer &other)
{
    Integer temp;
    if ((this->sign == other.sign)) // če sta si predznaka enaka
    {
        temp = DelnoSestej(other, 1);
        temp.sign = this->sign;
        return temp;
    }
    else
    {
        temp = DelnoSestej(other, -1);

        temp.sign = this->sign; // če je prvi negativen: -a+b = -(b-a)
        return temp;
    }
    return Integer(112); // errorcode
}

Integer Integer::operator-(const Integer &other)
{
    Integer temp = other;
    temp.sign *= -1;
    return *this + temp;
}

Integer Integer::operator*(Integer const &other)
{
    int i, j, carry, zmnozek;
    Integer answer;
    answer.integer.reserve(this->size() + other.size() + 1);
    Integer pristevek;
    pristevek.integer.reserve(other.size() + 1);

    for (i = 0; i < this->size(); i++) // desna stevilka pri pisnem mnozenju
    {
        pristevek.integer.clear();
        for (j = 0; j < i; j++)
        {
            pristevek.push_back(0);
        }

        carry = 0;
        for (j = 0; j < other.size(); j++) // leva stevilka pri pisnem mnozenju
        {
            zmnozek = this->integer[i] * other.integer[j] + carry;
            if (zmnozek > 9)
            {
                carry = zmnozek / 10;
                zmnozek = zmnozek % 10;
            }
            else
                carry = 0;
            pristevek.push_back(zmnozek);
        }

        if (carry > 0)
            pristevek.push_back(carry);
        answer = answer + pristevek;
    }

    answer.sign = this->sign * other.sign;
    return answer;
}

//--------------------------------------------------------------------------------------
// other
std::string Integer::to_str()
{
    std::string odgovor;
    if (sign == -1)
        odgovor.append("-1");
    for (int i = 0; i < integer.size(); i++)
    {
        odgovor.append("0");
        odgovor.back()=*(integer.end() - i - 1) + 48;
        if (((integer.size() - i + 2) % 3 == 0) && (i != integer.size() - 1)) {
            odgovor.append("'");
        }
    }
    return odgovor;
}

long long Integer::abs()
{
    int odgovor = 0;
    int faktor = 1;
    for (int i = 0; i < integer.size(); i++)
    {
        odgovor += integer[i] * faktor;
        faktor *= 10;
    }
    return odgovor;
}

long long Integer::to_int() {
    return (this->abs()) * (this->sign);
}

void Integer::trim()
{
    for (int i = integer.size() - 1; i >= 0; i--)
    {
        if (integer[i] == 0)
            integer.pop_back();
        else
            break;
    }
}