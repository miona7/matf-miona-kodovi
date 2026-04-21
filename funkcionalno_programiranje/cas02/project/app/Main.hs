module Main (main) where

import Spec
import Test.QuickCheck

main :: IO ()
main = do
  putStrLn "hello world"

  putStrLn "pokrecem testove"

  putStrLn "prop_conversions"
  quickCheck prop_conversions

  putStrLn "prop_fp_fn"
  quickCheck prop_fp_fn

  putStrLn "prop_fn_fp"
  quickCheck prop_fn_fp