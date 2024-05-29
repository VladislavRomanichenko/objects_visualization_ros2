# unique id of object (e.g. tracking id)
int32 id

# object class (implementation depended)
int32 label

# object confidence from 0 to 1, but other values may have special meaning
float32 score

int32 x # x-coordinate of the top-left corner
int32 y # y-coordinate of the top-left corner
int32 width # width of the bounding box
int32 height # height of the bounding box
