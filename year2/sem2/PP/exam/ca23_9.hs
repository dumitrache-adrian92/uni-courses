import Control.Monad.Trans.Accum (look)
data Term = Const String | Var String
    deriving (Eq, Show)
data Sentence = Atom String [Term]
type Substitution = [(String, Term)]

subst = [("X", Var "Y"), ("Y", Const "c")]

lookup::Substitution -> Term -> Term
lookup subst v@(Var x) = foldr (\(name, term) acc -> if x == name then term else acc) v subst
lookup _ term = term

lookupIterate subst term = iterate (Main.lookup subst) term

lookupEnd subst term =
    let
        stream = lookupIterate subst term
        shiftedStream = tail stream
        pairedUp = zip stream shiftedStream
    in
        fst $ head $ filter (\(x, y) -> x == y) pairedUp

unifyTerms subst term1 term2 =
    let
        stream = lookupIterate subst term1
        lastElement = lookupEnd subst term1
    in
        if (head $ filter (\x -> x == term2 || x == lastElement) stream) == term2 then True else False

unifySentences subst (Atom name1 terms1) (Atom name2 terms2) =
            name1 == name2 && length terms1 == length terms2 &&
            and (zipWith (unifyTerms subst) terms1 terms2)