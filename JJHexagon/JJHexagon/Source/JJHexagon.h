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
		HexData(int32 newX, int32 newY) : x(newX), y(newY) {}
		inline const PointData Coords() { return PointData(x, y); };
		inline const int32 X() { return x; };
		inline const int32 Y() { return y; };
		inline const int32 Z() { return -x - y; };
	};

	const std::vector<HexData> Directions = {
		HexData(1, 0), HexData(1, -1), HexData(0, -1),
		HexData(-1, 0), HexData(-1, 1), HexData(0, 1)
	};

#pragma region PointData Operations

	inline PointData operator +(PointData a, PointData b);

	inline PointData operator -(PointData a, PointData b);

	inline PointData operator *(PointData a, PointData b);

	inline PointData operator /(PointData a, PointData b);

	inline PointData operator /(PointData a, float b);

	inline bool operator ==(PointData a, PointData b);

	inline bool operator !=(PointData a, PointData b);

#pragma endregion

#pragma region HexData Operations

	inline bool operator ==(HexData a, HexData b);

	inline bool operator !=(HexData a, HexData b);

	inline HexData operator +(HexData a, HexData b);

	inline HexData operator -(HexData a, HexData b);

	inline HexData operator *(HexData a, HexData b);

	inline HexData operator /(HexData a, HexData b);

	inline HexData Add(HexData a, int32 offsetX, int32 offsetY);

	inline HexData Subtract(HexData a, int32 offsetX, int32 offsetY);

	inline HexData Multiply(HexData a, int32 offsetX, int32 offsetY);

	inline HexData Divide(HexData a, int32 offsetX, int32 offsetY);

		///Direction should be 0 to 5
	inline struct HexData Direction(int direction);

	inline HexData Neighbour(HexData hex, HexData direction);

	inline HexData Neighbour(HexData hex, int direction);

	inline HexData Neighbour(HexData hex, int directionX, int directionY);

	inline int32 Distance(HexData a, HexData b);

	inline PointData Position(HexData hex);

	const PointData Vertex(PointData hexCoords, int32 vertexIndex, int32 pointTop);

	const PointData Vertex(PointData hexCoords, float angle);

	const PointData Edge(PointData hexCoords, int32 edgeIndex, int32 pointTop);

	const float Angle(int32 angleIndex, bool vertex, bool pointTop);

#pragma endregion
}
