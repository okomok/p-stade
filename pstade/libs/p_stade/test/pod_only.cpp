

#include <string>


// hmm, "..." takes only POD.
void unused(...) { };


int main()
{
    std::string s("abc");
    std::string const cs("abc");
    int i = 12;
    int volatile vi = 10;
    int const ci = 3;
    int const volatile cvi = 3;
    unused(i, vi, ci, cvi, s, std::string("abc"), "abc", unused, &unused, 3);
}
