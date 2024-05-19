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
    // point 1
    if (IsInParallelepiped(glm::vec3(-788.f, 41.f, -1047.f), glm::vec3(-520.f, 154.f, -843.f), position))
        return false;

    return true;
}
bool BuildingsValidations(const glm::vec3& position)
{
   // Point bpoint01(glm::vec3(1581.26, 10.6445, -1396.4), glm::vec3(1839.84, 68.7172, -1794.53));
   // Point bpoint04(glm::vec3(1567.14, 21.0349, -1325.99), glm::vec3(1674.79, 233.561, -1272.87));

    if (IsInParallelepiped(glm::vec3(1581.26, 10.6445, -1794.53), glm::vec3(1839.84, 68.7172, -1396.4), position))
    {
        return false;
    }
    if (IsInParallelepiped(glm::vec3(1567.14, 21.0349, -1325.99), glm::vec3(1674.79, 233.561, -1272.87), position))
    {
        return false;
    }
   /* if (IsInParallelepiped(glm::vec3(1418.85, 24.4246, -1900.11), glm::vec3(1436.31, 31.6876, -1808.66), position))
    {
        return false;
    }*/
    /*if (IsInParallelepiped(glm::vec3(1545.34, 22.0622, -1897.39), glm::vec3(1531, 31.0776, -1804.88), position))
    {
        return false;
    }*/
    if (position.y >= 10.6445f && position.y <= 68.7172f &&
        position.x >= 1581.26f && position.x <= 1839.84f &&
        position.z >= -1794.53f && position.z <= -1396.4f) {
		return false;
	}

    if (position.y >= 21.0349f && position.y <= 233.561f &&
        		position.x >= 1567.14f && position.x <= 1674.79f &&
        position.z >= -1325.99f && position.z <= -1272.87f) {
        return false;
    }

    //Point bpoint03(glm::vec3(1418.85, 24.4246, -1900.11), glm::vec3(1436.31, 31.6876, -1808.66));
    //Point bpoint04(glm::vec3(1545.34, 22.0622, -1897.39), glm::vec3(1531, 31.0776, -1804.88));

    if (position.y >= 24.4246f && position.y <= 31.6876f &&
        position.x >= 1418.85f && position.x <= 1436.31f &&
        position.z >= -1900.11f && position.z <= -1808.66f) {
		return false;
	}

    if (position.y >= 22.0622f && position.y <= 31.0776f &&
        position.x >= 1545.34f && position.x <= 1531.f &&
        position.z >= -1897.39f && position.z <= -1804.88f) {
		return false;
	}
    return true;
}
bool IsValidPosition(const glm::vec3& position)
{
    return BorderValidation(position) && MountainsValidations(position) && BuildingsValidations(position);
}

bool IsInParallelepiped(const glm::vec3& lowerCorner, const glm::vec3& upperCorner, const glm::vec3& position)
{
    if(position.y >= lowerCorner.y && position.y <= upperCorner.y &&
        position.x >= lowerCorner.x && position.x <= upperCorner.x &&
        position.z >= lowerCorner.z && position.z <= upperCorner.z)
        return true;
    return false;
}
