# ifndef BMP_H
# define BMP_H
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#pragma warning(disable:4996)

const double EPSILON = 0.00000001;


struct BITMAPFILEHEADER
{
    //unsigned short bfType;                // 19778, must be a BM string, the corresponding hexadecimal is 0x4d42, and the decimal is 19778, otherwise it is not a bmp format file
    unsigned int   fileSize;                // File size in bytes (2-5 bytes)
    unsigned short reserved1;               // Reserved, must be set to 0 (6-7 bytes)
    unsigned short reserved2;               // Reserved, must be set to 0 (8-9 bytes)
    unsigned int   startingOffsetData;      // Offset from file header to pixel data (10-13 bytes)
};

//Image information header structure
struct BITMAPINFOHEADER
{
    unsigned int    infoSize;          // The size of this structure (14-17 bytes)
    long            width;         // The width of the image (18-21 bytes)
    long            height;        // The height of the image (22-25 bytes)
    unsigned short  planes;        // Indicates the plane attribute of the bmp picture, obviously the display has only one plane, so it is always equal to 1 (26-27 bytes)
    unsigned short  bitPerPixel;      // The number of bits occupied by a pixel, generally 24 (28-29 bytes)
    unsigned int    compression;   // Describe the type of image data compression, 0 means no compression. (30-33 bytes)
    unsigned int    imageSize;     // The size of pixel data, this value should be equal to fileSize-startingOffsetData (34-37 bytes) in the file header structure above
    long            horizontal; // Describe the horizontal resolution, expressed in pixels/meter. Generally 0 (38-41 bytes)
    long            vertical; // Describe the vertical resolution, expressed in pixels/meter. Generally 0 (42-45 bytes)
    unsigned int    clrUsed;       // Describe the number of color indexes in the color table actually used by the bitmap (if set to 0, all palette items are used). (46-49 bytes)
    unsigned int    clrImportant;  // Explain the number of color indexes that have an important influence on the image display. If it is 0, it means all are important. (50-53 bytes)

    unsigned int RedMask;       /* Mask identifying bits of red component */
    unsigned int GreenMask;     /* Mask identifying bits of green component */
    unsigned int BlueMask;      /* Mask identifying bits of blue component */
    unsigned int AlphaMask;     /* Mask identifying bits of alpha component */
    unsigned int CSType;        /* Color space type */
    long  RedX;          /* X coordinate of red endpoint */
    long  RedY;          /* Y coordinate of red endpoint */
    long  RedZ;          /* Z coordinate of red endpoint */
    long  GreenX;        /* X coordinate of green endpoint */
    long  GreenY;        /* Y coordinate of green endpoint */
    long  GreenZ;        /* Z coordinate of green endpoint */
    long  BlueX;         /* X coordinate of blue endpoint */
    long  BlueY;         /* Y coordinate of blue endpoint */
    long  BlueZ;         /* Z coordinate of blue endpoint */
    unsigned int GammaRed;      /* Gamma red coordinate scale value */
    unsigned int GammaGreen;    /* Gamma green coordinate scale value */
    unsigned int GammaBlue;     /* Gamma blue coordinate scale value */
};

//24 bitmap pixel information structure, namely palette
void showBmpHead();
void showBmpInfoHead();
void convertToLittleEndian(unsigned char matrix[], int start, int byteLength, int data);
void writeBMP(std::vector<std::vector<int>> map, std::string nameFile);
int** readBMP();

//==================================================================================


struct Point {
    //Point coordinates, here is calculated according to C++ array for convenience, 
    //x represents horizontal row, y represents vertical column
    int x, y; 
    double F, G, H; //F = G + H
    Point* parent; //The coordinates of parent, no pointer is used here, thus simplifying the code
    
    Point(int _x, int _y) : x(_x), y(_y), F(0), G(0), H(0), parent(NULL) {} // variable initialization
};

bool readFile(std::string fileName, Point& start, Point& end, int& limitedDistance);
void writeFile(std::string fileName, double pathCost, int interactivePoints);
void executeDataProcessing(Point& start, Point& end, int rows);
std::vector<std::vector<int>> convert(int** map);



class Astar {
public:
    void initAstar(std::vector<std::vector<int>>& map);
    std::list<Point*> getPath(Point& startPoint, Point& endPoint, int limitedDistance, int type);
    int getNumOfInteractivePoints();
    void setNumOfInteractivePoints(int value);
    double getPathCost();

private:
    Point* findPath(Point& startPoint, Point& endPoint, int limitedDistance, int type);
    std::vector<Point*> getSurroundPoints(const Point* point, int limitedDistance, std::vector<int>& values);
    //Determine whether a point can be used for the next judgment
    bool isCanReach(const Point* point, const Point* target, int limitedDistance, std::vector<int>& values);
    //Determine whether the open/close list contains a certain point
    Point* isInList(const std::list<Point*>& list, const Point* point) const;
    //Return the node with the smallest F value from the open list
    Point* getLeastFPoint();

    bool checkValueExists(const std::vector<int>& arr, int value);

    //Calculate FGH value and sign function
    double calcG(Point* temp_start, Point* point);
    double calcH(Point* point, Point* end, int limitedDistance, int type);
    double calcF(Point* point);
    int getSignFunc(int number);

    //Heuristic functions
    double calcHByHeuristic1(Point* point, Point* end, int limitedDistance);
    double calcHByHeuristic2(Point* point, Point* end, int limitedDistance);
    double calcHByHeuristic3(Point* point, Point* end, int limitedDistance);

private:
    std::vector<std::vector<int>> _map; //Matrix
    std::list<Point*> _openList; //Open the list
    std::list<Point*> _closeList; //Close the list
    int _interactivePoints = 0; //Initially does not interaction
    double _pathCost = 0;
};


#endif