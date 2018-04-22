// https://www.codingame.com/ide/puzzle/gravity

let inputs = readline().split(' ');
let w = parseInt(inputs[0]);
let h = parseInt(inputs[1]);
let fill = Array(w).fill(0);

for (let i = 0; i < h; i++) {
    let line = readline();
    for (let j = 0; j < line.length; j++) {
        if (line[j] === '#') {
            fill[j] += 1;
        }
    }
}

for (let i = 0; i < h; i++) {
    let line = '';
    for (let j = 0; j < w; j++) {
        line += fill[j] >= h - i ? '#' : '.';
    }
    print(line);
}
