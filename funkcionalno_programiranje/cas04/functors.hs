module Main where

import Prelude hiding (Maybe, Nothing, Just, Either, Left, Right)
import qualified Data.Char as Ch
import Data.Bifunctor

main :: IO ()
main = do 
    putStrLn "hello functors"

-- funktor je bilo sta sto implementira fju fmap ili <$>
-- funktor ima tacno 1 slobodan tipski parametar

stringToUpper :: String -> String
stringToUpper = fmap Ch.toUpper

stringToLower :: String -> String
stringToLower = fmap Ch.toLower

-- pravila
-- 1) fmap id = id
-- 2) fmap (f . g) == fmap f . fmap g


-- primeri funktora

data Maybe m = Nothing | Just m deriving (Show, Eq)

instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just m) = Just (f m)

makeBold :: String -> String
makeBold s = "<b>" ++ s ++ "</b>"

currentUserName :: Maybe String
currentUserName = Just "Miona"

formattedUserName :: Maybe String -> Maybe String
formattedUserName userName = fmap makeBold (fmap stringToUpper userName)

-- ekvivalentno
formattedUserName' :: Maybe String -> Maybe String
formattedUserName' = (fmap makeBold) . (fmap stringToUpper)


data Either a b = Left a | Right b deriving (Show, Eq)

type StrErr s = Either String s

instance Functor (Either a) where
    fmap _ (Left x) = Left x
    fmap f (Right x) = Right (f x)

safeHeadVerbose :: [a] -> StrErr a
safeHeadVerbose [] = Left "The list is empty"
safeHeadVerbose (x:xs) = Right x

maybeToErr :: Maybe a -> StrErr a
maybeToErr Nothing = Left "Unknown error"
maybeToErr (Just x) = Right x

errToMaybe :: StrErr a -> Maybe a
errToMaybe (Left _) = Nothing
errToMaybe (Right x) = Just x

currentUserNameVerbose :: StrErr String
currentUserNameVerbose = Right "Miona"

formattedUserNameVerbose :: StrErr String -> StrErr String
formattedUserNameVerbose = (fmap makeBold) . (fmap stringToUpper)

formattedUserNameUniversal :: Functor f => f String -> f String
formattedUserNameUniversal = (fmap makeBold) . (fmap stringToUpper)

-- ako zelimo da imamo mapiranje nad oba tipa u Either moze da iskoristimo bifunktore
-- bifunktor ima tacno 2 slobodna tipska parametra
-- bifunktor je sve ono sto implementira bimap ili first i second

instance Bifunctor Either where
    bimap f _ (Left x) = Left (f x)
    bimap _ g (Right y) = Right (g y)

    first f (Left x) = Left (f x)
    first _ (Right y) = Right y

    second _ (Left x) = Left x
    second g (Right y) = Right (g y)


-- aplikativi su nivo iznad funktora -> omogucavaju nam da nad podatkom u kutiji primenimo fju koja je i sama u kutiji

-- primer aplikativa

instance Applicative Maybe where
    -- "pakuje" u kutiju
    pure x = Just x 

    -- operator apply
    (<*>) Nothing _ = Nothing
    (<*>) _ Nothing = Nothing
    (<*>) (Just f) (Just x) = Just (f x)
