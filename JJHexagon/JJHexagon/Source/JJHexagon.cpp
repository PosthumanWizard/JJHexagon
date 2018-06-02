///<summary>
///<para>Implementation of a Hexagon-based grid system.
///<para>Written with frequent reference to https://www.redblobgames.com/grids/hexagons/
///<para>And http://keekerdc.com/2011/03/hexagon-grids-coordinate-systems-and-distance-calculations/
///<para> Flat Top Orientation
///<para>   240 ____ 300
///<para>	   /    \
///<para> 180 /      \ 0
///<para>     \      /    
///<para>  120 \____/ 60    
///</summary> 

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include <assert.h>
#include <vector>

using int32 = int;

namespace JJHexagon {
	///Information describing a 2D point on the grid.
	struct PointData
	{
		private:
			const float x;
			const float y;
		public:
			PointData(float newX, float newY) : x(newX), y(newY) {}
			inline const float X() { return x; };
			inline const float Y() { return y; };
	};

	///Information describing a cubic Hexagon. 
    struct HexData
	{
		private:
			const int32 x;
			const int32 y;
		public:
			HexData(int32 newX, int32 newY) : x(newX), y(newY){}
			inline const PointData Coords() { return PointData(x, y); };
			inline const int32 X() { return x; };
			inline const int32 Y() { return y; };
			inline const int32 Z() { return - x - y; };
	};

	const std::vector<HexData> Directions = {
		HexData(1, 0), HexData(1, -1), HexData(0, -1),
		HexData(-1, 0), HexData(-1, 1), HexData(0, 1)
	};

#pragma region PointData Operations

	inline PointData operator +(PointData a, PointData b)
	{
		return PointData(a.X() + b.X(), a.Y() + b.Y());
	}

	inline PointData operator -(PointData a, PointData b)
	{
		return PointData(a.X() - b.X(), a.Y() - b.Y());
	}

	inline PointData operator *(PointData a, PointData b)
	{
		return PointData(a.X() * b.X(), a.Y() * b.Y());
	}

	inline PointData operator /(PointData a, PointData b)
	{
		return PointData(a.X() / b.X(), a.Y() / b.Y());
	}

	inline PointData operator /(PointData a, float b)
	{
		return PointData(a.X() / b, a.Y() / b);
	}

	inline bool operator ==(PointData a, PointData b)
	{
		return (a.X() == b.X() && a.Y() == b.Y());
	}

	inline bool operator !=(PointData a, PointData b)
	{
		return (a.X() != b.X() || a.Y() != b.Y());
	}

#pragma endregion

#pragma region HexData Operations

	inline bool operator ==(HexData a, HexData b)
	{
		return (a.X() == b.X() && a.Y() == b.Y() && a.L() == b.L());
	}

	inline bool operator !=(HexData a, HexData b)
	{
		return (a.X() != b.X() || a.Y() != b.Y() || a.L() != b.L());
	}

	inline HexData operator +(HexData a, HexData b)
	{
		return HexData(a.X() + b.X(), a.Y() + b.Y());
	}

	inline HexData operator -(HexData a, HexData b)
	{
		return HexData(a.X() - b.X(), a.Y() - b.Y());
	}

	inline HexData operator *(HexData a, HexData b)
	{
		return HexData(a.X() * b.X(), a.Y() * b.Y());
	}

	inline HexData operator /(HexData a, HexData b)
	{
		return HexData(a.X() / b.X(), a.Y() / b.Y());
	}

	inline HexData Add(HexData a, int32 offsetX, int32 offsetY)
	{
		return HexData(a.X() + offsetX, a.Y() + offsetY);
	}

	inline HexData Subtract(HexData a, int32 offsetX, int32 offsetY)
	{
		return HexData(a.X() - offsetX, a.Y() - offsetY);
	}

	inline HexData Multiply(HexData a, int32 offsetX, int32 offsetY)
	{
		return HexData(a.X() * offsetX, a.Y() * offsetY);
	}

	inline HexData Divide(HexData a, int32 offsetX, int32 offsetY)
	{
		return HexData(a.X() / offsetX, a.Y() / offsetY);
	}

	///Direction should be 0 to 5
	inline HexData Direction(int direction)
	{
		return Directions[direction];
	}

	inline HexData Neighbour(HexData hex, HexData direction)
	{
		return hex + direction;
	}

	inline HexData Neighbour(HexData hex, int direction)
	{
		return Directions[direction];
	}

	inline HexData Neighbour(HexData hex, int directionX, int directionY)
	{
		return Add(hex, directionX, directionY)
	}

	inline int32 Distance(HexData a, HexData b) {
		return std::max(
			std::max(std::abs(b.X() - a.X()), std::abs(b.Y() - a.Y())),
			std::abs(b.Z() - a.Z()));
	}

	inline PointData Position(HexData hex)
	{
		return PointData(hex.X, hex.Y);
	}

	const PointData Vertex(PointData hexCoords, int32 vertexIndex, int32 pointTop)
	{
		float angle = Angle(vertexIndex, true, pointTop);
		return Vertex(hexCoords, angle);
	}

	const PointData Vertex(PointData hexCoords, float angle)
	{

	}

	const PointData Edge(PointData hexCoords, int32 edgeIndex, int32 pointTop)
	{
		float angle = Angle(edgeIndex, false, pointTop);
		float vertexAnglePrevious = angle - 30;
		float vertexAngleNext = angle + 30;
		if (vertexAnglePrevious < 0)
			vertexAnglePrevious = 330;
		if (vertexAngleNext >= 360)
			vertexAngleNext = 0;
		PointData previousVertex = Vertex(hexCoords, vertexAnglePrevious);
		PointData nextVertex = Vertex(hexCoords, vertexAngleNext);
		return (previousVertex + nextVertex) / 2;
	}

	const float Angle(int32 angleIndex, bool vertex, bool pointTop) {
		if (vertex)
		{
			if (pointTop)
				return angleIndex * 60;
			else ///flat top
				return 30 + (angleIndex * 60);
		}
		else ///edge
		{
			if (pointTop)
				return 30 + (angleIndex * 60);
			else ///flat top
				return angleIndex * 60;
		}

	}

#pragma endregion
}