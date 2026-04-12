module Lib where

-- aktivira sledeci prozor -> jedan alt + tab
switchActive :: [t] -> [t]
switchActive [] = []
switchActive [x] = [x]
switchActive (active:next:others) = next:active:others
-- ili switchActive (x:xs) = head xs : x : tail xs

-- povezani alt + tab
focusNext :: [t] -> [t]
focusNext [] = []
focusNext (x:xs) = xs ++ [x]

-- shift + alt + tab
focusPrev :: [t] -> [t]
focusPrev = reverse . focusNext . reverse

-- zatvaranje aktivnog prozora -> alt + f4
closeWindow :: [t] -> [t]
closeWindow = tail -- ovako definisano nije totalna funkcija
-- na sledeci nacin jeste totalna funkcija -> ne baca izuzetak za []
-- closeWindow [] = []
-- closeWindow (x:xs) = xs
-- ili = drop 1 -> radi i za praznu listu

-- otvara novi aktivan prozor
openWindow :: t -> [t] -> [t]
openWindow = (:) -- koristimo operator : kao funkciju
-- ili openWindow x lst = x:lst