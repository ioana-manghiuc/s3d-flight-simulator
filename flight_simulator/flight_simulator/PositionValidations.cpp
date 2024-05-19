#include "PositionValidations.h"
#include <iostream>

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

    //Point points2();
    if (IsInParallelepiped(glm::vec3(-900.f, 41.f, -864.f), glm::vec3(-620.f, 280.f, -306.f), position))
        return false;

    //Point points3();
    if (IsInParallelepiped(glm::vec3(-946.f, 41.f, -308.f), glm::vec3(-604.f, 340.f, 255.f), position))
        return false;

    //Point points4();
    if (IsInParallelepiped(glm::vec3(-888.f, 41.f, 290.f), glm::vec3(-667.f, 441.f, 481.f), position))
        return false;

    //point 5
    if (IsInParallelepiped(glm::vec3(-775.f, 41.f, 513.f), glm::vec3(-559.f, 475.f, 796.f), position))
        return false;
    //point 6
    if (IsInParallelepiped(glm::vec3(-683.f, 41.f, 805.f), glm::vec3(-505.f, 419.f, 968.f), position))
        return false;
    //point 7
    if (IsInParallelepiped(glm::vec3(-649.f, 41.f, 993.f), glm::vec3(-524.f, 260.f, 1017.f), position))
        return false;
    //point 8
    if (IsInParallelepiped(glm::vec3(312.f, 41.f, 133.f), glm::vec3(439.f, 329.f, 283.f), position))
        return false;
    //point 9
    if (IsInParallelepiped(glm::vec3(184.f, 41.f, -10.f), glm::vec3(224.f, 246.f, 48.f), position))
        return false;
    //point 10
    if (IsInParallelepiped(glm::vec3(431.f, 41.f, 292.f), glm::vec3(483.f, 280.f, 324.f), position))
        return false;
    //point 11
    if (IsInParallelepiped(glm::vec3(478.f, 41.f, 323.f), glm::vec3(510.f, 240.f, 351.f), position))
        return false;
    //point 12
    if (IsInParallelepiped(glm::vec3(477.f, 41.f, 360.f), glm::vec3(540.f, 169.f, 388.f), position))
        return false;
    //point 13
    if (IsInParallelepiped(glm::vec3(586.f, 41.f, 261.f), glm::vec3(638.f, 114.f, 409.f), position))
        return false;
    //point 14
    if (IsInParallelepiped(glm::vec3(248.f, 41.f, -14.f), glm::vec3(353.f, 277.f, 125.f), position))
        return false;
    //point 15
    if (IsInParallelepiped(glm::vec3(216.f, 41.f, -271.f), glm::vec3(524.f, 203.f, -83.f), position))
        return false;
    //point 16
    if (IsInParallelepiped(glm::vec3(346.f, 41.f, -334.f), glm::vec3(411.f, 299.f, -296.f), position))
        return false;
    //point 17
    if (IsInParallelepiped(glm::vec3(403.f, 41.f, -671.f), glm::vec3(431.f, 335.f, -361.f), position))
        return false;
    //point 18
    if (IsInParallelepiped(glm::vec3(407.f, 41.f, -671.f), glm::vec3(538.f, 443.f, -369.f), position))
        return false;
    //point 19
    if (IsInParallelepiped(glm::vec3(445.f, 41.f, -1009.f), glm::vec3(562.f, 502.f, -697.f), position))
        return false;
    //point 20
    if (IsInParallelepiped(glm::vec3(429.f, 41.f, -1119.f), glm::vec3(523.f, 395.f, -1008.f), position))
        return false;
    //point 21
    if (IsInParallelepiped(glm::vec3(473.f, 41.f, -1180.f), glm::vec3(544.f, 354.f, -1109.f), position))
        return false;
    //point 22
    if (IsInParallelepiped(glm::vec3(467.f, 41.f, -1235.f), glm::vec3(535.f, 318.f, -1174.f), position))
        return false;
    //point 23
    if (IsInParallelepiped(glm::vec3(447.f, 41.f, -1251.f), glm::vec3(552.f, 310.f, -1183.f), position))
        return false;
    //point 24
    if (IsInParallelepiped(glm::vec3(314.f, 41.f, -1417.f), glm::vec3(481.f, 232.f, -1221.f), position))
        return false;
    //point 25
    if (IsInParallelepiped(glm::vec3(537.f, 41.f, -1251.f), glm::vec3(583.f, 232.f, -1157.f), position))
        return false;
    //point 26
    if (IsInParallelepiped(glm::vec3(-432.f, 41.f, 670.f), glm::vec3(-314.f, 330.f, 1100.f), position))
        return false;
    //point 27
    if (IsInParallelepiped(glm::vec3(-530.f, 41.f, 189.f), glm::vec3(360.f, 230.f, 330.f), position))
        return false;
    //point 28
    if (IsInParallelepiped(glm::vec3(-345.f, 41.f, 662.f), glm::vec3(-169.f, 250.f, 1033.f), position))
        return false;
    //point 29
    if (IsInParallelepiped(glm::vec3(-490.f, 120.f, -1097.f), glm::vec3(100.f, 175.f, -100.f), position))
        return false;
    //point 30
    if (IsInParallelepiped(glm::vec3(30.f, 140.f, -1250.f), glm::vec3(241.f, 142.f, -1110.f), position))
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
    if (position.y >= lowerCorner.y && position.y <= upperCorner.y &&
        position.x >= lowerCorner.x && position.x <= upperCorner.x &&
        position.z >= lowerCorner.z && position.z <= upperCorner.z)
    {
        std::cout << "collision in:\n " << lowerCorner.x << ", " << lowerCorner.y << ", " << lowerCorner.z << "\n";
        std::cout << upperCorner.x << ", " << upperCorner.y << ", " << upperCorner.z << "\n";
        return true;
    }
    return false;
}
