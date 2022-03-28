#include "Astar.h"

BITMAPFILEHEADER bitmapHeader;
BITMAPINFOHEADER bitmapInfor;
void showBmpHead()
{  //Define the function of displaying information, pass in the file header structure
    std::cout << "\n=======BIT MAP FILE HEADER=======\n" << std::endl;
    std::cout << "BMP file size: " << bitmapHeader.fileSize / 1024 << " byte" << std::endl;
    std::cout << "Reserved words (1): " << bitmapHeader.reserved1 << std::endl;
    std::cout << "Reserved words: (2) " << bitmapHeader.reserved2 << std::endl;
    std::cout << "Offset bytes starting data: " << bitmapHeader.startingOffsetData << std::endl;
}
void showBmpInfoHead()
{//Define the function to display the information, and the information header structure is passed in
    std::cout << "\n=======BIT MAP INFORMATION HEADER=======\n" << std::endl;
    std::cout << "The size of Info header: " << bitmapInfor.infoSize << std::endl;
    std::cout << "Bitmap width: " << bitmapInfor.width << std::endl;
    std::cout << "Bitmap height: " << bitmapInfor.height << std::endl;
    std::cout << "The number of planes of the image: " << bitmapInfor.planes << std::endl;
    std::cout << "Number of bits per pixel: " << bitmapInfor.bitPerPixel << std::endl;
    std::cout << "Compression method: " << bitmapInfor.compression << std::endl;
    std::cout << "Image size: " << bitmapInfor.imageSize << std::endl;
    std::cout << "Horizontal resolution: " << bitmapInfor.horizontal << std::endl;
    std::cout << "Vertical resolution: " << bitmapInfor.vertical << std::endl;
    std::cout << "Number of colors used: " << bitmapInfor.clrUsed << std::endl;
    std::cout << "Number of important colors: " << bitmapInfor.clrImportant << std::endl;

    std::cout << "\n*******Bit Map version 4 has been added 17 extra fields*******\n" << std::endl;
    std::cout << "Red Mask: " << bitmapInfor.RedMask << std::endl;
    std::cout << "GreenMask: " << bitmapInfor.GreenMask << std::endl;
    std::cout << "BlueMask: " << bitmapInfor.BlueMask << std::endl;
    std::cout << "AlphaMask: " << bitmapInfor.AlphaMask << std::endl;
    std::cout << "CSType: " << bitmapInfor.CSType << std::endl;
    std::cout << "RedX: " << bitmapInfor.RedX << std::endl;
    std::cout << "RedY: " << bitmapInfor.RedY << std::endl;
    std::cout << "RedZ: " << bitmapInfor.RedZ << std::endl;
    std::cout << "GreenX: " << bitmapInfor.GreenX << std::endl;
    std::cout << "GreenY: " << bitmapInfor.GreenY << std::endl;
    std::cout << "GreenZ: " << bitmapInfor.GreenZ << std::endl;
    std::cout << "BlueX: " << bitmapInfor.BlueX << std::endl;
    std::cout << "BlueY: " << bitmapInfor.BlueY << std::endl;
    std::cout << "BlueZ: " << bitmapInfor.BlueZ << std::endl;
    std::cout << "GammaRed: " << bitmapInfor.GammaRed << std::endl;
    std::cout << "GammaGreen: " << bitmapInfor.GammaGreen << std::endl;
    std::cout << "GammaBlue: " << bitmapInfor.GammaBlue << std::endl;
    std::cout << "========================================================" << std::endl;
}

void convertToLittleEndian(unsigned char matrix[], int start, int byteLength, int data) {
    for (int i = 0; i < byteLength; i++) {
        matrix[start] = (unsigned char)(data >> i * 8);
        start++;
    }
}

