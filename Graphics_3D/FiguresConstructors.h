#pragma once

#include <vector>
#include <cmath>

#include "Models.h"

namespace FiguresConstructors {
	class FigureConstructor {
	public:
		virtual std::vector<Models3D::Point3D> ConstructCoords() const = 0;
		virtual std::vector<Models3D::Polygon3D> ConstructPolygons() const = 0;
	};

	namespace {
		std::vector<Models3D::Point3D> GetHexahedronCoords(double edge_len) {
			std::vector<Models3D::Point3D> coords = {
				{-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1},
				{-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}
			};
			double edge_half_len = edge_len / 2;
			for (Models3D::Point3D& coord : coords) {
				coord.x *= edge_half_len;
				coord.y *= edge_half_len;
				coord.z *= edge_half_len;
			}
			return coords;
		}
	}

	class HexahedronConstructor : public FigureConstructor {
	public:
		HexahedronConstructor(double edge_len)
			: edge_len_(edge_len) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			return GetHexahedronCoords(edge_len_);
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;

			polygons.push_back(Models3D::Polygon3D({ 0, 1, 2, 3 }));
			polygons.push_back(Models3D::Polygon3D({ 4, 5, 6, 7 }));

			polygons.push_back(Models3D::Polygon3D({ 1, 5, 6, 2 }));
			polygons.push_back(Models3D::Polygon3D({ 0, 4, 7, 3 }));

			polygons.push_back(Models3D::Polygon3D({ 0, 1, 5, 4 }));
			polygons.push_back(Models3D::Polygon3D({ 3, 2, 6, 7 }));

