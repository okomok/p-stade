BOOST_CHECK((
    biscuit::match< chseq<'x','y','z'> >(
        biscuit::make_filter_range< not_< chset<'&','.','%'> > >(
            biscuit::make_filter_range< not_<space> >(
                biscuit::make_filter_range< not_<digit> >(
                    oven::as_c_str("x & 4 y . 125 %  z")
                )
            )
        )
    )
));