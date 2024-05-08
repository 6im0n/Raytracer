/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory
*/

#include "Factory.hpp"

Core::SceneFactory::SceneFactory() {}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::createPrimitive(App::ParsingShape args)
{
    using CreateFunc = std::function<std::shared_ptr<RayTracer::IShape>(App::ParsingShape&)>;

    static const std::vector<std::pair<std::string, CreateFunc>> functionMap = {
        {"sphere", [this](App::ParsingShape& shapeArgs) {
            return makeSphere(shapeArgs); 
        }},
        {"cone", [this](App::ParsingShape& shapeArgs) {
            return makeCone(shapeArgs); 
        }},
        {"cube", [this](App::ParsingShape& shapeArgs) {
            return makeCube(shapeArgs); 
        }},
        {"cylinder", [this](App::ParsingShape& shapeArgs) {
            return makeCylinder(shapeArgs); 
        }},
        {"torus", [this](App::ParsingShape& shapeArgs) {
            return makeTorus(shapeArgs); 
        }},
        {"prism", [this](App::ParsingShape& shapeArgs) {
            return makePrism(shapeArgs); 
        }},
        {"plane", [this](App::ParsingShape& shapeArgs) {
            return makePlane(shapeArgs); 
        }}
    };

    std::string shapeType = args.getType();
    std::transform(shapeType.begin(), shapeType.end(), shapeType.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    for (const auto& pair : functionMap) {
        if (pair.first == shapeType) {
            return pair.second(args);
        }
    }

    throw std::runtime_error("Invalid primitive type");
}

std::shared_ptr<RayTracer::Camera> Core::SceneFactory::createCamera(App::ParsingCamera camera)
{
    Math::Vector3D viewFrom = camera.getViewFrom();
    Math::Vector3D viewAt = camera.getViewAt();
    Math::Vector3D viewUp = camera.getViewUp();
    double fov = static_cast<double>(camera.getFov());
    std::pair<int, int> res = camera.getResolution();
    double resolution = static_cast<double>(res.first) / res.second;
    double aperture = static_cast<double>(camera.getAperture());
    double focusDist = static_cast<double>(camera.getFocusDist());

    return std::make_shared<RayTracer::Camera>(viewFrom, viewAt, viewUp, fov, resolution, aperture, focusDist);
}

std::shared_ptr<RayTracer::Background> Core::SceneFactory::createBackground(App::ParsingBackground &background)
{
    Math::Vector3D color = background.getColor();
    std::string texture = background.getPath();

    (void)color;
    (void)texture;
    return std::make_shared<RayTracer::Background>();
}

std::shared_ptr<RayTracer::Light> Core::SceneFactory::createLight(App::ParsingLight &light)
{

    Math::Vector3D position = light.getPosition();
    Math::Vector3D color = light.getColor();
    float intensity = light.getIntensity();
    Math::Vector3D direction =  light.getDirection();
    std::string type = light.getType();

    (void)position;
    (void)color;
    (void)intensity;
    (void)direction;
    (void)type;
    return std::make_shared<RayTracer::Light>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeSphere(App::ParsingShape &sphere)
{
    Math::Vector3D center = sphere.getPosition();
    Math::Vector3D size = sphere.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    return std::make_shared<RayTracer::Sphere>(center, radius, material);
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeObj(App::ParsingShape &obj)
{
    Math::Vector3D center = obj.getPosition();
    Math::Vector3D size = obj.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Obj>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makePlane(App::ParsingShape &plane)
{
    Math::Vector3D center = plane.getPosition();
    Math::Vector3D size = plane.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Plane>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeCone(App::ParsingShape &cone)
{
    Math::Vector3D center = cone.getPosition();
    Math::Vector3D size = cone.getSize();
    float radius = size.x;
    float height = size.y;
    RayTracer::IMaterial *material = nullptr;

    return std::make_shared<RayTracer::Cone>(center, radius, height, material);
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeCube(App::ParsingShape &cube)
{
    Math::Vector3D center = cube.getPosition();
    Math::Vector3D size = cube.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Cube>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeCylinder(App::ParsingShape &cylinder)
{
    Math::Vector3D center = cylinder.getPosition();
    Math::Vector3D size = cylinder.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Cylinder>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makeTorus(App::ParsingShape &torus)
{
    Math::Vector3D center = torus.getPosition();
    Math::Vector3D size = torus.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Torus>();
}

std::shared_ptr<RayTracer::IShape> Core::SceneFactory::makePrism(App::ParsingShape &prism)
{
    Math::Vector3D center = prism.getPosition();
    Math::Vector3D size = prism.getSize();
    float radius = size.x;
    RayTracer::IMaterial *material = nullptr;

    (void)center;
    (void)radius;
    (void)material;
    return std::make_shared<RayTracer::Prism>();
}
