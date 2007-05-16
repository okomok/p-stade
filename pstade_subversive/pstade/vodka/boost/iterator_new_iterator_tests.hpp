

// missing headers
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>


#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable: 4100) // unreferenced formal parameter
    #pragma warning(disable: 4189) // local variable is initialized but not referenced
    #include <boost/iterator/new_iterator_tests.hpp>
    #pragma warning(pop)
#endif
