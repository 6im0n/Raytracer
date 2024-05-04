/*
** EPITECH PROJECT, 2024
** ClusterManagement.cpp
** File description:
** DESCRIPTION
*/

#include "ClusterManagement.hpp"
#include "Graphical/Sdl2.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Ray3D.hpp"
#include "Raytracer/Camera.hpp"
#include "Shapes/ShapeList.hpp"
#include "Shapes/Material.hpp"
#include <algorithm>

App::Cluster::Cluster(unsigned int startY, unsigned int endY, int cluster_id)
    : id(cluster_id)
{
    _axesY = std::make_pair(startY, endY);
}


/*----------------------------------------------*/

App::ClusterManagement::ClusterManagement(int width, int height)
{
    int clusterStartY = 0;
    _sample = 30;
    _nbThreads = std::thread::hardware_concurrency();
    _windowWidth = width;
    _windowHeight = height;
    _config = std::vector<std::pair<std::pair<unsigned int, unsigned int>, std::string>>();
    int cluster_id = 0;
    for (unsigned int i = 0; i < _nbThreads; i++) {
        int clusterEndY = height / _nbThreads * (i + 1);
        _clusters.push_back(std::make_shared<Cluster>(clusterStartY, clusterEndY, cluster_id));
        clusterStartY = clusterEndY;
        cluster_id++;
    }
}

App::ClusterManagement::~ClusterManagement()
{
    for (auto &cluster : _clusters)
        if (cluster->thread.joinable())
            cluster->thread.join();
    _clusters.clear();
}

static Math::Vector3D color(const Math::Ray3D &ray, RayTracer::IShape *scene, int depth)
{
    RayTracer::hits  hit;
    if (scene->hit(ray, 0.001, 10000.0, hit))
    {
        Math::Ray3D scattered;
        Math::Vector3D attenuation;
        if (depth < 50 && hit.material->scatter(ray, hit, attenuation, scattered))
        {
            return attenuation * color(scattered, scene, depth + 1);
        } else {
            return Math::Vector3D(0, 0, 0);
        }
    } else {
        Math::Vector3D unitDirection = ray.getDirection().getUnitVector();
        float t = 0.5 * (unitDirection.y + 1.0);
        return Math::Vector3D(1.0, 1.0, 1.0) * (1.0 - t) + Math::Vector3D(0.5, 0.7, 1.0) * t;
    }
}

thread_local int threadId = 0;

void App::ClusterManagement::render(std::pair<unsigned int, unsigned int> _axesY, int width, int height, int samples, std::shared_ptr<RayTracer::ShapeList> scene, std::shared_ptr<RayTracer::Camera> camera, int x)
{
    for (unsigned int y = _axesY.first; y < _axesY.second; y++) {
        Math::Vector3D col(0, 0, 0);
        for (int s = 0; s < samples; s++) {
            float u = float(x + drand48()) / float(width);
            float v = float(y + drand48()) / float(height);
            Math::Ray3D ray = camera->getRay(u, v);
            Math::Vector3D p = ray.pointOnRay(2.0);
            col += color(ray, scene.get(), 0);
        }
        col /= float(samples);
        col = Math::Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
        unsigned char r = (unsigned char) (255.99 * col.x);
        unsigned char g = (unsigned char) (255.99 * col.y);
        unsigned char b = (unsigned char) (255.99 * col.z);
        mtx.lock();
        std::string rgb = std::to_string((int)r) + " " + std::to_string((int)g) + " " + std::to_string((int)b);
        std::pair<unsigned int, unsigned int> coord = std::make_pair(x, y);
        _config.push_back(std::make_pair(coord, rgb));
        mtx.unlock();
    }
    threadId++;
}

void App::ClusterManagement::executeRendering(std::shared_ptr<RayTracer::ShapeList> scene, std::shared_ptr<RayTracer::Camera> camera)
{
    for (unsigned int i = 0; i < _windowWidth ; i++) {
        for (size_t j = 0; j < _clusters.size(); ++j) {
            auto cluster = _clusters[j];
            cluster->thread = std::thread(&App::ClusterManagement::render, this, cluster->getAxesY(), _windowWidth, _windowHeight, _sample, scene, camera, i);
        }
        for (auto &cluster: _clusters)
            if (cluster->thread.joinable())
                cluster->thread.join();
    }
}

void App::ClusterManagement::sortConfig()
{
    std::sort(_config.begin(), _config.end(), [](const std::pair<std::pair<unsigned int, unsigned int>, std::string> &a, const std::pair<std::pair<unsigned int, unsigned int>, std::string> &b) {
        if (a.first.second == b.first.second)
            return a.first.first > b.first.first;
        else
            return a.first.second > b.first.second;
    });
}