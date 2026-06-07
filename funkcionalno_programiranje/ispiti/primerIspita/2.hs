module Zad2 where
-- ghc -main-is Zad2 2.hs -o 2

import qualified System.Environment as Sys

-- Zadatak 2:
-- Napisati program koji iz fajla čija je putanja data kao argument 
-- komandne linije, čita brojeve jedan po jedan, svaki u zasebnom redu.
-- Program ispisuje sve brojeve poravnate udesno u odnosu na najduži
-- broj, a zatim podvlaku i sumu svih brojeva
--
-- Na primer, za fajl:
--
-- 1020
-- 10
-- 3
-- 8000
-- 2000
-- 1
--
-- Treba ispisati:
--
--      1020
--        10
--         3
--      8000
--      2000
--         1
--     -----
--     11034

main :: IO ()
main = do 
    -- putStrLn "Srecno"

    (arg:_) <- Sys.getArgs

    text <- readFile arg

    let nums = lines text
    let res = show $ sum' nums
    let n = length res
    
    print' $ transform n nums
    putStrLn $ replicate n '-'
    putStrLn res

print' :: [String] -> IO ()
print' [] = return ()
print' (x:xs) = do
    putStrLn x
    print' xs

transform :: Int -> [String] -> [String]
transform n nums = map (\s -> fill (n - length s) s) nums
    where
        fill k s = replicate k ' ' ++ s

sum' :: [String] -> Int
sum' [] = 0
sum' (x:xs) = (read x :: Int) + sum' xs