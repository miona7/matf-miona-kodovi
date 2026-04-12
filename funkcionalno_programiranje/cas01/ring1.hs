module Lib where

-- sakrivamo internu reprezentaciju tj listu u tip Ring
type Ring t = [t] -- samo alias, fje rade cak i ako prosledimo obicnu listu
    -- konstruktor + tipska promenljiva

fromList :: [t] -> Ring t
fromList = id

toList :: Ring t -> [t]
toList = id

switchActive :: Ring t -> Ring t
switchActive [] = []
switchActive [x] = [x]
switchActive (active:next:others) = next:active:others

focusNext :: Ring t -> Ring t
focusNext [] = []
focusNext (x:xs) = xs ++ [x]

focusPrev :: Ring t -> Ring t
focusPrev = reverse . focusNext . reverse

closeWindow :: Ring t -> Ring t
closeWindow = tail 

openWindow :: t -> Ring t -> Ring t
openWindow = (:) 