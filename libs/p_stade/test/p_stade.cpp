
#include <boost/optional/optional.hpp>
#include <cassert>


int main()
{
    {
        int const i = 10;
        boost::optional<int const &> o(i);
        assert(*o == 10);
        assert(&*o == &i);
    }
    {
        int const i = 10;
        boost::optional<int const &> o = i; // copy-initialization
        assert(*o == 10);
        assert(&*o == &i); // failed on gcc3.4 and 4.1.
    }
}

