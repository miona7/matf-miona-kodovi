data Zivotinja = Pas | Macka | Papagaj deriving Show

data Ljubimac = MkLjubimac { ime :: String
                           , godine :: Int
                           , tip :: Zivotinja
                           }
                           deriving Show