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
    float m_rotation;

    /**
     * Compute the axis of the rectangle.
     * This function should be called when the rectangle is rotated.
     */
    void computeAxis();

    public:
        CollisionRectangle();
        CollisionRectangle(const glm::vec2 &p, const glm::vec2 &size);

        /**
         * Get a specific vertex of the rectangle in global coordinates
         *
         * @param i index of the vertex < 4
         * @return copy of the vec2
         */
        inline glm::vec2 getVertex(int i) const { return m_vx[i]; }

        /**
         * Get the Origin of the rectangle in local coordinates
         *
         * @return copy of the origin as a vec2
         */
        inline glm::vec2 getOrigin() const { return m_origin; }

        /**
         * Change the origin
         * This should be called after creating the rectangles as it is easier
         * to calculate when the rectangle is axis aligned
         *
         * @param origin vec2 regarding the first vertex of the rectangle (Top Left)
         */
        inline void setOrigin(const glm::vec2 origin) { m_origin = origin; }

        /**
         * Project myself in an axis and return the projection
         * containing the min and the max value of the projection
         *
         * @param axis axis where to project
         * @return vec2 x = min, y = max
         */
        glm::vec2 projectOnAxis(const glm::vec2& axis) const;

        /**
         * Check a collision with another CollisionRectangle
         *
         * @param check_other this is mostly used internally for the second call: other.checkCollision(*this, false)
         * @return true if there is a collisison false otherwise
         */
        bool checkCollision(const CollisionRectangle& other, bool check_other = true) const;

        /**
         * Move the rectangle
         *
         * @param v vec2 representing the translation
         */
        void move(const glm::vec2 &v);

        /**
         * Change the position of the Rectangle based on the Origin
         *
         * @param p new position
         */
        void setPosition(const glm::vec2 &p);

        /**
         * Rotate the rectangle around its origin
         *
         * @param r relative rotation in radians
         */
        void rotate(float r);

        /**
         * Change the rectangle's rotation around its origin
         *
         * @param r new rotation in radians
         */
        void setRotation(float r);
};

#endif

