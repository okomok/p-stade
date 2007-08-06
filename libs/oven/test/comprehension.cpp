#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/comprehension.hpp>
#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"


#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <boost/mpl/assert.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/io.hpp>
#include <iostream>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


#if 0
template<class Expr>
void check_match(Expr const& expr)
{
    BOOST_MPL_ASSERT((boost::proto::matches<Expr, comprehension_detail::Grammar>));
}
#endif

void pstade_unit_test()
{
#if 0
    {
        std::string rng1, rng2, rng3;
        ::check_match(( _1 | _1 <= rng1 ));
        ::check_match(( _1 + _2 | _1 <= rng1, _2 <= rng2 ));
        ::check_match(( _1 + _2 | _1 <= rng1, _2 <= rng2, guard(_1 < _2) ));
        ::check_match(( _1 + _2 | _1 <= rng1, guard(_1 < 10), _2 <= rng2 ));
        ::check_match(( _1 + _2 + _3 | _1 <= rng1, _2 <= rng2, _3 <= rng3, guard(_1 < _2) ));
        //::check_match(( _1 + _2, _1 <= rng1, _2 <= rng2, pred) ));
    }
#endif
    {
        namespace bll = boost::lambda;
        int rng1[] = { 1,2,3 };
        int rng2[] = { 4,5,6,7 };
        int rng3[] = { 8,9 };

#if 0
        std::cout <<
            detail::monad_bind(
                rng1,
                comprehension_detail::make_to_unit(bll::_1)
            ) << std::endl;
#endif

        int ans[] = {
            1+4+8, 1+4+9, 1+5+8, 1+5+9, 1+6+8, 1+6+9, 1+7+8, 1+7+9,
            2+4+8, 2+4+9, 2+5+8, 2+5+9, 2+6+8, 2+6+9, 2+7+8, 2+7+9,
            3+4+8, 3+4+9, 3+5+8, 3+5+9, 3+6+8, 3+6+9, 3+7+8, 3+7+9
        };

        test::forward_constant(
            ans,
            comprehension_detail::make_nested0(
                rng1,
                comprehension_detail::make_nested(
                    rng2,
                    comprehension_detail::make_nested(
                        rng3,
                        comprehension_detail::make_to_unit(bll::_1 + bll::_2 + bll::_3, bll::_1 > 0) // 3ary
                    ) // 2ary
                ) // 1ary
            ) ()
        );
    }
}

#if 0

boost::proto::exprns_::expr<
    boost::proto::tag::comma,
    boost::proto::argsns_::args2<
        boost::proto::refns_::ref_<
            const boost::proto::exprns_::expr<
                boost::proto::tag::bitwise_or,
                boost::proto::argsns_::args2<
                    boost::proto::refns_::ref_<
                        const boost::proto::exprns_::expr<
                            boost::proto::tag::plus,
                            boost::proto::argsns_::args2<
                                boost::proto::refns_::ref_<
                                    const boost::proto::exprns_::expr<
                                        boost::proto::tag::terminal,
                                        boost::proto::argsns_::args0<
                                            pstade::oven::comprehension_detail::placeholder1
                                        >
                                    >
                                >,
                                boost::proto::refns_::ref_<
                                    const boost::proto::exprns_::expr<
                                        boost::proto::tag::terminal,
                                        boost::proto::argsns_::args0<
                                            pstade::oven::comprehension_detail::placeholder2
                                        >
                                    >
                                >
                            >
                        >
                    >,
                    boost::proto::refns_::ref_<
                        const boost::proto::exprns_::expr<
                            boost::proto::tag::less_equal,
                            boost::proto::argsns_::args2<
                                boost::proto::refns_::ref_<
                                    const boost::proto::exprns_::expr<
                                        boost::proto::tag::terminal,
                                        boost::proto::argsns_::args0<
                                            pstade::oven::comprehension_detail::placeholder1
                                        >
                                    >
                                >,
                                boost::proto::exprns_::expr<
                                    boost::proto::tag::terminal,
                                    boost::proto::argsns_::args0<std::string &>
                                >
                            >
                        >
                    >
                >
            >
        >,
        boost::proto::refns_::ref_<
            const boost::proto::exprns_::expr<
                boost::proto::tag::less_equal,
                boost::proto::argsns_::args2<boost::proto::refns_::ref_<const boost::proto::exprns_::expr<boost::proto::tag::terminal,boost::proto::argsns_::args0<pstade::oven::comprehension_detail::placeholder2>>>,boost::proto::exprns_::expr<boost::proto::tag::terminal,boost::proto::argsns_::args0<std::string &>>>>>>>,

boost::proto::exprns_::expr<
    boost::proto::tag::bitwise_or,
    boost::proto::argsns_::args2<
        boost::proto::refns_::ref_<
            const boost::proto::exprns_::expr<
                boost::proto::tag::plus,
                boost::proto::argsns_::args2<
                    boost::proto::refns_::ref_<
                        const boost::proto::exprns_::expr<
                            boost::proto::tag::terminal,
                            boost::proto::argsns_::args0<
                                pstade::oven::comprehension_detail::placeholder1
                            >
                        >
                    >,
                    boost::proto::refns_::ref_<
                        const boost::proto::exprns_::expr<
                            boost::proto::tag::terminal,
                            boost::proto::argsns_::args0<
                                pstade::oven::comprehension_detail::placeholder2
                            >
                        >
                    >
                >
            >
        >,
        boost::proto::refns_::ref_<
            const boost::proto::exprns_::expr<
                boost::proto::tag::comma,
                boost::proto::argsns_::args2<
                    boost::proto::refns_::ref_<
                        const boost::proto::exprns_::expr<
                            boost::proto::tag::comma,
                            boost::proto::argsns_::args2<
                                boost::proto::refns_::ref_<
                                    const boost::proto::exprns_::expr<
                                        boost::proto::tag::less_equal,
                                        boost::proto::argsns_::args2<
                                            boost::proto::refns_::ref_<
                                                const boost::proto::exprns_::expr<
                                                    boost::proto::tag::terminal,
                                                    boost::proto::argsns_::args0<
                                                        pstade::oven::comprehension_detail::placeholder1
                                                    >
                                                >
                                            >,
                                            boost::proto::exprns_::expr<
                                                boost::proto::tag::terminal,
                                                boost::proto::argsns_::args0<
                                                    std::string &
                                                >
                                            >
                                        >
                                    >
                                >,
                                boost::proto::refns_::ref_<
                                    const boost::proto::exprns_::expr<
                                        boost::proto::tag::less_equal,
                                        boost::proto::argsns_::args2<
                                            boost::proto::refns_::ref_<
                                                const boost::proto::exprns_::expr<
                                                    boost::proto::tag::terminal,
                                                    boost::proto::argsns_::args0<
                                                        pstade::oven::comprehension_detail::placeholder2
                                                    >
                                                >
                                            >,
                                            boost::proto::exprns_::expr<
                                                boost::proto::tag::terminal,
                                                boost::proto::argsns_::args0<
                                                    std::string &
                                                >
                                            >
                                        >
                                    >
                                >
                            >
                        >
                    >,
                    boost::proto::exprns_::expr<
                        boost::proto::tag::terminal,
                        boost::proto::argsns_::args0<
                            int &
                        >
                    >
                >
            >
        >
    >
>,
pstade::oven::comprehension_detail::Grammar
>
#endif
