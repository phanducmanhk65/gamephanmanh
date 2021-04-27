#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "function.h"
#include "baseobject.h"
#define MAX_TITLES 20
class TitleMat : public BaseObject
{
    public:
        TitleMat(){;}
        ~TitleMat(){;}

};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;};
    void SetMap(Map& map_data){game_map_=map_data;};
private:
    Map game_map_;
    TitleMat title_mat[MAX_TITLES];
};

#endif // GAME_MAP_H
