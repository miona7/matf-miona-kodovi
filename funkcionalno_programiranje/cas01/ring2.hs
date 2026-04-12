module Lib where

newtype Ring t = MkRing [t] 
-- definise "novi" tip i ne dozvoljava implicitne konverzije -> uvodimo konstruktor MkRing

fromList :: [t] -> Ring t
fromList = MkRing

toList :: Ring t -> [t]
toList (MkRing r) = r

-- ime@pattern se koristi ako zelimo da zadrzimo ime objekta koji zelimo da dekonstruisemo 
-- jer jednom dekonstruisan objekat vise ne moze da se koristi sa "neraspakovanim" imenom
switchActive :: Ring t -> Ring t
switchActive r@(MkRing []) = r -- stedi vreme i memoriju, jer ne pravimo novi objekat
switchActive r@(MkRing [x]) = r
switchActive (MkRing (active:next:others)) = MkRing (next:active:others)

focusNext :: Ring t -> Ring t
focusNext r@(MkRing []) = r
focusNext (MkRing (x:xs)) = MkRing (xs ++ [x])

-- ovde sad ne mozemo iskoristiti kompoziciju funkcija posto focusNext radi nad Ring-om
-- "undefined" se moze koristiti kao "placeholder" za definicije funkcija
-- poziv funkcije cija je definicija "undefined" uzrokuje izuzetak
focusPrev :: Ring t -> Ring t
focusPrev (MkRing xs) = undefined    -- implementirati
-- nekad je korisno videti sta Haskell dedukuje kao tip odredjenog izraza
-- u tim slucajevima mozemo koristiti "rupe" (holes) - tipske promenljive koje pocinju donjom crtom
-- prevodilac ce dati detaljan opis koji ukljucuje tip izraza kao i "okruzenje" - tipovi simbola koji su vidljivi u kontekstu u kom se nalazi rupa

-- primer koriscenja rupe: focusPrev (MkRing xs) = _a

closeWindow :: Ring t -> Ring t
closeWindow (MkRing r) = MkRing (tail r) 

openWindow :: t -> Ring t -> Ring t
openWindow w (MkRing r) = MkRing (w:r)