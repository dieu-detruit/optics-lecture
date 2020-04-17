#include <optics/ray.hpp>
#include <optics/unit.hpp>

#include <Eigen/Core>

int main()
{

    Optics::Geometry::Ray<Irradiance> ray = {
        .source = Eigen::Vector3d{0.0, 0.0, 0.0},
        .dir = Eigen::Vector3d{0.0, 0.0, 1.0},
        .I = 0.0_W / 1.0_m2};

    return 0;
}
