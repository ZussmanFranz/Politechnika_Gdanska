class Game {
    var word: String
    var word_len: Int
    var guessed_word: Array<Character>
    var guessed_letters: Int = 0
    var Ntries: Int
    var categories: Array<String> = ["Default"]
    var categories_count: Int = 1

    init(word: String, Ntries: Int, categories: Array<String>){
        self.word = word
        word_len = word.count
        self.Ntries = Ntries
        self.guessed_word = Array(repeating: "_", count: word_len)

        if categories.count != 0{
            self.categories = categories
            categories_count = categories.count
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
                    guessed_letters += 1
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
        if Ntries <= 0 || guessed_letters >= word_len{
            return true
        } else {
            return false
        }
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

    func print_categories(selected: Int){
        for (index, category) in categories.enumerated(){
            if index == selected{
                print("\u{1B}[7m\(index): \(category)\u{1B}[0m") // Inverted colors
            } else {
                print("\(index): \(category)")
            }
        }
    }

    func start_screen(){
        print("\u{1B}[2J") // Clear screen
        print("\u{1B}[H")  // Move cursor to top

        var selected = -1

        print("Choose category: ")
        print_categories(selected: selected)

        while selected == -1{
            if let input = readLine(){
                // selected = Int(input.first?.wholeNumberValue) ?
            }
        }
    }

    func play(){
        start_screen()

        while(!is_over()){
            print("\u{1B}[2J") // Clear screen
            print("\u{1B}[H")  // Move cursor to top
            print_game()
            take_input()
        }
        
        end_screen()
    }
}

var test_game: Game = Game(word: "hello", Ntries: 5, categories: ["movies", "medieval", "Ireland"]) 

test_game.play()


