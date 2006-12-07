#ifndef PSTADE_FUNCTIONAL_HPP
#define PSTADE_FUNCTIONAL_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// std::unary/binary_negate requires 'Predicate'
// to be Adaptable, which seems to be deprecated.
// See [1] at Boost.Phoenix2 about 'deduce_result'.
//
// [1] <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp> // if_c
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_adaptor.hpp>
#include <pstade/instance.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/yes_no.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(functional) {


    // identity
    //

    namespace identity_detail {

        struct baby
        {
            template< class Myself, class T >
            struct apply :
                boost::add_reference<T>
            { };

            template< class Result, class T >
            Result call(T& x) const
            {
                return x;
            }
        };

    } // namespace identity_detail

    PSTADE_EGG_FUNCTION(identity, identity_detail::baby)


    // not_
    //

    namespace not_detail {

        template< class Predicate >
        struct baby_op_result
        {
            explicit baby_op_result() // DefaultConstructible iif 'Predicate' is.
            { }

            explicit baby_op_result(Predicate const& pred) :
                m_pred(pred)
            { }

            template< class Myself, class T0, class T1 = void >
            struct apply
            {
                typedef bool type;
            };

            template< class Result, class T0 >
            Result call(T0& a0) const
            {
                return !m_pred(a0);
            }

            template< class Result, class T0, class T1 >
            Result call(T0& a0, T1& a1) const
            {
                return !m_pred(a0, a1);
            }

        private:
            mutable Predicate m_pred;
        };

    } // namespace not_detail

    PSTADE_EGG_FUNCTION_ADAPTOR(not_, not_detail::baby_op_result)


    // always
    //

    namespace always_detail {

        template< class T >
        struct op_result
        {
            typedef T& result_type;

            explicit op_result()
            { }

            explicit op_result(T& x) :
                m_px(boost::addressof(x))
            { }

            result_type operator()() const
            {
                return *m_px;
            }

        private:
            T *m_px;
        };

        struct baby
        {
            template< class Myself, class T >
            struct apply
            {
                typedef op_result<T> type;
            };

            template< class Result, class T >
            Result call(T& x) const
            {
                return Result(x);
            }
        };

    } // namespace always_detail

    PSTADE_EGG_FUNCTION(always, always_detail::baby)


    // equal_to
    //

    struct op_equal_to
    {
        typedef bool result_type;

        template< class X, class Y >
        bool operator()(X const& x, Y const& y) const
        {
            return x == y;
        }
    };

    PSTADE_SINGLETON_CONST(equal_to, op_equal_to)


    // less
    //

    struct op_less
    {
        typedef bool result_type;

        template< class X, class Y >
        bool operator()(X const& x, Y const& y) const
        {
            return x < y;
        }
    };

    PSTADE_SINGLETON_CONST(less, op_less)


    // is_zero
    //

    struct op_is_zero
    {
        typedef bool result_type;

        template< class X >
        bool operator()(X const& x) const
        {
            return x == 0;
        }
    };

    PSTADE_SINGLETON_CONST(is_zero, op_is_zero)


    // plus
    //

    struct plus_failed_to_deduce_result_type
    { };

    namespace plus_detail {

        template< class X, class Y >
        struct deduce_result
        {
        private:
            typedef typename remove_cvr<X>::type x_t;
            typedef typename remove_cvr<Y>::type y_t;

            template< class X_, class Y_ > static
            yes test(X_ const&);

            template< class X_, class Y_ > static
            no  test(Y_ const&, typename boost::disable_if< boost::is_same<X_, Y_> >::type * = 0);

            template< class X_, class Y_ > static
            plus_failed_to_deduce_result_type test(...);

            static x_t x;
            static y_t y;

            static bool const is_x =
                sizeof( test<x_t, y_t>(x + y) ) == sizeof(yes);

        public:
            typedef typename boost::mpl::if_c< is_x,
                x_t, y_t
            >::type type;
        };

    } // namespace plus_detail

    struct op_plus
    {
        template< class Signature >
        struct result;

        template< class _, class X, class Y >
        struct result<_(X, Y)> :
            plus_detail::deduce_result<X, Y>
        { };

        template< class X, class Y >
        typename result<int(X, Y)>::type operator()(X const& x, Y const& y) const
        {
            return x + y;
        }
    };

    PSTADE_SINGLETON_CONST(plus, op_plus)


    // at_first
    //

    namespace at_first_detail {

        struct baby
        {
            template< class Myself, class Pair >
            struct apply :
                boost::add_reference<
                    typename affect_const<
                        Pair, typename Pair::first_type
                    >::type
                >
            { };

            template< class Result, class Pair >
            Result call(Pair& x) const
            {
                return x.first;
            }
        };

    } // namespace at_first_detail

    PSTADE_EGG_FUNCTION(at_first, at_first_detail::baby)


    // at_second
    //

    namespace at_second_detail {

        struct baby
        {
            template< class Myself, class Pair >
            struct apply :
                boost::add_reference<
                    typename affect_const<
                        Pair, typename Pair::second_type
                    >::type
                >
            { };

            template< class Result, class Pair >
            Result call(Pair& x) const
            {
                return x.second;
            }
        };

    } // namespace at_second_detail

    PSTADE_EGG_FUNCTION(at_second, at_second_detail::baby)


    // flip
    //

    namespace flip_detail {

        template< class BinaryFun >
        struct baby_op_result
        {
            explicit baby_op_result()
            { }

            explicit baby_op_result(BinaryFun const& fun) :
                m_fun(fun)
            { }

            template< class Myself, class T0, class T1 >
            struct apply :
                boost::result_of<BinaryFun(T1&, T0&)>
            { };

            template< class Result, class T0, class T1 >
            Result call(T0& a0, T1& a1) const
            {
                return m_fun(a1, a0);
            }

        private:
            mutable BinaryFun m_fun;
        };

    } // namespace flip_detail

    PSTADE_EGG_FUNCTION_ADAPTOR(flip, flip_detail::baby_op_result)


} // ADL barrier

} // namespace pstade


#endif
