This is a repository about the system that notifies incoming user about the status of a Toilet  
   
 It tells user whether the Toilet is "FREE" or "OCCUPIED"

The 'OuterNode' is a directory containg a firmware that runs in a node placed outside the door (Where Incoming user interact with).

The 'InnerNode' is a directory containg a firmware that runs in a node placed inside the door. This is a decision maker about the system operation.

The Two nodes are able to communicate using the ESP_NOW protocal. A very fast and reliable for this project.
