class MyClass c where
    f :: c a -> a

instance MyClass Maybe where
    f lol@(Just x) = x