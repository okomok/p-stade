
#include "atlstr.h"


#define PSTADE_BISCUIT_DEBUG_OUT std::wcout
// パーサーデバッグ出力
#include <pstade/biscuit.hpp>

#include <pstade/oven.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/assign.hpp>
#include <boost/cstdint.hpp> // for uintXXX_t

#include <vector>

using namespace std;
using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_SET_LITERAL(nengo, L"元年月日明治大正昭和平成")


struct headpattern :
    seq<
        sol,
        repeat<or_<wchrng<L'０',L'９'>, nengo>, 2>,
        plus< not_< wchset<L' ',L'　',L'（'> > >
    >
{ };


struct bb_action
{
    template< class SubRange >
        void operator()(SubRange rng, std::wostream& out)
    {
	    out <<"<B>"<<oven::copy_range<std::wstring>(rng)<<"</B>";
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
    locale::global(locale("japanese"));// windows 日本語 外部S-JIS 内部 wchar_t

    biscuit::iterate< actor<headpattern, bb_action> >(
        oven::make_istream_range(wcin)|oven::multi_passed,
        wcout, biscuit::output_action()
    );

    return 0;
}
