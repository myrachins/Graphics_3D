#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Models.h"
#include "Operations.h"
#include "CanvasUtils.h"
#include "FiguresConstructors.h"

namespace Figures3D {
	using namespace System::Drawing;
	using Models3D::Point3D;
	using Models3D::Polygon3D;
	using Models3D::CanvasCoordinate;

	class Figure {
	public:
		Figure(const FiguresConstructors::FigureConstructor& constructor,
			double canvas_scale, double x_canvas_shift, double y_canvas_shift,
			double focus_distance, double camera_distance)
			: x_canvas_shift_(x_canvas_shift), y_canvas_shift_(y_canvas_shift)
			, canvas_scale_(canvas_scale), focus_distance_(focus_distance), camera_distance_(camera_distance) {
			coords_ = constructor.ConstructCoords();
			polygons_ = constructor.ConstructPolygons();
		}

		Figure(const Figure&) = delete;
		Figure& operator=(const Figure&) = delete;

		void RotateX(double angle) {
			UpdateCoordinates(Operations3D::RotateX(angle));
		}
		void RotateY(double angle) {
			UpdateCoordinates(Operations3D::RotateY(angle));
		}
		void RotateZ(double angle) {
			UpdateCoordinates(Operations3D::RotateZ(angle));
		}

		void TakeOrthogonalProjection(Bitmap^ bm) const {
			TakeProjection(bm, coords_, polygons_);
		}
		void TakeOnlyVisibleOrthogonalProjection(Bitmap^ bm) const {
			TakeProjection(bm, coords_, GetOnlyVisiblePlygons(coords_));
		}
		void TakePerspectiveProjection(Bitmap^ bm) const {
			std::vector<Point3D> transformed_coords = Operations3D::ApplyForAll(coords_, Operations3D::PerspectiveZProjection(focus_distance_));
			TakeProjection(bm, transformed_coords, polygons_);
		}
		void TakeOnlyVisiblePerspectiveProjection(Bitmap^ bm) const {
			std::vector<Point3D> transformed_coords = Operations3D::ApplyForAll(coords_, Operations3D::PerspectiveZProjection(focus_distance_));
			TakeProjection(bm, transformed_coords, GetOnlyVisiblePlygons(transformed_coords));
		}

		void Shift(double dx, double dy, double dz) {
			UpdateCoordinates(Operations3D::Shift(dx, dy, dz));
		}

		void Scale(double x_scale, double y_scale, double z_scale, double figure_scale) {
			UpdateCoordinates(Operations3D::Scale(x_scale, y_scale, z_scale, figure_scale));
		}

		void SetFocusDistance(double focus_distance) {
			focus_distance_ = focus_distance;
		}

		void SaveToFile(const std::string& file_name) const {
			std::ofstream file(file_name);
			if (!file) {
				throw std::runtime_error("");
			}

			file << coords_.size() << "\n";
			for (const Models3D::Point3D& point : coords_) {
				file << point.x << " " << point.y << " " << point.z << "\n";
			}

			file << polygons_.size() << "\n";
			for (const Models3D::Polygon3D& polygon : polygons_) {
				for (size_t ind : polygon.GetCoordsInds()) {
					file << ind << " ";
				}
				file << "\n";
			}
		}

	protected:
		void DrawFigure(Bitmap^ bm, const std::vector<Models3D::CanvasPolygon>& canvas_polygons) const {
			for (const Models3D::CanvasPolygon& polygon : canvas_polygons) {
				const Models3D::CanvasCoordinate* prev_coordinate = nullptr;
				const std::vector<CanvasCoordinate>& coords = polygon.GetCoords();
				for (size_t i = 0; i + 1 < coords.size(); ++i) {
					CanvasUtils::DrawLine(bm, coords[i], coords[i + 1], Color::Black);
				}
				if (!coords.empty()) {
					CanvasUtils::DrawLine(bm, coords.back(), coords[0], Color::Black);
				}
			}
		}

		void TakeProjection(Bitmap^ bm, const std::vector<Point3D>& coords, const std::vector<Polygon3D>& polygons) const {
			std::vector<Models3D::CanvasPolygon> canvas_polygons;
			for (const Polygon3D& polygon : polygons) {
				std::vector<CanvasCoordinate> current_polygon_coords;
				for (const Point3D* point : polygon.GetCoords(coords)) {
					Point3D transformed_point = Operations3D::Apply(*point, Operations3D::OrthogonalZProjection());
					current_polygon_coords.push_back(GetCanvasCoordinate(transformed_point));
				}
				canvas_polygons.push_back(Models3D::CanvasPolygon(std::move(current_polygon_coords)));
			}
			DrawFigure(bm, canvas_polygons);
		}

