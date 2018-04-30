/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/onboarding

import java.util.*;
import java.io.*;
import java.math.*;

class Player {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int lightX = in.nextInt();
        int lightY = in.nextInt();
        int thorX = in.nextInt();
        int thorY = in.nextInt();

        while (true) {
            String res = "";
            if (lightY < thorY) {
                res += "N";
                thorY--;
            } else if (lightY > thorY) {
                res += "S";
                thorY++;
            }

            if (lightX < thorX) {
                res += "W";
                thorX--;
            } else if (lightX > thorX) {
                res += "E";
                thorX++;
            }

            System.out.println(res);
        }
    }
}

// Solved