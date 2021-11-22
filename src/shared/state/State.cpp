#include "../state.h"

namespace state{

std::vector<std::vector<std::unique_ptr<Map>>>& State::getMap (){
    
    
}
void State::InitMap (std::string mapResource = "res/MapTest.txt"){
    unsigned int i = 0, j = 0, k = 0;

        // mapping (this will be dependent on the choosed resource)
        // dictionary to signalize the type of each tileset by his id
        // (tile id defined by the position of the tile in de resource, we dont define it)
        std::map<int, SpaceMapCellID> mapp_spaces;
        std::map<int, ObstacleMapCellID> mapp_obstacles;

        
        std::ifstream file(mapResource, ios::in);
        int map_tile[25 * 20];

        //this way we read the txt file.
        std::string content, line, tilecode;
        if (!file)
            return;
        while (getline(file, line))
        {
            line += ",";
            content += line;
        }
        cout << "--- file read succesfully ---" << endl;
        file.close();

        // from string to stream
        std::stringstream contentStream(content);
        cout << "--- from string to stream succesfully ---" << endl;

        // delimiting by comma
        while (std::getline(contentStream, tilecode, ','))
        {
            map_tile[i] = std::stoi(tilecode);
            i++;
        }
        cout << "--- building map_tile array succesfully ---" << endl;

        for (i = 0; i < 20; ++i)
        {
            std::vector<std::unique_ptr<MapCell>> newline;
            for (j = 0; j < 25; ++j)
            {
                cout << map_tile[k] << ",";
                if (map_tile[k])
                {
                    if (mapp_spaces.find(map_tile[k]) != mapp_spaces.end())
                    {
                        std::unique_ptr<SpaceMapCell> spc(new SpaceMapCell(mapp_spaces[map_tile[k]], j, i, map_tile[k]));
                        newline.push_back(move(spc));
                    }
                    else if (mapp_obstacles.find(map_tile[k]) != mapp_obstacles.end())
                    {
                        std::unique_ptr<ObstacleMapCell> obs(new ObstacleMapCell(mapp_obstacles[map_tile[k]], j, i, map_tile[k]));
                        newline.push_back(move(obs));
                    }
                    else
                    {
                        std::unique_ptr<SpaceMapCell> spc(new SpaceMapCell(mapp_spaces[map_tile[118]], j, i, map_tile[118]));
                        newline.push_back(move(spc));
                    }
                }
                k++;
            }
            cout << endl;
            map.push_back(move(newline));
        }
        cout << "--- map created succesfully ---" << endl;
        return;
}

}
