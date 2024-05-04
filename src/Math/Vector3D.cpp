/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-bsraytracer-florent.charpentier
** File description:
** Vector3D
*/


#include <ostream>
#include <complex>
#include "Vector3D.hpp"

namespace Math {
    Vector3D::Vector3D() : x(0), y(0), z(0) {}

    Vector3D::Vector3D(double a, double b, double c) : x(a), y(b), z(c) {}

    double Vector3D::sqLength() const noexcept {
        return x * x + y * y + z * z;
    }

    double Vector3D::length() const noexcept {
        return std::sqrt(sqLength());
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const noexcept {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D &Vector3D::operator+=(const Vector3D &other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const noexcept {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D &Vector3D::operator-=(const Vector3D &other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(const Vector3D &other) const noexcept {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }

    Vector3D &Vector3D::operator*=(const Vector3D &other) noexcept {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D &other) const noexcept {
        return Vector3D(x / other.x, y / other.y, z / other.z);
    }

    Vector3D &Vector3D::operator/=(const Vector3D &other) noexcept {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(double scale) const noexcept {
        return Vector3D(x * scale, y * scale, z * scale);
    }

    Vector3D &Vector3D::operator*=(double scale) noexcept {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3D Vector3D::operator/(double invScale) const
    {
        return Vector3D(x / invScale, y / invScale, z / invScale);
    }

    Vector3D &Vector3D::operator/=(double invScale)
     {
        x /= invScale;
        y /= invScale;
        z /= invScale;
        return *this;
    }

    Vector3D Vector3D::operator-() const noexcept
    {
        return Vector3D(-x, -y, -z);
    }

    double Vector3D::dot(const Vector3D &other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z;
    }

    double Vector3D::square() const noexcept {
        return x * x + y * y + z * z;
    }

    void Vector3D::makeUnitVector()
    {
        double len = length();
        x /= len;
        y /= len;
        z /= len;
    }

    Vector3D Vector3D::getUnitVector()
    {
        double len = length();
        return Vector3D(x / len, y / len, z / len);

    }

    Vector3D reflect(const Vector3D &v, const Vector3D &n)
    {
        return v - n * 2 * v.dot(n);
    }

    void Vector3D::output(std::ostream &os) const noexcept
    {
        os << "Vector3D(" << x << ", " << y << ", " << z << ")";
    }
}