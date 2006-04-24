#include <pstade/oven.hpp>

// ...

BOOST_FOREACH (int i, oven::one_to(argc)) {

    BOOST_CHECK((
        biscuit::match<xml_grammar::start>(
            oven::file_range<boost::uint8_t>(argv[i]) |
                oven::utf8_decoded<boost::uint32_t>()
        )
    ));

}