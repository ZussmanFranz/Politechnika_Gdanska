import Foundation


enum PlayerSign: Character {
    case X = "X"
    case O = "O"
    case empty = " "

    var opponent: PlayerSign {
        return self == .X ? .O : .X
    }
}

struct Player {
    let name: String
    let sign: PlayerSign
    let isAI: Bool
}


class Board {
    var grid: [[PlayerSign]]
    let size: Int

    init(size: Int = 3) {
        self.size = size
        self.grid = Array(repeating: Array(repeating: .empty, count: size), count: size)
    }

    func display() {
        print("\nBoard:")
        // Print column numbers
        var header = "   "
        for i in 0..<size {
            header += "\(i + 1) "
        }
        print(header)
        print(" +" + String(repeating: "--", count: size) + "-+")


        for (rIndex, row) in grid.enumerated() {
            var rowStr = "\(rIndex + 1) |"
            for cell in row {
                rowStr += "\(cell.rawValue)|"
            }
            print(rowStr)
            print(" +" + String(repeating: "--", count: size) + "-+")
        }
        print()
    }

    func isValidMove(row: Int, col: Int) -> Bool {
        return row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == .empty
    }

    func placeMark(row: Int, col: Int, sign: PlayerSign) -> Bool {
        if isValidMove(row: row, col: col) {
            grid[row][col] = sign
            return true
        }
        return false
    }

    func checkWin(sign: PlayerSign) -> Bool {
        // Check rows
        for row in 0..<size {
            if (0..<size).allSatisfy({ col in grid[row][col] == sign }) {
                return true
            }
        }
        // Check columns
        for col in 0..<size {
            if (0..<size).allSatisfy({ row in grid[row][col] == sign }) {
                return true
            }
        }
        // Check diagonals
        if (0..<size).allSatisfy({ i in grid[i][i] == sign }) {
            return true
        }
        if (0..<size).allSatisfy({ i in grid[i][size - 1 - i] == sign }) {
            return true
        }
        return false
    }

    func isFull() -> Bool {
        return grid.allSatisfy { row in row.allSatisfy { $0 != .empty } }
    }

    func reset() {
        grid = Array(repeating: Array(repeating: .empty, count: size), count: size)
    }

    func getAvailableMoves() -> [(row: Int, col: Int)] {
        var moves: [(Int, Int)] = []
        for r in 0..<size {
            for c in 0..<size {
                if grid[r][c] == .empty {
                    moves.append((r, c))
                }
            }
        }
        return moves
    }
}


enum GameLevel: String, CaseIterable {
    case easy = "Easy (3x3, Random AI)"
    case medium = "Medium (3x3, Smarter AI)"
    case hard = "Hard (4x4, Smarter AI)"

    var boardSize: Int {
        switch self {
        case .easy, .medium: return 3
        case .hard: return 4
        }
    }
}

class Game {
    var board: Board
    var player1: Player
    var player2: Player // Human or AI
    var currentPlayer: Player
    var level: GameLevel

    init() {
        // Default initialization, will be set properly in selectGameSetup
        self.level = .easy
        self.board = Board(size: self.level.boardSize)
        self.player1 = Player(name: "Player 1", sign: .X, isAI: false)
        self.player2 = Player(name: "Player 2", sign: .O, isAI: false)
        self.currentPlayer = player1
    }

    func selectGameSetup() {
        print("Welcome to Tic-Tac-Toe!")

        // Select Level
        print("\nSelect Difficulty Level:")
        for (index, levelCase) in GameLevel.allCases.enumerated() {
            print("\(index + 1). \(levelCase.rawValue)")
        }
        var levelChoice: Int?
        while levelChoice == nil {
            print("Enter level number (1-\(GameLevel.allCases.count)): ", terminator: "")
            if let input = readLine(), let choice = Int(input), choice > 0 && choice <= GameLevel.allCases.count {
                levelChoice = choice
            } else {
                print("Invalid input. Please try again.")
            }
        }
        self.level = GameLevel.allCases[levelChoice! - 1]
        self.board = Board(size: self.level.boardSize) 

        
        print("\nSelect Game Mode:")
        print("1. Player vs Player")
        print("2. Player vs AI")
        var modeChoice: Int?
        while modeChoice == nil {
            print("Enter mode number (1 or 2): ", terminator: "")
            if let input = readLine(), let choice = Int(input), (choice == 1 || choice == 2) {
                modeChoice = choice
            } else {
                print("Invalid input. Please try again.")
            }
        }

        self.player1 = Player(name: "Player 1", sign: .X, isAI: false)
        if modeChoice == 1 {
            self.player2 = Player(name: "Player 2", sign: .O, isAI: false)
        } else {
            self.player2 = Player(name: "AI", sign: .O, isAI: true)
        }
        self.currentPlayer = player1 // Player X always starts
    }


