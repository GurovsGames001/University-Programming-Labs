#include "overloadedInputOutput.h"
#include <iomanip>

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    using sep = DelimiterIO;
    using label = LabelIO;
    using ull = LongLongIO;
    using cmp = ComplexIO;
    using str = StringIO;

    DataStruct input;

    in >> sep{ '(' };

    label key;
    for (int i = 0; i < 3; i++)
    {
        in >> key;

        if (key.exp == "key1")
        {
            in >> ull{ input.key1 };
        }
        else if (key.exp == "key2")
        {
            in >> cmp{ input.key2 };
        }
        else if (key.exp == "key3")
        {
            in >> str{ input.key3 };
        }
        else
        {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> sep{ ':' } >> sep{ ')' };

    if (in)
    {
        dest = input;
    }

    return in;
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    char c = '0';
    in >> c;

    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, LongLongIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return in >> DelimiterIO{ '0' } >> std::oct >> dest.ref;
}

std::istream& operator>>(std::istream& in, ComplexIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } 
                >> dest.ref._Val[0] >> dest.ref._Val[1] >> DelimiterIO{ ')' };
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return in >> DelimiterIO{ ':' } >> dest.exp;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    StreamGuard guard(out);

    out << "(";
    out << ":key1 0" << std::oct << src.key1;
    out << ":key2 #c(" << std::fixed << std::setprecision(1) << src.key2._Val[0] << ' ' << src.key2._Val[1] << ')';
    out << ":key3 \"" << src.key3;
    out << "\":)";

    return out;
}