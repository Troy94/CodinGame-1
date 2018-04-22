var list = [];
var n = parseInt(readline());
for (var i = 0; i < n; i++) {
	var t = readline();
	list.push(t);
}

list.sort();
print(list[0]);