#pragma once

#include <vector>

namespace Environment {
    const std::vector<float> SKYBOXVERTICES = {        
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    const std::vector<std::string> SKYBOXCUBEMAP1 = {
        "Resources/Skybox/sky_19_cubemap_2k/px.png",
        "Resources/Skybox/sky_19_cubemap_2k/nx.png",
        "Resources/Skybox/sky_19_cubemap_2k/py.png",
        "Resources/Skybox/sky_19_cubemap_2k/ny.png",
        "Resources/Skybox/sky_19_cubemap_2k/pz.png",
        "Resources/Skybox/sky_19_cubemap_2k/nz.png",
    };

    const std::vector<std::string> SKYBOXCUBEMAP2 = {
        "Resources/Skybox/sky_23_cubemap_2k/px.png",
        "Resources/Skybox/sky_23_cubemap_2k/nx.png",
        "Resources/Skybox/sky_23_cubemap_2k/py.png",
        "Resources/Skybox/sky_23_cubemap_2k/ny.png",
        "Resources/Skybox/sky_23_cubemap_2k/pz.png",
        "Resources/Skybox/sky_23_cubemap_2k/nz.png",
    };

    const std::vector<std::string> SKYBOXCUBEMAP3 = {
        "Resources/Skybox/sky_42_cubemap_2k/px.png",
        "Resources/Skybox/sky_42_cubemap_2k/nx.png",
        "Resources/Skybox/sky_42_cubemap_2k/py.png",
        "Resources/Skybox/sky_42_cubemap_2k/ny.png",
        "Resources/Skybox/sky_42_cubemap_2k/pz.png",
        "Resources/Skybox/sky_42_cubemap_2k/nz.png",
    };

    const std::vector<std::string> SKYBOXCUBEMAP4 = {
        "Resources/Skybox/sky_17_cubemap_2k/px.png",
        "Resources/Skybox/sky_17_cubemap_2k/nx.png",
        "Resources/Skybox/sky_17_cubemap_2k/py.png",
        "Resources/Skybox/sky_17_cubemap_2k/ny.png",
        "Resources/Skybox/sky_17_cubemap_2k/pz.png",
        "Resources/Skybox/sky_17_cubemap_2k/nz.png",
    };
}