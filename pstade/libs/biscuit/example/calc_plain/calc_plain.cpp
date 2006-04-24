#include <pstade/vodka/begin.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <iostream>
#include <string>


namespace calculator
{
    using namespace pstade;
    using namespace biscuit;

    struct do_int
    {
        void operator()(boost::sub_range<std::string> rng, null_state_type)
        {
            std::cout
                << "PUSH("
                << oven::sequence_cast<std::string>(rng)
                << ')' << std::endl;
        }
    };

    struct do_add
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "ADD\n"; }
    };

    struct do_subt
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "SUBTRACT\n"; }
    };

    struct do_mult
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "MULTIPLY\n"; }
    };

    struct do_div
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "DIVIDE\n"; }
    };

    struct do_neg
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "NEGATE\n"; }
    };

    struct start;
    struct expression;
    struct term;
    struct factor;

    struct start :
        identity<expression>
    { };

    struct expression :
        seq<
            term,
            star<
                or_<
                    actor< seq< chseq<'+'>, term >, do_add >,
                    actor< seq< chseq<'-'>, term >, do_subt >
                >
            >
        >
    { };

    struct term :
        seq<
            factor,
            star<
                or_<
                    actor< seq< chseq<'*'>, factor >, do_mult >,
                    actor< seq< chseq<'/'>, factor >, do_div >
                >
            >
        >
    { };

    struct factor :
        or_<
            actor< plus<digit>, do_int >,
            seq< chseq<'('>, expression, chseq<')'> >,
            actor< seq< chseq<'-'>, factor >, do_neg >,
            seq< chseq<'+'>, factor >
        >
    { };
} // namespace calculator

int main()
{
    using namespace pstade;

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tExpression parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type an expression...or [q or Q] to quit\n\n";

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str[0] == 'q' || str[0] == 'Q')
            break;

        bool ok = biscuit::match<calculator::start>(str);

        if (ok) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "-------------------------\n";
        }
        else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";

    return 0;
}
