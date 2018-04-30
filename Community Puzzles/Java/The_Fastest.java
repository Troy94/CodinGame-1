/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/the-fastest

import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        String timings[] = new String[n];

        for (int i = 0; i < n; i++) {
            String t = in.next();
            timings[i] = t;
        }

        Arrays.sort(timings);
        System.out.println(timings[0]);
    }
}