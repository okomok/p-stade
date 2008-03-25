#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_POD_VECTOR_HPP
#define BOOST_EGG_DETAIL_POD_VECTOR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/preprocessor/cat3.hpp>


namespace boost { namespace egg { namespace details {


    template<class Seq, long N = mpl::size<Seq>::type::value>
    struct pod_vector;


#define BOOST_EGG_typedef(Z, I, _) \
    typedef typename mpl::at_c<Seq, I>::type BOOST_EGG_PP_CAT3(element, I, _type); \
/**/
#define BOOST_EGG_def(Z, I, _) \
    BOOST_EGG_PP_CAT3(element, I, _type) BOOST_PP_CAT(m_element, I); \
/**/
#define BOOST_EGG_at_(Z, I, _) \
    BOOST_EGG_PP_CAT3(element, I, _type) const &at_(mpl::int_<I>) const \
    { \
        return BOOST_PP_CAT(m_element, I); \
    } \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/pod_vector.hpp>))
    #include BOOST_PP_ITERATE()
#undef  BOOST_EGG_at_
#undef  BOOST_EGG_def
#undef  BOOST_EGG_typedef


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Seq>
    struct pod_vector<Seq, n>
    {
        BOOST_PP_REPEAT(n, BOOST_EGG_typedef, ~)
        BOOST_PP_REPEAT(n, BOOST_EGG_def, ~)
        BOOST_PP_REPEAT(n, BOOST_EGG_at_, ~)
    };


#undef  n
#endif
