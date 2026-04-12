module Lib where

-- zipper
type Ring t = ([t], [t])

fromList :: [t] -> Ring t
fromList lst = (lst, [])

toList :: Ring t -> [t]
toList (ls, rs) = ls ++ reverse rs

switchActive :: Ring t -> Ring t
switchActive ([], []) = ([], [])
switchActive ([w], []) = ([w], [])
                                    -- presipamo desnu u levu i probamo ponovo 
switchActive ([w], rs) = switchActive (w : reverse rs, [])
switchActive (active:next:others, rs) = (next:active:others, rs)

focusNext :: Ring t -> Ring t
focusNext ([], []) = ([], [])
                                -- presipamo desnu u levu i probamo ponovo
focusNext ([w], rs) = focusNext (w : reverse rs, [])
focusNext (l:ls, r) = (ls, l:r)

focusPrev :: Ring t -> Ring t
focusPrev ([], []) = ([], [])
focusPrev (l, []) = focusPrev ([], reverse l) -- prekrseno pravilo da leva nikad nije prazna
focusPrev (l, r:rs) = (r:l, rs)

closeWindow :: Ring t -> Ring t
closeWindow ([], []) = ([], [])
closeWindow ([w], r) = (reverse r, [])
closeWindow (l:ls, r) = (ls, r)

openWindow :: t -> Ring t -> Ring t
openWindow w (l, r) = (w:l, r)