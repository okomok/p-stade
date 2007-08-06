#ifndef PSTADE_OVEN_COMPREHENSION_HPP
#define PSTADE_OVEN_COMPREHENSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/xpressive/proto/proto.hpp>
#include <pstade/egg/adapt.hpp>
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


    namespace proto = boost::proto;


    struct placeholder1 { };
    struct placeholder2 { };
    struct placeholder3 { };


    template< class Lambda >
    struct guard_of
    {
        Lambda m_lambda;
    };

    template<class Lambda>
    struct base_guard
    {
        typedef typename
            proto::terminal<
                guard_of<typename pass_by_value<Lambda>::type>
            >::type
        result_type;

        result_type operator()(Lambda& lam) const
        {
            result_type result = {{lam}};
            return result;
        }
    };


    struct Placeholder :
        proto::or_<
            proto::terminal<placeholder1>,
            proto::terminal<placeholder2>,
            proto::terminal<placeholder3>
        >
    { };

    struct Expression :
        proto::_
    { };

    struct Range :
        proto::_
    { };

    struct Generator :
        proto::less_equal<Placeholder, Range>
    { };

    struct Guard :
        proto::terminal< guard_of<proto::_> >
    { };

    struct Expression_with_Generator :
        proto::bitwise_or<Expression, Generator>
    { };

    struct Qualifier :
        proto::or_<
            proto::comma<Generator, Qualifier>,
            proto::comma<Guard, Qualifier>,
            Generator,
            Guard
        >
    { };

    struct RightTree;

    struct LeftTree :
        proto::or_<
            Expression_with_Generator,
            proto::comma<LeftTree, RightTree>
        >
    { };

    struct RightTree :
        proto::or_<Generator, Guard>
    { };

    struct Tree :
        proto::or_<
            Expression_with_Generator,
            proto::comma<LeftTree, RightTree>
        >
    { };

    struct Grammar :
        Tree
    { };
            

    template< class Range, class Fun >
    struct nested :
        egg::function_facade< nested<Range, Fun> >
    {
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
                lambda::bind(
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
                lambda::bind(
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

    template< class Range, class Fun > inline
    nested<Range, Fun> make_nested(Range& rng, Fun fun)
    {
        return nested<Range, Fun>(rng, fun);
    }


#if 0
    template< class Range3, class Fun3 >
    struct function2 :
        egg::function_facade< function2<Range3, Fun3> >
    {
        typedef typename
            iter_range_of<Range3>::type
        rng3_t;

        template< class Myself, class Value1, class Value2 >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    rng3_t const&,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Fun3 const&)>::type,
                            Value1&,
                            Value2&,
                            egg::op_lambda_1 const&
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Value1, class Value2>
        Result call(Value1& v1, Value2& v2) const
        {
            return detail::monad_bind(
                m_rng3,
                lambda::bind(
                    egg::lambda_unlambda(m_fun3),
                    v1,
                    v2,
                    egg::lambda_1
                )
            );
        }

        function2(Range3& rng3, Fun3 fun3) :
            m_rng3(rng3), m_fun3(fun3)
        { }

    private:
        rng3_t m_rng3;
        Fun3 m_fun3;
    };

    template< class Range3, class Fun3 > inline
    function2<Range3, Fun3> make_function2(Range3& rng3, Fun3 fun3)
    {
        return function2<Range3, Fun3>(rng3, fun3);
    }

#endif


    template< class Lambda >
    struct to_unit :
        egg::function_facade< to_unit<Lambda> >
    {
        template< class Myself, class Value1, class Value2 = void, class Value3 = void >
        struct apply :
            result_of<
                detail::op_monad_unit(typename result_of<Lambda const(Value1&, Value2&, Value3&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2, class Value3 >
        Result call(Value1& v1, Value2& v2, Value3& v3) const
        {
            return detail::monad_unit(m_fun(v1, v2, v3));
        }

        template< class Myself, class Value1, class Value2 >
        struct apply<Myself, Value1, Value2> :
            result_of<
                detail::op_monad_unit(typename result_of<Lambda const(Value1&, Value2&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2 >
        Result call(Value1& v1, Value2& v2) const
        {
            return detail::monad_unit(m_fun(v1, v2));
        }

        template< class Myself, class Value1 >
        struct apply<Myself, Value1> :
            result_of<
                detail::op_monad_unit(typename result_of<Lambda const(Value1&)>::type)
            >
        { };

        template< class Result, class Value1 >
        Result call(Value1& v1) const
        {
            return detail::monad_unit(m_fun(v1));
        }

        explicit to_unit(Lambda fun) :
            m_fun(fun)
        { }

    private:
        Lambda m_fun;
    };

    template< class Lambda > inline
    to_unit<Lambda> make_to_unit(Lambda fun)
    {
        return to_unit<Lambda>(fun);
    }


#if 0

    template< class IterRange >
    struct context :
        proto::callable_context<context const>
    {
        template< class Left, class Right >
        result_type operator()(proto::tag::comma, Left const& left, Right const& right) const
        {
            return lambda::bind(detail::monad_bind, m_rng, ??);
        }

        template< class Left, class Right >
        result_type operator()(proto::tag::bitor, Left const& left, Right const& right) const
        {
            return lambda::bind(detail::monad_bind, m_rng, ??);
        }

        IterRange m_rngX, m_rngY, m_rngZ;
    };

#endif


} // comprehension_detail


PSTADE_POD_CONSTANT((boost::proto::terminal<comprehension_detail::placeholder1>::type), _1) = {{}};
PSTADE_POD_CONSTANT((boost::proto::terminal<comprehension_detail::placeholder2>::type), _2) = {{}};
PSTADE_POD_CONSTANT((boost::proto::terminal<comprehension_detail::placeholder3>::type), _3) = {{}};

typedef PSTADE_EGG_ADAPT((comprehension_detail::base_guard<boost::mpl::_>)) op_guard;
PSTADE_POD_CONSTANT((op_guard), guard) = PSTADE_EGG_ADAPT_INITIALIZER();


} } // namespace pstade::oven


#endif