void writeBMP(std::vector<std::vector<int>> map, std::string nameFile) {
    unsigned char header[14] = {
    'B','M',
    0,0,0,0, // size in bytes
    0,0, // app data
    0,0, // app data
    0,0,0,0 // start of data offset
    };
    unsigned char info[108] = {
        0,0,0,0, // info hd size
        0,0,0,0, // width
        0,0,0,0, // heigth
        0,0, // number color planes
        0,0, // bits per pixel
        0,0,0,0, // compression 
        0,0,0,0, // image bits size
        0,0,0,0, // horz resoluition in pixel / m
        0,0,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0,0,0,0, // #colors in pallete
        0,0,0,0, // #important colors
        0,0,0,0, // 17 extra fields in bitmap version 4  
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0
    };
    int padSize = (4 - (bitmapInfor.width * 4) % 4) % 4;
    // --------File Header
    convertToLittleEndian(header, 2, 4, bitmapHeader.fileSize);
    convertToLittleEndian(header, 6, 2, bitmapHeader.reserved1);
    convertToLittleEndian(header, 8, 2, bitmapHeader.reserved2);
    convertToLittleEndian(header, 10, 4, bitmapHeader.startingOffsetData);

    ////-------Info Header
    convertToLittleEndian(info, 0, 4, bitmapInfor.infoSize);
    convertToLittleEndian(info, 4, 4, bitmapInfor.width);
    convertToLittleEndian(info, 8, 4, bitmapInfor.height);
    convertToLittleEndian(info, 12, 2, bitmapInfor.planes);
    convertToLittleEndian(info, 14, 2, bitmapInfor.bitPerPixel);
    convertToLittleEndian(info, 16, 4, bitmapInfor.compression);
    convertToLittleEndian(info, 20, 4, bitmapInfor.imageSize);
    convertToLittleEndian(info, 24, 4, bitmapInfor.horizontal);
    convertToLittleEndian(info, 28, 4, bitmapInfor.vertical);
    convertToLittleEndian(info, 32, 4, bitmapInfor.clrUsed);
    convertToLittleEndian(info, 36, 4, bitmapInfor.clrImportant);
    convertToLittleEndian(info, 40, 4, bitmapInfor.RedMask);
    convertToLittleEndian(info, 44, 4, bitmapInfor.GreenMask);
    convertToLittleEndian(info, 48, 4, bitmapInfor.BlueMask);
    convertToLittleEndian(info, 52, 4, bitmapInfor.AlphaMask);
    convertToLittleEndian(info, 56, 4, bitmapInfor.CSType);
    convertToLittleEndian(info, 60, 4, bitmapInfor.RedX);
    convertToLittleEndian(info, 64, 4, bitmapInfor.RedY);
    convertToLittleEndian(info, 68, 4, bitmapInfor.RedZ);
    convertToLittleEndian(info, 72, 4, bitmapInfor.GreenX);
    convertToLittleEndian(info, 76, 4, bitmapInfor.GreenY);
    convertToLittleEndian(info, 80, 4, bitmapInfor.GreenZ);
    convertToLittleEndian(info, 84, 4, bitmapInfor.BlueX);
    convertToLittleEndian(info, 88, 4, bitmapInfor.BlueY);
    convertToLittleEndian(info, 92, 4, bitmapInfor.BlueZ);
    convertToLittleEndian(info, 96, 4, bitmapInfor.GammaRed);
    convertToLittleEndian(info, 100, 4, bitmapInfor.GammaGreen);
    convertToLittleEndian(info, 104, 4, bitmapInfor.GammaBlue);


    std::ofstream stream(nameFile, std::ios::binary);
    stream.write((char*)header, sizeof(header));
    stream.write((char*)info, sizeof(info));

    unsigned char pad[3] = { 0,0,0 };
    for (int i = 0; i < bitmapInfor.height; i++)
    {
        for (int j = 0; j < bitmapInfor.width; j++)
        {
            unsigned char pixel[4];     //blue-green-red-alpha
            if (map[i][j] == -1) {
                pixel[0] = 0;
                pixel[1] = 0;
                pixel[2] = 255;
                pixel[3] = 255;
            }
            else {
                pixel[0] = map[i][j];
                pixel[1] = map[i][j];
                pixel[2] = map[i][j];
                pixel[3] = 255;
            }
            stream.write((char*)pixel, 4);
        }
        stream.write((char*)pad, padSize);
    }
}

int** readBMP() {
    FILE* fp;
    fp = fopen("map.bmp", "rb");//Read the image.bmp file in the same directory.
    if (fp == NULL)
    {
        std::cout << "Failed to open'image.bmp'!" << std::endl;
        return NULL;
    }
    //If you do not read the bifType first, according to the C language structure Sizeof operation rule-the whole is greater than the sum of the parts, resulting in misalignment of the read file
    unsigned short  fileType;
    fread(&fileType, 1, sizeof(unsigned short), fp);
    if (fileType == 0x4d42) //0x4d42 = "BM"
    {
        std::cout << "Opening file to read completely!" << std::endl;
        fread(&bitmapHeader, 1, sizeof(BITMAPFILEHEADER), fp);
        showBmpHead();
        fread(&bitmapInfor, 1, sizeof(BITMAPINFOHEADER), fp);
        showBmpInfoHead();


        int row_padded = (bitmapInfor.width * 4 + 4) & (~4);
        unsigned char* data = new unsigned char[row_padded];
        unsigned char tmp;

        int** mapPixel = new int* [bitmapInfor.height];
        for (int i = 0; i < bitmapInfor.height; i++)
            mapPixel[i] = new int[bitmapInfor.width];

        for (int i = 0; i < bitmapInfor.height; i++)
        {
            int count = 0;
            fread(data, sizeof(unsigned char), row_padded, fp);
            for (int j = 0; j < bitmapInfor.width * 4; j += 4)
            {
                mapPixel[i][count] = (int)data[j];
                count++;
            }
        }

        fclose(fp);
        return mapPixel;
    }
    else return NULL;
}


