Object object

# predicted object linear velocity on x and y axis
geometry_msgs/Twist velocity

# predicted trajectory poses, in order of timstamp increasing
geometry_msgs/PoseStamped[] prediction

# previos xyz coordinates of object, in order of timstamp increasing
geometry_msgs/PointStamped[] trajectory
