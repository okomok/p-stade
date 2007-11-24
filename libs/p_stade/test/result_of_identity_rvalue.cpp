
#include <boost/utility/result_of.hpp>
using boost::result_of;

int const& make_lvalue(int const& v) { return v; }
int make_rvalue(int v) { return v; }

typedef int const& (*T_make_lvalue)(int const&);
typedef int (*T_make_rvalue)(int);

int main()
{
    result_of<
        T_make_rvalue(
            result_of<
                T_make_lvalue(
                    result_of<
                        T_make_lvalue(int)
                    >::type
                )
            >::type
        )
    >::type v = make_rvalue(make_lvalue(make_lvalue(999)));
}
