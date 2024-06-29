#include "func.h" 


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Provide valid point cloud path" << std::endl;
        return 1;
    }
    // Read point cloud from file
    auto pcd = open3d::io::CreatePointCloudFromFile(argv[1]);
    apply_translation(*pcd,5,5,5);
    apply_euclidean(*pcd , 5,5,5,90,0,0);
    apply_similarity(*pcd , 5,5,5,90,0,0,2);

    Eigen::Matrix4d affine = Eigen::Matrix4d::Identity();
    affine(0, 2) = 2; 
    affine(0,3) = 5;
    affine(1,3) = 5;

    Eigen::Matrix4d projective = Eigen::Matrix4d::Identity();
    projective(0,3) = 5;
    projective(1,3) = 5;
    projective(3,2) = 0.05;
    projective(3,1) = 0.1;

    apply_affine_transformation(*pcd,affine);
    apply_projective_transformation(*pcd , projective);

    return 0;
}

