#include <optics/ray.hpp>
#include <optics/unit.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <cmath>
#include <iostream>
#include <random>

#define QUESTION_A 0
#define QUESTION_B 1 - A

int main()
{

    using namespace Eigen;
    using Ray = typename Optics::Geometry::Ray<Irradiance>;

    constexpr double stddev_x = 0.0001 * 1.0_m / 1.0_m;
    constexpr double stddev_y = 0.001 * 1.0_m / 1.0_m;

    constexpr Irradiance I_sum = 1.0_W / 1.0_m2;
    constexpr int N = 2500;

    const Vector3d origin = Vector3d::Zero();

#if QUESTION_A
    {  // A 各光線で強度が等しいとき

        std::vector<Ray> flux(N);

        constexpr Irradiance I0 = I_sum / double(N);

        std::random_device rd{};
        std::mt19937 gen{rd()};

        std::normal_distribution<double> dist_x{0.0, stddev_x};
        std::normal_distribution<double> dist_y{0.0, stddev_y};

        for (int i = 0; i < N; ++i) {
            Length x = dist_x(gen) * 1.0_m;
            Length y = dist_y(gen) * 1.0_m;
            flux[i] = {
                .source = origin,
                .dir = {x / 1.0_m, y / 1.0_m, 1.0},
                .I = I0};
        }

        // z=1上の分布をみる
        for (int i = 0; i < N; ++i) {
            std::cout << flux[i].dir(0) << ' '
                      << flux[i].dir(1) << ' '
                      << flux[i].I / I_sum << std::endl;
            std::cout << std::endl;
        }
    }
#endif

#if QUESTION_B
    {  // 強度分布を持つとき

        constexpr int div_x = 50;
        constexpr int div_y = 50;

        constexpr double range_ratio = 5.0;

        std::vector<Ray> flux;
        flux.reserve(N);


        Length cell_w = range_ratio * 2.0 * stddev_x * 1.0_m / (double)div_x;
        Length cell_h = range_ratio * 2.0 * stddev_y * 1.0_m / (double)div_y;

        auto dist = [rt2 = sqrt(2)](double x, double sigma) {
            return 0.5 * (1.0 + std::erf(x / sigma / rt2));
        };

        Irradiance I_s = 0.0_W / 1.0_m2;

        for (int i = 0; i < div_x / 2; ++i) {

            Length x = cell_w * (0.5 + i);

            for (int j = 0; j < div_y / 2; ++j) {

                Length y = cell_h * (0.5 + j);

                Irradiance I = I_sum
                               * (dist((x + 0.5 * cell_w) / 1.0_m, stddev_x) - dist((x - 0.5 * cell_w) / 1.0_m, stddev_x))
                               * (dist((y + 0.5 * cell_h) / 1.0_m, stddev_y) - dist((y - 0.5 * cell_h) / 1.0_m, stddev_y));

                flux.push_back(Ray{origin, Vector3d{-x / 1.0_m, -y / 1.0_m, 1.0}, I});
                flux.push_back(Ray{origin, Vector3d{-x / 1.0_m, y / 1.0_m, 1.0}, I});
                flux.push_back(Ray{origin, Vector3d{x / 1.0_m, -y / 1.0_m, 1.0}, I});
                flux.push_back(Ray{origin, Vector3d{x / 1.0_m, y / 1.0_m, 1.0}, I});

                I_s += 4.0 * I;
            }
        }

        // z=1上の分布をみる
        for (int i = 0; i < N; ++i) {
            std::cout << flux[i].dir(0) << ' '
                      << flux[i].dir(1) << ' '
                      << flux[i].I / I_sum << std::endl;
        }
    }
#endif

    return 0;
}
