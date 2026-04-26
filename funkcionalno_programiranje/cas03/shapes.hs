-- pravimo nove strukture podataka
data Circle = MkCircle { r :: Float }

data Rectangle = MkRectangle { a :: Float, b :: Float }

-- definisemo "interfejs" -> definisemo grupu tipova s koju cemo zvati Shape
-- svaki tip koji zeli da bude Shape mora da implementira area i circumference
class Shape s where
    area :: s -> Float
    circumference :: s -> Float

instance Shape Circle where
    area x = r' * r' * pi where r' = r x
    circumference x = 2 * r' * pi where r' = r x

instance Eq Circle where
    (==) c1 c2 = (r c1) == (r c2)

instance Show Circle where
    show c = "(r = " ++ show (r c) ++ ")"


instance Shape Rectangle where
    area x = a' * b' 
        where 
            a' = a x
            b' = b x
    circumference (MkRectangle a b) = 2 * (a + b) 
                -- pattern matching

instance Eq Rectangle where
    (==) r1 r2 = ((a r1) == (a r2) && (b r1) == (b r2)) || ((a r1) == (b r2) && (b r1) == (a r2))  

instance Show Rectangle where
    show r = "(a = " ++ show (a r) ++ ", b = " ++ show (b r) ++ ")"