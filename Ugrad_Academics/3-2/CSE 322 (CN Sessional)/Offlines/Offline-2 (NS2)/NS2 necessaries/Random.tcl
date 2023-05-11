
#puts [lindex $argv 0]

proc My_Random {min max} {

 set range [expr ($max-$min+1)]
 set x [expr int(rand()*100)]
 set y [expr ($x % $range)]
 set rand_num [expr ($y+$min)]
 return $rand_num

}

#set min [lindex $argv 0]
#set max [lindex $argv 1]

set x [My_Random 1 5]
puts $x
