#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fusion/drop.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>

#if defined(PSTADE_EGG_HAS_FUSIONS)
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/equal_to.hpp>
#endif


template<int N, class From, class To>
void test_tuple()
{
    namespace egg = pstade::egg;
    using namespace egg;

    // lvalue
    BOOST_MPL_ASSERT((boost::is_same<To&, typename pstade::result_of<X_fusion_drop_c<N>(From&)>::type>));
    BOOST_MPL_ASSERT((boost::is_same<To const&, typename pstade::result_of<X_fusion_drop_c<N>(From const&)>::type>));
    // rvalue
    BOOST_MPL_ASSERT((boost::is_same<To const&, typename pstade::result_of<X_fusion_drop_c<N>(From)>::type>));
    BOOST_MPL_ASSERT((boost::is_same<To const&, typename pstade::result_of<X_fusion_drop_c<N>(From const)>::type>));
}


template<int N, class From>
void test_tuple0()
{
    namespace egg = pstade::egg;
    using namespace egg;

    // lvalue
    BOOST_MPL_ASSERT((boost::is_same<boost::tuples::null_type, typename pstade::result_of<X_fusion_drop_c<N>(From&)>::type>));
    BOOST_MPL_ASSERT((boost::is_same<boost::tuples::null_type, typename pstade::result_of<X_fusion_drop_c<N>(From const&)>::type>));
    // rvalue
    BOOST_MPL_ASSERT((boost::is_same<boost::tuples::null_type, typename pstade::result_of<X_fusion_drop_c<N>(From)>::type>));
    BOOST_MPL_ASSERT((boost::is_same<boost::tuples::null_type, typename pstade::result_of<X_fusion_drop_c<N>(From const)>::type>));
}


#if defined(PSTADE_EGG_HAS_FUSIONS)

template<int N, class From, class To>
void test_fusion()
{
    namespace egg = pstade::egg;
    using namespace egg;

    // lvalue
    BOOST_MPL_ASSERT((boost::mpl::equal<To, typename pstade::result_of<X_fusion_drop_c<N>(From&)>::type>));
    BOOST_MPL_ASSERT((boost::mpl::equal<To, typename pstade::result_of<X_fusion_drop_c<N>(From const&)>::type>));
    // rvalue
    BOOST_MPL_ASSERT((boost::mpl::equal<To, typename pstade::result_of<X_fusion_drop_c<N>(From)>::type>));
    BOOST_MPL_ASSERT((boost::mpl::equal<To, typename pstade::result_of<X_fusion_drop_c<N>(From const)>::type>));
}

#endif


void pstade_minimal_test()
{
    {
        using boost::tuples::cons;
        using boost::tuples::tuple;
        using boost::tuples::null_type;

        ::test_tuple< 1, tuple<char, int, double, int&>, cons<int, cons<double, cons<int&, null_type> > > >();
        ::test_tuple< 2, tuple<char, int, double, int&>, cons<double, cons<int&, null_type> > >();
        ::test_tuple< 3, tuple<char, int, double, int&>, cons<int&, null_type> >();
        ::test_tuple0< 4, tuple<char, int, double, int&> >();
        ::test_tuple0< 0, null_type >();

        namespace egg = pstade::egg;
        int k = 999;
        tuple<char, int, double, int&> t('a', 1, 1.0, k);
        BOOST_CHECK( egg::is_same(boost::get<3>(egg::fusion_drop_c<0>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::get<2>(egg::fusion_drop_c<1>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::get<1>(egg::fusion_drop_c<2>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::get<0>(egg::fusion_drop_c<3>(t)), k) );

        null_type nt;
        null_type nt_ = egg::fusion_drop_c<0>(nt);
        (void)nt_;
    }

#if defined(PSTADE_EGG_HAS_FUSIONS)
    {
        using boost::fusion::vector;

        ::test_fusion< 1, vector<char, int, double, int&>, vector<int, double, int&> >();
        ::test_fusion< 2, vector<char, int, double, int&>, vector<double, int&> >();
        ::test_fusion< 3, vector<char, int, double, int&>, vector<int&> >();
        ::test_fusion< 4, vector<char, int, double, int&>, vector<> >();

        namespace egg = pstade::egg;
        int k = 999;
        vector<char, int, double, int&> t('a', 1, 1.0, k);
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<3>(egg::fusion_drop_c<0>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<2>(egg::fusion_drop_c<1>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(egg::fusion_drop_c<2>(t)), k) );
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(egg::fusion_drop_c<3>(t)), k) );
        
        vector<> nt;
        BOOST_CHECK( boost::fusion::equal_to(egg::fusion_drop_c<0>(nt), nt) );
    }
#endif
}
