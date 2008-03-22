#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_OVERLOAD_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_OVERLOAD_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/fuse.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/overload_resolution.hpp>


namespace boost { namespace egg { namespace details {


#define BOOST_EGG_base(Z, N, _) \
    typedef typename function_types::result_type<BOOST_PP_CAT(Sig, N)>::type BOOST_EGG_PP_CAT3(base, N, _type); \
    BOOST_EGG_PP_CAT3(base, N, _type) BOOST_EGG_CAT(m_base, N); \
/**/
#define BOOST_EGG_at_(Z, N, _) \
    template<int I> \
    BOOST_EGG_PP_CAT3(base, N, _type) at_(boost::mpl::int_<I>) const \
    { \
        return BOOST_EGG_CAT(m_base, N); \
    } \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_ARITY, <boost/egg/detail/little_overload_result.hpp>))
    #include BOOST_PP_ITERATE()
#undef  BOOST_EGG_at_
#undef  BOOST_EGG_base


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<BOOST_PP_ENUM_PARAMS(n, class Sig)>
    struct BOOST_PP_EGG_CAT3(little_overload, n, _result)
    {
        BOOST_PP_REPEAT(n, BOOST_EGG_base, ~)
        BOOST_PP_REPEAT(n, BOOST_EGG_at_, ~)

        typedef mpl::BOOST_PP_CAT(vector, n)<BOOST_PP_ENUM_PARAMS(n, Sig)> sigs_type;

        template<class Me, class Args>
        struct apply :
            result_of_<
                typename result_of_<
                    T_fuse(typename overload_resolution<sigs_type, Args>::target_type)
                >::type(Args &)
            >
        { };

        template<class Re, class Args>
        Re class(Args &args) const
        {
            return fuse(at_(typename overload_resolution<sigs_type, Args>::index_type())(args);
        }
    };


#undef  n
#endif
