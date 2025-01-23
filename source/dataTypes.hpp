
#ifndef U1180779_DATA_TYPES_H
#define U1180779_DATA_TYPES_H

struct vec4 
{
    vec4() { }
    vec4(float x, float y, float z, float w) 
        : x(x), y(y), z(z), w(w) { }
    
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    /* vec4 op vec4 */
    
    inline vec4 operator+(const vec4& o) const
    {
        return vec4(x + o.x, y + o.y, z + o.z, w + o.w);
    }

    inline vec4 operator-(const vec4& o) const
    {
        return vec4(x - o.x, y - o.y, z - o.z, w - o.w);
    }

    inline vec4 operator*(const vec4& o) const
    {
        return vec4(x * o.x, y * o.y, z * o.z, w * o.w);
    }

    inline vec4 operator/(const vec4& o) const
    {
        return vec4(x / o.x, y / o.y, z / o.z, w / o.w);
    }

    /* vec4 op */

    inline vec4 operator+(float f) const
    {
        return vec4(x + f, y + f, z + f, w + f);
    }

    inline vec4 operator-(float f) const
    {
        return vec4(x - f, y - f, z - f, w - f);
    }

    inline vec4 operator*(float f) const
    {
        return vec4(x * f, y * f, z * f, w * f);
    }

    inline vec4 operator/(float f) const
    {
        return vec4(x / f, y / f, z / f, w / f);
    }
};



#endif