import os

def print_header(test_number):
    print(f'''#include <vector>
using namespace std;
const string path_dict = "../examples/dictionary.txt";
const string path_file = "../test-cases/in/test-{test_number}-in.txt";
vector<char> freq_single = {{'E', 'T', 'A', 'I'}};''', file=open('header.hpp', 'w'))

for i in range(8):
    print(f"Checking Test-Case {i}")
    print_header(i)
    os.system('g++ -std=c++17 main.cpp')
    os.system(f'gtimeout 200s ./a.out > ../test-cases/user-out/user-{i}-out.txt')
    os.system(f'diff ../test-cases/out/test-{i}-out.txt ../test-cases/user-out/user-{i}-out.txt')
    