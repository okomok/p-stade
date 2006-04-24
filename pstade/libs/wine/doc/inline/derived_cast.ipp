#include <pstade/derived_cast.hpp>

// CRTP
template< class Derived >
struct WindowBase
{
    void create()
    {
        pstade::derived_cast<Derived>(*this).create_impl();

        Derived& d = pstade::derived(*this);
        d.create_impl();;
    }
};
