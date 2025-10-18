prosekOdlicni :: [[Int]] -> Double
prosekOdlicni l =
    let odlicni = filter (\x -> prosek x >= 4.5) l
        proseci = map prosek odlicni
        in if null proseci then 0.0 else izracunaj proseci
    where
        prosek uc = fromIntegral (sum uc) / fromIntegral (length uc)
        izracunaj p = sum p / fromIntegral (length p)


prosekOdlicni' :: [[Int]] -> Double
prosekOdlicni' l = prosek (filter (>= 4.5) (map prosek l))
    where
        prosek uc = realToFrac (sum uc) / fromIntegral (length uc)