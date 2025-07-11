data MultiMap k a = MultiMap [(k, [a])]
    deriving (Eq, Show)

lookup' key (MultiMap ((k, vals) : xs)) = if k == key then vals else lookup' key (MultiMap xs)
lookup' key (MultiMap []) = []

removeItem _ []                 = []
removeItem x (y:ys) | x == y    = removeItem x ys
                    | otherwise = y : removeItem x ys

insert' key value m@(MultiMap vals) = if null existing then (MultiMap ((key, [value]) : vals))
                                        else (MultiMap ((key, added) : (removeItem (key, existing) vals)))
        where
            existing = lookup' key m
            added = value : existing

map' f m@(MultiMap vals) = (MultiMap (map g vals))
    where
        g (key, list) = (key, map f list)

test = insert' 2 'z' $ insert' 3 'c' $ insert' 2 'b' $ insert' 1 'a' $ MultiMap []