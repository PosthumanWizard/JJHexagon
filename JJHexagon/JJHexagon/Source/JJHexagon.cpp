#include "JJHexagon.h"

namespace JJHexagon {
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

    inline bool JJHexagon::operator ==(PointData a, PointData b)
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

	inline HexData JJHexagon::Add(HexData a, int32 offsetX, int32 offsetY)
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
		return JJHexagon::Directions[direction];
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
		return Add(hex, directionX, directionY);
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

#pragma endregion */
}