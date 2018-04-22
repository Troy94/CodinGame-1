// https://www.codingame.com/ide/puzzle/the-greatest-number

var n = parseInt(readline());
var chars = readline().split(' ')
chars.sort();

if(chars.includes('-')){
    if(chars.includes('.')) {
        chars.splice(1, 1);
        chars.splice(2, 0, '.');
    }
}
else{
    chars.reverse();
    if(chars.includes('.')) {
        chars.splice(-1, 1);
        chars.splice(-1, 0, '.');
    }
}

print(parseFloat(chars.join('')));