module Spec ( prop_conversions
            , prop_fp_fn
            , prop_fn_fp
            ) where

import Lib
import Test.QuickCheck

-- property - funkcija koja uzme nesto i vraca bool
-- ako property vrati false biblioteka pretpostavlja da test nije prosao
prop_conversions :: [Int] -> Bool
prop_conversions ws = toList (fromList ws) == ws
            -- where types = ws :: [Int] ili deklaracija

-- prop_fp_fn :: [Int] -> Bool ili where
prop_fp_fn ws = toList (focusPrev $ focusNext $ fromList ws) == ws
                where types = ws :: [Int]

prop_fn_fp ws = toList (focusNext $ focusPrev $ fromList ws) == ws
                where types = ws :: [Int]
