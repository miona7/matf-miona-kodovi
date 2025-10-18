glava :: [a] -> a
glava (x:_) = x

rep :: [a] -> [a]
rep (_:xs) = xs

glava1 = head
rep1 = tail