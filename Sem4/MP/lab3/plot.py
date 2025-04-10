import random
import numpy as np

def evaluateRandom(numbers, N_counters, min_val, max_val):
    counters = np.zeros(N_counters)

    counters_thresholds = np.full(N_counters, min_val)

    step = (max_val - min_val) / N_counters

    for i in range(1, N_counters + 1):
        counters_thresholds[i - 1] += step * i

    for val in numbers:
        for counter_id in range(0, N_counters):
            if val <= counters_thresholds[counter_id]:
                counters[counter_id] += 1
                break

    return counters

def generateN(n, generatorFunc, **generateFuncArgs):
    print(f'arguments: {generateFuncArgs}')
    values = []

    for _ in range(0, n):
        values.append(generatorFunc(**generateFuncArgs))  

    return values

def generate_range(range_start, range_end):
    # random.random returns float from [0.0, 1.0] range
    return (range_start + random.random() * (range_end - range_start))


def distribute(distributor_table, value, min_value, max_value):
    # distributor table example:
    # [[0.1, 1], [0.3, 3], [0.2, 4], [0.4, 10]]

    normalized = (value - min_value) / (max_value - min_value)

    chance = 0.0

    for bucket in distributor_table:
        chance += bucket[0]
        if normalized < chance:
            return bucket[1]
    
    return bucket[-1]
            
def distribute_values(distributor_table, values, min_value, max_value):
    return_values = []
    
    for element in values:
        distr_val = distribute(distributor_table, element, min_value, max_value)
        return_values.append(distr_val)

    return return_values

def elimination_method(possibility_func, fmax, a, b, counter):
    # U1 nalezy do osi X (a, b)
    # U2 nalezy do osi Y (0, d), gdzie d = fmax + epsilon

    # losujemy U1, U2

    # if f(U1) > U2
    #   return U1
    # else
    #   return None

    # badana funkcja:
    # f(x) = liniowa od 50 do 150
    # fmax = 1/50
    # epselon +-= fmax/100

    # wyświetlić buckets
    # wyświetlić, ile prób było, żeby 100000 wyników uzyskać?

    epselon = fmax / 100

    result = None

    while (not result):
        counter[0] += 1

        U1 = a + random.random() * (b - a) # from a to b
        U2 = random.random() * (fmax + epselon)

        if possibility_func(U1) > U2:
            result = U1        
        
    return result

def possibility_func_linear(x):
    # f(x) = ax + b
    # 0 = a * 50 + b
    # 1/50 = a * 150 + b
    # 50a = 150a - 1/50
    # 100a = 1/50
    # a = 1/5000
    return (x / 5000) - 0.01


def main():
    # print(f'f(0) = {possibility_func_linear(0)}')
    # print(f'f(50) = {possibility_func_linear(50)}')
    # print(f'f(100) = {possibility_func_linear(100)}')
    # print(f'f(150) = {possibility_func_linear(150)}')
    
    range_start = 50
    range_end = 150

    values = generateN(n = 100000, generatorFunc = generate_range, range_start = 50, range_end = 150)

    # print(f'Initial values from ({range_start}, {range_end}) interval:')
    # print(values)

    print('Random distribution:')
    buckets = evaluateRandom(values, 10, 50, 150)
    print(buckets)

    print('Distributor table:')
    distributor_table = [(0.2, 1), (0.4, 2), (0.3, 3), (0.1, 4)]
    print(distributor_table)

    print('Discrete values:')
    discrete_values = distribute_values(distributor_table, values, 50, 150)
    # print(discrete_values)

    buckets = evaluateRandom(discrete_values, 10, 1, 4)
    print(buckets)

    counter_ref = [0]

    values = generateN(n = 100000, generatorFunc=elimination_method, possibility_func = possibility_func_linear, 
                       fmax = 1/50, a = 50, b = 150, counter=counter_ref)
    
    buckets = evaluateRandom(values, 10, 50, 150)

    print(f'{counter_ref[0]} attempts for {100000} values generation')
    print(buckets)



if __name__ == "__main__":
    main()