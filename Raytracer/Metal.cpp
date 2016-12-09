#include <glm\gtc\random.hpp>

#include "Metal.h"

using namespace std;
using namespace glm;

void Metal::setRoughness(const float roughness)
{
    this->roughness = min(roughness, 1.f);
}

float Metal::getRoughness() const
{
    return roughness;
}

std::unique_ptr<ScatteredRay> Metal::getScattered(const Ray & in, const HitInfo * hit) const
{
    vec3 reflected = reflect(normalize(in.getDirection()), hit->getNormal());

    return make_unique<ScatteredRay>(hit->getLocation(), reflected + roughness * ballRand(1.f), getAlbedo());
}
