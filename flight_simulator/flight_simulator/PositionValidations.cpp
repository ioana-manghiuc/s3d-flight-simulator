#include "PositionValidations.h"


bool BorderValidation(glm::vec3& position, const float& speed, const glm::vec3& orientation)
{
    float newYPosition = (position + (speed * orientation)).y;
    float newXPosition = (position + (speed * orientation)).x;
    float newZPosition = (position + (speed * orientation)).z;
    if (newYPosition >= 21.01f && newYPosition <= 654.0f && newXPosition>=-2702.f && newXPosition<=2702.f&& newZPosition>=-2702.f&& newZPosition<=2702.f) {
        return true;
    }
    return false;
}