		void UpdateCoordinates(const Operations3D::BaseOperation& operation) {
			for (size_t i = 0; i < coords_.size(); ++i) {
				coords_[i] = Operations3D::Apply(coords_[i], operation);
			}
		}

		CanvasCoordinate GetCanvasCoordinate(const Point3D& point) const {
			return {
				(int) (point.x * canvas_scale_ + x_canvas_shift_),
				(int) (point.y * canvas_scale_ + y_canvas_shift_)
			};
		}

		bool IsPolygonVisible(const Polygon3D& polygon, const std::vector<Point3D>& coords) const {
			Models3D::PlaneEquation plane = polygon.GetPlaneEquation(coords);
			Point3D centroid = Get—entroid();

			double m = -Utils::Sign(plane.a * centroid.x + plane.b * centroid.y + plane.c * centroid.z + plane.d);
			plane.a *= m; plane.b *= m; plane.c *= m; plane.d *= m;
			Point3D view_point = GetViewPoint();

			return (plane.a * view_point.x + plane.b * view_point.y + plane.c * view_point.z + plane.d) > 0;
		}

		std::vector<Polygon3D> GetOnlyVisiblePlygons(const std::vector<Point3D>& coords) const {
			std::vector<Polygon3D> only_visible;
			std::copy_if(polygons_.begin(), polygons_.end(), std::back_inserter(only_visible),
				[&](const Polygon3D& polygon) {
				return IsPolygonVisible(polygon, coords);
			});
			return only_visible;
		}
		
		Point3D Get—entroid() const {
			Point3D centroid;

			for (const Point3D& point : coords_) {
				centroid.x += point.x;
				centroid.y += point.y;
				centroid.z += point.z;
			}
			centroid.x /= coords_.size();
			centroid.y /= coords_.size();
			centroid.z /= coords_.size();

			return centroid;
		}

		Point3D GetViewPoint() const {
			return { 0, 0, camera_distance_ };
		}
		
	protected:
		std::vector<Point3D> coords_;
		std::vector<Polygon3D> polygons_;
		double x_canvas_shift_, y_canvas_shift_, canvas_scale_;
		double focus_distance_, camera_distance_;
	};

	class FuguresFabric {
	public:
		FuguresFabric(double canvas_scale, double x_canvas_shift, double y_canvas_shift, double focus_distance, double camera_distance)
			: x_canvas_shift_(x_canvas_shift), y_canvas_shift_(y_canvas_shift)
			, canvas_scale_(canvas_scale), focus_distance_(focus_distance), camera_distance_(camera_distance) { }

		std::unique_ptr<Figure> CreateHexahedron(double edge_len) {
			return CreateFigure(FiguresConstructors::HexahedronConstructor(edge_len));
		}

		std::unique_ptr<Figure> CreateTetrahedron(double edge_len) {
			return CreateFigure(FiguresConstructors::TetrahedronConstructor(edge_len));
		}

		std::unique_ptr<Figure> CreateOctahedron(double edge_len) {
			return CreateFigure(FiguresConstructors::OctahedronConstructor(edge_len));
		}

		std::unique_ptr<Figure> CreateIcosahedron(double edge_len) {
			return CreateFigure(FiguresConstructors::IcosahedronConstructor(edge_len));
		}

		std::unique_ptr<Figure> CreateSphere(double radius) {
			return CreateFigure(FiguresConstructors::SphereConstructor(radius));
		}

		std::unique_ptr<Figure> CreateDodecahedron(double edge_len) {
			return CreateFigure(FiguresConstructors::DodecahedronConstructor(edge_len));
		}

		std::unique_ptr<Figure> CreateTorus(double big_r, double small_r) {
			return CreateFigure(FiguresConstructors::TorusConstructor(big_r, small_r));
		}

		std::unique_ptr<Figure> CreateFromFile(const std::string& file_name) {
			return CreateFigure(FiguresConstructors::FromFileConstructor(file_name));
		}

	protected:
		std::unique_ptr<Figure> CreateFigure(const FiguresConstructors::FigureConstructor& constructor) const {
			return std::make_unique<Figure>(constructor, canvas_scale_, x_canvas_shift_, y_canvas_shift_, focus_distance_, camera_distance_);
		}

	protected:
		double x_canvas_shift_, y_canvas_shift_, canvas_scale_;
		double focus_distance_, camera_distance_;
	};
}