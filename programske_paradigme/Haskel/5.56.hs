glava :: [a] -> Maybe a
glava l 
    | null l = Nothing
    | otherwise = Just (head l)

glava' :: [a] -> Maybe a
glava' [] = Nothing
glava' (x:_) = Just x

rep :: [a] -> Maybe [a]
rep [] = Nothing
rep (_:xs) = Just xs