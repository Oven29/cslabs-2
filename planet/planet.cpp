#include "planet.h"

namespace planet {

Planet::Planet(const char* name, int diametr, bool hasLife, int countOfSatellites)
    : name(name), diametr(diametr), hasLife(hasLife), countOfSatellites(countOfSatellites) {
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.name << ": ";
    os << "diametr - " << planet.diametr << ", ";
    os << (planet.hasLife ? "has life" : "has not life") << ", ";
    os << "count of satellites - " << planet.countOfSatellites;

    return os;
}

}  // namespace planet
