#pragma once

#include "Figures.h"
#include "Models.h"

#include <vector>
#include <optional>

namespace Figures3D {
	class SceneFigures {
	public:
		SceneFigures(size_t scene_width, size_t scene_height) 
			: scene_width_(scene_width), scene_height_(scene_height) { }

		std::vector<Figure>& GetFigures() {
			return figures_;
		}

		void TakeOrthogonalProjection(Bitmap^ bm) const {
			for (const Figure& figure : figures_) {
				figure.TakeOrthogonalProjection(bm);
			}
		}
		void TakePerspectiveProjection(Bitmap^ bm) const {
			for (const Figure& figure : figures_) {
				figure.TakePerspectiveProjection(bm);
			}
		}

		void TakeOrthogonalProjectionRobertsAlgo(Bitmap^ bm) const {
			for (const Figure& figure : figures_) {
				figure.TakeOnlyVisibleOrthogonalProjection(bm);
			}
		}
		void TakePerspectiveProjectionRobertsAlgo(Bitmap^ bm) const {
			for (const Figure& figure : figures_) {
				figure.TakeOnlyVisiblePerspectiveProjection(bm);
			}
		}

		void TakeOrthogonalProjectionZAlgo(Bitmap^ bm) const {
			TakeProjectionZAlgo(bm, false);
		}
		void TakePerspectiveProjectionZAlgo(Bitmap^ bm) const {
			TakeProjectionZAlgo(bm, true);
		}

	protected:
		void TakeProjectionZAlgo(Bitmap^ bm, bool is_perspective) const {
			using namespace Models3D;

			Buffer buffer(scene_width_, std::vector<std::optional<double>>(scene_height_));

			for (const Figure& figure : figures_) {
				std::vector<Point3D> scene_coords = figure.GetSceneCoords(is_perspective);
				const std::vector<Polygon3D>& polygons = figure.GetPolygons();
				for (const Polygon3D& polygon : polygons) {
					std::vector<const Point3D*> polygon_coords = polygon.GetCoords(scene_coords);
					PlaneEquation plane = polygon.GetPlaneEquation(scene_coords);
					AddPolygonOnScene(bm, buffer, polygon_coords, plane, figure.GetFigureColor());
				}
			}
		}

	protected:
		typedef std::vector<std::vector<std::optional<double>>> Buffer;

		void AddPolygonOnScene(Bitmap^ bm, Buffer& buffer, const std::vector<const Point3D*>& polygon_coords, const Models3D::PlaneEquation& plane, const Color& figure_color) const {
			using namespace Models3D;

			int min_y = (int)polygon_coords[0]->y;
			int max_y = (int)polygon_coords[0]->y;

			for (const Point3D* coordinate : polygon_coords) {
				min_y = std::min(min_y, (int)coordinate->y);
				max_y = std::max(max_y, (int)coordinate->y);
			}

			std::vector<const Point3D*> cycled_coordinates(polygon_coords);
			cycled_coordinates.push_back(polygon_coords[0]);

			for (int y = min_y; y <= max_y; ++y) {
				std::vector<int> x_crossings;
				for (int i = 0; i + 1 < cycled_coordinates.size(); ++i) {
					const Point3D* first = cycled_coordinates[i];
					const Point3D* second = cycled_coordinates[i + 1];
					const Point3D* prev = i > 0 ? cycled_coordinates[i - 1] : polygon_coords.back();

					if (first->x == second->x) {
						if (y >= std::min(first->y, second->y) && y <= std::max(first->y, second->y)) {
							x_crossings.push_back((int)first->x);
						}
					}
					else {
						if (first->y != second->y) {
							double k = ((double)(first->y - second->y)) / (first->x - second->x);
							double x = (first->x + (y - first->y) / k);
							if (x >= std::min(first->x, second->x) && x <= std::max(first->x, second->x)) {
								if (!(first->y == y && ((second->y > y && prev->y < y) || (second->y < y && prev->y > y)))) {
									x_crossings.push_back((int)x);
								}
							}
						}
					}
				}
				std::sort(x_crossings.begin(), x_crossings.end());

				for (int i = 0; i + 1 < x_crossings.size(); i += 2) {
					for (int x = x_crossings[i]; x <= x_crossings[i + 1]; ++x) {
						if (x >= 0 && x < scene_width_ && y >= 0 && y < scene_height_ && plane.c != 0) {
							double z = (-plane.d - plane.a * x - plane.b * y) / plane.c;
							if (!buffer[x][y].has_value() || *buffer[x][y] < z) {
								buffer[x][y] = z;
								bm->SetPixel(x, y, figure_color);
							}
						}
					}
				}
			}
		}

	protected:
		std::vector<Figure> figures_;
		size_t scene_width_, scene_height_;
	};
}