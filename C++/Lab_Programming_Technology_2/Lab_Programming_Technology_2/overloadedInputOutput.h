#include <iterator>
#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DataStruct& ob);
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, LongLongIO&& dest);
std::istream& operator>>(std::istream& in, ComplexIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO& dest);

std::ostream& operator<<(std::ostream& out, const DataStruct& src);

class StreamGuard 
{ 
public:
	StreamGuard(std::basic_ios<char>& s) :
		s_(s), 
		fill_(s.fill()),
		precision_(s.precision()),
		flags_(s.flags()) 
	{};
	~StreamGuard() 
	{
		s_.fill(fill_);
		s_.precision(precision_); 
		s_.flags(flags_); 
	}
private:
	std::basic_ios<char>& s_; 
	char fill_;
	std::streamsize precision_; 
	std::basic_ios<char>::fmtflags flags_; 
};