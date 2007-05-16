struct expression ;
struct group      : seq< char_<'('>, expression, char_<')'> > { };
struct factor     : or_< integer, group > { };
struct term       : seq< factor, star< or_< seq< char_<'*'>, factor >, seq< char_<'/'>, factor > > > > { };
struct expression : seq< term, star< or_< seq< char_<'+'>, term >, seq< char_<'-'>, term > > > > { };
