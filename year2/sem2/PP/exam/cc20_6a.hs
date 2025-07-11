instance (Num a, Enum a, Eq b) => Eq (a -> b) where
    f == g =
        let
            nums = [1..100]
            fn = map f nums
            gn = map g nums
            check (x:xs) (y:ys) = if x == y then 1 + check xs ys else check xs ys
            check [] _ = 0
        in
            check fn gn >= 10