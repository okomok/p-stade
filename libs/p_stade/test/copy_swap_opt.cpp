
#include <pstade/clone_ptr.hpp>
#include <string>

using pstade::clone_ptr;

int main()
{
    clone_ptr<std::string> p(new std::string());
    std::auto_ptr<std::string> p_(new std::string());
    p = p_;
}
