select(STDOUT); $| = 1; # DO NOT REMOVE

while (1) {
    chomp($enemy1 = <STDIN>); # name of enemy 1
    chomp($dist1 = <STDIN>); # distance to enemy 1
    chomp($enemy2 = <STDIN>); # name of enemy 2
    chomp($dist2 = <STDIN>); # distance to enemy 2
    
    if($dist1<$dist2){
        print "$enemy1\n"
    }
    else{
        print "$enemy2\n"
    }
}