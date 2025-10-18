parMax :: (Double, Double) -> Double
parMax p
    | fst p >= snd p = fst p
    | otherwise = snd p

parMax' :: (Double, Double) -> Double
parMax' p = max (fst p) (snd p)

parMax'' :: (Double, Double) -> Double
parMax'' (l, r) = max l r