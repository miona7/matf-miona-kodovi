sufiksi :: [a] -> [[a]]
sufiksi [] = [[]]
sufiksi (x:xs) = [x:xs] ++ sufiksi xs