bool readFile(std::string fileName, Point& start, Point& end, int& limitedDistance) {
    std::ifstream ifs(fileName, std::ios::in);
    int counter = 0;

    if (ifs) {
        while (ifs) {
            char trash;

            if (counter == 0) {
                ifs >> trash;
                ifs >> start.x;
                ifs >> trash;
                ifs >> start.y;
                ifs >> trash;

                counter++;
            }
            else if (counter == 1) {
                ifs >> trash;
                ifs >> end.x;
                ifs >> trash;
                ifs >> end.y;
                ifs >> trash;

                counter++;
            }
            else {
                ifs >> limitedDistance;
            }
        }
        ifs.close();
    }
    else {
        std::cout << "Could not be opened!" << std::endl;

        return false;
    }

    return true;
}

void executeDataProcessing(Point& start, Point& end, int rows) {
    int tempCoordinate;

    tempCoordinate = start.x;
    start.x = rows - start.y;
    start.y = tempCoordinate;

    tempCoordinate = end.x;
    end.x = rows - end.y;
    end.y = tempCoordinate;
}

void writeFile(std::string fileName, double pathCost, int interactivePoints) {
    std::ofstream ofs(fileName, std::ios::out);

    ofs << pathCost << std::endl << interactivePoints;

    ofs.close();
}

// A* algorithm
void Astar::initAstar(std::vector<std::vector<int>>& map) {
    _map = map;
}

int Astar::getSignFunc(int number) {
    if (number == 0) {
        return 0;
    }
    else if (number > 0) {
        return 1;
    }
    else {
        return -1;
    }
}

double Astar::calcG(Point* tempStart, Point* point) {
    double delta = (double)(_map[tempStart->x][tempStart->y] - _map[point->x][point->y]);

    double extraG = (double)sqrt((point->x - tempStart->x) * (point->x - tempStart->x) + (point->y - tempStart->y) * (point->y - tempStart->y))
        + (double)((0.5 * getSignFunc(delta)) + 1.0) * abs(delta);
    
    //If it is the initial node, the parent node is empty
    double parentG = point->parent == NULL ? 0.0 : point->parent->G;

    return extraG + parentG;
}

double Astar::calcH(Point* point, Point* end, int limitedDistance, int type) {
    switch (type) {
    case 0:
        return calcHByHeuristic1(point, end, limitedDistance);
        break;
    case 1:
        return calcHByHeuristic2(point, end, limitedDistance);
        break;
    case 2:
        return calcHByHeuristic3(point, end, limitedDistance);
        break;
    default:
        break;
    }
    return 0.0;
}

double Astar::calcHByHeuristic1(Point* point, Point* end, int limitedDistance) {
    int deltaX = abs(end->x - point->x);
    int deltaY = abs(end->y - point->y);

    int diagonal = deltaX < deltaY ? deltaX : deltaY;
    int straight = deltaX + deltaY;


    return (double)((limitedDistance * diagonal) + ((limitedDistance / 2) * (straight - (2 * diagonal))));
}

double Astar::calcHByHeuristic2(Point* point, Point* end, int limitedDistance) {
    return (double)(sqrt((end->x - point->x) * (end->x - point->x) + (end->y - point->y) * (end->y - point->y)) * limitedDistance);
}

double Astar::calcHByHeuristic3(Point* point, Point* end, int limitedDistance) {
    int deltaX = abs(end->x - point->x);
    int deltaY = abs(end->y - point->y);

    return (double)(limitedDistance * (deltaX + deltaY)) + ((-0.75 * limitedDistance) * (deltaX < deltaY ? deltaX : deltaY));
}

double Astar::calcF(Point* point) {
    return point->G + point->H;
}

int Astar::getNumOfInteractivePoints() {
    return _interactivePoints;
}

bool Astar::checkValueExists(const std::vector<int>& arr, int value) {
    for (auto const& i : arr) {
        if (value == i) {
            return true;
        }
    }

    return false;
}

Point* Astar::getLeastFPoint() {
    if (!_openList.empty()) {
        auto resPoint = _openList.front();
        for (auto& point : _openList) {
            if (point->F < resPoint->F 
                || ((point->F - resPoint->F) < EPSILON && (resPoint->F - point->F) < EPSILON)) {
                resPoint = point;
            }
        }

        return resPoint;
    }

    return NULL;
}

