#ifndef __COLLISIONRECTANGLE_H__
#define __COLLISIONRECTANGLE_H__
/*******************************************************************************
 *  CollisionRectangle                                                         *
 *  Fri Feb 21 CET 2014                                                        *
 *  Copyright Eduardo San Martin Morote                                        *
 *  i@posva.net                                                                *
 *  http://posva.net                                                           *
 ******************************************************************************/

#include <glm/vec2.hpp>

/*
 * The tab of the vec2 represent the rectangle this way
 * 0----1
 * |    |
 * |    |
 * 3----2
 */

class CollisionRectangle {
    glm::vec2 m_vx[4]; ///< Rectangles vertexes
    glm::vec2 m_axis[2]; ///< Rectangle axis
    glm::vec2 m_projection[2]; ///<myself projection on each axis
    glm::vec2 m_origin; /// Rectangle Center, used for rotations

    /**
     * Compute the axis of the rectangle.
     * This function should be called when the rectangle is rotated.
     */
    void computeAxis();

    public:
        CollisionRectangle();
        CollisionRectangle(const glm::vec2 &p, const glm::vec2 &size);

        inline glm::vec2 getVertex(int i) const { return m_vx[i]; }
        inline glm::vec2 getOrigin() const { return m_origin; }

        inline void setOrigin(const glm::vec2 origin) { m_origin = origin; }

        glm::vec2 projectOnAxis(const glm::vec2& axis) const;

        bool checkCollision(const CollisionRectangle& other, bool check_other = true) const;

        void move(const glm::vec2 &v);
        void setPosition(const glm::vec2 &p);

        void rotate(float r);
};

#endif

