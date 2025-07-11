lol([], []).
lol([L | T], [(N, L) | TOut]) :-
    sort(L, L), !, last(L, N), lol(T, TOut).
            %   ^
            %   |
            %   pentru a nu genera solutii cu N = primul element daca am descoperit ca e sortat

lol([[H | T2] | T], [(H, [H | T2]) | TOut]) :- lol(T, TOut).