fib :: Int -> Int
fib n = fib' n 2 0 1
 where
    fib' :: Int -> Int -> Int -> Int -> Int 
    fib' n k a b  
        | n == k = a + b
        | otherwise = fib' n (k+1) b (a+b)