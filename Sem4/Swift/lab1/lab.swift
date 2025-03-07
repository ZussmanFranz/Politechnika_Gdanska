import Foundation

// Exercise 1
print("\tExercise 1")

var a = 5
var b = 223
var c = a + b
print("\(a) + \(b) = \(c)")

let str = "Gdansk University of Technology"
var new_str = ""

for ch in str {
  if (ch == "n"){
    new_str += "⭐️"
  }
  else {
    new_str += String(ch)
  }
}

print(new_str)

let full_name = "Yauheni Pyryeu"
var new_name = ""

for ch in full_name{
  new_name = String(ch) + new_name
} 

print("\(full_name) -> \(new_name)")

// Exercise 2 
print("\tExercise 2")

for i in 1 ... 11 {
  print("\(i):\tI will pass this course with best mark, because Swift is great!")
}

func FirstNSqr(N: Int) {
    for i in 1...N{
        print(i * i)
    }
}

FirstNSqr(N: 5)

func DrawSquare(N: Int) {
    for i in 1...N{
        for j in 1...N{
            print("@", terminator: "")
        }
        print()
    }
}

DrawSquare(N:5)

// Exercise 3
print("\tExercise 3")

var numbers = [5, 10, 20, 15, 80, 13]
var max = numbers[0]

for n in numbers{
    if n > max {
        max = n
    }
}

print("max: \(max)")

print("reversed: ", terminator:"")
for n in numbers.reversed(){
    print("\(n) ", terminator:"")
}
print()

var allNumbers = [10, 20, 10, 11, 13, 20, 10, 30]
var unique: [Int] = []
var add = true

for n in allNumbers {
    add = true
    
    for u in unique{
        if u == n{
            add = false
        }
    }
    
    if add {
        unique.append(n)
    }
}

print(allNumbers)
print(unique)

// Exercise 4
print("\tExercise 4")

let number = 10
var divisors: Set<Int> = [1]
var divisor: Int = number

while divisor > 1{
    if (number % divisor) == 0 {
        divisors.insert(divisor)
    }
    divisor -= 1
}

print(divisors.sorted())

// Exercise 5
print("\tExercise 5")

var flights: [[String: String]] = [
    [
        "flightNumber" : "AA8025",
        "destination" : "Copenhagen"
    ],
    [
        "flightNumber" : "BA1442",
        "destination" : "New York"
    ],
    [
        "flightNumber" : "BD6741",
        "destination" : "Barcelona"
    ]
]

var flight_numbers: Array<String> = []

for f in flights{
    if let fn = f["flightNumber"]{
        flight_numbers.append(fn)
    }
}

print(flight_numbers)

var names = ["Hommer","Lisa","Bart"]
let surname = "Simpson"
var full_names: [String:String] = [:]

for n in names{
    full_names[n] = surname
}

print(full_names)