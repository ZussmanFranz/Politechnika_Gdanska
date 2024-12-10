import Data.Char (intToDigit)
import Data.List (subsequences)

--                                          49
-- if n = a^2 + k*b^2
canBeRepresented :: Integer -> Integer -> Bool
canBeRepresented n k = any (\a -> let b2 = n - a*a in b2 >= 0 && b2 `mod` k == 0 && isSquare (b2 `div` k)) [0..floor (sqrt (fromIntegral n))]
  where
    isSquare x = let s = floor (sqrt (fromIntegral x)) in s * s == x

findNumbers :: Integer -> [Integer]
findNumbers n = filter (\x -> canBeRepresented x 1 &&
                               canBeRepresented x 2 &&
                               canBeRepresented x 3 &&
                               canBeRepresented x 7) [1..n]

-- count the numbers
countNumbers :: Integer -> Int
countNumbers n = length (findNumbers n)

--                                          22
isPalindrome :: String -> Bool
isPalindrome s = s == reverse s

-- num to bin
toBinary :: Integer -> String
toBinary n = map intToDigit $ reverse $ toBinary' (fromInteger n) []
  where
    toBinary' :: Int -> [Int] -> [Int]
    toBinary' 0 acc = acc
    toBinary' n' acc = toBinary' (n' `div` 2) ((n' `mod` 2) : acc)

sumDecimalBinaryPalindromes :: Integer -> Integer
sumDecimalBinaryPalindromes n = sum $ filter isDecimalBinaryPalindrome [1..n]
  where
    isDecimalBinaryPalindrome x = isPalindrome (show x) && isPalindrome (toBinary x)

--                                          31
hasEqualSumDisjointSubsets :: [Integer] -> Bool
hasEqualSumDisjointSubsets xs = any (\k -> hasEqualSumSubsetsOfSize k xs) [1..(length xs `div` 2)]
  where
    hasEqualSumSubsetsOfSize k xs =
      let subsets = filter (\s -> length s == k) (subsequences xs)
      in any (\s1 -> any (\s2 -> s1 /= s2 && sum s1 == sum s2 && null (s1 `intersect` s2)) subsets) subsets
      where
        intersect [] _ = []
        intersect _ [] = []
        intersect (x:xs) ys
            | x `elem` ys = x : intersect xs ys
            | otherwise   = intersect xs ys

-- Example usage
main :: IO ()
main = do
  putStrLn "49: Enter n:"
  input <- getLine
  let n = read input :: Integer
  print (countNumbers n)

  putStrLn "22: Enter n:"
  input <- getLine
  let n = read input :: Integer
  print (sumDecimalBinaryPalindromes n)

  putStrLn "31: Enter setA1: "
  -- example: 81 88 75 42 87 84 86 65
  input <- getLine
  let setA1 = map read $ words input :: [Integer]
  print (hasEqualSumDisjointSubsets (setA1))
