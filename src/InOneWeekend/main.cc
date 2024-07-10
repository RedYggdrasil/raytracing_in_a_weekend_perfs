#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
//#include "write_to_file.h"
#include "test_perf_scene.h"

int main() {
    hittable_list world;
    std::vector<std::shared_ptr<material>> materials;
    camera cam;

    Create_test_perf_scene(/*InOut*/world, /*InOut*/materials, /*InOut*/cam);

    cam.render(world);
}
