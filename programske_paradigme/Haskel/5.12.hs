izDekadne :: Int -> Int -> Int
izDekadne x osn = if x == 0 then 0 else izDekadne (x `div` osn) osn * 10 + (x `mod` osn) 

uDekadnu :: Int -> Int -> Int
uDekadnu x osn = if x == 0 then 0 else uDekadnu (x `div` 10) osn * osn + (x `mod` 10)