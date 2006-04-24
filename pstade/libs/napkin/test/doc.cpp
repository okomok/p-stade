#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <pstade/napkin.hpp>
#include <windows.h>
#include <pstade/napkin/dout.hpp>
#include <boost/format.hpp>


void introduction()
{
    using namespace pstade;

    napkin::ostream os;

    os.reset(std::cout);
    os << "to cout:" << 1 << '\n';

#if !defined(__MINGW32__)
    os.reset(std::wcout);
    os << "to wcout";
#endif

    std::ofstream fout("log.txt");
    os.reset(fout);
    os << "to file:" << 3.14 << '\n';

    os << boost::format("%2% %1%")
        % "boost" % "using";

    std::stringstream sout;
    os.reset(sout);
    os << "to string stream:" << 'x';

    os.reset(napkin::dout);
    os << "to debugger:" << sout.str();

    os.reset(napkin::nout);
    os << "to trash box";

    std::vector<char> vout;
    os.reset(vout);
    os << "to sequence";

    std::string strout;
    os.reset(strout);
    os << "to string";
}


void classes_ostream()
{
    using namespace pstade;

    napkin::ostream os1(std::cout);
    os1 << "constructor style\n";

    napkin::ostream os2;
    os2.reset(std::cout);
    os2 << "reset style\n";

    napkin::ostream os3 = os2;
    os3 << "copy\n";

    napkin::ostream os4;
    os4.reset(os3);
    os4 << "os3 is StringOutputable.\n";
}


#include <pstade/if_debug.hpp>
#include <pstade/comma_protect.hpp>

void remove_side_effects()
{
    using namespace std;
    using namespace pstade;

    PSTADE_IF_DEBUG (
        napkin::ostream os;
    )

    PSTADE_IF_DEBUG (
        os.reset(cout);
        os << "Removed under release compilation\n";
    )

    // When you need comma out of ()
    PSTADE_IF_DEBUG (
        comma_protect<void(basic_ofstream< char, char_traits<char> >)>::type fout("debug.log");
        os.reset(fout);
        os << "'#if !defined(NDEBUG)' is much easier!";
    )
}


#include <iostream>
#include <pstade/napkin.hpp>
using namespace pstade;

void quick_start()
{
    napkin::ostream os(std::cout);
    os << "hello, napkin\n";
}


int test_main(int, char*[])
{
    ::introduction();
    ::quick_start();
    ::classes_ostream();
    ::remove_side_effects();

    return 0;
}