Point* Astar::findPath(Point& startPoint, Point& endPoint, int limitedDistance, int type) {
    
    //Place the starting point, copy and open a node, isolate inside and outside
    _openList.push_back(new Point(startPoint.x, startPoint.y));

    std::vector<int> values;

    while (!_openList.empty()) {
        
        auto curPoint = getLeastFPoint(); //Find the point with the smallest F value
        _openList.remove(curPoint); //Remove from the open list
        _closeList.push_back(curPoint); //Put into the close list

        //1, find the grid that can be passed among the eight grids around
        auto surroundPoints = getSurroundPoints(curPoint, limitedDistance, values);
        
        for (auto& target : surroundPoints) {
            //2, for a certain grid, if it is not in the open list, add it to the open list, set the current grid as its parent node, and calculate F G H
            if (!isInList(_openList, target)) {
                target->parent = curPoint;

                target->G = calcG(curPoint, target);
                target->H = calcH(target, &endPoint, limitedDistance, type);
                target->F = calcF(target);

                _openList.push_back(target);
            }
            else { //3, for a certain grid, it calculates the G value in the open list, if it is larger than the original, it will do nothing, otherwise set its parent node to the current point, and update G and F
                double tempG = calcG(curPoint, target);

                if (tempG < target->G) {
                    target->parent = curPoint;

                    target->G = tempG;
                    target->F = calcF(target);
                }
            }

            Point* resPoint = isInList(_openList, &endPoint);
            if (resPoint) {
                //Return the node pointer in the list, 
                //do not use the original endpoint pointer passed in,
                //because a deep copy has occurred
                return resPoint;
            }
        }
    }

    return NULL;
}

std::list<Point*> Astar::getPath(Point& startPoint, Point& endPoint, int limitedDistance, int type) {
    
    Point* result = findPath(startPoint, endPoint, limitedDistance, type);

    _pathCost = result->G;

    std::list<Point*> path;

    //Return path, if no path is found, return empty list
    while (result) {
        path.push_front(result);

        result = result->parent;
    }

    // Clear the temporary opening and closing list to prevent repeated execution of GetPath and result in abnormal results
    _openList.clear();
    _closeList.clear();

    return path;
}

Point* Astar::isInList(const std::list<Point*>& list, const Point* point) const {
    //Determine whether a node is in the list, you can't compare pointers here, because every time you join the list is a newly opened node, you can only compare coordinates
    for (auto p : list)
        if (p->x == point->x && p->y == point->y)
            return p;

    return NULL;
}

bool Astar::isCanReach(const Point* point, const Point* target, int limitedDistance, std::vector<int>& values) {
    
    //If the point coincides with the current node, exceeds the map, or is in the closed list then returns false
    if (target->y < 0 || target->y > _map.size() - 1
        || target->x < 0 || target->x > _map[0].size() - 1
        || target->x == point->x && target->y == point->y
        || isInList(_closeList, target)) {
        return false;
    }

    //If the point is unsatisfied conditions, 
    //then it is checked whether it have interacted, if the answer is true(have interacted), do nothing 
    //otherwise add it to the values vector, increase number of interaction by 1
    //return false
    if (abs(target->x - point->x) > 1 || abs(target->y - point->y) > 1
        || abs(_map[point->x][point->y] - _map[target->x][target->y]) > limitedDistance) {
        int value = ((_map.size() > _map[0].size() ? _map.size() : _map[0].size()) * target->y) + target->x;

        if (!checkValueExists(values, value)) {
            values.push_back(value);

            _interactivePoints++;
        }

        return false;
    }

    int value = ((_map.size() > _map[0].size() ? _map.size() : _map[0].size()) * target->y) + target->x;

    if (!checkValueExists(values, value)) {
        values.push_back(value);

        _interactivePoints++;
    }

    return true;
}

std::vector<Point*> Astar::getSurroundPoints(const Point* point, int limitedDistance, std::vector<int>& values) {
    std::vector<Point*> surroundPoints;

    for (int x = point->x - 1; x <= point->x + 1; x++)
        for (int y = point->y - 1; y <= point->y + 1; y++)
            if (isCanReach(point, new Point(x, y), limitedDistance, values))
                surroundPoints.push_back(new Point(x, y));

    return surroundPoints;
}


double Astar::getPathCost() {
    return _pathCost;
}

void Astar::setNumOfInteractivePoints(int value) {
    _interactivePoints = value;
}

std::vector<std::vector<int>> convert(int** map) {
    std::vector<std::vector<int>> result(bitmapInfor.height, std::vector<int>(bitmapInfor.width, 0));
    for (int i = 0; i < bitmapInfor.height; i++) {
        for (int j = 0; j < bitmapInfor.width; j++) {
            result[i][j] = map[i][j];
        }
    }
    return result;
}