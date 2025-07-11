xs([1, 2, 3]).
yss([[1, 4], [1, 3, 2], [4]]).

findall(Ys,
        (yss(Yss), xs(Xs), member(Ys, Yss),
            (forall(member(Y, Ys), member(Y, Xs));
             forall(member(Y, Ys), \+member(Y, Xs)))
            ),
        Result).