#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// UTF8ファイル限定になりましたが、
// Mingwで日本語が扱えるようになりました。


// Visual C++ 2005 Express Edition は、
// 日本語のパスのファイルを開けないようです。


// キーワードのリンクを有効にするときは
// 'cpp_to_hatena::set_hatena_mode(false);'


#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/void.hpp>

#include <pstade/biscuit.hpp>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>
#include "./start.hpp"
#include "./hatena_mode.hpp"


// タブサイズをカスタマイズしてください
//
template< class = void >
struct tabsize :
    boost::mpl::int_<4>
{ };


struct newline_cvter
{
    typedef boost::uint32_t result_type;

    template< class SubRange >
    boost::uint32_t operator()(SubRange rng) const
    {
        using namespace pstade;
        if (biscuit::match<biscuit::wnewline>(rng)) {
            return '\n';
        }
        else {
            if (pstade::oven::distance(rng) == 0)
                BOOST_ASSERT(false);
            BOOST_ASSERT(pstade::oven::distance(rng) == 1);
            return *boost::begin(rng);
        }
    }
};


int main(int argc, char *argv[])
{
    using namespace pstade;
    using namespace biscuit;

    // cpp_to_hatena::set_hatena_mode(false);

    std::cout << "<cpp_to_hatena>";

    BOOST_FOREACH (int i, oven::from_1_to(argc)) {

        try {

            std::string iname(argv[i]);
            std::cout << "<input-file>" << iname << "</input-file>";

            std::string oname = iname + ".xml";
            std::ofstream fout(oname.c_str(), std::ios::binary);
            pstade::require(fout, "good output file: " + oname);

            oven::copy("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"
                "<pre class=\"cpp_source\">"|oven::as_literal, oven::to_stream(fout));

             biscuit::match<
                iteration<cpp_to_hatena::start, cpp_to_hatena::act_line_escape>
            >(
                oven::file_range<boost::uint8_t>(iname)                  // spirit::file_iteratorのペア
                    | pstade::required("non-empty input file: " + iname) // 空のRangeは例外に
                    | oven::utf8_decoded                                 // UTF-8をUTF-32に変換
                    | biscuit::tokenized< or_<wnewline, any> >()         // 改行とそうでないものに分ける
                    | oven::transformed(::newline_cvter())               // 改行なら'\n'に変換する
                    | oven::tab_expanded(::tabsize<>::value)             // タブを空白にする
                    | oven::memoized,                                    // 速くするためキャッシュする
                oven::to_utf8_encoder(oven::to_stream(fout))|to_reference// UTF-8に戻して出力
            );

            oven::copy("</pre>"|oven::as_literal, oven::to_stream(fout));

            std::cout << "<output-file>" << oname << "</output-file>";

        }
        catch (std::exception& err) {
            std::cout << "<error>" << err.what() << "</error>\n";
            return 0; // continue;
        }

    } // BOOST_FOREACH

    return std::cout << "</cpp_to_hatena><press-any-key/>", pstade::pause();
}
