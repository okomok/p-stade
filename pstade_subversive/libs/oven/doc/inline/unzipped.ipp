std::cout <<
    (
        assign::list_of
            (boost::make_tuple(1,2))
            (boost::make_tuple(2,3))
            (boost::make_tuple(3,4))
            | unzipped
    );

// output> ({1,2,3} {2,3,4})