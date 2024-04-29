import os
import re
import timeit
from pprint import pprint
from colorama import Fore, Style, init

init(autoreset=True)

PROGRAM = 'build/bin/main'
TESTS_IN_FOLDER = 'tests/in'
TESTS_OUT_FOLDER = 'tests/out'

def check_folders():
    if not os.path.exists(TESTS_IN_FOLDER):
        print(Fore.RED + TESTS_IN_FOLDER + ' does not exist')
        return False
    if not os.path.exists(TESTS_OUT_FOLDER):
        print(Fore.RED + TESTS_OUT_FOLDER + ' does not exist')
        return False
    print(Fore.GREEN + 'Folders checked')
    return True

def get_dict():
    dict = {}
    filesIn = os.listdir(TESTS_IN_FOLDER)
    filesOut = os.listdir(TESTS_OUT_FOLDER)
    # in: out
    for fileIn in filesIn:
        for fileOut in filesOut:
            if fileIn.split('.')[0] == fileOut.split('.')[0]:
                dict[fileIn] = fileOut
    return dict

def compare_files(actualFile, expectedFile):
    is_same = True
    with open(actualFile, 'r') as f1:
        with open(expectedFile, 'r') as f2:
            actual = re.sub(r'\s+', ' ', f1.read().strip())
            expected = re.sub(r'\s+', ' ', f2.read().strip())

    actual = actual.split(' ')
    expected = expected.split(' ')
    # if len(actual) != len(expected):
    #     print(Fore.RED + 'Files have different length')
    #     print(Fore.RED + f'Expected: {len(expected)}, got: {len(actual)}')
    #     return False
    for k, (word1, word2) in enumerate(zip(actual, expected)):
        if word1 != word2:
            print(Fore.RED + f'Expected: {word2}, got: {word1} at position {k}')
            # exit(1)
            is_same = False
    return is_same


if __name__ == '__main__':
    if not check_folders():
        exit(1)
    if not os.path.exists(".cache"):
        os.mkdir(".cache")
    dict = get_dict()
    print(Fore.WHITE + f'Loaded {len(dict)} tests')
    average = 0
    for key in dict:
        # if (key == 'is_gameover.in'):
        print(Fore.YELLOW + f'Running test {key}')

        averageInside = 0
        for i in range(5):
            start = timeit.default_timer()
            os.system(f'{PROGRAM} < {TESTS_IN_FOLDER}/{key} > .cache/{key}')
            averageInside += timeit.default_timer() - start
        average += averageInside / 5

        if compare_files(f'.cache/{key}', f'{TESTS_OUT_FOLDER}/{dict[key]}'):
            print(Fore.GREEN + 'Test passed')
        print()
    print(Fore.WHITE + f'Average time: {average / len(dict)}')
