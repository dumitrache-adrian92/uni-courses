import Data.ByteString (intersperse)
instance (Num a, Num b, Show a, Show b, Enum a) => Show (a->b) where
    show f = show $ map (\x -> (x, f x)) [0..5]