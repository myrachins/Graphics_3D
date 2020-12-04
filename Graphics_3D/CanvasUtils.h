#pragma once

#include "Operations.h"
#include <cmath>
#include <memory>

namespace CanvasUtils {
	using namespace System::Drawing;
	using namespace Operations3D;

	void DrawLine(Bitmap^ bm, const Models3D::CanvasCoordinate& start, const Models3D::CanvasCoordinate& end, Color color) {
		Graphics^ g = Graphics::FromImage(bm);
		Pen^ p = gcnew Pen(color, 1);

		try {
			g->DrawLine(p, start.x, start.y, end.x, end.y);
		} finally {
			delete p;
			delete g;
		}
	}

	struct ApplicationSettings {
		static double GetRotateAngle() {
			return 0.2;
		}
		static double GetScale() {
			return 1.1;
		}
		static double GetFocusDistance() {
			return 10;
		}
		static double GetShiftDelta() {
			return 0.5;
		}
		static double GetCanvasScale() {
			return 80;
		}
		static double GetCameraDistance() {
			return 500;
		}
		static double GetFiguresDefaultSize() {
			return 2;
		}
		static Color GetDefaultColor() {
			return Color::Black;
		}
	};

	template <typename T>
	ref class AutoPtr {
	public:
		AutoPtr() : m_ptr(0) { }
		AutoPtr(T* ptr) : m_ptr(ptr) { }
		AutoPtr(AutoPtr<T>% right) : m_ptr(right.Release()) { }

		~AutoPtr() {
			if (m_ptr != 0) {
				delete m_ptr;
				m_ptr = 0;
			}
		}

		T& operator*() {
			return *m_ptr;
		}
		T* operator->() {
			return m_ptr;
		}
		T* Get() {
			return m_ptr;
		}

		T* Release() {
			T* released = m_ptr;
			m_ptr = 0;
			return released;
		}
		void Reset() {
			Reset(0);
		}
		void Reset(T* ptr) {
			if (0 != m_ptr) {
				delete m_ptr;
			}
			m_ptr = ptr;
		}
		void Reset(std::unique_ptr<T> ptr) {
			Reset(ptr.release());
		}

	private:
		T* m_ptr;
	};
}