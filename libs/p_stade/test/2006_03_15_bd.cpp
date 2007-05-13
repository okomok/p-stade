#include <boost/test/minimal.hpp>


#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <boost/lambda/core.hpp>

std::string f()
{
        return "";
}

int test_main(int, char*[])
{
        std::vector<std::string> v;
        boost::split(v, boost::lambda::make_const(f()), boost::is_any_of(","));
        return 0;
}
