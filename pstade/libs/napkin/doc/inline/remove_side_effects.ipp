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
        comma_protect<void(basic_ofstream< char, char_traits<char> >)>::type
        fout("debug.log");
        os.reset(fout);
        os << "'#if !defined(NDEBUG)' is much easier!";
    )
}