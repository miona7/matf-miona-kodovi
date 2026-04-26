-- truthiness -> bilo koji podatak moze da se posmatra kao True ili False bilo da je Bool ili ne

-- interfejs
class YesNo a where
    yesno :: a -> Bool

instance YesNo Int where
    yesno 0 = False
    yesno _ = True

instance YesNo [a] where
    yesno [] = False
    yesno _ = True

instance YesNo Bool where
    yesno = id -- id fja -> vraca ono sto je dobila

instance YesNo (Maybe a) where
    yesno Nothing = False
    yesno _ = True

        -- ogranicenje -> argument moze biti bilo koji tip sve dok ono spada u YesNo
yesNoIf :: (YesNo y) => y -> a -> a -> a
yesNoIf val yesRes noRes = if yesno val then yesRes else noRes