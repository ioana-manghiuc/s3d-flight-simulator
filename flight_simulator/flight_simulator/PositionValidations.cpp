#include "PositionValidations.h"


bool BorderValidation(glm::vec3& position)
{
    //-2015.12 75.9778 - 1978.86
    //204.159 83.0502 -443.938
    //2083.29 91.8203 1966.94

    if (position.y >= 41.01f && position.y <= 654.0f &&
        position.x >= -1978.f && position.x <= 1978.f &&
        position.z >= -1978.f && position.z <= 1978.f) {
        return true;
    }
    return false;
}
