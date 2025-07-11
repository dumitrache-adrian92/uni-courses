data Trie = Root { getChildren :: [Trie] }
            | Node {
                getC :: Char,
                getChildren :: [Trie]
                }
            deriving (Show, Eq)

emptyTrie = Root []

canBeFollowedBy c node = elem c $ map getC (getChildren node)

getSubtreeFor c node = let
                        l = filter (\x -> getC x == c) (getChildren node)
                    in
                        if null l then undefined else head l

addWord (x:xs) node = if canBeFollowedBy x node then addWord xs (getSubtreeFor x node) else addWord (x:xs)