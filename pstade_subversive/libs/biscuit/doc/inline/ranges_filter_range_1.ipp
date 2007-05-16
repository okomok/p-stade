BOOST_CHECK((
    biscuit::match< chseq<'x','y','z'> >(
        biscuit::make_filter_range< not_< chset<'&','.','%'> > >(
            biscuit::make_filter_range< not_<space> >(
                biscuit::make_filter_range< not_<digit> >(
                    oven::make_null_terminate_range("x & 4 y . 125 %  z")
                )
            )
        )
    )
));