import asyncio
import hashlib
import itertools
import string
import sys
import time
from concurrent.futures import ThreadPoolExecutor

# Characters allowed in password
CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()"

# Number of async tasks
NUM_WORKERS = 8

# Calculates SHA256 hash for given password
def hash_password(password: str) -> str:
    return hashlib.sha256(password.encode()).hexdigest()

# Password search in a prefix scope
async def crack_worker(target_hash: str, length: int, prefixes: list[str], loop):
    with ThreadPoolExecutor() as pool:
        for prefix in prefixes:
            # Combinations for full password length
            for combo in itertools.product(CHARS, repeat=length - len(prefix)):
                candidate = prefix + ''.join(combo)
                # function in additional thread
                result = await loop.run_in_executor(pool, hash_password, candidate)
                if result == target_hash:
                    print(f"[✓] Hasło znalezione: {candidate}")
                    return candidate
    return None

# Prefix division between async workers
def divide_work(charset, prefix_length, workers):
    prefixes = [''.join(p) for p in itertools.product(charset, repeat=prefix_length)]
    chunk_size = len(prefixes) // workers
    return [prefixes[i*chunk_size:(i+1)*chunk_size] for i in range(workers)]

async def main():
    if len(sys.argv) != 3:
        print("Użycie: python3 cpu_crack.py <HASH_SHA256> <DŁUGOŚĆ_HASŁA>")
        sys.exit(1)

    target_hash = sys.argv[1]
    try:
        password_length = int(sys.argv[2])
    except ValueError:
        print("Długość hasła musi być liczbą całkowitą.")
        sys.exit(1)

    print(f"[i] Rozpoczynanie łamania hasła: długość={password_length}, hash={target_hash}")

    # Timer start
    start_time = time.time()

    # Work division: prefixes of length 1 for 8 workers
    prefix_groups = divide_work(CHARS, 1, NUM_WORKERS)
    loop = asyncio.get_event_loop()

    # Tasks start
    tasks = [crack_worker(target_hash, password_length, group, loop) for group in prefix_groups]
    results = await asyncio.gather(*tasks)

    # Timer stop
    end_time = time.time()

    # Result
    for res in results:
        if res:
            print(f"[✓] Złamane hasło: {res}")
            break
    else:
        print("[x] Nie udało się znaleźć hasła.")

    print(f"[i] Czas wykonania: {end_time - start_time:.2f} sekundy")

if __name__ == "__main__":
    asyncio.run(main())
