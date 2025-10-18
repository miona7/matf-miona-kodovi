parOdListi :: [String] -> [Int] -> [(String, Int)]
parOdListi [] _ = []
parOdListi _ [] = []
parOdListi (x:xs) (y:ys) = (x, y) : parOdListi xs ys