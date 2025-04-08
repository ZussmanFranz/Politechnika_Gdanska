import numpy as np
# import matplotlib.pyplot as plt 


def generateX(Xprev):
    global a, c, M
    result = (Xprev * a + c) % M

    # returns (number, next_element_base)
    return (result, result)

def generateNextBit(bits):
    global p, q
    bitp = int(bits[-p])
    bitq = int(bits[-q])
    return str(bitp ^ bitq)

def generateBitsNumber(start_bits):
    global size
    str_number = start_bits
    n_generated = len(str_number)

    while n_generated < size:
        str_number += generateNextBit(str_number)
        n_generated += 1

    # returns (number, next_element_base)
    return (int(str_number, 2), str_number[-len(start_bits):])

def generateN(generate_func, n, start_value):
    numbers = []
    
    base = start_value
    for _ in range(0, n):
        (val, base) = generate_func(base)
        numbers.append(val)

    return numbers

def evaluateRandom(numbers, N_counters, max_val):
    counters = np.zeros(N_counters)

    counters_thresholds = np.zeros(N_counters)
    step = max_val / N_counters

    for i in range(1, N_counters + 1):
        counters_thresholds[i - 1] = step * i

    for val in numbers:
        for counter_id in range(0, N_counters):
            if val <= counters_thresholds[counter_id]:
                counters[counter_id] += 1
                break

    return counters

def generateBinaryNumbers(start_bits, count):
    global q
    binary_numbers = []
    current_bits = start_bits
    
    for _ in range(count):
        binary_numbers.append(int(current_bits, 2))
        next_bits = ''
        for _ in range(len(current_bits)):
            next_bits += generateNextBit(current_bits)
            current_bits = current_bits[1:] + next_bits[-1]
        current_bits = current_bits[-q:]
    
    return binary_numbers


# Zadanie 1: Xn+1 = (a * Xn + c) mod M

Xo = 15
a = 69069
c = 1
M = 2**31

n = 1000000
N_counters = 10

# Generujemy n liczb, potem badamy rownomiernosc przez podzial zakresu (0:M-1) na N_licznikow i liczymy, do ktorego przedzialu nalezy liczba 

print('First method:')
numbers = generateN(generateX, n, Xo)
countersX = evaluateRandom(numbers, N_counters, M)
print(countersX)

# Zadanie 2: bi = bi-p xor bi-q

start_bits = '1101101'
p = 7
q = 3
size = 31

print('Second method:')
numbers = generateN(generateBitsNumber, n, start_bits)
countersB = evaluateRandom(numbers, N_counters, 2**size)
# print(numbers)
print(countersB)

# print(f'{numbers[0]} in binary: {bin(numbers[0])}')

