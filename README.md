# Delivery-Bot
Line follower bot that delivers items from multile source to destination in a fixed map, with real-time obstacle resolution feature that are dynamic in nature.

# Virtualization: 
I am using VREP software to visualize and run the bot virtually

# Hardware used:
The final code is meant to be transferred to Arduino mega.

# Path planning algorithm used:
I have used Dijkstras’s algorithm to find the shortest path between pickup and drop points and also when changing the path during obstacle detection.
This algorithm finds the shortest path based on the ‘Weights’ of the edges between the nodes.

# Algorithm’s specific implementation: 
I have used a graph for representing the map and have used weights to represent distances between nodes (zero where no connection) and another matrix to input the relative direction of one node to another.
Then I  passed the graph to the dijkstras function which computes the cost to travel from source to each node and also assigns a parent node to each node of the graph.
Then I have used the function printsolution to make a solution of nodes (based on the parent nodes of each node).
Then finally, path array is formed consisting of actual directions that bot has to travel using the Dir matrix. 
After reaching any pickup point OR any dropout, the bot gives its location back to the dijkstras’s function to calculate new shortest path to next destination.
This process continues until all 4 fruits are placed or all six pickup points are checked.
I have made the program assuming that the obstacles are at the middle of and edge of the map so bot has to return to previous node before recalculating the path (as you can see in the video).

Outut:
Video URL:   https://youtu.be/QUbwssJymbI
