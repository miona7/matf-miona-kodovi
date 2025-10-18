delioci :: Int -> [Int]
delioci n = filter (\e -> n `mod` e == 0) [x | x <- [1..n]]

prost :: Int -> Bool
prost n = if ( (length (delioci n)) == 2 && (delioci n !! 0) == 1 && (delioci n !! 1) == n ) then True else False

prosti :: Int -> [Int]
prosti n = [x | x <- [1..n], prost x]