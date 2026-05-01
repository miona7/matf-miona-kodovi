module Main where

import Prelude hiding (Maybe, Nothing, Just, Either, Left, Right)

main :: IO ()
main = do 
    putStrLn "hello applicatives"

data Maybe m = Nothing | Just m deriving (Show, Eq)

instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just m) = Just (f m)

instance Applicative Maybe where
    pure x = Just x 

    (<*>) Nothing _ = Nothing
    (<*>) _ Nothing = Nothing
    (<*>) (Just f) (Just x) = Just (f x)

maybeResult = pure (+) <*> (Just 5) <*> (Just 4)