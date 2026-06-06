import System.Environment as Sys
import Data.Char as Char (toLower, isLetter)
import Data.List as List (sort, group, sortOn)

main :: IO ()
main = do
    (arg:_) <- Sys.getArgs
    let n = read arg :: Int
    print arg
    
    putStrLn "unesite tekst:"

    text <- getContents
    print $ process n text

process :: Int -> String -> String
process n text = unwords 
    $ map fst
    $ take n
    $ reverse
    $ List.sortOn snd
    $ map (\xs -> (head xs, length xs))
    $ List.group
    $ List.sort
    $ words 
    $ map (\c -> if Char.isLetter c then c else ' ') 
    $ map Char.toLower text