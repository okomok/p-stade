#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_RET_HPP
#define PSTADE_RET_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade {


    namespace ret_detail {


        template< class Result_, class Function >
        struct baby_fun
        {
			typedef Result_ nullary_result_type;

			template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class T, void) >
			struct apply
			{
				typedef Result_ type;
			};

            // 0ary
            template< class Result >
            Result call()
            {
                return m_fun();
            }

            // 1ary
            template< class Result, class A0 >
            Result call(A0& a0)
            {
                return m_fun(a0);
            }

            // 2ary-
        #define PSTADE_max_arity PSTADE_EGG_MAX_ARITY
        #define PSTADE_ref_param(Z, N, _) BOOST_PP_CAT(A, N) & BOOST_PP_CAT(a, N)
            #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/ret.hpp>))
            #include BOOST_PP_ITERATE()
        #undef PSTADE_ref_param
        #undef PSTADE_max_arity

            explicit baby_fun() // DefaultConstructible iff 'Function' is.
            { }

            explicit baby_fun(Function const& fun) :
                m_fun(fun)
            { }

        private:
            Function m_fun;
        };


    } // namespace ret_detail


	template< class Result, class Function >
	struct result_of_ret
	{
		typedef egg::function< ret_detail::baby_fun<Result, Function> > type;
	};


	template< class Result, class Function > inline
	typename result_of_ret<Result, Function>::type
	ret(Function fun)
	{
		return typename result_of_ret<Result, Function>::type(fun);
	}


	template< class Result >
	struct with_ret;


	namespace with_ret_detail {

		struct adl_marker
		{ };

		template< class Result, class Function > inline
		typename result_of_ret<Result, Function>::type
		operator|(Function fun, with_ret<Result> const&)
		{
			return typename result_of_ret<Result, Function>::type(fun);
		}

	} // namespace with_ret_detail


	template< class Result >
	struct with_ret :
		with_ret_detail::adl_marker,
		private nonassignable
	{ };


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( BOOST_PP_ENUM(n, PSTADE_ref_param, ~) )
{
    return m_fun( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
