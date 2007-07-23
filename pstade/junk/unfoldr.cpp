#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unfoldr.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <utility> // pair
#include <boost/optional/optional.hpp>
#include <string>
#include <pstade/oven/equals.hpp>
#include <boost/lexical_cast.hpp>


struct my_inc
{
    std::string m_to;

    my_inc() { }
    my_inc(std::string to) : m_to(to) { }

    typedef boost::optional<
        std::pair<int, std::string>
    > result_type;

    result_type operator()(std::string const& s) const
    {
        if (s == m_to)
            return result_type(); // the end.

        int i = boost::lexical_cast<int>(s);
        return std::make_pair(i, boost::lexical_cast<std::string>(i+1));
    }
};

struct my_pure_inc :
    my_inc
{
    typedef my_pure_inc is_pure;

    my_pure_inc() : my_inc("10")
    { }
};


boost::optional<std::pair<int, int> >
inc_fun(int i)
{
    if (i == 10)
        return boost::optional<std::pair<int, int> >();

    return std::make_pair(i, i+1);
}


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::single_pass_readable(unfoldr("0", my_inc("10")), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::forward_constant(unfoldr("0", pure(my_inc("10"))), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::forward_constant(unfoldr("0", my_pure_inc()), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::single_pass_readable(unfoldr(0, &::inc_fun), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::forward_constant(unfoldr(0, pure(&::inc_fun)), a);
    }
}
