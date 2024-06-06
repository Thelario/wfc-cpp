#include "Utils.h"

#include <chrono>
#include <ctime>

namespace Satellite
{
    const std::string Utils::CurrentDateTimeToString()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm;
        localtime_s(&local_tm, &now_time);
        char time_buffer[80];
        std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &local_tm);
        return time_buffer;
    }

    const std::string Utils::GetTagName(ColliderTag tag)
    {
        switch (tag)
        {
        case ColliderTag::PLAYER:
            return "Player";
        case ColliderTag::OBSTACLE:
            return "Obstacle";
        case ColliderTag::BULLET:
            return "Bullet";
        case ColliderTag::ENEMY:
            return "Enemy";
        default:
            return "None";
        }
    }
}