			return polygons;
		}
	protected:
		double edge_len_;
	};

	class TetrahedronConstructor : public FigureConstructor {
	public:
		TetrahedronConstructor(double edge_len)
			: edge_len_(edge_len) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			std::vector<Models3D::Point3D> cube_coords = GetHexahedronCoords(edge_len_ / std::sqrt(2.));
			std::vector<Models3D::Point3D> tet_coords = { cube_coords[0], cube_coords[5], cube_coords[7], cube_coords[2] };
			return tet_coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;

			polygons.push_back(Models3D::Polygon3D({ 0, 1, 3 }));
			polygons.push_back(Models3D::Polygon3D({ 1, 2, 3 }));
			polygons.push_back(Models3D::Polygon3D({ 0, 2, 3 }));
			polygons.push_back(Models3D::Polygon3D({ 0, 1, 2 }));

			return polygons;
		}
	protected:
		double edge_len_;
	};

	class OctahedronConstructor : public FigureConstructor {
	public:
		OctahedronConstructor(double edge_len)
			: edge_len_(edge_len) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			std::vector<Models3D::Point3D> cube_coords = GetHexahedronCoords(edge_len_ * std::sqrt(2.));
			std::vector<Models3D::Point3D> oct_coords = {
				{0, 0, cube_coords[0].z}, {cube_coords[0].x, 0, 0}, {0, 0, -cube_coords[0].z}, {-cube_coords[0].x, 0, 0},
				{0, cube_coords[1].y, 0}, {0, -cube_coords[1].y, 0}
			};
			return oct_coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;

			for (size_t i = 4; i <= 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ 0, 1, i }));
				polygons.push_back(Models3D::Polygon3D({ 1, 2, i }));
				polygons.push_back(Models3D::Polygon3D({ 2, 3, i }));
				polygons.push_back(Models3D::Polygon3D({ 3, 0, i }));
			}
			return polygons;
		}
	protected:
		double edge_len_;
	};

	class IcosahedronConstructor : public FigureConstructor {
	public:
		IcosahedronConstructor(double edge_len)
			: edge_len_(edge_len) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			std::vector<Models3D::Point3D> coords;
			double r = edge_len_ * std::sin(3 * PI / 10) / std::sin(2 * PI / 5);
			double plane_shift = edge_len_ * std::sqrt(3.) / 4;
			double current_angle = PI / 2;
			for (int i = 0; i < 5; ++i) {
				coords.push_back({ r * std::sin(current_angle), r * std::cos(current_angle), plane_shift });
				current_angle += 2 * PI / 5;
			}
			current_angle = PI / 2 + PI / 5;
			for (int i = 0; i < 5; ++i) {
				coords.push_back({ r * std::sin(current_angle), r * std::cos(current_angle), -plane_shift });
				current_angle += 2 * PI / 5;
			}
			double hat_shift = std::sqrt(edge_len_ * edge_len_ - r * r);
			coords.push_back({ 0, 0, plane_shift + hat_shift });
			coords.push_back({ 0, 0, -plane_shift - hat_shift });

			return coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;
			
			for (size_t i = 0; i + 1 < 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i, i + 5, i + 1 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4, 4 + 5, 0 }));
			
			for (size_t i = 0; i + 1 < 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i + 5, i + 1, i + 5 + 1 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4 + 5, 0, 5 }));
			
			for (size_t i = 0; i + 1 < 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i, i + 1, 10 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4, 0, 10 }));
			
			for (size_t i = 5; i + 1 < 10; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i, i + 1, 11 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4 + 5, 0 + 5, 11 }));
			
			return polygons;
		}
	protected:
		double edge_len_;
		const double PI = std::acos(-1);
	};

	class SphereConstructor : public FigureConstructor {
	public:
		SphereConstructor(double radius)
			: radius_(radius) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			std::vector<Models3D::Point3D> coords;

			for (double nu = 0; nu <= 2 * PI; nu += STEP) {
				for (double teta = 0; teta < PI; teta += STEP) {
					coords.push_back({
					radius_ * std::sin(teta) * std::cos(nu),
					radius_ * std::sin(teta) * std::sin(nu),
					radius_ * std::cos(teta) });
				}
				coords.push_back({
					radius_ * std::sin(PI) * std::cos(nu),
					radius_ * std::sin(PI) * std::sin(nu),
					radius_ * std::cos(PI) });
			}
			return coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;
			const size_t vert_shift = GetStepsNumberInVertical();
			const size_t number_of_shifts = ConstructCoords().size() / vert_shift;

			for (size_t shift_num = 0; shift_num + 1 < number_of_shifts; ++shift_num) {
				size_t current_shift = shift_num * vert_shift;
				for (size_t local_i = 0; local_i + 1 < vert_shift; ++local_i) {
					size_t i = local_i + current_shift;
					polygons.push_back(Models3D::Polygon3D({ i, i + 1, i + vert_shift }));
					if (local_i + 2 != vert_shift) {
						polygons.push_back(Models3D::Polygon3D({ i + 1, i + vert_shift, i + 1 + vert_shift }));
					}
				}
			}
			size_t current_shift = (number_of_shifts - 1) * vert_shift;
			for (size_t local_i = 0; local_i + 1 < vert_shift; ++local_i) {
				size_t i = local_i + current_shift;
				polygons.push_back(Models3D::Polygon3D({ i, i + 1, local_i }));
				if (local_i + 2 != vert_shift) {
					polygons.push_back(Models3D::Polygon3D({ i + 1, local_i, local_i + 1 }));
				}
			}
			return polygons;
		}

	protected:
		size_t GetStepsNumberInVertical() const { // because PI / STEP could fail
			size_t steps_num = 0;
			for (double teta = 0; teta < PI; teta += STEP) {
				++steps_num;
			}
			return steps_num + 1;
		}

	protected:
		double radius_;
		const double STEP = 0.15;
		const double PI = std::acos(-1);
	};

	class DodecahedronConstructor : public FigureConstructor {
	public:
		DodecahedronConstructor(double edge_len)
			: edge_len_(edge_len) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			IcosahedronConstructor icosahedron_constructor(edge_len_ * 3. / (std::sqrt(2.) * std::sqrt(1 - std::cos(3. * PI / 5.))));
			std::vector<Models3D::Point3D> icosahedron_coords = icosahedron_constructor.ConstructCoords();
			std::vector<Models3D::Polygon3D> icosahedron_polygons = icosahedron_constructor.ConstructPolygons();

			std::vector<Models3D::Point3D> coords;
			for (const Models3D::Polygon3D& polygon : icosahedron_polygons) {
				Models3D::Point3D average_point;
				for (const Models3D::Point3D* point : polygon.GetCoords(icosahedron_coords)) {
					average_point.x += point->x;
					average_point.y += point->y;
					average_point.z += point->z;
				}
				size_t coords_num = polygon.GetCoords(icosahedron_coords).size();
				average_point.x /= coords_num;
				average_point.y /= coords_num;
				average_point.z /= coords_num;

				coords.push_back(average_point);
			}

			return coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;

			polygons.push_back(Models3D::Polygon3D({ 10, 11, 12, 13, 14 }));
			polygons.push_back(Models3D::Polygon3D({ 15, 16, 17, 18, 19 }));
			
			for (size_t i = 0; i + 1 < 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i, i + 5, i + 1, i + 11, i + 10 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4, 4 + 5, 0, 10,  4 + 10 }));
			
			for (size_t i = 0; i + 1 < 5; ++i) {
				polygons.push_back(Models3D::Polygon3D({ i + 5, i + 1, i + 5 + 1, i + 16, i + 15 }));
			}
			polygons.push_back(Models3D::Polygon3D({ 4 + 5, 0, 5, 15, 4 + 15 }));

			return polygons;
		}
	protected:
		double edge_len_;
		const double PI = std::acos(-1);
	};

	class TorusConstructor : public FigureConstructor {
	public:
		TorusConstructor(double big_r, double small_r)
			: big_r_(big_r), small_r_(small_r) { }

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			std::vector<Models3D::Point3D> coords;

			for (double nu = 0; nu <= 2 * PI; nu += STEP) {
				for (double teta = 0; teta <= 2 * PI; teta += STEP) {
					coords.push_back({
					(big_r_ + small_r_ * std::cos(teta)) * std::cos(nu),
					(big_r_ + small_r_ * std::cos(teta)) * std::sin(nu),
					small_r_ * std::sin(teta) });
				}
			}
			return coords;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			std::vector<Models3D::Polygon3D> polygons;
			const size_t vert_shift = GetStepsNumberInVertical();
			const size_t number_of_shifts = ConstructCoords().size() / vert_shift;

			for (size_t shift_num = 0; shift_num + 1 < number_of_shifts; ++shift_num) {
				size_t current_shift = shift_num * vert_shift;
				for (size_t local_i = 0; local_i + 1 < vert_shift; ++local_i) {
					size_t i = local_i + current_shift;
					polygons.push_back(Models3D::Polygon3D({ i, i + 1, i + vert_shift }));
					polygons.push_back(Models3D::Polygon3D({ i + 1, i + vert_shift, i + 1 + vert_shift }));
				}
				if (vert_shift > 1) {
					size_t last_i = vert_shift - 1 + current_shift;
					polygons.push_back(Models3D::Polygon3D({ last_i, current_shift, last_i + vert_shift }));
					polygons.push_back(Models3D::Polygon3D({ current_shift, last_i + vert_shift, current_shift + vert_shift }));
				}
			}
			if (number_of_shifts > 1) {
				size_t current_shift = (number_of_shifts - 1) * vert_shift;
				for (size_t local_i = 0; local_i + 1 < vert_shift; ++local_i) {
					size_t i = local_i + current_shift;
					polygons.push_back(Models3D::Polygon3D({ i, i + 1, local_i }));
					polygons.push_back(Models3D::Polygon3D({ i + 1, local_i, local_i + 1 }));
				}
				if (vert_shift > 1) {
					size_t last_local_i = vert_shift - 1;
					polygons.push_back(Models3D::Polygon3D({ last_local_i + current_shift, current_shift, last_local_i }));
					polygons.push_back(Models3D::Polygon3D({ last_local_i, 0, current_shift }));
				}
			}
			return polygons;
		}
	protected:
		size_t GetStepsNumberInVertical() const { // because 2*PI / STEP could fail
			size_t steps_num = 0;
			for (double teta = 0; teta <= 2 * PI; teta += STEP) {
				++steps_num;
			}
			return steps_num;
		}
	protected:
		double big_r_, small_r_;
		const double STEP = 0.15;
		const double PI = std::acos(-1);
	};

	class FromFileConstructor : public FigureConstructor {
	public:
		FromFileConstructor(const std::string& file_name) {
			std::ifstream file(file_name);
			if (!file) {
				throw std::runtime_error("");
			}

			size_t coords_num;
			file >> coords_num;
			for (size_t i = 0; i < coords_num; ++i) {
				double x, y, z;
				file >> x >> y >> z;
				coords_.push_back({ x, y, z });
			}

			size_t polygons_num;
			file >> polygons_num;
			file.ignore(1);
			for (size_t i = 0; i < polygons_num; ++i) {
				std::string current_line;
				std::getline(file, current_line);
				std::stringstream ss(current_line);

				std::vector<size_t> inds;
				size_t ind;
				while (ss >> ind) {
					inds.push_back(ind);
				}
				polygons_.push_back({ inds });
			}
		}

		std::vector<Models3D::Point3D> ConstructCoords() const override {
			return coords_;
		}

		std::vector<Models3D::Polygon3D> ConstructPolygons() const override {
			return polygons_;
		}
	protected:
		std::vector<Models3D::Point3D> coords_;
		std::vector<Models3D::Polygon3D> polygons_;
	};
}


