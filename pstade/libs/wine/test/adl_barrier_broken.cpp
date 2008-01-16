
namespace xxx {
    namespace nested {
        struct aaa {};
    }
    void begin(nested::aaa) {}
}

namespace nnn {
    void begin(xxx::nested::aaa) {}
}

int main()
{
    {
        using namespace nnn;
        xxx::nested::aaa a;
        begin(a); // ambiguous error in msvc-9.0
    }
}
