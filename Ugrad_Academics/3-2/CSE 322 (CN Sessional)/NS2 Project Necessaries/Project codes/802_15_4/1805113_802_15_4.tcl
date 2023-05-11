# simulator
set ns [new Simulator]

#taking command line argument <packets_per_second,number of nodes,number of flows>
set num_of_nodes [lindex $argv 0]
set num_of_flows [lindex $argv 1]
set packets_per_second [lindex $argv 2]
set tx_factor [lindex $argv 3]




# ======================================================================
# Define options

set val(chan)         Channel/WirelessChannel  ;# channel type
set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
set val(ant)          Antenna/OmniAntenna      ;# Antenna type
set val(ll)           LL                       ;# Link layer type
set val(ifq)          Queue/DropTail/PriQueue  ;# Interface queue type
set val(ifqlen)       10                      ;# max packet in ifq
set val(netif)        Phy/WirelessPhy/802_15_4         ;# network interface type
set val(mac)          Mac/802_15_4               ;# MAC type
set val(rp)           DSDV                     ;# ad-hoc routing protocol 
set val(nn)           $num_of_nodes            ;# number of mobilenodes
set val(nf)           $num_of_flows            ;# number of flows
set val(grid_size)    1500                     ;# grid size    
set val(packet_rate)  $packets_per_second      ;# packets_per_second 
set val(Tx_factor)    $tx_factor					;# Tx_factor 1,2,3,4,5 (Coverage area parameter)

#Energy model



set tcp_interval		[expr 1.0/$packets_per_second]


# =======================================================================

# trace file
set trace_file [open trace.tr w]
$ns trace-all $trace_file

# nam file
set nam_file [open animation.nam w]
$ns namtrace-all-wireless $nam_file $val(grid_size) $val(grid_size)

# topology: to keep track of node movements
set topo [new Topography]
$topo load_flatgrid $val(grid_size) $val(grid_size) 



# general operation director for mobilenodes
create-god $val(nn)


# node configs
# ======================================================================

# $ns node-config -addressingType flat or hierarchical or expanded
#                  -adhocRouting   DSDV or DSR or TORA
#                  -llType	   LL
#                  -macType	   Mac/802_11
#                  -propType	   "Propagation/TwoRayGround"
#                  -ifqType	   "Queue/DropTail/PriQueue"
#                  -ifqLen	   50
#                  -phyType	   "Phy/WirelessPhy"
#                  -antType	   "Antenna/OmniAntenna"
#                  -channelType    "Channel/WirelessChannel"
#                  -topoInstance   $topo
#                  -energyModel    "EnergyModel"
#                  -initialEnergy  (in Joules)
#                  -rxPower        (in W)
#                  -txPower        (in W)
#                  -agentTrace     ON or OFF
#                  -routerTrace    ON or OFF
#                  -macTrace       ON or OFF
#                  -movementTrace  ON or OFF

# ======================================================================

$ns node-config -adhocRouting $val(rp) \
                -llType $val(ll) \
                -macType $val(mac) \
                -ifqType $val(ifq) \
                -ifqLen $val(ifqlen) \
                -antType $val(ant) \
                -propType $val(prop) \
                -phyType $val(netif) \
                -topoInstance $topo \
                -channelType $val(chan) \
                -agentTrace ON \
                -routerTrace ON \
                -macTrace OFF \
                -movementTrace OFF 
                #-energyModel $val(energymodel_11) \
			    #-idlePower $val(idlepower_11) \
			    #-rxPower $val(rxpower_11) \
			    #-txPower $val(txpower_11) \
          		#-sleepPower $val(sleeppower_11) \
          		#-transitionPower $val(transitionpower_11) \
			    #-transitionTime $val(transitiontime_11) \
			    #-initialEnergy $val(initialenergy_11)


#setting packet rate
Mac/802_11 set dataRate_ 1Mb
Mac/802_11 set syncFlag_ 1
Mac/802_11 set dutyCycle_ tcp_interval


#Generating a random number with in a range
proc My_Random {min max} {

 set range [expr ($max-$min+1)]
 set x [expr int(rand()*100)]
 set y [expr ($x % $range)]
 set rand_num [expr ($y+$min)]
 return $rand_num

}


# create nodes

set Even_X_value 100
set Odd_X_value 200 


for {set i 0} {$i < $val(nn) } {incr i} {
 
    set node($i) [$ns node]
    $node($i) random-motion 0       ;# disable random motion

    set check [expr ($i % 2)]
	if { $check == 0 } {

        
        set X_value $Even_X_value 
    	set Y_value [expr (100 +($i / 2)*20 )]

    	$node($i) set X_ $X_value 
    	$node($i) set Y_ $Y_value
    	$node($i) set Z_ 0
        $node($i) set range_ [expr (20*$tx_factor)]


    }

	if { $check == 1 } {

        set X_value $Odd_X_value 
    	set Y_value [expr (100 +($i / 2)*20 )]

    	$node($i) set X_ $X_value 
    	$node($i) set Y_ $Y_value
    	$node($i) set Z_ 0
        $node($i) set range_ [expr (20*$tx_factor)]

    }

  

	#seeting initial position and radius = 10
    $ns initial_node_pos $node($i) 10


} 







# creating flows

for {set i 0} {$i < $val(nf) } {incr i}  {

    #Here "random source destination" will be applied
    #Randomly choosing a src from 1st column 
    #Randomly choosing a dest from 2nd column 

 
    set min 0
    set max [expr (($val(nn)/2)-1)]
    set src [My_Random  $min $max]
    set dest [My_Random $min $max]

    set src [expr (2 * $src)]
    set dest [expr ((2 * $dest)+1)]
  

    # Traffic config for UDP connection
    # create agent
    set tcp [new Agent/TCP/Reno]
    set tcp_sink [new Agent/TCPSink]
    # attach to nodes
    $ns attach-agent $node($src) $tcp
    $ns attach-agent $node($dest) $tcp_sink
    # connect agents
    $ns connect $tcp $tcp_sink
    $tcp set maxseq_ $packets_per_second
    $tcp set fid_ $i

    # Traffic generator
    set ftp [new Application/FTP]
    # attach to agent
    $ftp attach-agent $tcp
	
    
    # start traffic generation
    $ns at 1.0 "$ftp start"

 
}


# Stop nodes(routers)
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at 100.0 "$node($i) reset"
}

# End Simulation
$ns at 50.0001 "finish"
$ns at 50.0002 "halt_simulation"


# procedure to plot the congestion window
# cwnd_ used from tcp-reno.cc file
proc plotWindow {tcpSource outfile} {
   global ns
   set now [$ns now]
   set cwnd_ [$tcpSource set cwnd_]
   #set ssthreash [$tcpSource set ssthresh_]

# the data is recorded in a file called outfile.csv
   puts  $outfile  "$now,$cwnd_"
   $ns at [expr $now+0.1] "plotWindow $tcpSource  $outfile"
}

set outfile [open  "outfile.csv"  w]
$ns  at  1.0  "plotWindow $tcp  $outfile"


# call final function
proc finish {} {
 	#exec nam congestion.nam &
 	#exec xgraph congestion.xg -geometry 300x300 &
    #exit 0   

    global ns trace_file nam_file
    $ns flush-trace
    close $trace_file
    close $nam_file
}

proc halt_simulation {} {
    global ns
    puts "Simulation ending"
    $ns halt
}




# Run simulation
puts "Simulation starting"
$ns run

