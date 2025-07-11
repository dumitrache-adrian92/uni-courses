instance (Num a, Enum a, Show b) => Show (a->b) where
    show f =
        let
            nums = [1..10]
            f_nums = map f nums
            string = foldl (\acc s -> acc ++ show s) "" f_nums
        in
            string