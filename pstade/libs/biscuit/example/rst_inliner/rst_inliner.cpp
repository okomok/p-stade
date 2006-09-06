#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// <pre class="literal-block">
// example_algorithms_match.ipp
// </pre>


#include <fstream>
#include <cassert>
#include <string>
#include <boost/range.hpp>

#include "../cpp_to_xhtml/cpp_to_xhtml.hpp"
#include <pstade/biscuit.hpp>
#include <pstade/unused.hpp>


struct on_inline_filename
{
    template< class Range, class UserState >
    void operator()(Range& rng, UserState& out)
    {
        std::string filename(boost::begin(rng), boost::end(rng));
        std::ifstream ifs(filename.c_str());
        assert( ifs.good() );
        std::string text;
        std::getline(ifs, text, '\0');
        tab2space(text, 4);
        if (!match< cpp_to_xhtml::start >(text, out))
        {
            assert(false);
        }
    }
};


struct on_pre_stag
{
    template< class Range, class UserState >
    void operator()(Range& rng, UserState& out)
    {
        pstade::unused(rng);
        out << "<pre class=\"cpp_source\">\n";
    }
};


struct on_pre_etag
{
    template< class Range, class UserState >
    void operator()(Range& rng, UserState& out)
    {
        pstade::unused(rng);
        out << "</pre>\n";
    }
};


struct rst_pre_content :
    star_until< not_< chseq<'<'> >, chseq<'.','i','p','p'> >
{ };


struct rst_pre_stag :
    seq<
        chseq<'<'>, star<space>,
        chseq<'p','r','e'>, plus<space>,
        chseq<'c','l','a','s','s'>, star<space>, chseq<'='>, star<space>,
        seq<
            chseq<'"'>, chseq<'l','i','t','e','r','a','l'>, chseq<'-','b','l','o','c','k'>, chseq<'"'>, star<space>,
            chseq<'>'>, star<space>
        >
    >
{ };


struct rst_pre_etag :
    seq< star<space>, chseq<'<','/','p','r','e','>'> >
{ };


struct rst_pre_element : lazy_actions<
    seq<
        actor< rst_pre_stag,        on_pre_stag >,
        actor< rst_pre_content,     on_inline_filename>,
        actor< rst_pre_etag,        on_pre_etag >
    >
>
{ };


int main(int argc, char *argv[])
{
    if (argc > 1) {
        std::string filename(argv[1]);
        std::ifstream ifs(filename.c_str());
        assert( ifs.good() );
        std::string text;
        std::getline(ifs, text, '\0');

        std::ofstream ofs( (filename + ".html").c_str());
        assert( ofs.good() );

        iterate<rst_pre_element>(text, ofs, output_action());
    }

    pstade::unused(argc, argv);
    return 0;
}
