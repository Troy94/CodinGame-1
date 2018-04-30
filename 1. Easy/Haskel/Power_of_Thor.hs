import System.IO
import Control.Monad

main :: IO ()
main = do
	hSetBuffering stdout NoBuffering -- DO NOT REMOVE


	input_line <- getLine
	let input = words input_line
	let lightX = read (input !! 0) :: Int
	let lightY = read (input !! 1) :: Int
	let initX = read (input !! 2) :: Int
	let initY = read (input !! 3) :: Int
	loop initX initY lightX lightY

loop :: Int -> Int -> Int -> Int -> IO ()
loop thorX thorY lightX lightY = do
	input_line <- getLine
	let remainingturns = read input_line :: Int
	
	let dy
		| lightY > thorY = "S"
		| lightY < thorY = "N"
		| otherwise = ""

	let dx
		| lightX > thorX = "E"
		| lightX < thorX = "W"
		| otherwise = ""

	let newThorY
		| lightY > thorY = thorY + 1
		| lightY < thorY = thorY - 1
		| otherwise = thorY

	let newThorX
		| lightX > thorX = thorX + 1
		| lightX < thorX = thorX + 1
		| otherwise = thorX

	putStrLn (dy++dx)
	
	loop newThorX newThorY lightX lightY