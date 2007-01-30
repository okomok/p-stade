std::cout <<
    (
        boost::make_tuple(
            assign::list_of(1)(2)(3),
            assign::list_of(2)(3)(4)
        )
            | zipped
    );

// output> (1 2)(2 3)(3 4)