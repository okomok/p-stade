#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INITIAL_VALUES_HPP
#define PSTADE_OVEN_INITIAL_VALUES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Simpler/faster version of 'boost::assign::cref_list_of'.
// Precondition: A2-AN must be convertible to A1.


// References:
//
// [1] Bjarne Stroustrup and Gabriel Dos Reis, Initializer Lists, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2100.pdf
// [2] Thorsten Ottosen, Boost.Assign, 2002-2004.
//     http://www.boost.org/libs/assign/doc/index.html


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <pstade/egg/bll_bindable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./copy_range.hpp"
#include "./detail/config.hpp"


#if !defined(PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY)
    #define PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


namespace initial_values_detail {


    template< class Value, std::size_t N >
    struct result_range
    {
        // Prefer 'boost::array' to built-in array;
        // If 'To' also is 'boost::array', the initialization can be
        // efficient because 'copy_range' can return directly.
        boost::array<Value, N> m_array;

        // convertible to CopyableRange
        template< class Range >
        operator Range() const
        {
            PSTADE_CONCEPT_ASSERT((Copyable<Range>));
            return copy<Range>();
        }

        template< class Range >
        Range copy() const
        {
            PSTADE_CONCEPT_ASSERT((Copyable<Range>));
            return oven::copy_range<Range>(m_array);
        }

    // range implementation
        typedef Value const *iterator;
        typedef iterator const_iterator;
        typedef std::size_t size_type;

        iterator begin() const
        {
            return m_array.data();
        }

        iterator end() const
        {
            return m_array.data() + N;
        }

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
        size_type size() const
        {
            return N;
        }
#endif
    };


    // 'result_range' also is CopyableRange.
    template< class Value, std::size_t N, class From > inline
    result_range<Value, N> pstade_oven_copy_range(boost::type< result_range<Value, N> >, From& from)
    {
        result_range<Value, N> r = { oven::copy_range< boost::array<Value, N> >(from) };
        return r;
    }


} // namespace initial_values_detail


template< class Value = boost::use_default >
struct X_initial_values
{
    template< class A >
    struct value_ :
        eval_if_use_default< Value, pass_by_value<A> >
    { };

// 1ary-
    template< class FunCall >
    struct result;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY, <pstade/oven/initial_values.hpp>))
    #include BOOST_PP_ITERATE()

    #include PSTADE_EGG_BLL_BINDABLE()
};


typedef X_initial_values<> T_initial_values;
PSTADE_POD_CONSTANT((T_initial_values), initial_values) = {};


template< class Value, std::size_t N >
struct result_of_initial_values
{
    typedef
        initial_values_detail::result_range<Value, N> const
    type;
};


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n)
    {
        typedef
            initial_values_detail::result_range<typename value_<A0>::type, n> const
        type;
    };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const
    {
        initial_values_detail::result_range<typename value_<A0 const&>::type, n> r = { { { BOOST_PP_ENUM_PARAMS(n, a) } } };
        return r;
    }


#undef n
#endif
