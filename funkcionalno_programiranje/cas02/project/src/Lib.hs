module Lib ( fromList
           , toList
           , focusNext
           , focusPrev
           , closeWindow
           , openWindow
           ) where -- definicija funkcija -> u zagradi sve ono  sto je javno u ovom modulu

data Ring t = MkRing [t] [t]

fromList :: [t] -> Ring t
fromList lst = MkRing lst []

toList :: Ring t -> [t]
toList (MkRing ls rs) = ls ++ reverse rs

switchActive :: Ring t -> Ring t
switchActive r@(MkRing [] []) = r
switchActive r@(MkRing [_] []) = r
switchActive (MkRing [w] rs) = switchActive (MkRing (w:reverse rs) [])
switchActive (MkRing (active:next:others) rs) = MkRing (next:active:others) rs

focusNext :: Ring t -> Ring t
focusNext r@(MkRing [] []) = r
focusNext r@(MkRing [_] []) = r
focusNext (MkRing [w] rs) = focusNext (MkRing (w:reverse rs) [])
focusNext (MkRing (l:ls) r) = MkRing ls (l:r)

focusPrev :: Ring t -> Ring t
focusPrev r@(MkRing [] []) = r
focusPrev r@(MkRing [_] []) = r
focusPrev (MkRing l []) = focusPrev (MkRing [] (reverse l))
focusPrev (MkRing l (r:rs)) = MkRing (r:l) rs

closeWindow :: Ring t -> Ring t
closeWindow r@(MkRing [] []) = r
closeWindow (MkRing [w] r) = MkRing (reverse r) []
closeWindow (MkRing (l:ls) r) = MkRing ls r

openWindow :: t -> Ring t -> Ring t
openWindow w (MkRing l r) = MkRing (w:l) r