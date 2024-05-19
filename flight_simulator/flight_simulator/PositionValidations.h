#pragma once
#include <GLM.hpp>

bool BorderValidation(const glm::vec3& position);

bool MountainsValidations(const glm::vec3& position);

bool BuildingsValidations(const glm::vec3& position);

bool IsValidPosition(const glm::vec3& position);

bool IsInParallelepiped(const glm::vec3& lowerCorner, const glm::vec3& upperCorner, const glm::vec3& position);