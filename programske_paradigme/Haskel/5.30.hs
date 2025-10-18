sledbenici :: [Int] -> [Int]
sledbenici l = map (+1) (filter (>= 0) l)

sledbenici' :: [Int] -> [Int]
sledbenici' = map (+1) . filter (>= 0)