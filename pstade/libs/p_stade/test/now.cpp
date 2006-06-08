
#include <pstade/vodka/drink.hpp>
#include <pstade/biscuit.hpp>
#include <pstade/oven/sequence_cast.hpp>

#include <sstream>
//#include <boost/test/unit_test.hpp>
//#include <boost/test/minimal.hpp>
//#include <boost/range.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>
//#include <boost/regex.hpp>


using namespace std;
using namespace pstade;
using namespace biscuit;


const wstring wtext(L"＜/＊ Hello, だんだん Biscuit! >");
const string text("</＊ Hello, だんだん Biscuit! >");

//string ww( caps[0].begin(), caps[0].end()); // iterator_range → string 不 
//cout << ww<<endl;
//wstring www( wcaps[0].begin(), wcaps[0].end());
//wcout << www <<endl;

#include <pstade/biscuit/parser/utility/symbol.hpp>
PSTADE_BISCUIT_SYMBOL(hello, "hello")
PSTADE_BISCUIT_SYMBOL(bye, "bye")
PSTADE_BISCUIT_SYMBOL(wbye, L"漢字かなbye")
struct ff : debugger<ff,
     	bye
> { };

int wmain()
{
  locale::global(locale("japanese"));// windows 日本語 外部S-JIS 内部wchar_t

  //biscuit::debugger_reset_ostream(std::cout);

//wcout << biscuit::match<hello>("hello") ;
//wcout << biscuit::match<bye>("bye") ;
  wcout  << biscuit::match<ff>(std::string("bye")) ;// debugger は wchar_t 未対応
//  struct ff: "2845023383123631239498121101"     十進数です ▲  ▲
//  /struct ff: ""
//  1      ＜＜＜＜ パースは正常らしい

//
//cout << oven::sequence_cast<string>(rng); // range → string 不調
//wcout << biscuit::search<bye>(L"--bye") ;


   return 0;
}