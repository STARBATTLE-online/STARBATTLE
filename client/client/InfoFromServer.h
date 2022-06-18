#pragma once
#include <iostream>
#include <memory>
#include "MapCreator.h"

// Request format:

// MAP_WIDTH, MAP_HEIGHT
// asteroid_count, ship_count
// for each asteroid:
//  ASTEROID_TYPE
//  serialize(asteroid)
// for each ship:
//  SHIP
//  serialize(ship)
//  

// Singleton
class InfoFromServer {
    static std::shared_ptr<MapCreator> m_map_creator;
public:
    InfoFromServer() {};
    ~InfoFromServer() {};
    static void SetMapCreator(std::shared_ptr<MapCreator> map_creator);
    static std::string ProcessRequest(std::string request);
    static void InitRequest(std::stringstream& ss);
    static void TickRequest(std::stringstream& ss);
};

std::shared_ptr<MapCreator> InfoFromServer::m_map_creator;

void InfoFromServer::SetMapCreator(std::shared_ptr<MapCreator> map_creator) {
    InfoFromServer::m_map_creator = map_creator;
}

std::string InfoFromServer::ProcessRequest(std::string request) {
    std::lock_guard<std::mutex> lock(InfoFromServer::m_map_creator->mt);
    std::stringstream ss(request);
    std::string output, commandType;

    std::cout << request << std::endl;

    while (ss >> commandType) {
        if (commandType == "INIT") {

            std::cout << "INIT" << std::endl;
            InitRequest(ss);
        }
        else if (commandType == "TICK") {

            std::cout << "TICK" << std::endl;
            TickRequest(ss);
        }
    }

    return output;
}

void InfoFromServer::InitRequest(std::stringstream& ss) {
    double x, y;
    uint64_t sprite_id;
    ss >> PERSONAL_ID_PUBLIC >> PERSONAL_ID_PRIVATE >> x >> y >> sprite_id >> MAP_WIDTH >> MAP_HEIGHT;
	
    InfoFromServer::m_map_creator->AddMainHero(x, y, sprite_id);

    request = "TICK";
    is_connected = 1;
}

void InfoFromServer::TickRequest(std::stringstream& ss) {

    std::string commandType;
    int i = 0, j = 0, k = 0;
	Ship* ship;
    while (ss >> commandType)
    {
        if (commandType == "BigAsteroid")
        {
			double x, y;
			uint64_t sprite_id;
			ss >> x >> y ;
            bool flag = false;
            while (i < InfoFromServer::m_map_creator->asteroids.size())
            {
                if (InfoFromServer::m_map_creator->asteroids[i]->GetName() == "BigAsteroid")
                {
                    InfoFromServer::m_map_creator->asteroids[i]->SetCoordsByCenter(x, y);
                    flag = true;

                    i++;
                    break;
                }
                i++;
            }
            std::cout << i << std::endl;
            if (i >= InfoFromServer::m_map_creator->asteroids.size() && !flag)
            {
                InfoFromServer::m_map_creator->AddBigAsteroid(x, y);
            }
			
		}
		else if (commandType == "SmallAsteroid")
		{
            double x, y;
            uint64_t sprite_id;
            ss >> x >> y;

            bool flag = false;
            while (j < InfoFromServer::m_map_creator->asteroids.size())
            {
                if (InfoFromServer::m_map_creator->asteroids[j]->GetName() == "SmallAsteroid")
                {
                    InfoFromServer::m_map_creator->asteroids[j]->SetCoordsByCenter(x, y);
                    flag = true;
                    j++;
                    break;
                }
                j++;
            }
            std::cout << j << std::endl;
            if (j >= InfoFromServer::m_map_creator->asteroids.size() && !flag)
            {
                InfoFromServer::m_map_creator->AddSmallAsteroid(x, y);
            }
		}
		/*else if (commandType == "Ship")
		{
			double x, y;
			uint64_t sprite_id, public_id;
            char rotation;
            Rotation rot;

            ss >> x >> y >> rotation >> sprite_id >> public_id;
			
            switch (rotation) {
            case 'T':
                rot = Rotation::Top;
                break;
            case 'L':
                rot = Rotation::Left;
                break;
            case 'B':
                rot = Rotation::Bottom;
                break;
            case 'R':
                rot = Rotation::Right;
                break;
            }

            if (PERSONAL_ID_PUBLIC == public_id)
            {
                InfoFromServer::m_map_creator->main_hero.SetCoordsByCenter(x, y);				
                ship = &(InfoFromServer::m_map_creator->main_hero);
            }
            else
            {
                while (k < InfoFromServer::m_map_creator->asteroids.size())
                {
                    InfoFromServer::m_map_creator->asteroids[i]->SetCoordsByCenter(x, y);
                    k++;
                }
                if (k >= InfoFromServer::m_map_creator->asteroids.size() - 1)
                {
                    InfoFromServer::m_map_creator->AddEnemyShip(x, y, rot, sprite_id);
                }
            }
		}*/
    }
   /* if (i > j)
    {
        InfoFromServer::m_map_creator->asteroids.erase(std::remove_if(InfoFromServer::m_map_creator->asteroids.begin() + i,
            InfoFromServer::m_map_creator->asteroids.end(),
            [&](auto& asteroid)-> bool
            { return asteroid->GetName() == "BigAsteroid"; }),
            InfoFromServer::m_map_creator->asteroids.end());

        InfoFromServer::m_map_creator->asteroids.erase(std::remove_if(InfoFromServer::m_map_creator->asteroids.begin() + j,
            InfoFromServer::m_map_creator->asteroids.end(),
            [&](auto& asteroid)-> bool
            { return asteroid->GetName() == "SmallAsteroid"; }),
            InfoFromServer::m_map_creator->asteroids.end());
    }
    else
    {
        InfoFromServer::m_map_creator->asteroids.erase(std::remove_if(InfoFromServer::m_map_creator->asteroids.begin() + j,
            InfoFromServer::m_map_creator->asteroids.end(),
            [&](auto& asteroid)-> bool
            { return asteroid->GetName() == "SmallAsteroid"; }),
            InfoFromServer::m_map_creator->asteroids.end());
		
        InfoFromServer::m_map_creator->asteroids.erase(std::remove_if(InfoFromServer::m_map_creator->asteroids.begin() + i,
            InfoFromServer::m_map_creator->asteroids.end(),
            [&](auto& asteroid)-> bool
            { return asteroid->GetName() == "BigAsteroid"; }),
            InfoFromServer::m_map_creator->asteroids.end());
    }*/
 /*   if (InfoFromServer::m_map_creator->ships.size()>0)
    {
        InfoFromServer::m_map_creator->ships.erase(InfoFromServer::m_map_creator->ships.begin() + k);
    }
	*/

    for (auto asteroid : InfoFromServer::m_map_creator->asteroids)
    {
		std::cout << asteroid->GetName() << " " << asteroid->GetCenterGlobal().first << " " << asteroid->GetCenterGlobal().second << std::endl;
		
    }
}