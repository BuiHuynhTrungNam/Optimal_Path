#include <iostream>
#include "Astar.h"

std::string FileName[3] = { "map1.bmp", "map2.bmp" , "map3.bmp"};


int main() {
    int** mapPixel = readBMP();
    Astar astar;
    std::vector<std::vector<int>> map = convert(mapPixel);
    astar.initAstar(map);

    int m;
    Point start(0, 0), end(0, 0);
    
    if (!readFile("input.txt", start, end, m)) {
        std::cout << "can not open file txt" << std::endl;
        return 0;
    }

    executeDataProcessing(start, end, 512);

    //A* algorithm to find the path
    for (int i = 0; i < 3; i++) {

        std::list<Point*> path = astar.getPath(start, end, m, i);

        //Print
        for (auto& p : path) {
            map[p->x][p->y] = -1;
        }
        
        std::string fileName = "output" + std::to_string(i + 1) + ".txt";
        writeFile(fileName, astar.getPathCost(), astar.getNumOfInteractivePoints());

        std::cout << "Heuristic " << i + 1 << std::endl;
        std::cout << "Path Cost: " << astar.getPathCost() << std::endl;
        std::cout << "Sum of interactive points: " << astar.getNumOfInteractivePoints() << std::endl;
        writeBMP(map, FileName[i]);
        map = convert(mapPixel);
        astar.setNumOfInteractivePoints(0);
    }

    return 0;
}