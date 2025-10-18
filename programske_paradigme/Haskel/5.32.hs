module Lib where

    type Tacka = (Float, Float)
    type Putanja = [Tacka]

    tacka :: Float -> Float -> Tacka
    tacka x y = (x, y)

    kp :: Tacka
    kp = (0.0, 0.0)

    putanja :: [Tacka] -> Putanja
    putanja p = p

    duzinaPutanje :: Putanja -> Int
    duzinaPutanje = length

    translirajTacku :: Tacka -> Int -> Int -> Tacka
    translirajTacku t dx dy = tacka (x + fromIntegral dx) (y + fromIntegral dy)
        where 
            x = fst t
            y = snd t

    rastojanje :: Tacka -> Tacka -> Float
    rastojanje (x1, y1) (x2, y2) = sqrt ( (x1-x2)^2 + (y1-y2)^2 )

    uKrugu :: Float -> [Tacka] -> [Tacka]
    uKrugu r = filter (\t -> rastojanje t kp < r) 

    translirajPutanju :: Putanja -> Int -> Int -> Putanja
    translirajPutanju putanja dx dy = map (\t -> translirajTacku t dx dy) putanja

    nadovezi :: Tacka -> Putanja -> Putanja
    nadovezi t p = p ++ [t]

    spojiPutanje :: Putanja -> Putanja -> Putanja
    spojiPutanje p1 p2 = p1 ++ p2

    centroid :: [Tacka] -> Tacka
    centroid tacke = tacka prosekX prosekY
        where
            prosekX = prosek (map fst tacke)
            prosekY = prosek (map snd tacke)
            prosek s = sum s / fromIntegral (length s)

    kvadrantTacke :: Tacka -> Int
    kvadrantTacke (x, y)
        | x > 0 && y > 0 = 1
        | x < 0 && y > 0 = 2
        | x < 0 && y < 0 = 3
        | x > 0 && y < 0 = 4
        | otherwise = 0

    kvadrantPutanje :: Putanja -> Int
    kvadrantPutanje p = if istiKvadranti then head kvadranti else 0
        where
            istiKvadranti = all (== head kvadranti) (tail kvadranti)
            kvadranti = map kvadrantTacke p

    tackeUKvadrantu :: Int -> [Tacka] -> [Tacka] 
    tackeUKvadrantu kv = filter (\t -> (==) (kvadrantTacke t) kv)

    tackeVanKvadrantu :: Int -> [Tacka] -> [Tacka] 
    tackeVanKvadrantu kv = filter (\t -> (/=) (kvadrantTacke t) kv)

    maksimumi :: [Tacka] -> (Float, Float)
    maksimumi t = (maksimum x, maksimum y)
        where 
            x = map fst t
            y = map snd t
            maksimum = foldl1 max 

