#include <pstade/vodka/drink.hpp>
#include <pstade/biscuit.hpp>
#include <pstade/oven/copy_range.hpp>
//#include <sstream>
//#include <boost/test/unit_test.hpp>
#include <string>

using namespace std;
using namespace pstade;
using namespace biscuit;

  namespace calculator {
     struct do_r
     {
		template< class CharRange, class Context >
		void operator()(CharRange rng, Context&)
        {
             std::wcout
                 << "PUSH("
                 << oven::copy_range<std::wstring>(rng)
// string → wstring 書き換えが 不調です。
/* c:\Boost\include\boost-1_33_1\boost\range\iterator_range.hpp(68): error  
C2440:
'型キャスト' : 'boost::range_iterator<C>::type' から  
'boost::range_iterator<C>::type' に変換できません。
         with
         [
             C=boost::remove_cv<pstade::biscuit::the_state_class::state<std::string,results_t>::super_t>::type
         ]
         and
         [
             C=boost::remove_cv<std::wstring>::type
         ]
*/
                 << ')' << std::endl;
         }
     };



     struct act_acom :
  actor< seq< chseq<'<'>, star_until<  any, chseq<'>'> > >,do_r >
     { };

        struct start :
         identity<act_acom>
     { };
  }

string text("</ Hello, Biscuit! >");

int wmain()
{
  //locale::global(locale("japanese"));// windows 日本語 外部S-JIS 内部wchar_t

biscuit::match<calculator::start>(text);

  return 0;
/*
// Biscuit はchar と wchar_t を区別する sub_range だから？
// Boost::spirit は 混用できるのに、１文字ずつ const比較iterator だから？

  typedef
  seq< chseq<'<'>, star_until<  any, chseq<'>'> > >
  acom;



  if (biscuit::match<acom,string>(text)) {
     wcout << L"ok -- 成功 しました" <<endl;}
     //...
  typedef
  seq< chseq<'<'>, star_until<  any, chseq<'>'> > >
  wcom;

wstring wtext(L"</＊ Hello, だんだん Biscuit! >");
wstring w2text(L"＜/＊ Hello, だんだん Biscuit! >");

  if (biscuit::match<wcom,wstring>(wtext)) {
     wcout << L"wok -- 成功 しました"<< endl;}
     //...
  typedef
  seq< chseq<L'<'>, star_until<  any, chseq<L'>'> > >
  w2com;
  if (biscuit::match<w2com,wstring>(wtext)) {
     wcout << L"w2ok -- 成功 しました"<< endl;}
     //...
  typedef
  seq< wchseq<L'<'>, star_until<  any, wchseq<L'>'> > >
  w3com;
  if (biscuit::match<w3com,wstring>(wtext)) {
     wcout << L"w3ok -- 成功 しました"<< endl;}
     //...
  typedef
  seq< wchar<L'<'>, star_until<  any, wchar<L'>'> > >
  w4com;
  if (biscuit::match<w4com,wstring>(wtext)) {
     wcout << L"w4ok -- 成功 しました"<< endl;}
     //...
  typedef
  seq< wchseq<L'＜'>, star_until<  any, wchseq<L'>'> > >
  w5com;
  if (biscuit::match<w5com,wstring>(w2text)) {
     wcout << L"w5ok -- 成功 しました"<< endl;}
     //...
  typedef
  seq< wchar<L'＜'>, star_until<  any, wchar<L'>'> > >
  w6com;
  if (biscuit::match<w6com,wstring>(w2text)) {
     wcout << L"w6ok -- 成功 しました"<< endl;}
     //...
typedef
  seq< wchseq<L'＜'>, star_until<  any, wchseq<L'>'> > >
  a2com;
  if (biscuit::match<a2com,wstring>(w2text)) {
     wcout << L"a2ok -- 成功 しました"<< endl;}
     //...








  return 0;
  */
}

  /*
typedef seq<
     wchseq<L'/',L'＊'>,
     star_until< any, wchseq<L'＊',L'/'> >
> c_comment;

struct decorate_action
{
     void operator()(boost::sub_range<wstring> rng, ...)
     {
         wcout << "[" << oven::copy_range<wstring>(rng) << "]";
       //  boost::to_upper(rng);
     }
};
  */

//struct xml_comment :
//    seq<
//        wchseq<L'＜',L'!',L'-',L'-'>,
//        star<
//            or_<
//                minus< any, wchseq<L'-'> >,
//                seq<
//                    wchseq<L'-'>,
//                    minus< any, wchseq<L'-'> >
//                >
//            >
//        >,
//        wchseq<L'-',L'-',L'＞'>
//    >
//{ };
//
//struct xml_comment_action :
//    actor< c_comment, decorate_action >
//{ };
//
//void test_actor()
//{
//    wstring text(L"＜!-- xml comment --＞");
//    std::stringstream out;
//    biscuit::match<xml_comment_action>(text, out) ;
//     oven::equal(out.str(), "[<!-- xml comment -->]") ;
////     oven::equal(text, "<!-- XML COMMENT -->") ;
//}


//test_actor();

//std::stringstream out;
//std::string s0("<!-- xml comment no.1 -->");
//
//match<xml_comment_action>(s0, out);
//
//////BOOST_CHECK( std::string("[<!-- xml comment no.1 -->]") ==
////                                               out.str() );
//
//