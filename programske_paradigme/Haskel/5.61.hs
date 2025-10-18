pozicija :: String -> [String] -> [Int]
pozicija x l = map snd $ filter (\e -> fst e == x) (zip l [0..(length l)])