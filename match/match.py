import subprocess
from random import *

CC = "g++-13"
CC_ARGS = "-std=c++20 -O2 -Wall -DLOCAL"
CUR_PATH = "/".join(__file__.split("/")[:-1])
MY_CODE_PATH = f"{CUR_PATH}/Zme.cpp"
AC_CODE_PATH = f"{CUR_PATH}/Zac.cpp"
MY_BINARY_PATH = f"{CUR_PATH}/me"
AC_BINARY_PATH = f"{CUR_PATH}/ac"
MY_OUTPUT_PATH = f"{CUR_PATH}/outputs/me.out"
AC_OUTPUT_PATH = f"{CUR_PATH}/outputs/ac.out"
INPUT_PATH = f"{CUR_PATH}/input.txt"

NUM_TESTS = 100


def make_input(outfile):
    """
    TODO: Modify this function to randomly generate input for the problem
    """
    T = 1
    outfile.write(f"{T}\n")
    for t in range(T):
        N = randint(1, 100)
        outfile.write(f"{N}\n")
        for _ in range(N):
            outfile.write(f"{randint(1, N)} {randint(1, N)}\n")


def compile_code():
    subprocess.run([CC, MY_CODE_PATH, CC_ARGS, MY_BINARY_PATH])
    subprocess.run([CC, AC_CODE_PATH, CC_ARGS, AC_BINARY_PATH])


def run_code():
    subprocess.run([MY_BINARY_PATH], stdin=open(INPUT_PATH, "r"), stdout=open(MY_OUTPUT_PATH, "w"))
    subprocess.run([AC_BINARY_PATH], stdin=open(INPUT_PATH, "r"), stdout=open(AC_OUTPUT_PATH, "w"))


def compare_output() -> bool:
    my_output = open(MY_OUTPUT_PATH, "r").read()
    ac_output = open(AC_OUTPUT_PATH, "r").read()
    if my_output == ac_output:
        print("AC")
        return True
    else:
        print("WA")
        return False


def cleanup():
    subprocess.run(["rm", MY_BINARY_PATH])
    subprocess.run(["rm", AC_BINARY_PATH])


if __name__ == "__main__":
    print("Compiling code...")
    compile_code()
    print("Running tests...")
    for i in range(NUM_TESTS):
        with open(INPUT_PATH, "w") as infile:
            make_input(infile)
        print(f"Running test {(i + 1):2}", end=": ")
        run_code()
        if not compare_output():
            print("Test case:")
            print(open(INPUT_PATH, "r").read())
            break
    cleanup()
