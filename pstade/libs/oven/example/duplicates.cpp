#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?STLAlgorithmExtensions/NonUniqueCopy


#include <pstade/oven/tests.hpp>


#include <iostream>
#include <string>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/functional.hpp>
#include <pstade/oven.hpp>
#include <pstade/as.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


template< class BinaryPred >
struct skip_unique
{
    typedef skip_unique is_constant;

    template< class ForwardIter >
    ForwardIter operator()(ForwardIter first, ForwardIter last) const
    {
        ForwardIter next(first);
        while (++next != last) {
            if (m_pred(*first, *next))
                return next;
            else // skip
                first = next;
        }

        return last;
    }

    explicit skip_unique() 
    { }

    explicit skip_unique(BinaryPred const& pred) :
        m_pred(pred)
    { }

private:
    BinaryPred m_pred;
};



template<typename Range>
typename boost::result_of<
    op_make_uniqued(
        typename boost::result_of<
            op_make_dropped(
                typename boost::result_of<
                    op_make_successors(Range&, ::skip_unique<pstade::op_equal_to>)
                >::type,
                int
            )
        >::type
    )
>::type
make_duplicates(Range& rng)
{
    return
        make_uniqued(
            make_dropped(
                make_successors(rng, ::skip_unique<pstade::op_equal_to>(pstade::equal_to)),
                1
            )
        );
}



void test()
{
    std::string src("11223444445");
    std::cout << ::make_duplicates(src);

    BOOST_CHECK( equals(
        ::make_duplicates(std::string("1223444445")|pstade::as_ref),
        std::string("24")
    ) );

    BOOST_CHECK( equals(
        ::make_duplicates(std::string("12234444455")|pstade::as_ref),
        std::string("245")
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
