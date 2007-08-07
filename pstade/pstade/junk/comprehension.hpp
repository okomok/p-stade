#ifndef PSTADE_OVEN_COMPREHENSION_HPP
#define PSTADE_OVEN_COMPREHENSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adapt.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/lambda_bind.hpp>
#include <pstade/egg/lambda_placeholders.hpp>
#include <pstade/egg/lambda_unlambda.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of_lambda.hpp>
#include "./detail/monad.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace comprehension_detail {


    template< class Range, class Fun >
    struct nested :
        egg::function_facade< nested<Range, Fun> >
    {
        // Hold range by value in order to avoid dangling.
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        template< class Myself, class Value1, class Value2 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    rng_t const&,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Fun const&)>::type,
                            Value1&,
                            Value2&,
                            egg::op_lambda_1 const&
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Value1, class Value2 >
        Result call(Value1& v1, Value2& v2) const
        {
            return detail::monad_bind(
                m_rng,
                egg::lambda_bind(
                    egg::lambda_unlambda(m_fun),
                    v1,
                    v2,
                    egg::lambda_1
                )
            );
        }

        template< class Myself, class Value1 >
        struct apply<Myself, Value1> :
            result_of<
                detail::op_monad_bind(
                    rng_t const&,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Fun const&)>::type,
                            Value1&,
                            egg::op_lambda_1 const&
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Value1 >
        Result call(Value1& v1) const
        {
            return detail::monad_bind(
                m_rng,
                egg::lambda_bind(
                    egg::lambda_unlambda(m_fun),
                    v1,
                    egg::lambda_1
                )
            );
        }

        nested(Range& rng, Fun fun) :
            m_rng(rng), m_fun(fun)
        { }

    private:
        rng_t m_rng;
        Fun m_fun;
    };

    struct baby_make_nested
    {
        template< class Myself, class Range, class Fun >
        struct apply
        {
            typedef
                nested<Range, typename pass_by_value<Fun>::type>
            type;
        };

        template< class Result, class Range, class Fun >
        Result call(Range& rng, Fun& fun) const
        {
            return Result(rng, fun);
        }
    };

    typedef egg::function<baby_make_nested> op_make_nested;
    PSTADE_POD_CONSTANT((op_make_nested), make_nested) = {};


    template< class Expr, class Guard >
    struct to_unit :
        egg::function_facade< to_unit<Expr, Guard> >
    {
        template< class Myself, class Value1, class Value2 = void, class Value3 = void >
        struct apply :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&, Value2&, Value3&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2, class Value3 >
        Result call(Value1& v1, Value2& v2, Value3& v3) const
        {
            typedef typename result_of<Expr const(Value1&, Value2&, Value3&)>::type val_t;

            if (m_guard(v1, v2, v3))
                return detail::monad_unit(m_expr(v1, v2, v3));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        template< class Myself, class Value1, class Value2 >
        struct apply<Myself, Value1, Value2> :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&, Value2&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2 >
        Result call(Value1& v1, Value2& v2) const
        {
            typedef typename result_of<Expr const(Value1&, Value2&)>::type val_t;

            if (m_guard(v1, v2))
                return detail::monad_unit(m_expr(v1, v2));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        template< class Myself, class Value1 >
        struct apply<Myself, Value1> :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&)>::type)
            >
        { };

        template< class Result, class Value1 >
        Result call(Value1& v1) const
        {
            typedef typename result_of<Expr const(Value1&)>::type val_t;

            if (m_guard(v1))
                return detail::monad_unit(m_expr(v1));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        to_unit(Expr expr, Guard guard) :
            m_expr(expr), m_guard(guard)
        { }

    private:
        Expr m_expr;
        Guard m_guard;
    };

    struct baby_make_to_unit
    {
        template< class Myself, class Expr, class Guard >
        struct apply
        {
            typedef
                to_unit<typename pass_by_value<Expr>::type, typename pass_by_value<Guard>::type>
            type;
        };

        template< class Result, class Expr, class Guard >
        Result call(Expr& expr, Guard& guard) const
        {
            return Result(expr, guard);
        }
    };

    typedef egg::function<baby_make_to_unit> op_make_to_unit;
    PSTADE_POD_CONSTANT((op_make_to_unit), make_to_unit) = {};


    struct baby
    {
        template< class Myself, class Expr, class Guard, class Range1, class Range2 = void, class Range3 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    Range1&,
                    typename result_of<
                        op_make_nested(
                            Range2&,
                            typename result_of<
                                op_make_nested(
                                    Range3&,
                                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                                )
                            >::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class Range1, class Range2, class Range3 >
        Result call(Expr& expr, Guard& guard, Range1& rng1, Range2& rng2, Range3& rng3) const
        {
            return detail::monad_bind(
                rng1,
                make_nested(
                    rng2,
                    make_nested(
                        rng3,
                        make_to_unit(expr, guard) // 3ary
                    ) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class Range1, class Range2 >
        struct apply<Myself, Expr, Guard, Range1, Range2> :
            result_of<
                detail::op_monad_bind(
                    Range1&,
                    typename result_of<
                        op_make_nested(
                            Range2&,
                            typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class Range1, class Range2 >
        Result call(Expr& expr, Guard& guard, Range1& rng1, Range2& rng2) const
        {
            return detail::monad_bind(
                rng1,
                make_nested(
                    rng2,
                    make_to_unit(expr, guard) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class Range1 >
        struct apply<Myself, Expr, Guard, Range1> :
            result_of<
                detail::op_monad_bind(
                    Range1&,
                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class Range1 >
        Result call(Expr& expr, Guard& guard, Range1& rng1) const
        {
            return detail::monad_bind(
                rng1,
                make_to_unit(expr, guard) // 1ary
            );
        }
    };


} // namespace comprehension_detail


typedef egg::function<comprehension_detail::baby> op_comprehension;
PSTADE_POD_CONSTANT((op_comprehension), comprehension) = {{}};


struct op_no_guard
{
    typedef bool result_type;

    template< class A1, class A2, class A3 >
    bool operator()(A1 const&, A2 const&, A3 const&) const
    {
        return true;
    }

    template< class A1, class A2 >
    bool operator()(A1 const&, A2 const&) const
    {
        return true;
    }

    template< class A1 >
    bool operator()(A1 const&) const
    {
        return true;
    }
};

PSTADE_POD_CONSTANT((op_no_guard), no_guard) = {};


} } // namespace pstade::oven


#endif
