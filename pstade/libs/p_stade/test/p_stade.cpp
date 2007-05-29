
#include <iostream>
#include <sstream>
#include <pstade/oven/popped.hpp>
#include <pstade/oven/stream_lines.hpp> // thanks to hamigaki.
#include <boost/foreach.hpp>

int main()
{
    using namespace pstade::oven;

    std::stringstream sin;
    sin << "ABC\nDE\nFGHI\nZZZ";
    BOOST_FOREACH (std::string const& line, stream_lines(sin)|popped) {
        std::cout << line << std::endl;
    }
}
