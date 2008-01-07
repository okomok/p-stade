#include <pstade/vodka/drink.hpp>

#include <pstade/oven/transformed.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/io.hpp>
#include <pstade/oven/regular.hpp>
#include <iostream>
#include <string>
#include <pstade/egg/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <pstade/oven/cycled.hpp>
#include <pstade/oven/initial_values.hpp>
#include <pstade/oven/zipped_with.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/egg/functional.hpp> // plus
#include <pstade/egg/tuple/pack.hpp>
#include <pstade/egg/to_string.hpp>
#include <pstade/oven/rvalues.hpp>
#include <pstade/oven/const_refs.hpp>
#include <pstade/egg/bll/string.hpp>


namespace lambda = boost::lambda;
using namespace pstade::oven;
using lambda::_1;


std::string f(std::string s, int n)
{
    return s.empty() ? pstade::egg::to_string(n) : s;
}


int main()
{
    std::cout << (
        counting(1, 101) |
            transformed(regular(
                lambda::if_then_else_return(!(_1 % 15),
                    lambda::constant(std::string("fizzbuzz")),
                    lambda::if_then_else_return(!(_1 % 5),
                        lambda::constant(std::string("buzz")),
                        lambda::if_then_else_return(!(_1 % 3),
                            lambda::constant(std::string("fizz")),
                            lambda::bind<std::string const>(pstade::egg::to_string, _1)
                        )
                    )
                )
            )));


    // See http://d.hatena.ne.jp/takatoh/20070509/fizzbuzz

    std::cout << '\n';

    std::cout << (
        make_zipped_with(
            pstade::egg::tuple_pack(
                make_zipped_with(
                    pstade::egg::tuple_pack(
                        make_cycled(initial_values(std::string(), "", "Fizz")),
                        make_cycled(initial_values(std::string(), "", "", "", "Buzz"))
                    ),
                    pstade::egg::plus
                )|taken(100)
                 // | const_refs, // no longer needs workaround for boost::zip_iterator
                ,
                counting(1, 101)
            ),
            &f
        ));
}
