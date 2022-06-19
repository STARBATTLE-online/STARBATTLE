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
    static std::string ProcessRequest(const std::string& request);
    static void InitRequest(std::stringstream& ss);
    static void TickRequest(std::stringstream& ss);
};

std::shared_ptr<MapCreator> InfoFromServer::m_map_creator;

void InfoFromServer::SetMapCreator(std::shared_ptr<MapCreator> map_creator) {
    InfoFromServer::m_map_creator = map_creator;
}

std::string InfoFromServer::ProcessRequest(const std::string& request) {
    Sleep(0);//?
    std::lock_guard<std::mutex> lock(InfoFromServer::m_map_creator->mt);
    std::stringstream ss(request);
    std::string output, commandType;

    //std::cout << request << std::endl;

    while (ss >> commandType) {
        if (commandType == "INIT") {

            //std::cout << "INIT" << std::endl;
            InitRequest(ss);
        }
        else if (commandType == "TICK") {

            //std::cout << "TICK" << std::endl;
            TickRequest(ss);
        }
    }

    return output;
}

void InfoFromServer::InitRequest(std::stringstream& ss) {
    int x, y;
    uint64_t sprite_id;
    ss >> PERSONAL_ID_PUBLIC >> PERSONAL_ID_PRIVATE >> x >> y >> sprite_id >> MAP_WIDTH >> MAP_HEIGHT;
	
    InfoFromServer::m_map_creator->AddMainHero(x, y, sprite_id);

    request = "TICK";
    is_connected = 1;
}

void InfoFromServer::TickRequest(std::stringstream& ss) {

    std::string commandType;
    InfoFromServer::m_map_creator->asteroids.clear();
    InfoFromServer::m_map_creator->asteroids.reserve(50);
    InfoFromServer::m_map_creator->ships.clear();
    InfoFromServer::m_map_creator->ships.reserve(50);
    InfoFromServer::m_map_creator->bullets.clear();
    InfoFromServer::m_map_creator->bullets.reserve(50);
	Ship* ship;
    while (ss >> commandType)
    {
        if (commandType == "BigAsteroid")
        {
            int x, y;
			ss >> x >> y ;
            InfoFromServer::m_map_creator->asteroids.emplace_back(Asteroid(x, y, AsteroidTypes::Big));
		}
		else if (commandType == "SmallAsteroid")
		{
            int x, y;
            ss >> x >> y;
            InfoFromServer::m_map_creator->asteroids.emplace_back(Asteroid(x, y, AsteroidTypes::Small));

		}
		else if (commandType == "Ship")
		{
			int x, y;
			uint64_t sprite_id, public_id;
            char rotation;
            bool is_engine;
            Rotation rot = Rotation::Top;

            ss >> x >> y >> rotation >> sprite_id >> is_engine >> public_id;
			
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
            default:
                break;
            }

            if (PERSONAL_ID_PUBLIC == public_id)
            {
                InfoFromServer::m_map_creator->main_hero.SetCoordsByCenter(x, y);	
                InfoFromServer::m_map_creator->main_hero.SetEngine(is_engine);
                ship = &(InfoFromServer::m_map_creator->main_hero);
                WINDOW_X = InfoFromServer::m_map_creator->main_hero.GetCenterGlobal().first - WINDOW_WIDTH / 2;
                WINDOW_Y = InfoFromServer::m_map_creator->main_hero.GetCenterGlobal().second - WINDOW_HEIGHT / 2;
            }
            else
            {
                InfoFromServer::m_map_creator->ships.push_back(EnemyShip(x, y, rot, sprite_id));
                InfoFromServer::m_map_creator->ships.back().SetRotation(rot);
                InfoFromServer::m_map_creator->ships.back().SetEngine(is_engine);
                ship = &InfoFromServer::m_map_creator->ships.back();
            }
		}
        else if (commandType == "Bullet")
        {
            int x, y;
            int x_speed, y_speed;
			ss >> x >> y >> x_speed >> y_speed;
            InfoFromServer::m_map_creator->Shoot(x, y);
        }
    }
    //std::cout << InfoFromServer::m_map_creator->asteroids.size() << " " << InfoFromServer::m_map_creator->ships.size() << " " << InfoFromServer::m_map_creator->bullets.size() << "\n";
   
}