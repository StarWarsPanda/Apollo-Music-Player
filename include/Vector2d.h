#pragma once

#define MAX_ITERATIONS 10

template <typename T>
class Vector2D
{
public:
    T x;
    T y;

    Vector2D();
    Vector2D(T X, T Y);

    Vector2D<T> operator+(const Vector2D& other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D<T> operator-(const Vector2D& other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D<T> operator*(T scalar) const
    {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D<T> operator/(T scalar) const
    {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D<T>& operator+=(const Vector2D& other)
    {
        *this = *this + other;

        return *this;
    }

    Vector2D<T>& operator-=(const Vector2D& other)
    {
        *this = *this - other;

        return *this;
    }

    Vector2D<T>& operator*=(T scalar)
    {
        *this = *this * scalar;

        return *this;
    }

    Vector2D<T>& operator/=(T scalar)
    {
        *this = *this / scalar;

        return *this;
    }

    bool operator==(const Vector2D& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Vector2D& other) const
    {
        return (x != other.x) || (y != other.y);
    }

    T dot() const;
    T dot(const Vector2D& other) const;
    T magnitude() const;
    Vector2D<T> normalized(T normalValue) const;
private:
    T sqrt(T x);
};

template<typename T>
Vector2D<T>::Vector2D()
{
    x = T(0);
    y = T(0);
}

template<typename T>
Vector2D<T>::Vector2D(T X, T Y)
{
    x = X;
    y = Y;
}

template<typename T>
T Vector2D<T>::dot() const
{
    return x * x + y * y;
}

template<typename T>
T Vector2D<T>::dot(const Vector2D& other) const
{
    return x * other.x + y * other.y;
}

template<typename T>
T Vector2D<T>::magnitude() const
{
    return sqrt(x * x + y * y);
}

template<typename T>
Vector2D<T> Vector2D<T>::normalized(T normalValue) const
{
    Vector2D<T> temp = Vector2D(x, y);

    if (normalValue == ((T)1))
    {
        temp /= temp.magnitude();
    }
    else
    {
        temp = (temp * normalValue) / temp.magnitude();
    }

    return temp;
}

/* Newtonian method */
template<typename T>
T Vector2D<T>::sqrt(T x)
{
    T y = x / ((T)2);

    for (size_t i = 0; i < MAX_ITERATIONS; i++)
    {
        T y_n = (y + (x / y)) / ((T)2);

        if ((((y_n - y) < 0) ? (-(y_n - y)) : (y_n - y)) <= 0)
        {
            return y_n;
        }

        y = y_n;
    }

    return y;
}