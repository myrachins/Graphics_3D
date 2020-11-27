#pragma once

#include <cmath>
#include <memory>
#include "Models.h"

namespace Utils {
	Models3D::Matrix Multiply(const Models3D::Matrix& lhs, const Models3D::Matrix& rhs) {
		if (lhs.empty() || rhs.empty()) {
			return Models3D::Matrix();
		}
		if (lhs[0].size() != rhs.size()) {
			throw std::runtime_error("");
		}
		Models3D::Matrix result = Models3D::Matrix(lhs.size(), Models3D::Vector(rhs[0].size()));

		for (size_t i = 0; i < lhs.size(); ++i) {
			for (size_t j = 0; j < rhs[0].size(); ++j) {
				for (size_t k = 0; k < lhs[0].size(); ++k) {
					result[i][j] += lhs[i][k] * rhs[k][j];
				}
			}
		}
		return result;
	}

	int Sign(double value) {
		if (value > 0) {
			return 1;
		} else if (value < 0) {
			return -1;
		}
		return 0;
	}
}

namespace Operations3D {
	Models3D::Matrix GetMatrixFromPoint(const Models3D::Point3D& point) {
		return { { point.x, point.y, point.z, point.h } };
	}

	Models3D::Point3D GetPointFromMatrix(const Models3D::Matrix& matrix) {
		return Models3D::Point3D(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
	}

	class BaseOperation {
	public:
		virtual Models3D::Matrix Apply(const Models3D::Matrix& left) const = 0;
		virtual ~BaseOperation() = default;
	};

	Models3D::Point3D Apply(const Models3D::Point3D& left, const BaseOperation& operation) {
		Models3D::Matrix left_matrix = GetMatrixFromPoint(left);
		Models3D::Matrix result_matrix = operation.Apply(left_matrix);

		return GetPointFromMatrix(result_matrix);
	}

	std::vector<Models3D::Point3D> ApplyForAll(const std::vector<Models3D::Point3D>& coords, const BaseOperation& operation) {
		std::vector<Models3D::Point3D> transformed_coords;
		for (const Models3D::Point3D& coord : coords) {
			transformed_coords.push_back(Apply(coord, operation));
		}
		return transformed_coords;
	}

	class Rotate : public BaseOperation {
	public:
		Rotate(double angle_phi) 
			: angle_phi(angle_phi) { }

	protected:
		double angle_phi;
	};

	class RotateX : public Rotate {
	public:
		RotateX(double angle_phi) : Rotate(angle_phi) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix rotate_matrix = {
			{ 1, 0, 0, 0 },
			{ 0, std::cos(angle_phi), std::sin(angle_phi), 0 },
			{ 0, -std::sin(angle_phi), std::cos(angle_phi), 0 },
			{ 0, 0, 0, 1 } };

			return Utils::Multiply(left, rotate_matrix);
		}
	};

	class RotateY : public Rotate {
	public:
		RotateY(double angle_phi) : Rotate(angle_phi) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix rotate_matrix = {
			{ std::cos(angle_phi), 0, -std::sin(angle_phi), 0 },
			{ 0, 1, 0, 0 },
			{ std::sin(angle_phi), 0, std::cos(angle_phi), 0 },
			{ 0, 0, 0, 1 } };

			return Utils::Multiply(left, rotate_matrix);
		}
	};

	class RotateZ : public Rotate {
	public:
		RotateZ(double angle_phi) : Rotate(angle_phi) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix rotate_matrix = {
			{ std::cos(angle_phi), std::sin(angle_phi), 0, 0 },
			{ -std::sin(angle_phi), std::cos(angle_phi), 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 } };

			return Utils::Multiply(left, rotate_matrix);
		}
	};

	class Shift : public BaseOperation {
	public:
		Shift(double dx, double dy, double dz)
			: dx(dx), dy(dy), dz(dz) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix shift_matrix = {
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ dx, dy, dz, 1 } };

			return Utils::Multiply(left, shift_matrix);
		}
	protected:
		double dx, dy, dz;
	};

	class Scale : public BaseOperation {
	public:
		Scale(double x_scale, double y_scale, double z_scale, double figure_scale)
			: x_scale(x_scale), y_scale(y_scale), z_scale(z_scale), figure_scale(figure_scale) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix scale_matrix = {
			{ x_scale, 0, 0, 0 },
			{ 0, y_scale, 0, 0 },
			{ 0, 0, z_scale, 0 },
			{ 0, 0, 0, 1 / figure_scale } };

			return Utils::Multiply(left, scale_matrix);
		}
	protected:
		double x_scale, y_scale, z_scale, figure_scale;
	};

	class OrthogonalZProjection : public BaseOperation {
	public:
		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix projection_matrix = {
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 1 } };

			return Utils::Multiply(left, projection_matrix);
		}
	};

	class PerspectiveZProjection : public BaseOperation {
	public:
		PerspectiveZProjection(double focus_distance)
			: focus_distance(focus_distance) { }

		Models3D::Matrix Apply(const Models3D::Matrix& left) const override {
			Models3D::Matrix projection_matrix = {
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, -1 / focus_distance },
			{ 0, 0, 0, 1 } };

			return Utils::Multiply(left, projection_matrix);
		}
	protected:
		double focus_distance;
	};
}
