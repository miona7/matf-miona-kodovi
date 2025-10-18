data Krug = MkKrug { radijus :: Float }

instance Show Krug where
    show k = "Krug r = " ++ show (radijus k)

instance Eq Krug where
    (==) k1 k2 = (radijus k1) == (radijus k2)

data Pravougaonik = MkPravougaonik { a :: Float, b :: Float }

instance Show Pravougaonik where
    show p = "Pravougaonik sa a = " ++ show (a p) ++ " b = " ++ show (b p)

instance Eq Pravougaonik where
    (==) p1 p2 = ((a p1 == a p2) && (b p1 == b p2)) || ((a p1 == b p2) && (b p1 == a p2)) 