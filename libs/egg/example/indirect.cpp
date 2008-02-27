

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/indirect.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/noncopyable.hpp>
#include <functional> // plus
#include <algorithm> // for_each


#include "./egg_example.hpp"


//[code_example_indirect
typedef
    result_of_pipable< /*< Make __EGG_PIPABLE__ be __CONCEPT_PIPABLE_FUNCTION_OBJECT__.>*/
        result_of_indirect<T_pipable const *>::type
    >::type
T_pipi;

T_pipi const pipi /*< `&pipable` is an /address constant expression/, so that `pipi` can be __STATICALLY_INITIALIZED__. >*/
  = BOOST_EGG_PIPABLE_L
        BOOST_EGG_INDIRECT(&pipable) /*< A macro invocation must be sandwiched using `_L` and `_R`. >*/
    BOOST_EGG_PIPABLE_R;

struct counter :
    private boost::noncopyable
{
    typedef void result_type;

    template<class T>
    void operator()(T const &)
    {
        m_count += 1;
    }

    int m_count;
    counter() : m_count(0) {}
};

void egg_example()
{
    std::plus<int> plus;
    BOOST_CHECK( (1|pipable(plus)(3)) == 1+3 );
    BOOST_CHECK( (1|(plus|pipi)(3)) == 1+3 );

    counter c;
    int a[] = {1,2,3};
    std::for_each(a, a+3, indirect(&c)); /*< `indirect(&c)` is copyable, whereas `c` is not. >*/
    BOOST_CHECK(c.m_count == 3);
}
//]
