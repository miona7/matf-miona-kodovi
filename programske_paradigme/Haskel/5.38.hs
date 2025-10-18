praviDelioci :: Int -> [Int]
praviDelioci x = [y | y <- [1..x-1], x `mod` y == 0]

savrsen :: Int -> Bool
savrsen x = sum (praviDelioci x) == x

savrseni :: Int -> [Int]
savrseni n = [x | x <- [1..n-1], savrsen x]