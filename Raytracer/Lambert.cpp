#include "Lambert.h"

using namespace std; 
using namespace glm;

std::unique_ptr<ScatteredRay> Lambert::getScattered(const Ray& in, const HitInfo* hit) const
{
    vec3 target = hit->getNormal() + ballRand(1.f);
    return make_unique<ScatteredRay>(hit->getLocation(), target, getAlbedo());
}
