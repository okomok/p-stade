#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_ANY_FUNPTR_HPP
#define PSTADE_ANY_FUNPTR_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/none.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/is_function.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>
#include "./any_fwd.hpp"


#if !defined(PSTADE_ANY_FUNPTR_MAX_ARITY)
#   define PSTADE_ANY_FUNPTR_MAX_ARITY 5
#endif


namespace pstade {


    namespace any_funptr_detail {


        template<class X>
        struct is_function_pointer :
            boost::mpl::false_
        { };

        template<class X>
        struct is_function_pointer<X *> :
            boost::is_function<X>
        { };


    } // namespace any_funptr_detail

    // 0ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_ANY_FUNPTR_MAX_ARITY, <pstade/any_funptr.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct any_funptr<Result(BOOST_PP_ENUM_PARAMS(n, A))> :
        radish::bool_testable< any_funptr<Result(BOOST_PP_ENUM_PARAMS(n, A))>,
        radish::swappable    < any_funptr<Result(BOOST_PP_ENUM_PARAMS(n, A))> > >
    {
    private:
        typedef any_funptr self_t;
        typedef void (*void_funptr_t)();

    public:
        typedef Result function_type(BOOST_PP_ENUM_PARAMS(n, A));
        typedef Result result_type;

    // structors
        any_funptr(boost::none_t = boost::none) :
            m_fp(PSTADE_NULLPTR)
        { }

        template<class Fp>
        any_funptr(Fp fp, typename enable_if< any_funptr_detail::is_function_pointer<Fp> >::type = 0) :
            m_fp(reinterpret_cast<void_funptr_t>(fp))
        { }

    // assignments
        void reset(boost::none_t = boost::none)
        {
            m_fp = PSTADE_NULLPTR;
        }

        template<class Fp>
        void reset(Fp fp)
        {
            m_fp = reinterpret_cast<void_funptr_t>(fp);
        }

        PSTADE_RESET_ASSIGNMENT(any_funptr)

    // operator()
        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            BOOST_ASSERT(m_fp);
            return reinterpret_cast<function_type *>(m_fp)(BOOST_PP_ENUM_PARAMS(n, a));
        }

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(m_fp);
        }

    // swappable
        void swap(self_t &other)
        {
            egg::do_swap(m_fp, other.m_fp);
        }

    // misc
        bool empty() const
        {
            return !m_fp;
        }

    private:
        void_funptr_t m_fp;
    };


#undef n
#endif
