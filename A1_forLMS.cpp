#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

const double PI = 3.14159265358979323846;


struct Circle {
  double x, y, r;

  // Проверка, находится ли точка внутри круга
  bool contains(double px, double py) const {
    double dx = px - x;
    double dy = py - y;
    return dx * dx + dy * dy <= r * r;
  }
};

// Класс для вычисления площади пересечения методом Монте-Карло
class MonteCarloIntersection {
 private:
  std::vector<Circle> circles_;

 public:
  MonteCarloIntersection(const std::vector<Circle>& circles)
      : circles_(circles) {}

  // Вычисление площади пересечения для заданной прямоугольной области
  double computeIntersectionArea(double left, double right, double bottom,
                                 double top, int num_points, int seed = 42) {
    double rect_area = (right - left) * (top - bottom);
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> dist_x(left, right);
    std::uniform_real_distribution<double> dist_y(bottom, top);

    int points_inside = 0;
    for (int i = 0; i < num_points; ++i) {
      double x = dist_x(generator);
      double y = dist_y(generator);

      // Проверяем, находится ли точка внутри всех кругов
      bool in_all_circles = true;
      for (const auto& circle : circles_) {
        if (!circle.contains(x, y)) {
          in_all_circles = false;
          break;
        }
      }

      if (in_all_circles) {
        ++points_inside;
      }
    }

    
    return (static_cast<double>(points_inside) / num_points) * rect_area;
  }
};

// Вычисление площади пересечения для кругов
double computeExactArea() {
  // Площадь прямоугольного треугольника
  double S_T = 0.5;

  // Площадь сегмента C1
  double S_C1 = (PI / 2.0 - 1.0) / 2.0;  

  // Площадь сегментов C2 и C3
  double r = std::sqrt(5.0) / 2.0;
  double theta = std::asin(0.8);
  double S_C2 = (theta - 0.8) / 2.0 * r * r;  

  return S_T + S_C1 + 2.0 * S_C2;
}

int main() {
  // Круги из условия задачи A1
  std::vector<Circle> circles = {{1.0, 1.0, 1.0},
                                 {1.5, 2.0, std::sqrt(5.0) / 2.0},
                                 {2.0, 1.5, std::sqrt(5.0) / 2.0}};

  // Вычисление точной площади для сравнения
  double exact_area = computeExactArea();
  std::cout << "Exact intersection area: " << exact_area << std::endl;

  MonteCarloIntersection mc(circles);

  // Области для генерации точек
  // Широкая область: [0, 3] x [0, 3] 
  double wide_left = 0.0, wide_right = 3.0;
  double wide_bottom = 0.0, wide_top = 3.0;

  // Узкая область: [1, 2] x [1, 2] 
  double narrow_left = 1.0, narrow_right = 2.0;
  double narrow_bottom = 1.0, narrow_top = 2.0;

  // Проведение экспериментов для разных количеств точек
  std::ofstream results("monte_carlo_results.csv");
  results
      << "N,wide_area,wide_relative_error,narrow_area,narrow_relative_error\n";

  for (int N = 100; N <= 100000; N += 500) {
    // Вычисление для широкой области
    double wide_area = mc.computeIntersectionArea(wide_left, wide_right,
                                                  wide_bottom, wide_top, N);
    double wide_error = std::abs(wide_area - exact_area) / exact_area;

    // Вычисление для узкой области
    double narrow_area = mc.computeIntersectionArea(
        narrow_left, narrow_right, narrow_bottom, narrow_top, N);
    double narrow_error = std::abs(narrow_area - exact_area) / exact_area;

    // Запись результатов в CSV файл
    results << N << "," << wide_area << "," << wide_error << "," << narrow_area
            << "," << narrow_error << "\n";

    // Вывод прогресса каждые 10000 точек
    if (N % 10000 == 0) {
      std::cout << "N = " << N << ", Wide area: " << wide_area
                << " (error: " << wide_error * 100 << "%)"
                << ", Narrow area: " << narrow_area
                << " (error: " << narrow_error * 100 << "%)" << std::endl;
    }
  }

  results.close();
  std::cout << "Experimental data saved to monte_carlo_results.csv"
            << std::endl;

  return 0;
}