    func startGame() {
        selectGameSetup()
        gameLoop()
    }

    func gameLoop() {
        var gameIsOver = false
        while !gameIsOver {
            board.display()
            print("\(currentPlayer.name)'s turn (\(currentPlayer.sign.rawValue)).")

            var moveMade = false
            if currentPlayer.isAI {
                print("AI is thinking...")
                
                let aiMove = getAIMove()
                board.placeMark(row: aiMove.row, col: aiMove.col, sign: currentPlayer.sign)
                print("AI placed \(currentPlayer.sign.rawValue) at (\(aiMove.row + 1), \(aiMove.col + 1))")
                moveMade = true
            } else {
                while !moveMade {
                    print("Enter your move (row,col), e.g., 1,1 for top-left: ", terminator: "")
                    if let input = readLine() {
                        let parts = input.split(separator: ",").map { $0.trimmingCharacters(in: .whitespacesAndNewlines) }
                        if parts.count == 2, let row = Int(parts[0]), let col = Int(parts[1]) {
                            if board.placeMark(row: row - 1, col: col - 1, sign: currentPlayer.sign) {
                                moveMade = true
                            } else {
                                print("Invalid move. Cell might be taken or out of bounds. Try again.")
                            }
                        } else {
                            print("Invalid format. Use row,col (e.g., 1,2). Try again.")
                        }
                    }
                }
            }

            if board.checkWin(sign: currentPlayer.sign) {
                board.display()
                print("🎉 \(currentPlayer.name) (\(currentPlayer.sign.rawValue)) wins! 🎉")
                gameIsOver = true
            } else if board.isFull() {
                board.display()
                print("It's a Draw! 🤝")
                gameIsOver = true
            } else {
                switchPlayer()
            }
        }
        askToPlayAgain()
    }

    func switchPlayer() {
        currentPlayer = (currentPlayer.sign == player1.sign) ? player2 : player1
    }

    func getAIMove() -> (row: Int, col: Int) {
        let availableMoves = board.getAvailableMoves()
        guard !availableMoves.isEmpty else {
            fatalError("AI called with no available moves.") // Should not happen if game logic is correct
        }

        // --- Levels Integration for AI ---
        switch level {
        case .easy:
            // Easy: Random move
            return availableMoves.randomElement()!
        case .medium, .hard: // For hard, we use the same logic but potentially on a larger board
            // Medium/Hard:
            // 1. Check if AI can win in the next move
            for move in availableMoves {
                board.grid[move.row][move.col] = currentPlayer.sign // Try move
                if board.checkWin(sign: currentPlayer.sign) {
                    board.grid[move.row][move.col] = .empty // Undo move
                    return move
                }
                board.grid[move.row][move.col] = .empty // Undo move
            }

            // 2. Check if opponent can win in the next move, and block it
            let opponentSign = currentPlayer.sign.opponent
            for move in availableMoves {
                board.grid[move.row][move.col] = opponentSign // Try opponent's move
                if board.checkWin(sign: opponentSign) {
                    board.grid[move.row][move.col] = .empty // Undo move
                    return move // Block this move
                }
                board.grid[move.row][move.col] = .empty // Undo move
            }
            
            // 3. Try to take the center (if available and board is 3x3 or 4x4 and we target a centerish spot)
            if board.size % 2 == 1 { // Odd size board has one center
                 let center = board.size / 2
                 if board.isValidMove(row: center, col: center) {
                     return (center, center)
                 }
            } else { // Even size board has 4 center-ish spots
                let c1 = board.size / 2 - 1
                let c2 = board.size / 2
                let centerSpots = [(c1,c1), (c1,c2), (c2,c1), (c2,c2)]
                for spot in centerSpots {
                    if board.isValidMove(row: spot.0, col: spot.1) {
                        return spot
                    }
                }
            }


            // 4. Try to take a corner
            let corners = [
                (0, 0), (0, board.size - 1),
                (board.size - 1, 0), (board.size - 1, board.size - 1)
            ]
            let availableCorners = corners.filter { board.isValidMove(row: $0.0, col: $0.1) }
            if let cornerMove = availableCorners.randomElement() {
                return cornerMove
            }

            // 5. Take any available side (fallback)
            return availableMoves.randomElement()!
        }
    }

    func askToPlayAgain() {
        print("\nPlay again? (yes/no): ", terminator: "")
        if let response = readLine()?.lowercased(), response == "yes" || response == "y" {
            board.reset()
            currentPlayer = player1 // Player X starts again
            print("\n--- New Game ---")
            selectGameSetup() // Allow changing settings for the new game
            gameLoop()
        } else {
            print("Thanks for playing Tic-Tac-Toe!")
        }
    }
}


let game = Game()
game.startGame()