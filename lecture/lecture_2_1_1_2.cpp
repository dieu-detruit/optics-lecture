#include <optics/ray.hpp>
#include <optics/unit.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <iostream>

int main()
{

    using namespace Eigen;

    Optics::Geometry::Ray<Irradiance> ray = {
        .source = Vector3d{0.0, 0.0, 0.0},
        .dir = Vector3d{0.0, 0.0, 1.0},
        .I = 0.0_W / 1.0_m2};

    ray.dir = AngleAxis(1.0_mrad, Vector3d::UnitX()).toRotationMatrix() * ray.dir;

    std::cout << ray.dir << std::endl;

    return 0;
}
