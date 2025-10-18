broj :: [Int] -> Int
broj [] = 0
broj (x:xs) = x * (10^(length xs)) + broj xs 

brojObrnut :: [Int] -> Int
brojObrnut l = broj (obrni l)
    where 
        obrni l = foldl azuriraj [] l
        azuriraj ak e = e : ak