import subprocess

def run_echo(input_data):
    process = subprocess.Popen(
        ['tets.exe'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_echo():
    tests = [
        {
            "input": "1+1\n",
            "expected_output": "2.000000"
        },
        {
            "input": "min(2,1)\n",
            "expected_output": "1.000000"
        },
        {
            "input": "max(2,1)\n",
            "expected_output": "2.000000"
        },
        {
            "input": "max(min(1,2),min(3,2))\n",
            "expected_output": "2.000000"
        },
        {
            "input": "max(3^2,min(3,2))\n",
            "expected_output": "9.000000"
        },
        {
            "input": "abs(-5^3)\n",
            "expected_output": "125.000000"
        }
    ]
    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_echo(input_data)

        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")

if __name__ == "__main__":
    test_echo()
