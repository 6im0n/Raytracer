/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory
*/

#pragma once

#include <memory>
#include <stdexcept>
#include "IShape.hpp"
#include "Shapes/Sphere.hpp"
#include "Shapes/Cone.hpp"
#include "Shapes/Prism.hpp"
#include "Shapes/Torus.hpp"
#include "Shapes/Cube.hpp"
#include "Shapes/Plane.hpp"
#include "Shapes/Obj.hpp"
#include "Shapes/Cylinder.hpp"
#include "Raytracer/Background.hpp"
#include "Raytracer/Light.hpp"
#include "Raytracer/Camera.hpp"
#include "IMaterial.hpp"
#include "DataRetriever/Parsing.hpp"

/**
 * @brief Factory class for creating shshared_ptrapes, cameras, lights, and backgrounds for a ray tracer scene.
 */
namespace Core {
    class SceneFactory {
    public:

        /**
         * @brief Default constructor.
         */
        SceneFactory();

        /**
         * @brief Destructor.
         */
        ~SceneFactory() = default;

        /**
         * @brief Creates a primitive shape.
         * @tparam Args - Type of arguments for creating the shape.
         * @param type - Type of primitive shape to create.
         * @param arg - Arguments for creating the shape.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created shape.
         */
        std::shared_ptr<IShape> createPrimitive(ParsingShape args);

        /**
         * @brief Creates a camera.
         * @return std::unique_ptr<RayTracer::Camera> - Pointer to the created camera.
         */
        static std::shared_ptr<RayTracer::Camera> createCamera(ParsingCamera camera);

        /**
         * @brief Creates a background.
         * @return std::unique_ptr<RayTracer::Background> - Pointer to the created background.
         */
        static std::unique_ptr<RayTracer::Background> createBackground(ParsingBackground &background);

        /**
         * @brief Creates a light.
         * @return std::unique_ptr<RayTracer::Light> - Pointer to the created light.
         */
        static std::unique_ptr<RayTracer::Light> createLight(ParsingLight &light);

        /**
         * @brief Creates a sphere shape.
         * @param sphere - Parsing data for creating the sphere.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created sphere shape.
         */
        std::unique_ptr<RayTracer::IShape> makeSphere(ParsingShape &sphere);

        /**
         * @brief Creates a plane shape.
         * @param plane - Parsing data for creating the plane.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created plane shape.
         */
        std::unique_ptr<RayTracer::IShape> makePlane(ParsingShape &plane);

        /**
         * @brief Creates a cone shape.
         * @param cone - Parsing data for creating the cone.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created cone shape.
         */
        std::unique_ptr<RayTracer::IShape> makeCone(ParsingShape &cone);

        /**
         * @brief Creates a cube shape.
         * @param cube - Parsing data for creating the cube.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created cube shape.
         */
        std::unique_ptr<RayTracer::IShape> makeCube(ParsingShape &cube);

        /**
         * @brief Creates a cylinder shape.
         * @param cylinder - Parsing data for creating the cylinder.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created cylinder shape.
         */
        std::unique_ptr<RayTracer::IShape> makeCylinder(ParsingShape &cylinder);

        /**
         * @brief Creates a torus shape.
         * @param torus - Parsing data for creating the torus.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created torus shape.
         */
        std::unique_ptr<RayTracer::IShape> makeTorus(ParsingShape &torus);

        /**
         * @brief Creates a prism shape.
         * @param prism - Parsing data for creating the prism.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created prism shape.
         */
        std::unique_ptr<RayTracer::IShape> makePrism(ParsingShape &prism);

        /**
         * @brief Creates an OBJ shape.
         * @param obj - Parsing data for creating the OBJ.
         * @return std::unique_ptr<RayTracer::IShape> - Pointer to the created OBJ shape.
         */
        std::unique_ptr<RayTracer::IShape> makeObj(ParsingShape &obj);
    };
}