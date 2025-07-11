mul([X | R], [X | T]) :- findall(A, (member(A, R), 0 is X mod A), Divisible),
                            length(Divisible, Len), length(R, Len), !, mul(R, T).
mul([_ | R], T) :- mul(R, T).
mul([], []).

secondMax(L, SecondMax) :- setof(X, member(X, L), Sorted), reverse(Sorted, [_ | [SecondMax | _]]).

p(R, S) :- member(X, R),
    findall(Y, (member(Y, R), Y \= X), T), !, q(X, T, S).
q(X, A, [X|A]). q(X, [A|B], [A|C]) :- q(X, B, C).

% c(alex, celia). c(alex, delia). c(alex, marcel).
% c(barbra, celia). c(barbra, delia). c(barbra, marcel).
% c(delia, faramir). c(delia, george). c(delia, herodot).
% c(erus, faramir). c(erus, george). c(erus, herodot).

frati(X, F) :- findall(B, (c(P, X), c(P, B), X \= B), Pula), sort(Pula, F).

c(alex, celia). c(alex, delia). c(alex, marcel).
c(barbra, celia). c(barbra, delia). c(barbra, marcel).
c(delia, faramir).
c(ion, jenny). c(ion, karl). c(celia, jenny). c(celia, karl).
c(marcel, ninel). c(marcel, octav).

veri(X, V) :- findall(Verik, (c(P, X), c(PP, P), c(PV, Verik), PV \= PP, c(PP, PV), Verik \= X), VMessy), sort(VMessy, V).