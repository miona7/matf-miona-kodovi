import Data.Char (isUpper, isLower)

uzastopni :: [Char] -> [Char]
uzastopni [] = []
uzastopni l 
    | isUpper (head l) = takeWhile isUpper l
    | otherwise = takeWhile isLower l

sekvence :: [Char] -> [Int]
sekvence [] = []
sekvence l = u : ostatak
    where 
        u = length (uzastopni l)
        ostatak = sekvence (drop u l)
    -- | isUpper (head l) = length (takeWhile isUpper l) : sekvence (dropWhile isUpper l)
    -- | otherwise = length (takeWhile isLower l) : sekvence (dropWhile isLower l)

listaSekvenci :: [[Char]] -> [[Int]]
listaSekvenci = map sekvence
--listaSekvenci [] = []
--listaSekvenci (x:xs) = sekvence x : listaSekvenci xs 