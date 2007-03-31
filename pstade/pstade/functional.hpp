#ifndef PSTADE_FUNCTIONAL_HPP
#define PSTADE_FUNCTIONAL_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Adds 'boost::result_of' support to <functional>.
// Also, these are Assignable and DefaultConstructible;
// Boost.Lambda functors are not.


// Note:
//
// std::unary/binary_negate requires 'Predicate'
// to be Adaptable, which seems to be obsolete.
// See [1] at Boost.Phoenix2 about deduction of arithmetic results.
//
// [1] <boost/spirit/phoenix/detail/type_deduction.hpp>


#include <boost/mpl/if.hpp> // if_c
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_fun.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp> // disable_if
#include <pstade/object_generator.hpp>
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
        struct return_op
        {
            typedef T& result_type;

            T& operator()() const
            {
                return *m_px;
            }

            explicit return_op()
            { }

            explicit return_op(T& x) :
                m_px(boost::addressof(x))
            { }

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
            typedef always_detail::return_op<T> type;
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
        struct return_op :
            callable< return_op<Predicate> > 
        {
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

            explicit return_op()
            { }

            explicit return_op(Predicate const& pred) :
                m_pred(pred)
            { }

        private:
            Predicate m_pred;
        };

    } // namespace not_detail

    PSTADE_OBJECT_GENERATOR(not_, (not_detail::return_op< deduce<_1, to_value> >))
    typedef op_not_ op_not;


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

    struct functional_failed_to_deduce_arithmetic_operation_result_type;

    namespace functional_detail {

        template< class X, class Y >
        yes are_you_x(X const&);

        template< class X, class Y >
        no  are_you_x(Y const&, typename disable_if< boost::is_same<X, Y> >::type = 0);

        template< class X, class Y >
        functional_failed_to_deduce_arithmetic_operation_result_type are_you_x(...);

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
            sizeof( functional_detail::are_you_x<x_t, y_t>(x Op y) ) == sizeof(yes); \
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
        struct return_op :
            callable< return_op<BinaryFun> >
        {
            template< class Myself, class A0, class A1 >
            struct apply :
                boost::result_of<PSTADE_CONST_FUN_TPL(BinaryFun)(A1&, A0&)>
            { };

            template< class Result, class A0, class A1 >
            Result call(A0& a0, A1& a1) const
            {
                return m_fun(a1, a0);
            }

            explicit return_op()
            { }

            explicit return_op(BinaryFun const& fun) :
                m_fun(fun)
            { }

        private:
            BinaryFun m_fun;
        };

    } // namespace flip_detail

    PSTADE_OBJECT_GENERATOR(flip, (flip_detail::return_op< deduce<_1, to_value> >))


    // equal_to_0
    //

    struct op_equal_to_0
    {
        typedef bool result_type;

        template< class X >
        bool operator()(X const& x) const
        {
            return x == X(0);
        }
    };

    PSTADE_CONSTANT(equal_to_0, (op_equal_to_0))


} // ADL barrier

} // namespace pstade


#endif
