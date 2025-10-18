sumaKvadrata :: Int -> Integer
sumaKvadrata n
 | n == 1 = 1
 | otherwise = (sumaKvadrata (n-1)) + (toInteger (n * n))