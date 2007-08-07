#ifndef PSTADE_OVEN_COMPREHENSION_HPP
#define PSTADE_OVEN_COMPREHENSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/egg/adapt.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/lambda_bind.hpp>
#include <pstade/egg/lambda_placeholders.hpp>
#include <pstade/egg/lambda_unlambda.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/nullary_result_of.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/result_of_lambda.hpp>
#include "./detail/monad.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace comprehension_detail {


    template< class MakeRange, class Function >
    struct nested :
        egg::function_facade< nested<MakeRange, Function> >
    {
        template< class Myself, class Value1, class Value2 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange const(Value1&, Value2&)>::type,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Function const&)>::type,
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
                m_makeRng(v1, v2),
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
                    typename result_of<MakeRange const(Value1&)>::type,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Function const&)>::type,
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
                m_makeRng(v1),
                egg::lambda_bind(
                    egg::lambda_unlambda(m_fun),
                    v1,
                    egg::lambda_1
                )
            );
        }

        nested(MakeRange makeRng, Function fun) :
            m_makeRng(makeRng), m_fun(fun)
        { }

    private:
        MakeRange m_makeRng;
        Function m_fun;
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
        template< class Myself, class Expr, class Guard, class MakeRange1, class MakeRange2 = void, class MakeRange3 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<
                        op_make_nested(
                            MakeRange2&,
                            typename result_of<
                                op_make_nested(
                                    MakeRange3&,
                                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                                )
                            >::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1, class MakeRange2, class MakeRange3 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1, MakeRange2& makeRng2, MakeRange3& makeRng3) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_nested(
                    makeRng2,
                    make_nested(
                        makeRng3,
                        make_to_unit(expr, guard) // 3ary
                    ) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class MakeRange1, class MakeRange2 >
        struct apply<Myself, Expr, Guard, MakeRange1, MakeRange2> :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<
                        op_make_nested(
                            MakeRange2&,
                            typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1, class MakeRange2 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1, MakeRange2& makeRng2) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_nested(
                    makeRng2,
                    make_to_unit(expr, guard) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class MakeRange1 >
        struct apply<Myself, Expr, Guard, MakeRange1> :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_to_unit(expr, guard) // 1ary
            );
        }
    };


} // namespace comprehension_detail


typedef egg::function<comprehension_detail::baby> op_comprehension;
PSTADE_POD_CONSTANT((op_comprehension), comprehension) = {{}};


// no guard
//

struct op_no_guard
{
    typedef bool result_type;

    bool operator()(dont_care = 0, dont_care = 0, dont_care = 0) const
    {
        return true;
    }
};

PSTADE_POD_CONSTANT((op_no_guard), no_guard) = {};


// always_return
//

namespace always_return_detail {

    template< class Range >
    struct result_
    {
        typedef typename
            iter_range_of<Range>::type
        result_type;

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
        // For some reason, msvc needs this unless compiled on IDE.
        // I'm not sure this workaround is needed even under Boost1.35.
        // See also <pstade/result_of.hpp> comments.

        typedef result_type nullary_result_type; // for Egg's macro

        template< class Signature >
        struct result
        {
            typedef result_type type;
        };
#endif

        result_type operator()(dont_care = 0, dont_care = 0, dont_care = 0) const
        {
            return m_rng;
        }

        explicit result_(Range& rng) :
            m_rng(rng)
        { }

    private:
        // Hold by value to avoid dangling.
        result_type m_rng;
    };

} // namespace always_return_detail

typedef
    egg::generator<
        always_return_detail::result_< egg::deduce<boost::mpl::_1, egg::as_qualified> >
    >::type
op_always_return;

PSTADE_POD_CONSTANT((op_always_return), always_return) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::oven


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::oven::always_return_detail::result_, (class))
#endif


#endif
