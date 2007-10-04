#include <pstade/if_debug.hpp>
#include <pstade/unparenthesize.hpp>

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
        PSTADE_UNPARENTHESIZE((basic_ofstream< char, char_traits<char> >))
        fout("debug.log");
        os.reset(fout);
        os << "'#if !defined(NDEBUG)' is much easier!";
    )
}