#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional>
#include <iostream>
#include <string>
#include <stack>
#include <pstade/lexical_cast.hpp>
#include <pstade/biscuit.hpp>
#include <pstade/oven/copy_range.hpp>


// See: http://www.boost.org/libs/spirit/example/fundamental/calc_debug.cpp
// Note: I did changed name calculator to calculator_debug, for unknown troubles.


namespace calculator_debug 
{
    namespace biscuit = pstade::biscuit;
    namespace oven = pstade::oven;
    using namespace biscuit;

    struct push_int
    {
        template< class Range >
        void operator()(Range& rng, std::stack<long>& eval)
        {
            std::string s = rng|oven::copied;
            long n = s|pstade::lexicalized; // or std::strtol(chseq, 0, 10);
            eval.push(n);
            std::cout << "push\t" << long(n) << std::endl;
        }
    };

    template< class Function >
    void do_op(Function op, std::stack<long>& eval)
    {
        long rhs = eval.top();
        eval.pop();
        long lhs = eval.top();
        eval.pop();

        std::cout << "popped " << lhs << " and " << rhs << " from the stack. ";
        std::cout << "pushing " << op(lhs, rhs) << " onto the stack.\n";
        eval.push(op(lhs, rhs));
    }

    struct do_add
    {
        template< class Range >
        void operator()(Range&, std::stack<long>& eval)
        { do_op(std::plus<long>(), eval); }
    };

    struct do_subt
    {
        template< class Range >
        void operator()(Range&, std::stack<long>& eval)
        { do_op(std::minus<long>(), eval); }
    };

    struct do_mult
    {
        template< class Range >
        void operator()(Range&, std::stack<long>& eval)
        { do_op(std::multiplies<long>(), eval); }
    };

    struct do_div
    {
        template< class Range >
        void operator()(Range&, std::stack<long>& eval)
        { do_op(std::divides<long>(), eval); }
    };

    struct do_negate
    {
        template< class Range >
        void operator()(Range&, std::stack<long>& eval)
        {
            long lhs = eval.top();
            eval.pop();

            std::cout << "popped " << lhs << " from the stack. ";
            std::cout << "pushing " << -lhs << " onto the stack.\n";
            eval.push(-lhs);
        }
    };

    struct integer;
    struct factor;
    struct term;
    struct expression;

    struct start : debugger<start,
        expression
    >
    { };

    struct integer : debugger<integer,
        actor< plus<digit>, push_int >
    >
    { };

    struct factor : debugger<factor,
        or_<
            integer,
            seq< chseq<'('>, expression, chseq<')'> >,
            actor< seq< chseq<'-'>, factor >, do_negate >,
            seq< chseq<'+'>, factor >
        >
    >
    { };

    struct expression : debugger<expression,
        seq<
            term,
            star<
                or_<
                    actor< seq< chseq<'+'>, term >, do_add >,
                    actor< seq< chseq<'-'>, term >, do_subt >
                >
            >
        >
    >
    { };
    
    struct term : debugger<term,
        seq<
            factor,
            star<
                or_<
                    actor< seq< chseq<'*'>, factor >, do_mult >,
                    actor< seq< chseq<'/'>, factor >, do_div >
                >
            >
        >
    >
    { };
}


int main()
{
    using namespace pstade;

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tDebugging Expression parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type an expression...or [q or Q] to quit\n\n";

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str[0] == 'q' || str[0] == 'Q')
            break;

        biscuit::filter_range< biscuit::not_<biscuit::space>, std::string > rng(str);
        std::stack<long> eval;
        bool ok = biscuit::match< calculator_debug::start >(rng, eval);

        if (ok && !eval.empty()) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << eval.top() << std::endl;
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
