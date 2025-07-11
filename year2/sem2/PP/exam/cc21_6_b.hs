instance (Num a, Enum a, Ord b) => Ord (a -> b) where
    f <= g =
        let
            nums = [0..100]
            f_nums = map f nums
            g_nums = map g nums
            check (x:xs) (y:ys) = if x > y then False else check xs ys
            check [] _ = True
        in
            check f_nums g_nums