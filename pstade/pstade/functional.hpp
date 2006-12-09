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
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/yes_no.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(functional) {


    // identity
    //

    struct op_identity :
        callable<op_identity>
    {
        template< class Myself, class T >
        struct apply
        {
            typedef T& type;
        };

        template< class Result, class T >
        Result call(T& x) const
        {
            return x;
        }
    };

    PSTADE_CONSTANT(identity, op_identity)


    // not_
    //

    namespace not_detail {

        template< class Predicate >
        struct op_result :
            callable< op_result<Predicate> > 
        {
            explicit op_result() // DefaultConstructible iif 'Predicate' is.
            { }

            explicit op_result(Predicate const& pred) :
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
            Predicate m_pred;
        };

    } // namespace not_detail

    PSTADE_OBJECT_GENERATOR(not_, not_detail::op_result, 1, (object_by_value))


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

    } // namespace always_detail

    struct op_always :
        callable<op_always>
    {
        template< class Myself, class T >
        struct apply
        {
            typedef always_detail::op_result<T> type;
        };

        template< class Result, class T >
        Result call(T& x) const
        {
            return Result(x);
        }
    };

    PSTADE_CONSTANT(always, op_always)


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

    PSTADE_CONSTANT(equal_to, op_equal_to)


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

    PSTADE_CONSTANT(less, op_less)


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

    PSTADE_CONSTANT(is_zero, op_is_zero)


    // plus
    //

    struct plus_failed_to_deduce_result_type
    { };

    namespace plus_detail {

        template< class X, class Y >
        struct deduce_result
        {
        private:
            typedef typename boost::remove_cv<X>::type x_t;
            typedef typename boost::remove_cv<Y>::type y_t;

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

    struct op_plus :
        callable<op_plus>
    {
        template< class Myself, class X, class Y >
        struct apply :
            plus_detail::deduce_result<X, Y>
        { };

        template< class Result, class X, class Y >
        Result call(X const& x, Y const& y) const
        {
            return x + y;
        }
    };

    PSTADE_CONSTANT(plus, op_plus)


    // at_first
    //

    struct op_at_first :
        callable<op_at_first>
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

    PSTADE_CONSTANT(at_first, op_at_first)


    // at_second
    //

    struct op_at_second :
        callable<op_at_second>
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

    PSTADE_CONSTANT(at_second, op_at_second)


    // flip
    //

    namespace flip_detail {

        template< class BinaryFun >
        struct op_result :
            callable< op_result<BinaryFun> >
        {
            explicit op_result()
            { }

            explicit op_result(BinaryFun const& fun) :
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
            BinaryFun m_fun;
        };

    } // namespace flip_detail

    PSTADE_OBJECT_GENERATOR(flip, flip_detail::op_result, 1, (object_by_value))


} // ADL barrier

} // namespace pstade


#endif
