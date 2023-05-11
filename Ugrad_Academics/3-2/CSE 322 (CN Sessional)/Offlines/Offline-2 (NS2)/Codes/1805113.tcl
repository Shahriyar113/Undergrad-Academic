# simulator
set ns [new Simulator]

#taking command line argument <area_size,number of nodes,number of flows>
set area_size [lindex $argv 0]
set num_of_nodes [lindex $argv 1]
set num_of_flows [lindex $argv 2]


# ======================================================================
# Define options

set val(chan)         Channel/WirelessChannel  ;# channel type
set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
set val(ant)          Antenna/OmniAntenna      ;# Antenna type
set val(ll)           LL                       ;# Link layer type
set val(ifq)          CMUPriQueue              ;# Interface queue type
set val(ifqlen)       50                       ;# max packet in ifq
set val(netif)        Phy/WirelessPhy          ;# network interface type
set val(mac)          Mac/802_11               ;# MAC type
set val(rp)           DSR                      ;# ad-hoc routing protocol 
set val(nn)           $num_of_nodes            ;# number of mobilenodes
set val(nf)           $num_of_flows            ;# number of flows
set val(grid_size)    $area_size               ;# grid size     

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


#Generating a random number with in a range
proc My_Random {min max} {

 set range [expr ($max-$min+1)]
 set x [expr int(rand()*100)]
 set y [expr ($x % $range)]
 set rand_num [expr ($y+$min)]
 return $rand_num

}


# create nodes
set num_of_columns [expr ($val(nn)/4)] ;#letting, always num_of_rows = 4
set minimum_distance_between_two_nodes [expr ($val(grid_size)/25)] ;#because highest num of columns can be
                                                                 ;# 25 (when num of node =100) 
set minimum_distance_between_two_nodes [expr ($minimum_distance_between_two_nodes - 5)]


for {set i 0} {$i < $val(nn) } {incr i} {
 
    set node($i) [$ns node]
    $node($i) random-motion 0       ;# disable random motion
    
    set X_value [expr ((($i % $num_of_columns)*$minimum_distance_between_two_nodes)+100)]
    set Y_value [expr ((($i / $num_of_columns)*$minimum_distance_between_two_nodes)+100)]

    $node($i) set X_ $X_value 
    $node($i) set Y_ $Y_value
    $node($i) set Z_ 0

	#seeting initial position and radius = 10
    $ns initial_node_pos $node($i) 10

    #setting a random speed between 1m/s and 5m/s for each node
    set speed [My_Random 1 5]
    
    #each node will start moving from 1 sec
    #each node will move parallel top x axis

    set moving_distance_X [expr ($X_value+20)]
	set moving_distance_Y [expr ($Y_value+20)]
     
    $ns at 1.0 "$node($i) setdest $moving_distance_X $moving_distance_Y $speed"
   
   
} 







# creating flows
set num_of_flows_created 0

while { $num_of_flows_created < $val(nf) } {

    #Here "random source destination" will be applied

    #set nn_half [expr $val(nn)/2]	
    #set start_src 0
    #set end_src [expr $nn_half-1]

    #set start_dest $nn_half
    #set end_dest [expr $val(nn)-1]

    #set src [My_Random $start_src $end_src]
    #set dest [My_Random $start_dest $end_dest]


    #Here "random source destination" is applied
    set min 0
    set max [expr ($val(nn)-1)]
    set src [My_Random  $min $max]
    set dest [My_Random $min $max]
    
    if { $src == $dest } {

      continue 

    }

    incr num_of_flows_created


    # Traffic config for UDP connection
    # create agent
    set udp [new Agent/UDP]
    set null [new Agent/Null]
	$udp set class_ 2
    # attach to nodes
    $ns attach-agent $node($src) $udp
    $ns attach-agent $node($dest) $null
    # connect agents
    $ns connect $udp $null
    $udp set fid_ $i

    # Traffic generator
    #Setup a CBR over UDP connection
	set cbr [new Application/Traffic/CBR]
	$cbr attach-agent $udp
	$cbr set type_ CBR
	$cbr set packet_size_ 1000
	$cbr set rate_ 1mb
	$cbr set random_ false

    
    # start traffic generation
    $ns at 1.0 "$cbr start"
}



# End Simulation

# Stop nodes(routers)
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at 50.0 "$node($i) reset"
}


# call final function
proc finish {} {
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

$ns at 50.0001 "finish"
$ns at 50.0002 "halt_simulation"



# Run simulation
puts "Simulation starting"
$ns run

