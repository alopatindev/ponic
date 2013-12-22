#pragma once

#include "misc/Singleton.h"
#include <string>
#include <unordered_map>
#include <vector>

class GridManager_Class
{
public:
    enum TileType {Empty, Surface, Player};
    typedef std::vector<std::vector<TileType>> Grid;

private:
    std::unordered_map<std::string, Grid> m_grids;

public:
    GridManager_Class();
    virtual ~GridManager_Class();

    void loadGrid(const std::string& grid);
    void freeGrid(const std::string& grid);
    void freeAllGrids();
};

typedef Singleton<GridManager_Class> GridManager;
