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

pool = ThreadPoolExecutor()

# Hash function
def hash_password(password: str) -> str:
    return hashlib.sha256(password.encode()).hexdigest()

# Cracking
async def crack_worker(target_hash: str, length: int, prefixes: list[str], loop, found_flag: asyncio.Event):
    for prefix in prefixes:
        if found_flag.is_set():
            return None  # Stop looking for a password
        for combo in itertools.product(CHARS, repeat=length - len(prefix)):
            candidate = prefix + ''.join(combo)

            if found_flag.is_set():
                return None

            result = await loop.run_in_executor(pool, hash_password, candidate)
            if result == target_hash:
                print(f"[✓] Hasło znalezione: {candidate}")
                found_flag.set()
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

    prefix_groups = divide_work(CHARS, 1, NUM_WORKERS)
    loop = asyncio.get_event_loop()
    found_flag = asyncio.Event()

    # Tasks creation
    tasks = [asyncio.create_task(crack_worker(target_hash, password_length, group, loop, found_flag))
             for group in prefix_groups]

    # Wait for not-None value from tasks
    done, pending = await asyncio.wait(tasks, return_when=asyncio.FIRST_COMPLETED)

    # Stop other tasks
    for task in pending:
        task.cancel()

    result = None
    for d in done:
        result = d.result()
        if result:
            break

    
    # Timer stop
    end_time = time.time()

    if result:
        print(f"[✓] Złamane hasło: {result}")
    else:
        print("[x] Nie udało się znaleźć hasła.")

    print(f"[i] Czas wykonania: {end_time - start_time:.2f} sekundy")

if __name__ == "__main__":
    asyncio.run(main())
