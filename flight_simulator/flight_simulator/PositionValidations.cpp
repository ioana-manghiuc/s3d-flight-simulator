#include "PositionValidations.h"


bool BorderValidation(glm::vec3& position, const float& speed, const glm::vec3& orientation)
{
    if ((position + (speed * orientation)).y >= 21.01f && (position +( speed * orientation)).y < 624.0f)
        return true;
    return false;
}
