#ifndef _DATA_STRUCT
#define _DATA_STRUCT
#include <string>
#include <complex>

struct DataStruct
{
	unsigned long long key1;
	std::complex<double> key2;
	std::string key3;
};

struct DataStructComparator 
{
    bool operator()(const DataStruct& ob1, const DataStruct& ob2) const 
    {
        bool isLess = false;

        if (ob1.key1 < ob2.key1)
        {
            isLess = true;
        }
        else if (ob1.key1 == ob2.key1)
        {
            if (abs(ob1.key2) < abs(ob2.key2))
            {
                isLess = true;
            }
            else if (abs(ob1.key2) == abs(ob2.key2))
            {
                if (ob1.key3 < ob2.key3)
                {
                    isLess = true;
                }
            }
        }

        return isLess;
    }
};

struct DelimiterIO
{
    char exp;
};

struct LongLongIO
{
    unsigned long long& ref;
};

struct ComplexIO
{
    std::complex<double>& ref;
};

struct StringIO
{
    std::string& ref;
};

struct LabelIO
{
    std::string exp;
};

#endif