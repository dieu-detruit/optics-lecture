#include <optics/ray.hpp>
#include <optics/unit.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <cmath>
#include <iostream>

int main()
{

    using namespace Eigen;

    constexpr int division_v = 50;
    constexpr int division_r = 50;

    Optics::Geometry::Ray<Irradiance> flux[division_v * division_r];
    Vector3d origin = Vector3d::Zero();
    constexpr Angle range = 1.0_rad;

    double versin_range = (1.0 - std::cos(range)) / (1.0 - 0.5 / division_v);
    auto vertical_angle = [c = versin_range](double x) -> Angle {
        return std::acos(1.0 - c * x) * 1.0_rad;
    };

    const auto v_axis = Vector3d::UnitY();
    const auto r_axis = Vector3d::UnitZ();

    for (int i = 0; i < division_v; ++i) {
        Angle vth = vertical_angle((double)i / division_v) * 1.0_rad;
        Vector3d ray = AngleAxis(double(1.0_rad), v_axis).toRotationMatrix() * Vector3d{0.0, 0.0, 1.0};

        for (int j = 0; j < division_r; ++j) {
            Angle rth = 2 * M_PI * j / division_r * 1.0_rad;
            flux[division_v * i + j] = {
                .source = origin,
                .dir = AngleAxis(double(rth), r_axis).toRotationMatrix() * ray,
                .I = 0.0_W / 1.0_m2};
        }
    }

    // 原点から距離1の球面上に投影する
    for (int i = 0; i < division_v * division_r; ++i) {
        Vector3d projection = flux[i].dir.normalized();
        std::cout << projection(0) << ' '
                  << projection(1) << ' '
                  << projection(2) << std::endl;
    }


    return 0;
}
