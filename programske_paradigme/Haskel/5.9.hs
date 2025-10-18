prost :: Int -> Bool
prost n = prostTest n 2
 where 
    prostTest :: Int -> Int -> Bool
    prostTest n k
      | n == k = True
      | mod n k == 0 = False
      | otherwise = prostTest n (k+1)