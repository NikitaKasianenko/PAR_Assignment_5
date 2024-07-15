#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <sstream>

using namespace std;

class QueueList {
public:
    QueueList() : pointer(0), capacity(10) {
        array = new string[capacity];
    }

    ~QueueList() {
        delete[] array;
    }

    void Add(const string& element) {
        if (pointer == capacity) {
            extendArray();
        }
        array[pointer++] = element;
    }

    void Remove(const string& element) {
        for (int i = 0; i < pointer; i++) {
            if (array[i] == element) {
                for (int j = i; j < pointer - 1; j++) {
                    array[j] = array[j + 1];
                }
                pointer--;
                break;
            }
        }
    }

    string GetAt(int index) const {
        return array[index];
    }

    bool Contains(const string& element) const {
        for (int i = 0; i < pointer; i++) {
            if (array[i] == element) {
                return true;
            }
        }
        return false;
    }

    int Count() const {
        return pointer;
    }

    string* begin() const {
        return array;
    }

    string* end() const {
        return array + pointer;
    }

private:
    string* array;
    int pointer;
    int capacity;

    void extendArray() {
        int newCapacity = capacity * 2;
        string* extendedArray = new string[newCapacity];
        for (int i = 0; i < capacity; i++) {
            extendedArray[i] = array[i];
        }
        delete[] array;
        array = extendedArray;
        capacity = newCapacity;
    }
};

QueueList Tokenizated(const string& input) {
    QueueList tokens;
    string curToken;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];
        if (ch == '.' || isdigit(ch) || isalpha(ch) || (ch == '-' && (i == 0 || input[i - 1] == '('))) {
            curToken += ch;
        }
        else if (ch == '*' || ch == '+' || ch == '-' || ch == ',' || ch == '*' || ch == ')' || ch == '(' || ch == '^' || ch == '/') {
            if (!curToken.empty()) {
                tokens.Add(curToken);
                curToken.clear();
            }
            tokens.Add(string(1, ch));
        }
    }

    if (!curToken.empty()) {
        tokens.Add(curToken);
    }

    return tokens;
}

QueueList ShuntingYard(const QueueList& allTokens) {
    QueueList queue;
    stack<string> stack;

    unordered_map<string, int> priority = {
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"(", 0}, {")", 0}, {"m", 4}, {"M", 4},{"a", 4},
    };

    for (const auto& token : allTokens) {
        double token_double;
        istringstream iss(token);
        bool isNumber = (iss >> token_double) ? true : false;

        if (isNumber) {
            queue.Add(token);
        }
        else {
            if (token == "(") {
                stack.push(token);
            }
            else if (token == ",") {
                while (!stack.empty() && stack.top() != "(") {
                    queue.Add(stack.top());
                    stack.pop();
                }
            }
            else if (token == ")") {
                while (!stack.empty() && stack.top() != "(") {
                    queue.Add(stack.top());
                    stack.pop();
                }
                stack.pop();
            }
            else {
                while (!stack.empty() && priority[stack.top()] >= priority[token]) {
                    queue.Add(stack.top());
                    stack.pop();
                }
                stack.push(token);
            }
        }
    }

    while (!stack.empty()) {
        queue.Add(stack.top());
        stack.pop();
    }

    return queue;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double Abs(double a) {
    return (a < 0) ? a * -1 : a;
}

string Calculation(QueueList& shuntingYard) {
    stack<string> resultStack;

    for (const auto& element : shuntingYard) {
        double digit;
        istringstream iss(element);
        if (iss >> digit) {
            resultStack.push(element);
        }
        else {
            if (element == "a") {
                double digit = stod(resultStack.top());
                resultStack.pop();
                resultStack.push(to_string(Abs(digit)));
            }
            else {
                double digit2 = stod(resultStack.top());
                resultStack.pop();
                double digit1 = stod(resultStack.top());
                resultStack.pop();

                if (element == "+") {
                    resultStack.push(to_string(digit1 + digit2));
                }
                else if (element == "-") {
                    resultStack.push(to_string(digit1 - digit2));
                }
                else if (element == "*") {
                    resultStack.push(to_string(digit1 * digit2));
                }
                else if (element == "/") {
                    resultStack.push(to_string(digit1 / digit2));
                }
                else if (element == "^") {
                    resultStack.push(to_string(pow(digit1, digit2)));
                }
                else if (element == "m") {
                    resultStack.push(to_string(min(digit1, digit2)));
                }
                else if (element == "M") {
                    resultStack.push(to_string(max(digit1, digit2)));
                }
            }
        }
    }

    return resultStack.top();
}

string replaceFunctions(const string& expression) {
    string result = expression;

    size_t pos = result.find("min(");
    while (pos != string::npos) {
        result.replace(pos, 4, "m(");
        pos = result.find("min(", pos + 1);
    }

    pos = result.find("max(");
    while (pos != string::npos) {
        result.replace(pos, 4, "M(");
        pos = result.find("max(", pos + 1);
    }

    pos = result.find("abs(");
    while (pos != string::npos) {
        result.replace(pos, 4, "a(");
        pos = result.find("abs(", pos + 1);
    }

    return result;
}

int main() {
    string expression;
    getline(cin, expression);


    expression = replaceFunctions(expression);
    QueueList tokens = Tokenizated(expression);
    QueueList rpn = ShuntingYard(tokens);
    string result = Calculation(rpn);

    cout << result << endl;
    return 0;
}
