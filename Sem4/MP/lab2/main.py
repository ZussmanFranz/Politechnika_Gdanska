class LinearGenerator:
    def __init__(self, a: int, c: int, m: int, seed: int = 1):
        self.a = a
        self.c = c
        self.m = m
        self.seed = seed

    def __generate_number(self) -> int:
        self.seed = (self.a * self.seed + self.c) % self.m
        return self.seed

    def generate_probability(self) -> float:
        return self.__generate_number() / self.m

    def generate_probabilities(self, n: int):
        for _ in range(n):
            yield self.generate_probability()

    def generate_number(self, m: int = None) -> int:
        if m is None:
            m = self.m
        return int(m * self.generate_probability())

    def generate_numbers(self, n: int, m: int = None):
        if m is None:
            m = self.m
        for _ in range(n):
            yield self.generate_number(m)

class RegisterGenerator:
    def __init__(self, p: int, q: int, seed: int = 2**31, accuracy: int = 31):
        self.p = p
        self.q = q
        self.size = p+q
        self.seed = seed
        self.accuracy = accuracy

    def __generate_bit(self) -> int:
        p_bit = (self.seed >> (self.p-1)) & 1
        q_bit = (self.seed >> (self.q-1)) & 1
        bit = p_bit ^ q_bit
        self.seed >>= 1
        self.seed |= bit << self.size
        return bit

    def generate_probability(self) -> float:
        result = 0
        weight = 0.5
        for _ in range(self.accuracy):
            if self.__generate_bit() == 1:
                result += weight
            weight /= 2
        return result

    def generate_probabilities(self, n: int):
        for _ in range(n):
            yield self.generate_probability()

    def generate_number(self, m: int = None) -> int:
        if m is None:
            m = 2**self.accuracy
        return int(m * self.generate_probability())

    def generate_numbers(self, n: int, m: int = None):
        if m is None:
            m = 2**self.accuracy
        for _ in range(n):
            yield self.generate_number(m)

class Bucket:
    def __init__(self, min: int, max: int, count: int = 0):
        self.min = min
        self.max = max
        self.count = count

    def __str__(self):
        return f"[{self.min} - {self.max}] {self.count}"

def split_into_buckets(data: list[int], bucket_count: int, max_value: int = 2**31) -> list:
    per_bucket = int(max_value / bucket_count)

    buckets = [Bucket(i*per_bucket, (i+1)*per_bucket) for i in range(bucket_count)]

    for number in data:
        bucket_id = number // per_bucket
        buckets[bucket_id].count += 1
    return buckets


a = 69069
c = 1
m = 2**31

p = 7
q = 3

seed = 15
N = 100_000
buckets = 10

print(f"a = {a}, c = {c}, m = {m}\np = {p}, q = {q}\nseed = {seed}, N = {N}, buckets = {buckets}")


linear_generator = LinearGenerator(a, c, m, seed)
register_generator = RegisterGenerator(p, q, seed)

linear_numbers = list(linear_generator.generate_numbers(N, m))
generator_numbers = list(register_generator.generate_numbers(N, m))

print(f"linear average = {sum(linear_numbers)/N}")
print(f"generator average = {sum(generator_numbers)/N}")

linear_buckets = split_into_buckets(linear_numbers, buckets, m)
generator_buckets = split_into_buckets(generator_numbers, buckets, m)

print("\nLinear buckets:")
for bucket in linear_buckets:
    print(bucket)

print("\nGenerator buckets:")
for bucket in generator_buckets:
    print(bucket)


# linear_probabilities = list(linear_generator.generate_probabilities(N))
# register_probabilities = list(register_generator.generate_probabilities(N))

# print(sum(linear_probabilities)/N)
# print(sum(register_probabilities)/N)

