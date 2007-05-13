#include <boost/test/minimal.hpp>


#include <boost/type_traits.hpp>
#include <iostream>


struct pstade_overload_detail_adl_marker
{ };

namespace pstade {

    typedef pstade_overload_detail_adl_marker overload;

} // namespace pstade


namespace pstade { namespace foo { namespace customize {


    // customization points
    template< class T >
    struct tag;

    template< class Tag >
    struct functions;


    namespace detail {


        template< class T >
        struct bare :
            boost::remove_cv<typename boost::remove_reference<T>::type>
        { };


        template< class T >
        struct tag_of :
            tag<typename detail::bare<T>::type>
        { };

        template< class T >
        struct functions_of
        {
            typedef functions<typename tag_of<T>::type> type;
        };


    } // namespace detail


    // layer3
    struct default_tag { };

    template< class T >
    struct tag
    {
        typedef default_tag type;
    };

    template< >
    struct functions<default_tag>
    {
        template< class T >
        void bar(T& x)
        {
            return pstade_foo_bar(x, pstade::overload());
        }
    };


} } } // namespace pstade::foo::customize



// layer1
template< class T >
void pstade_foo_bar(T& x)
{
    x.pstade_foo_bar();
}


// layer2
template< class T >
void pstade_foo_bar(T& x, pstade::overload)
{
    pstade_foo_bar(x);
}


namespace pstade { namespace foo {

    struct bar_function
    {
        template< class T >
        void operator()(T& x) const
        {
            typedef typename customize::detail::functions_of<T>::type functions_t;
            return functions_t().bar(x);
        }

        typedef void result_type;
    };

    template< class T >
    struct instance
    {
        static T& get()
        {
            static T x;
            return x;
        }
    };

    namespace {
        const bar_function& bar = instance<bar_function>::get();
    }

} } // namespace pstade::foo


namespace my {

    struct A
    {
        void pstade_foo_bar()
        {
            std::cout << "A" << std::endl;
        }
    };

}


namespace your {

    struct B { };

    void pstade_foo_bar(B&)
    {
        std::cout << "B" << std::endl;
    }

}


namespace adobe {

    struct C { };

    struct D
    {
        void barbar() { }
    };

    struct E
    {
        void barbar() { }
    };

}


void pstade_foo_bar(adobe::C&, pstade::overload)
{
    std::cout << "C" << std::endl;
}


#include <boost/mpl/identity.hpp>

namespace pstade { namespace foo { namespace customize {

    struct adobe_tag { };

    template< >
    struct tag<adobe::D> : boost::mpl::identity<adobe_tag>
    { };

    template< >
    struct tag<adobe::E> : boost::mpl::identity<adobe_tag>
    { };

    template< >
    struct functions<adobe_tag>
    {
        template< class DorE >
        void bar(DorE& de)
        {
            std::cout << "D or E" << std::endl;
            de.barbar();
        }
    };

} } } // namespace pstade::foo::customize


// 新しいFusionも出来てます・・・http://www.boost.org/more/formal_review_schedule.html
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/spirit/fusion/algorithm/for_each.hpp>

void test_2006_02_22()
{
    using namespace pstade;
    using namespace boost;

    fusion::tuple<my::A, your::B, adobe::C, adobe::D, adobe::E> foos;
    fusion::for_each(foos, foo::bar);
}


int test_main(int, char*[])
{
    test_2006_02_22();
    return 0;
}
