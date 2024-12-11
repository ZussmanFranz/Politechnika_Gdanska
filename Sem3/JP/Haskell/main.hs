--                                          49
-- if n = a^2 + k*(b^2)
isSumOfSquares :: Int -> Int -> Bool
isSumOfSquares n k = any (\a -> let b2 = n - a*a in b2 >= 0 && b2 `mod` k == 0 && isSquare (b2 `div` k)) [0..floor (sqrt (fromIntegral n))]
  where
    isSquare x = let s = floor (sqrt (fromIntegral x)) in s * s == x

findNums :: Int -> [Int]
findNums n = filter (\x -> isSumOfSquares x 1 &&
                              isSumOfSquares x 2 &&
                              isSumOfSquares x 3 &&
                              isSumOfSquares x 7) [1..n]

-- count the numbers
countNums :: Int -> Int
countNums n = length (findNums n)


--                                          22
genDecPalindromes :: Int -> [Int]
genDecPalindromes n = [i | i <- [1..n], show i == reverse (show i)]

-- number to bin
toBinary :: Int -> String
toBinary 0 = "0"
toBinary n = toBinary' n []
  where
    toBinary' 0 bs = bs
    toBinary' n bs = toBinary' (n `div` 2) ((if n `mod` 2 == 0 then '0' else '1') : bs)

-- string is a palindrome
isPalindrome :: String -> Bool
isPalindrome s = s == reverse s

genPalindromes:: Int -> [Int]
genPalindromes n = filter (\i -> isPalindrome (toBinary i)) (genDecPalindromes n)

sumOfPalindromes:: Int -> Int
sumOfPalindromes n = sum (genPalindromes n)



--                                31
--- get all possible subsets of a set
getSubsets :: [a] -> [[a]]
getSubsets [] = [[]]
getSubsets (x:xs) = getSubsets xs ++ map (x:) (getSubsets xs)

-- if two lists are disjoint
disjoint :: Eq a => [a] -> [a] -> Bool
disjoint [] _ = True
disjoint _ [] = True
disjoint (x:xs) (y:ys)
  | x == y = False
  | otherwise = disjoint (x:xs) ys && disjoint xs (y:ys)

hasSubsets :: [Int] -> Bool
hasSubsets setA1 = any (\(b, c) -> sum b == sum c && disjoint b c && not (null b) && not (null c)) pairs
  where
    subsets = getSubsets setA1
    pairs = [(b, c) | b <- subsets, c <- subsets, b /= c]

--                              main
main :: IO ()
main = do
  putStrLn "49: Enter n:"
  n <- readLn :: IO Int
  print (countNums n)

  putStrLn "22: Enter n:"
  n <- readLn :: IO Int
  print(sumOfPalindromes n)

  putStrLn "31: Enter set: "
  input <- getLine
  let setA1 = map read $ words input :: [Int]
  print (hasSubsets setA1)
