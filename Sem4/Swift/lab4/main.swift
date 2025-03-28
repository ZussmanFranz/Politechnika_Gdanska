import Foundation

class Game {
    var word: String = "default"
    var word_len: Int
    
    var guessed_word: Array<Character>
    var guessed_letters: Int = 0
    
    var Ntries: Int
    
    var categories: Array<String> = ["Default"]
    var categories_count: Int = 1
    var categories_values: Array<Array<String>> = [["default", "none", "nil", "error"]]
    
    var category_selected: Int = 1

    var difficulties: Array<String> = ["Easy", "Medium", "Hard"]
    var diff_values: Array<Int> = [6, 4, 2]
    var diff_count: Int = 3

    var difficulty_selected: Int = 1

    init(Ntries: Int, categories: Array<String>, categories_values: Array<Array<String>>){
        word_len = word.count
        self.Ntries = Ntries
        self.guessed_word = Array(repeating: "_", count: word_len)

        if categories.count != 0{
            self.categories = categories
            categories_count = categories.count
            self.categories_values = categories_values
        }
    }

    func print_word(){
        print("┌", terminator: "")
        print(String(repeating: "—", count: word_len + 2), terminator: "")
        print("┐")
        print("| \(String(guessed_word)) |")
        print("└", terminator: "")
        print(String(repeating: "—", count: word_len + 2), terminator: "")
        print("┘")
    }

    func print_game(){
        print("Guess the word!")
        print_word()
        print("Press the letter to check if it is in a word")
        print("Number of guesses left: \(Ntries)")
    }

    func take_input(){
        if let input = readLine(), let guessed_char: Character = input.first {
            print("You entered: \(guessed_char)")
            
            var guessed = false

            for (index, char) in word.enumerated() {
                if char == guessed_char { //&& guessed_word.firstIndex(of: char == nil) {
                    guessed_word[index] = char
                    guessed = true 
                }
            }

            if !guessed{
                print("Not correct")
                Ntries -= 1
            } else {
                print("Correct!")
            }
        }
    }

    func is_over() -> Bool{
        return (Ntries <= 0 || guessed_word.filter{ $0 == "_" }.count == 0)
    }

    func end_screen(){
        print("\u{1B}[2J") // Clear screen
        print("\u{1B}[H")  // Move cursor to top

        print("\nGame over!")
        print_word()
        
        if Ntries > 0{
            print("You won! Tries left: \(Ntries)")
        } else{
            print("You loose :(")
        }
    }

    func print_options(selected: Int, options: Array<String>){
        for (index, option) in options.enumerated(){
            if index == selected{
                print("\u{1B}[7m\(index + 1): \(option)\u{1B}[0m") // Inverted colors
            } else {
                print("\(index + 1): \(option)")
            }
        }
    }

    func select(options: Array<String>, options_count: Int, subject_name: String) -> Int{
        var selected = -1

        print("Choose \(subject_name): ")
        print_options(selected: selected, options: options)
        print("Enter \(subject_name) number:")

        while selected < 0 || selected >= options_count{
            if let input = readLine(), let first_char: Character = input.first{
                selected = (first_char.wholeNumberValue ?? 0) - 1 // I need to get integer out of char digit
            } else {
                print("Invalid option!")
            }
        }

        print("Chosen \(subject_name): ")
        print_options(selected: selected, options: options)

        return selected
    }

    func start_screen(){
        print("\u{1B}[2J") // Clear screen
        print("\u{1B}[H")  // Move cursor to top

        category_selected = select(options: categories, options_count: categories_count, subject_name: "category")

        if let random_word = categories_values[category_selected].randomElement() {
            word = random_word
            word_len = word.count
            guessed_word = Array(repeating: "_", count: word_len)
        } else {
            print("Error: No words available in this category.")
        }
    }

    func difficulty_screen(){
        difficulty_selected = select(options: difficulties, options_count: diff_count, subject_name: "difficulty")

        if difficulty_selected >= 0 && difficulty_selected < diff_count{
            Ntries = diff_values[difficulty_selected]
        } else {
            print("Error: No tries number defined for this difficulty.")
        }

        sleep(1)
    }

    func play(){
        start_screen()
        difficulty_screen()

        while(!is_over()){
            print("\u{1B}[2J") // Clear screen
            print("\u{1B}[H")  // Move cursor to top
            print_game()
            take_input()
        }
        
        end_screen()
    }
}

var test_game: Game = Game(Ntries: 5, categories: ["movies", "medieval", "Ireland"], 
    categories_values: [["guard", "bruges", "billboards"], ["holy", "peasant", "chivalry"], ["catholic", "freedom", "guiness"]]) 

test_game.play()


