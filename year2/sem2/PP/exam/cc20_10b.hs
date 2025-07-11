import Data.IntMap (insert)
class Hashable a where hash :: a -> Int -- nu a fost cerut ^ın rezolvare
instance Hashable Int where hash x = mod x 2 -- nu a fost cerut ^ın rezolvare

data HashSet h a = HS [(h, [a])]
    deriving (Show, Eq)

parseList hash ((h, vals):xs) = if hash == h then vals else parseList hash xs
parseList hash [] = []

values' hash (HS list) = parseList hash list

insertList [] value hash = [(hash, [value])]
insertList (current@(h, vals):xs) value hash = if h == hash then (h, value:vals):xs else current : insertList xs value hash

insert' :: Int -> HashSet Int Int-> HashSet Int Int
insert' value (HS list) = (HS (insertList list value (hash value)))

map' f (HS list) = map g list where
    g (hash, list) = (hash, map f list)

test2 = insert' 5 $ insert' 2 $ insert' 4 $ insert' 8 $ HS []
test3 = map' (+1) $ test2