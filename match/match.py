import subprocess
from random import *

CC = "g++-13"
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
    n = 5
    ls = list(range(1, n + 1))
    shuffle(ls)
    print(n, file=outfile)
    print(*ls, file=outfile)


def compile_code():
    subprocess.run([CC, "-std=c++23", "-O2", MY_CODE_PATH, "-o", MY_BINARY_PATH])
    subprocess.run([CC, "-std=c++23", "-O2", AC_CODE_PATH, "-o", AC_BINARY_PATH])


def run_code():
    subprocess.run([MY_BINARY_PATH], stdin=open(INPUT_PATH, "r"), stdout=open(MY_OUTPUT_PATH, "w"))
    subprocess.run([AC_BINARY_PATH], stdin=open(INPUT_PATH, "r"), stdout=open(AC_OUTPUT_PATH, "w"))


def compare_output() -> bool:
    my_output = open(MY_OUTPUT_PATH, "r").read()
    ac_output = open(AC_OUTPUT_PATH, "r").read()
    my_output = my_output.strip()
    ac_output = ac_output.strip()
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
