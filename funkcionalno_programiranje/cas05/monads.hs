import Prelude hiding (Maybe, Nothing, Just)

data Maybe a = Nothing | Just a deriving (Show, Eq)

instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just x) = Just (f x)

instance Applicative Maybe where
    pure = Just 

    (<*>) Nothing _ = Nothing
    (<*>) _ Nothing = Nothing
    (<*>) (Just f) (Just x) = Just (f x)

instance Monad Maybe where
    -- fju return nije neophodno implemtirati jer radi isto sto i pure
    -- return = Just
    -- return = pure

    -- operator bind
    (>>=) Nothing _ = Nothing
    (>>=) (Just x) f = f x

-- zakoni Monada:
-- 1) levi identitet: return x >>= f == f x 
-- 2) desni identitet: m >>= return == m
-- 3) asocijativnost: (m >>= f) >>= g == m >>= (\x -> f x >>= g)
