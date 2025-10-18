proizvodPrvih :: Num a => Int -> a
proizvodPrvih n 
    | n == 1 = 1
    | otherwise = (fromIntegral n) * proizvodPrvih (n-1)