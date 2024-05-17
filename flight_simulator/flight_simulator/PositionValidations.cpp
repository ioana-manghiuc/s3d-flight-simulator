#include "PositionValidations.h"


bool BorderValidation(const glm::vec3& position)
{
    //-2015.12 75.9778 - 1978.86
    //204.159 83.0502 -443.938
    //2083.29 91.8203 1966.94

    if (position.y >= 21.01f && position.y <= 754.0f &&
        position.x >= -1978.f && position.x <= 1978.f &&
        position.z >= -1978.f && position.z <= 1978.f) {
        return true;
    }
    return false;
}

bool MountainsValidations(const glm::vec3& position)
{
        //370.665 115.286 514.834
        //0.649505 115.286 793.077
        //- 440.624 115.286 - 4.96145
        //51.1512 114.819 - 160.208

        //370.665 230.286 514.834
        //0.649505 230.286 793.077
        //- 440.624 230.286 - 4.96145
        //51.1512 230.819 - 160.208

    if (position.y >= 41.2f && position.y <= 185.0f &&
        position.x >= -440.f && position.x <= 312.f &&
        position.z >= -4.f && position.z <= 638.f) {
        return false;
    }

    if (position.y >= 41.2f && position.y <= 416.0f &&
        position.x >= 92.f && position.x <= 722.f &&
        position.z >= -186.f && position.z <= 481.f) {
        return false;
    }
    if (position.y >= 41.2f && position.y <= 540.0f &&
        position.x >= 117.f && position.x <= 731.f &&
        position.z >= -1483.f && position.z <= -24.f) {
        return false;
    }

    if (position.y >= 41.2f && position.y <= 266.0f &&
        position.x >= -1173.f && position.x <= -516.f &&
        position.z >= -1040.f && position.z <= -333.f) {
        return false;
    }

    if (position.y >= 41.2f && position.y <= 382.0f &&
        position.x >= -1143.f && position.x <= -464.f &&
        position.z >= -349.f && position.z <= 168.f) {
        return false;
    }

    if (position.y >= 41.2f && position.y <= 498.0f &&
        position.x >= -1143.f && position.x <= -15.f &&
        position.z >= 153.f && position.z <= 1366.f) {
        return false;
    }


    return true;
}
bool IsValidPosition(const glm::vec3& position)
{
    return BorderValidation(position) && MountainsValidations(position);
}
