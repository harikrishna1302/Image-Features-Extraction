# Image-Features-Extraction
Computer Vision approaches is of two categories:<br />
1. Appearence-based<br />
2. Model-based or point-based.<br />
This project implements image features using LBP(Local Binary Pattern) which is an appearence based one.
## Technologies
* VisualStudio.
* OpenCV and Boost libraries.
* C++ programming.<br />
Make sure, the input and output directories should be stored in the same project file directory. These two directories' names should be given in command line arguments in visualstudio. <br />
./input ./output
## Implementation
* Program will take TWO arguments:<br />
1. Input image directory <br />
2. Output image directory
* Get the FILENAMES for all .png images in the input directory and sort them alphabetically.
*  For each filename in the list, compute the LBP labels.<br />
Load the image and we will use 8 samples with a radius of 1. For simplicity, we may directly use the 8-neighbors around a given pixel. Grab the neighbor values going clockwise around the current pixel, starting at the “north” neighbor: (row-1, col), (row-1, col+1), (row, col+1), and so on. For thresholding, assign a 1 to a neighbor value ONLY if the value is GREATER than that of the center pixel.
(we use rotation-invariant uniform LBP labels.)<br />
If the number of 1-0 or 0-1 transitions is less than or equal to 2, then use the number of “one” neighbors to determine the label. If the number of transitions is greater than 2, then use the label (sample cnt + 1) = (8 + 1) = 9.
* For each image, append its filename and histogram to a SINGLE file “HISTOGRAMS.txt”.
* Compute and save the histogram distances from the histogram for “droid_1.png”. 
