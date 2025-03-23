import pandas as pd

from math import factorial, sqrt

class Counter:
    count = 0

    @classmethod
    def Count(self):
        self.count += 1

    @classmethod
    def Restart(self):
        self.count = 0

class City:
    def __init__(self, city_id, town, population, latitude, longitude):
        self.city_id = city_id
        self.town = town
        self.population = population
        self.latitude = latitude
        self.longitude = longitude

    def __repr__(self):
        return f"City({self.city_id}, {self.town}, {self.population}, {self.latitude}, {self.longitude})"
    

# Funkcje task1

def nVariation(N, M, repeat=False):
    if N < M:
        raise Exception("N must not be lesser than M")
    
    if repeat:
        return N**M
    else:
        return factorial(N)/factorial(M)
    
def nCombination(N, M):
    if N <= M:
        raise Exception("N must be bigger than M")

    return factorial(N)/(factorial(M) * factorial(N - M))

def printVariations(N, M, current_variation, possible_indexes, variations_counter_reference):
    if len(current_variation) == M:
        variations_counter_reference.Count()
        print(variations_counter_reference.count, ": ", current_variation)
        return
    
    for index in possible_indexes:
        new_variation = current_variation[:]
        new_variation.append(index)

        new_indexes = possible_indexes[:]
        new_indexes.remove(index)

        printVariations(N, M, new_variation, new_indexes, variations_counter_reference)


def validVariations(N, M, current_variation, possible_indexes, cities, counter, lower_bound, upper_bound):
    if len(current_variation) == M:
        subset_population = sum(cities[i].population for i in current_variation)
        counter[1] += 1 # new variation complete
        if lower_bound <= subset_population <= upper_bound:
            counter[0] += 1 # variation is between bounds
        return
    for index in possible_indexes:
        new_variation = current_variation[:]
        new_variation.append(index)
        new_indexes = possible_indexes[:]
        new_indexes.remove(index)
        validVariations(N, M, new_variation, new_indexes, cities, counter, lower_bound, upper_bound)

def task1(N=None, M=None):
    if N == None:
        N = int(input("N = "))
    if M == None:
        M = int(input("M = "))

    n_variations = nVariation(N, M)
    print("\nTheoretical number of variations: ", n_variations)

    possible_indexes = list(range(1, N + 1))

    variations_counter = Counter()
    variations_counter.Restart()

    printVariations(N, M, [], possible_indexes, variations_counter)

# Zadanie 1: 
# Dla podanych liczb N i M wygeneruj (w porządku leksykograficznym) ponumerowane
# porządki odwiedzin M z N miast.

N = 6
M = 3


task1(N, M)

# Funkcje task2

def printVariationsRepeat(N, M, current_variation, possible_indexes, variations_counter_reference):
    if len(current_variation) == M:
        variations_counter_reference.Count()
        print(variations_counter_reference.count, ": ", current_variation)
        return
    
    for index in possible_indexes:
        new_variation = current_variation[:]
        new_variation.append(index)

        printVariationsRepeat(N, M, new_variation, possible_indexes, variations_counter_reference)

def task2(N=None, M=None):
    if N == None:
        N = int(input("N = "))
    if M == None:
        M = int(input("M = "))

    n_variations_repeat = nVariation(N, M, repeat=True)
    print("\nTheoretical number of variations (with repeat): ", n_variations_repeat)
    possible_indexes = list(range(1, N + 1))

    variations_repeat_counter = Counter()
    variations_repeat_counter.Restart()

    printVariationsRepeat(N, M, [], possible_indexes, variations_repeat_counter)

# Zadanie 2: 
# Dla podanych liczb N i M wygeneruj (w porządku leksykograficznym) ponumerowane
# wszystkie podzbiory, z możliwymi powtórzeniami, M z N miast


N = 6
M = 3


task2(N, M)

# Funkcje dla dodatkowych zadań

def load_cities_from_csv(filename):
    df = pd.read_csv(filename)  # Load CSV using pandas
    cities = [
        City(row["Id"], row["Town"], row["Population"], row["Latitude"], row["Longitude"])
        for _, row in df.iterrows()
    ]
    return cities

def calculateDistance(cityA, cityB):
    return sqrt((cityB.longitude - cityA.longitude)**2 + (cityB.latitude - cityA.latitude)**2)

def calculateRoute(route, cities):
    length = 0
    
    prev = -1
    
    for id in route:
        if prev == -1:
            prev = id
            continue

        length += calculateDistance(cities[prev], cities[id])

        prev = id

    return length

def printRoute(route, cities):
    for id in route:
        print(" -> ", cities[id].city_id, cities[id].town, end="")
    print("\n")

def shortestVariation(N, M, current_variation, possible_indexes, cities, minimum_route):
    if len(current_variation) == M:
        current_route = calculateRoute(current_variation, cities)

        if minimum_route[1] == None or current_route < minimum_route[1]:
            print(f"New candidate ({current_route}vs{minimum_route[1]}): ", current_variation)
            minimum_route[1] = current_route
            minimum_route[0] = current_variation

        return
    
    for index in possible_indexes:
        new_variation = current_variation[:]
        new_variation.append(index)

        new_indexes = possible_indexes[:]
        new_indexes.remove(index)

        shortestVariation(N, M, new_variation, new_indexes, cities, minimum_route)

def task1_u(cities, M):
    minimum_route = [None, None] # minumum_route[0] is route itself, minimum_route[1] is it's length

    n_cities = len(cities)

    print(f"\tNumber of possible routes: {nVariation(n_cities, M)}")

    possible_indexes = list(range(0, n_cities))

    shortestVariation(n_cities, M, [], possible_indexes, cities, minimum_route)

    print("Minimum route is: ")
    printRoute(minimum_route[0], cities)


# Load cities and print them
cities = load_cities_from_csv("cities.csv")
for city in cities:
    print(city)

n_cities = len(cities)
print("Number of cities loaded: ", n_cities)

task1_u(cities, 5)

def task2_u(cities, M):
    total_population = sum(city.population for city in cities)

    lower_bound = 0.4 * total_population
    upper_bound = 0.6 * total_population

    possible_indexes = list(range(len(cities)))

    counter = [0, 0] # [0] = valid_subsets, [1] = variations_count

    validVariations(len(cities), M, [], possible_indexes, cities, counter, lower_bound, upper_bound)
    
    probability = counter[0] / counter[1] if counter[1] > 0 else 0

    print(f"Probability that the sum of the population of a random subset of {M} cities falls within 40%-60% of the total population: {probability:.4f}")

task2_u(cities, 5)


