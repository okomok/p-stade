#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_fwd.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/pipable.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/const.hpp>
#include <pstade/egg/call_little.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/egg/unref_by.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my_by_value
{
    typedef by_value type;
};

BOOST_MPL_ASSERT((detail::is_compatible_strategy<my_by_value, by_value>));


namespace pstade { namespace egg {

    template<class Little>
    struct function<Little, my_by_value>
    {
        typedef Little little_type;
        typedef function function_type;

        Little m_little;

        Little little() const
        {
            return m_little;
        }

    private:
        template<class I>
        struct result1 :
            Little::template apply<Little const, I>
        { };

        template<class I, class J>
        struct result2 :
            Little::template apply<Little const, I, J>
        { };

    public:
        template<class Signature>
        struct result;

        template<class _, class I>
        struct result<_(I)> :
            result1<typename unref_by_value<I>::type>
        { };

        template<class _, class I, class J>
        struct result<_(I, J)> :
            result2<typename unref_by_value<I>::type, typename unref_by_value<J>::type>
        { };

        typename result1<int>::type operator()(int i) const
        {
            return egg::call_little<typename result1<int>::type>(m_little, i);
        }

        typename result2<int, int>::type operator()(int i, int j) const
        {
            return egg::call_little<typename result2<int, int>::type>(m_little, i, j);
        }
    };

} }


struct base_mult3
{
    typedef int result_type;

    result_type operator()(int i, int j, int k) const
    {
        return i*j*k;
    }
};


struct base_plus2
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};


typedef result_of_pipable<base_mult3, my_by_value>::type T_mult3;
PSTADE_EGG_CONST((T_mult3), mult3) = {{}};
typedef result_of_ambi2<base_plus2, my_by_value>::type T_plus2;
PSTADE_EGG_CONST((T_plus2), plus2) = {{}};


void pstade_minimal_test()
{
    BOOST_CHECK( (3|mult3(4, 5)) == 3*4*5 );

    BOOST_CHECK( plus2(1, 2) == 3 );
    BOOST_CHECK( (1|plus2(2)) == 3 );
}
