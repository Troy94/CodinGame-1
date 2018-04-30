/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/the-fastest

package main

import "fmt"
import "sort"

func main() {
	var n int
	fmt.Scan(&n)
	var a []string

	for i := 0; i < n; i++ {
		var t string
		fmt.Scan(&t)
		a = append(a, t)
	}

	sort.Strings(a)
	fmt.Println(a[0])
}
