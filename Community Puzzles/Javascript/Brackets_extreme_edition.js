// https://www.codingame.com/ide/puzzle/brackets-extreme-edition

let brackets = ['[', '{', '('];
let complement = {
    ']': '[',
    '}': '{',
    ')': '('
};

var expression = readline();
var stack = [];
var i;
for (i = 0; i < expression.length; i++) {
    let c = expression[i];
    if (brackets.includes(c)) {
        stack.push(c);
    }
    else if (c in complement) {
        if (complement[c] === stack[stack.length - 1]) {
            stack.pop();
        }
        else {
            break;
        }
    }
}

print(stack.length === 0 && i === expression.length ? 'true' : 'false');
