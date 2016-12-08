#include "Metal.h"

using namespace std;
using namespace glm;

std::unique_ptr<ScatteredRay> Metal::getScattered(const Ray & in, const HitInfo * hit) const
{
    vec3 reflected = reflect(normalize(in.getDirection()), hit->getNormal());

    return make_unique<ScatteredRay>(hit->getLocation(), reflected, getAlbedo());
}
