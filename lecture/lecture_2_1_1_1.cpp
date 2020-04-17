#include <optics/ray.hpp>

#include <Eigen/Core>

int main()
{

    Optics::Geometry::Ray ray = {
        .source = Eigen::Vector3d{0.0, 0.0, 0.0},
        .dir = Eigen::Vector3d{0.0, 0.0, 1.0},
    };

    return 0;
}
