#include <pstade/debug.hpp> // for the macros

void remove_side_effects()
{
    using namespace std;
    using namespace pstade;

    napkin::ostream os;

    PSTADE_DEBUG_EXPR(os).reset(cout);
    PSTADE_DEBUG_EXPR(os) << "Removed under release compilation\n";

    PSTADE_DEBUG_BLOCK {
        basic_ofstream< char, char_traits<char> > fout("debug.log");
        os.reset(fout);
        os << "'#if !defined(NDEBUG)' is easier!?";
    }
}
