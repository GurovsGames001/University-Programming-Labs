#include "overloadedInputOutput.h"
#include <string>

std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    int n = 0;
    in >> n;
    if (in)
    {
        Polygon inputPolygon;
        Point tempPoint;

        for (int i = 0; i < n; i++)
        {
            in >> tempPoint;
            inputPolygon.points.push_back(tempPoint);
        }

        char extraSymbol;
        if (in && !(in >> extraSymbol))
        {
            dest = inputPolygon;
            in.clear(std::ios::eofbit);
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
    }

	return in;
}

std::istream& operator>>(std::istream& in, Point& ob)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    using sep = DelimiterIO;

    in >> sep{ '(' } >> ob.x >> sep{ ';' } >> ob.y >> sep{ ')' };

	return in;
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    char c;
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, Command& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> dest.command;
    if (dest.command != "EXIT")
    {
        if ((dest.command != "MAXSEQ") && (dest.command != "ECHO"))
        {
            in >> dest.parameter;
        }
        else
        {
            in >> dest.polygon;
        }
    }

    return in;
}