typedef seq<
    chseq<'/','*'>,
    star_until< any, chseq<'*','/'> >
> c_comment;
