module Main where

import qualified System.Environment as Sys 
import qualified Data.Map.Strict as Map
import qualified Data.Char as Char 
import qualified Data.List as List 

main :: IO ()
main = do
    (arg:_) <- Sys.getArgs
    
    let n = read arg :: Int
    print n

    putStrLn "unesite tekst:"

    text <- getContents
    print $ process n text 

process :: Int -> String -> String
process n text = 
    let 
        -- reci
        ws = words
            $ map (\c -> if Char.isLetter c then c else ' ')
            $ map Char.toLower text
        
        -- broj pojavljivanja reci
        ws_occ = Map.fromListWith (+) [(w, 1) | w <- ws]

        -- sortirana lista u odnosu na broj pojavljivanja
        sorted_ws_occ = List.sortOn snd $ Map.toList ws_occ

    in unwords $ take n $ map fst $ List.reverse sorted_ws_occ