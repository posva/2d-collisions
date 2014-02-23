#include "CollisionRectangle.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>
#include <iostream>

CollisionRectangle::CollisionRectangle() : m_origin(0.f, 0.f), m_rotation(0.f)
{
    m_vx[0].x = 0.f;
    m_vx[0].y = 0.f;

    m_vx[1].x = 1.f;
    m_vx[1].y = 0.f;

    m_vx[2].x = 1.f;
    m_vx[2].y = 1.f;

    m_vx[3].x = 0.f;
    m_vx[3].y = 1.f;

    computeAxis();
}

CollisionRectangle::CollisionRectangle(const glm::vec2 &p, const glm::vec2 &size): m_origin(0.f, 0.f)
{
    for (int i = 0; i < 4; i++)
        m_vx[i] = p;

    m_vx[1].x += size.x;

    m_vx[2] += size;

    m_vx[3].y += size.y;

    computeAxis();
}

void CollisionRectangle::computeAxis()
{
    m_axis[0] = glm::normalize(m_vx[1] - m_vx[0]);
    m_axis[1] = glm::normalize(m_vx[1] - m_vx[2]);

    m_projection[0] = projectOnAxis(m_axis[0]);
    m_projection[1] = projectOnAxis(m_axis[1]);
}

glm::vec2 CollisionRectangle::projectOnAxis(const glm::vec2& axis) const
{
    //float axis_len = axis.x*axis.x + axis.y*axis.y, dot;
    float tmp;
    glm::vec2 mm(INFINITY, -INFINITY);
    for (int i = 0; i < 4; i++) {
        tmp = glm::dot(axis, m_vx[i]);
        //tmp = glm::dot((dot/axis_len)*axis, axis);
        if (tmp > mm.y) mm.y = tmp;
        if (tmp < mm.x) mm.x = tmp;
    }
    return mm;
}

bool CollisionRectangle::checkCollision(const CollisionRectangle& other, bool check_other) const
{
    glm::vec2 v;

    v = other.projectOnAxis(m_axis[0]);
    if (v.x > m_projection[0].y || v.y < m_projection[0].x)
        return false;

    v = other.projectOnAxis(m_axis[1]);
    if (v.x > m_projection[1].y || v.y < m_projection[1].x)
        return false;

    return check_other?other.checkCollision(*this, false):true;
}

void CollisionRectangle::move(const glm::vec2 &v)
{
    // TODO
    for (int i = 0; i <4; i++)
        m_vx[i] += v;

    m_projection[0] = projectOnAxis(m_axis[0]);
    m_projection[1] = projectOnAxis(m_axis[1]);
}

void CollisionRectangle::setPosition(const glm::vec2 &v)
{
    glm::vec2 tmp(m_origin+m_vx[0]);
    for (int i = 0; i <4; i++)
        m_vx[i] = m_vx[i]-tmp+v;

    m_projection[0] = projectOnAxis(m_axis[0]);
    m_projection[1] = projectOnAxis(m_axis[1]);
}

void CollisionRectangle::rotate(float r)
{
    glm::vec2 old = m_vx[0];
    for (int i = 0; i < 4; i++)
        m_vx[i] = glm::rotate(m_vx[i]-(m_origin+old), r) + m_origin+old;
    m_origin += old - m_vx[0];

    m_rotation += r;

    computeAxis();
}

void CollisionRectangle::setRotation(float r)
{
    rotate(r-m_rotation);
}
