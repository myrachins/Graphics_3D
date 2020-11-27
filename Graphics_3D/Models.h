#pragma once

#include <vector>

namespace Models3D {
	typedef std::vector<double> Vector;
	typedef std::vector<Vector> Matrix;

	class Point3D {
	public:
		Point3D(double x, double y, double z, double h)
			: x(x / h), y(y / h), z(z / h), h(1) { }

		Point3D(double x, double y, double z) : Point3D(x, y, z, 1) { }

		Point3D() : Point3D(0, 0, 0) { }

		double x, y, z, h;
	};

	struct CanvasCoordinate {
		int x;
		int y;
	};

	struct PlaneEquation {
		double a, b, c, d;
	};

	class Polygon3D {
	public:
		Polygon3D(std::vector<const Point3D*> coords)
			: coords_(std::move(coords)) {
			if (coords_.size() < 3) {
				throw std::runtime_error("");
			}
		}
		const std::vector<const Point3D*>& GetCoords() const {
			return coords_;
		}
		PlaneEquation GetPlaneEquation() const {
			Point3D vector1(coords_[0]->x - coords_[1]->x, coords_[0]->y - coords_[1]->y, coords_[0]->z - coords_[1]->z);
			Point3D vector2(coords_[0]->x - coords_[2]->x, coords_[0]->y - coords_[2]->y, coords_[0]->z - coords_[2]->z);

			PlaneEquation plane;
			plane.a = vector1.y * vector2.z - vector2.y * vector1.z;
			plane.b = vector1.z * vector2.x - vector2.z * vector1.x;
			plane.c = vector1.x * vector2.y - vector2.x * vector1.y;
			plane.d = -(plane.a * vector1.x + plane.b * vector1.y + plane.c * vector1.z);

			return plane;
		}

	protected:
		std::vector<const Point3D*> coords_;
	};

	class CanvasPolygon {
	public:
		CanvasPolygon(std::vector<CanvasCoordinate> coords)
			: coords_(std::move(coords)) {
			if (coords_.size() < 3) {
				throw std::runtime_error("");
			}
		}
		const std::vector<CanvasCoordinate>& GetCoords() const {
			return coords_;
		}

	protected:
		std::vector<CanvasCoordinate> coords_;
	};
}