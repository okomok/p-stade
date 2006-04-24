BOOST_CHECK((
    biscuit::match< repeat< char_<'D'>, 3 > >(
        "abcdabcdabcd" |
            oven::null_terminated |
            biscuit::filtered< not_< char_<'a'> > >() |
            biscuit::filtered< not_< char_<'b'> > >() |
            biscuit::filtered< not_< char_<'c'> > >() |
            oven::transformed(toupper_fun())
    )
));