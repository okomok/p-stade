BOOST_CHECK((
    biscuit::match< repeat< char_<'D'>, 3 > >(
        "abcdabcdabcd" |
            oven::as_c_str |
            biscuit::filtered< not_< char_<'a'> > >() |
            biscuit::filtered< not_< char_<'b'> > >() |
            biscuit::filtered< not_< char_<'c'> > >() |
            oven::transformed(to_upper)
    )
));