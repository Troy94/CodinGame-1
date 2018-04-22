// https://www.codingame.com/ide/puzzle/may-the-triforce-be-with-you!

var n = parseInt(readline());

for (let i = 1; i <= n; i++) {
    let line = Array(2 * n - i).fill(' ');
    line = line.concat(Array(2 * i - 1).fill('*'));
    if (i === 1) {
        line[0] = '.';
    }
    print(line.join(''));
}

for (let i = 1; i <= n; i++) {
    let line = Array(n - i).fill(' ');
    line = line.concat(Array(2 * i - 1).fill('*'));
    line = line.concat(Array(2 * (n - i) + 1).fill(' '));
    line = line.concat(Array(2 * i - 1).fill('*'));
    print(line.join(''));
}
