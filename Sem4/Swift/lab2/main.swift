// Functions:

func minimum(val1: Int, val2: Int) -> Int{
    if (val1 <= val2){
        return val1
    }
    else{
        return val2
    }
}

// print(minimum(val1: 5,val2: 10))
// print(minimum(val1: 5,val2: 4))

func last_digit(value:Int) -> Int{
    return value%10
}

// print(last_digit(value:12349))

func divides(divided:Int, divisor:Int) -> Bool{
    return (divided % divisor == 0 && divided >= divisor)
}

func countDivisors(value: Int) -> Int {
    var divisor = 0
    var divisors = 0

    while(divisor < value){
        divisor += 1
        if divides(divided: value, divisor: divisor) {
            divisors += 1
        }
    }

    return divisors;
}

// print(countDivisors(value: 5))
// print(countDivisors(value: 20))

func isPrime(value: Int) -> Bool{
    return (countDivisors(value: value) == 2)
}

// print(isPrime(value: 3))
// print(isPrime(value: 10))
// print(isPrime(value: 13))

// Closures:

func smartBard(n: Int, closure: ()->()){
    for _ in 1...n{
        closure()
    }
}

smartBard(n: 10) {
    print("I will pass this course with best mark, because Swift is great!")
}

let numbers = [10, 16, 18, 30, 38, 40, 44, 50]
var filtered_array = numbers.filter{$0 % 4 == 0}
print(filtered_array)

var maxNumber = numbers.reduce(0){max($1, $0)}

print(maxNumber)

let strings = ["Gdansk", "University", "of", "Technology"]
var accumulated = strings.reduce(""){$0 + $1 + " "}

print(accumulated)

let new_numbers = [1, 2, 3, 4, 5, 6]

// Returns sum of squares of the odd numbers in the array
var sumSquaresOdd = new_numbers.filter{$0 % 2 == 1}.map{$0 * $0}.reduce(0){$0 + $1}
print(sumSquaresOdd)

// Tuples:

func minmax(a: Int, b: Int) -> (Int, Int) {
    if (a >= b){
        return (a, b)
    }else{
        return (b, a)
    }
}

print(minmax(a: 5, b: 6))

var stringsArray = ["gdansk", "university","gdansk", "university", "university",
"of", "technology", "technology","gdansk","gdansk"]

var countedStrings:[(String, Int)] = []

for str in stringsArray{
    if let index = countedStrings.firstIndex(where: {$0.0 == str}){
        countedStrings[index].1 += 1
    } else {
        countedStrings.append((str, 1))
    }
}

print(countedStrings)

// Enums:

enum Day: Int {
    case Monday = 1
    case Tuesday = 2
    case Wednesday = 3
    case Thursday = 4
    case Friday = 5
    case Saturday = 6
    case Sunday = 7

    func emoji() -> String {
        switch self{
            case .Monday:
                return "🤺"
            case .Tuesday:
                return "💪"
            case .Wednesday:
                return "⚔️"
            case .Thursday:
                return "🙈"
            case .Friday:
                return "🤩"
            case .Saturday:
                return "👑"
            case .Sunday:
                return "👣"
        }
    }
}

var day = Day(rawValue: 3)

print(day?.emoji() ?? "❓")
