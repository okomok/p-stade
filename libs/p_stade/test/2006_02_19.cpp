#include <boost/test/minimal.hpp>


#include <atlbase.h> // CAutoPtr
#include <boost/foreach.hpp>
#include <boost/pointee.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
#include <functional> // equal_to
#include <string>
#include <pstade/oven.hpp>


namespace boost {


    template< class E >
    struct pointee< ATL::CAutoPtr<E> > :
        boost::mpl::identity<E>
    { };


} // namespace boost


void test_2006_02_19()
{
    using namespace pstade;
    using namespace oven;

    CAutoPtr<std::string> ptrs[] = {
        CAutoPtr<std::string>(new std::string("hello")),
        CAutoPtr<std::string>(new std::string("goodbye"))
    };

    int i = 0;
    BOOST_FOREACH (std::string& str, ptrs|indirected) {
        if (i == 0) BOOST_CHECK( str == "hello" ), str = "goodbye";
        if (i == 1) BOOST_CHECK( str == "goodbye" );
        ++i;
    }

    BOOST_CHECK( 
        boost::make_indirect_fun(std::equal_to<std::string>())
            (ptrs[0], ptrs[1])
    );
}


int test_main(int, char*[])
{
    test_2006_02_19();
    return 0;
}
