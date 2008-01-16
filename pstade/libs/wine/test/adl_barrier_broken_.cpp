
#include <boost/detail/lightweight_test.hpp>
#include <boost/noncopyable.hpp>


// Note: overloaded operator too incurs ambiguity in vc-9.0.


namespace xxx {
    namespace nested {
        struct aaa {};
    }
    void begin(nested::aaa) {}
}

namespace nnn {
    void begin(xxx::nested::aaa) {}
}

namespace boost {
    template<class X>
    void the_end(X& x) {}
}

namespace my {
    struct ccc : private boost::noncopyable {};
    template<class X>
    void the_end(X& x) {}
}

int main()
{
    {
        using namespace nnn;
        xxx::nested::aaa a;
        begin(a); // ambiguous error in msvc-9.0
    }
    {
        my::ccc c;
        the_end(c); // ambiguous error in msvc-9.0
    }

    return boost::report_errors();
}
