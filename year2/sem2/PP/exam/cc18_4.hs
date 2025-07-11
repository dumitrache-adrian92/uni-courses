f x y z = x . y z

class Composable t where
    compose :: (b -> t c) -> (a -> t b) -> (a -> t c)

instance Composable Maybe where
    compose f g a = case g a of
        Nothing -> Nothing
        Just b -> f b