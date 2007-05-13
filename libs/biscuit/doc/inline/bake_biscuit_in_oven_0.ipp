#include <pstade/oven.hpp>

// ...

BOOST_FOREACH (int i, oven::count_from_to(1, argc)) {

    BOOST_CHECK((
        biscuit::match<xml_grammar::start>(
            oven::file_range<boost::uint8_t>(argv[i]) |
                oven::utf8_decoded<boost::uint32_t>()
        )
    ));

}