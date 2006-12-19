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
// See [1] at Boost.Phoenix2 about deduction of arithmetic results.
//
// [1] <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp> // if_c
#include <boost/preprocessor/cat.hpp>
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

    PSTADE_CONSTANT(identity, (op_identity))


    // always
    //

    namespace always_detail {

        template< class T >
        struct op_result
        {
            typedef T& result_type;

            explicit op_result() // for ForwardIterator
            { }

            explicit op_result(T& x) :
                m_px(boost::addressof(x))
            { }

            T& operator()() const
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

    PSTADE_CONSTANT(always, (op_always))


    // not_
    //

    namespace not_detail {

        template< class Predicate >
        struct op_result :
            callable< op_result<Predicate> > 
        {
            explicit op_result() // for ForwardIterator
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

    PSTADE_OBJECT_GENERATOR(not_, (not_detail::op_result< deduce<_1, to_value> >))


    // comparison and logical
    //

#define PSTADE_binary_pred(F, Op) \
    struct BOOST_PP_CAT(op_, F) \
    { \
        typedef bool result_type; \
        \
        template< class X, class Y > \
        bool operator()(X const& x, Y const& y) const \
        { \
            return x Op y; \
        } \
    }; \
    \
    PSTADE_CONSTANT( F, (BOOST_PP_CAT(op_,F)) ) \
/**/

    PSTADE_binary_pred(equal_to, ==)
    PSTADE_binary_pred(greater, >)
    PSTADE_binary_pred(less, <)
    PSTADE_binary_pred(greater_equal, >=)
    PSTADE_binary_pred(less_equal, <=)
    PSTADE_binary_pred(logical_and, &&)
    PSTADE_binary_pred(logical_or, ||)

#undef  PSTADE_binary_pred

    struct op_logical_not
    {
        typedef bool result_type;

        template< class X >
        bool operator()(X const& x) const
        {
            return !x;
        }
    };

    PSTADE_CONSTANT(logical_not, (op_logical_not))


    // arithmetic
    //

    struct functional_failed_to_deduce_arithmetic_operation_result_type
    { };

    namespace functional_detail {

        template< class X, class Y > static
        yes test_x(X const&);

        template< class X, class Y > static
        no  test_x(Y const&, typename boost::disable_if< boost::is_same<X, Y> >::type * = 0);

        template< class X, class Y > static
        functional_failed_to_deduce_arithmetic_operation_result_type test_x(...);

    }

#define PSTADE_binary_arithmetic(F, Op) \
    template< class X, class Y > \
    struct BOOST_PP_CAT(functional_detail_result_of_, F) \
    { \
    private: \
        typedef typename boost::remove_cv<X>::type x_t; \
        typedef typename boost::remove_cv<Y>::type y_t; \
        \
        static x_t x; \
        static y_t y; \
        \
        static bool const is_x = \
            sizeof( functional_detail::test_x<x_t, y_t>(x Op y) ) == sizeof(yes); \
        \
    public: \
        typedef typename \
            boost::mpl::if_c< is_x, \
                x_t, y_t \
            >::type \
        type; \
    }; \
    \
    struct BOOST_PP_CAT(op_, F) : \
        callable< BOOST_PP_CAT(op_, F) > \
    { \
        template< class Myself, class X, class Y > \
        struct apply : \
            BOOST_PP_CAT(functional_detail_result_of_, F)<X, Y> \
        { }; \
        \
        template< class Result, class X, class Y > \
        Result call(X const& x, Y const& y) const \
        { \
            return x Op y; \
        } \
    }; \
    \
    PSTADE_CONSTANT( F, (BOOST_PP_CAT(op_, F)) ) \
/**/

    PSTADE_binary_arithmetic(plus, +)
    PSTADE_binary_arithmetic(minus, -)
    PSTADE_binary_arithmetic(multiplies, *)
    PSTADE_binary_arithmetic(divides, /)
    PSTADE_binary_arithmetic(modulus, %)

#undef  PSTADE_binary_arithmetic

    struct op_negate :
        callable<op_negate>
    {
        template< class Myself, class X >
        struct apply :
            boost::remove_cv<X>
        { };

        template< class Result, class X >
        Result call(X const& x) const
        {
            return -x;
        }
    };

    PSTADE_CONSTANT(negate, (op_negate))


    // flip
    //

    namespace flip_detail {

        template< class BinaryFun >
        struct op_result :
            callable< op_result<BinaryFun> >
        {
            explicit op_result() // for ForwardIterator
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

    PSTADE_OBJECT_GENERATOR(flip, (flip_detail::op_result< deduce<_1, to_value> >))


    // at_first/second
    //

#define PSTADE_FUNCTIONAL_MEMBER(F, Xxx, XxxType) \
    struct BOOST_PP_CAT(op_, F) : \
        callable< BOOST_PP_CAT(op_, F) > \
    { \
        template< class Myself, class A > \
        struct apply \
        { \
            typedef typename \
                affect_cv< \
                    A, typename A::XxxType \
                >::type & \
            type; \
        }; \
        \
        template< class Result, class A > \
        Result call(A& a) const \
        { \
            return a.Xxx; \
        } \
    }; \
    \
    PSTADE_CONSTANT( F, (BOOST_PP_CAT(op_, F)) ) \
/**/

    PSTADE_FUNCTIONAL_MEMBER(at_first, first, first_type)
    PSTADE_FUNCTIONAL_MEMBER(at_second, second, second_type)


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

    PSTADE_CONSTANT(is_zero, (op_is_zero))


} // ADL barrier

} // namespace pstade


#endif
