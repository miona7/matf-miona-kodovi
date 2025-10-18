glava :: [a] -> Either String a
glava [] = Left "Lista je prazna"
glava (x:_) = Right x

rep :: [a] -> Either String [a]
rep [] = Left "Lista je prazna"
rep (_:xs) = Right xs

