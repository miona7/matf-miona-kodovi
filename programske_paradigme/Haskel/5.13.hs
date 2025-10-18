ceoDeo :: Int -> Int
ceoDeo x = floor (sqrt (fromIntegral x))


ceoDeo' :: Int -> Int
ceoDeo' x = nadji 2 x
    where
        nadji k x 
            | k*k > x = k-1
            | otherwise = nadji (k+1) x  