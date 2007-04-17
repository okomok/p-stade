
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <cassert>

using std::string;

class regex_callback
{
    int m_sum;
public:
    regex_callback() : m_sum(0) {}

    template <typename T> void operator()(const T& what)
    { m_sum += boost::lexical_cast<int>(what[1].str().c_str()); }

    int sum() const { return m_sum; } 
};
 int main()
{
    boost::regex reg("(\\d+),?");
    string s = "1,1,2,3,5,8,13,21";

    boost::sregex_iterator it(s.begin(), s.end(), reg);
    // Is end initialized to anything here? 
    boost::sregex_iterator end;

    regex_callback c;

    // How is end valid here?
    int sum = for_each(it, end, c).sum();
    assert(sum == 54);

    return 0;
}