

#include <pstade/minimal_test.hpp>
#include <boost/assign/list_of.hpp>
#include <map>
#include <pstade/copy_construct.hpp>

class A {
public:
    typedef std::map<int, int> map_type;
 
    template< class InitList >
    explicit A(InitList const& l)
        : m_map(static_cast<map_type const&>(l))
    { }

    map_type m_map;
};


void pstade_minimal_test()
{
    A a(boost::assign::map_list_of(1,1)(2,2));
    BOOST_CHECK(a.m_map[1] == 1);
    BOOST_CHECK(a.m_map[2] == 2);
}
