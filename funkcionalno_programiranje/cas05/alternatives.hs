import Prelude hiding (Maybe, Nothing, Just)
import Control.Applicative

data Maybe a = Nothing | Just a deriving (Show, Eq)

instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just x) = Just (f x)

instance Applicative Maybe where
    pure = Just 

    (<*>) Nothing _ = Nothing
    (<*>) _ Nothing = Nothing
    (<*>) (Just f) (Just x) = Just (f x)

instance Alternative Maybe where
    empty = Nothing

    (<|>) l Nothing = l
    (<|>) Nothing r = r