#include <iostream>
#include "open3d/Open3D.h"
#include <math.h>
using namespace open3d;

// Function to apply a transformation to a point cloud
geometry::PointCloud applyTransformation(geometry::PointCloud pcd, const Eigen::Matrix4d &transformation) {
    return pcd.Transform(transformation);
}
 
 
void apply_translation(open3d::geometry::PointCloud& pcd , int tx , int ty , int tz){
    // Define translation matrix
    Eigen::Matrix4d translation = Eigen::Matrix4d::Identity();
    translation(0, 3) = tx; // Translation along x-axis
    translation(1, 3) = ty; // Translation along y-axis
    translation(2, 3) = tz; // Translation along z-axis
    
    // Apply translation to the original point cloud
    open3d::geometry::PointCloud translated_pcd = applyTransformation(pcd, translation);
    
    // Merge original and translated point clouds
    open3d::geometry::PointCloud combined_pcd;
    combined_pcd += pcd;
    combined_pcd += translated_pcd;
    open3d::visualization::Visualizer visualizer;
    std::shared_ptr<open3d::geometry::PointCloud> pcd_pointer = std::make_shared<open3d::geometry::PointCloud>(combined_pcd);
    visualizer.CreateVisualizerWindow("Translation Demo ", 1280, 720);
    visualizer.AddGeometry(pcd_pointer); // Add combined point cloud directly
    visualizer.Run();
    visualizer.DestroyVisualizerWindow();
}


void apply_euclidean(open3d::geometry::PointCloud& pcd , int tx , int ty , int tz, float rx , float ry , float rz){
    //The sequence is z rotation , y rotation , z rotation and translation
    Eigen::Matrix4d translation = Eigen::Matrix4d::Identity();
    translation(0, 3) = tx;  
    translation(1, 3) = ty;  
    translation(2, 3) = tz;  

    Eigen::Matrix4d rotation_x = Eigen::Matrix4d::Identity();
    rotation_x(1, 1) = cos(rx * M_PI/180.);  
    rotation_x(1, 2) = -sin(rx * M_PI/180.);  
    rotation_x(2, 1) = sin(rx * M_PI/180.);   
    rotation_x(2, 2) = cos(rx * M_PI/180.);  

    Eigen::Matrix4d rotation_y = Eigen::Matrix4d::Identity();
    rotation_y(0, 0) = cos(ry * M_PI/180.);  
    rotation_y(0, 2) = sin(ry * M_PI/180.);  
    rotation_y(2, 0) = -sin(ry * M_PI/180.);   
    rotation_y(2, 2) = cos(ry * M_PI/180.);  

    Eigen::Matrix4d rotation_z = Eigen::Matrix4d::Identity();
    rotation_z(0, 0) = cos(rz * M_PI/180.);  
    rotation_z(0, 1) = -sin(rz * M_PI/180.);  
    rotation_z(1, 0) = sin(rz * M_PI/180.);   
    rotation_z(1, 1) = cos(rz * M_PI/180.);

    
    // Apply translation to the original point cloud
    open3d::geometry::PointCloud euclidean_pcd;
    euclidean_pcd = applyTransformation(pcd, rotation_z);
    euclidean_pcd = applyTransformation(euclidean_pcd, rotation_y);
    euclidean_pcd = applyTransformation(euclidean_pcd, rotation_x);
    euclidean_pcd = applyTransformation(euclidean_pcd, translation);
    
    // Merge original and translated point clouds
    open3d::geometry::PointCloud combined_pcd;
    combined_pcd += pcd;
    combined_pcd += euclidean_pcd;
    open3d::visualization::Visualizer visualizer;
    std::shared_ptr<open3d::geometry::PointCloud> pcd_pointer = std::make_shared<open3d::geometry::PointCloud>(combined_pcd);
    visualizer.CreateVisualizerWindow("Euclidean Demo ", 1280, 720);
    visualizer.AddGeometry(pcd_pointer); // Add combined point cloud directly
    visualizer.Run();
    visualizer.DestroyVisualizerWindow();
}


void apply_similarity(open3d::geometry::PointCloud& pcd , int tx , int ty , int tz, float rx , float ry , float rz, float scale){
    // The sequence is scaling, z rotation, y rotation, z rotation, and translation
    
    // Create transformation matrices
    Eigen::Matrix4d scaling = Eigen::Matrix4d::Identity();
    scaling(0, 0) = scale;
    scaling(1, 1) = scale;
    scaling(2, 2) = scale;

    Eigen::Matrix4d translation = Eigen::Matrix4d::Identity();
    translation(0, 3) = tx;  
    translation(1, 3) = ty;  
    translation(2, 3) = tz;  

    Eigen::Matrix4d rotation_x = Eigen::Matrix4d::Identity();
    rotation_x(1, 1) = cos(rx * M_PI/180.);  
    rotation_x(1, 2) = -sin(rx * M_PI/180.);  
    rotation_x(2, 1) = sin(rx * M_PI/180.);   
    rotation_x(2, 2) = cos(rx * M_PI/180.);  

    Eigen::Matrix4d rotation_y = Eigen::Matrix4d::Identity();
    rotation_y(0, 0) = cos(ry * M_PI/180.);  
    rotation_y(0, 2) = sin(ry * M_PI/180.);  
    rotation_y(2, 0) = -sin(ry * M_PI/180.);   
    rotation_y(2, 2) = cos(ry * M_PI/180.);  

    Eigen::Matrix4d rotation_z = Eigen::Matrix4d::Identity();
    rotation_z(0, 0) = cos(rz * M_PI/180.);  
    rotation_z(0, 1) = -sin(rz * M_PI/180.);  
    rotation_z(1, 0) = sin(rz * M_PI/180.);   
    rotation_z(1, 1) = cos(rz * M_PI/180.);

    // Apply transformations to the original point cloud
    open3d::geometry::PointCloud similarity_pcd;
    similarity_pcd = applyTransformation(pcd, rotation_z);
    similarity_pcd = applyTransformation(similarity_pcd, rotation_y);
    similarity_pcd = applyTransformation(similarity_pcd, rotation_x);
    similarity_pcd = applyTransformation(similarity_pcd, scaling);
    similarity_pcd = applyTransformation(similarity_pcd, translation);
    
    // Merge original and transformed point clouds
    open3d::geometry::PointCloud combined_pcd;
    combined_pcd += pcd;
    combined_pcd += similarity_pcd;
    
    // Visualize the combined point cloud
    open3d::visualization::Visualizer visualizer;
    std::shared_ptr<open3d::geometry::PointCloud> pcd_pointer = std::make_shared<open3d::geometry::PointCloud>(combined_pcd);
    visualizer.CreateVisualizerWindow("Similarity Demo", 1280, 720);
    visualizer.AddGeometry(pcd_pointer); // Add combined point cloud directly
    visualizer.Run();
    visualizer.DestroyVisualizerWindow();
}

void apply_affine_transformation(open3d::geometry::PointCloud& pcd, Eigen::Matrix4d& transformation_matrix) {
    // Apply affine transformation to the original point cloud
    open3d::geometry::PointCloud transformed_pcd;
    transformed_pcd = applyTransformation(pcd, transformation_matrix);
    
    // Merge original and transformed point clouds
    open3d::geometry::PointCloud combined_pcd;
    combined_pcd += pcd;
    combined_pcd += transformed_pcd;
    
    // Visualize the combined point cloud
    open3d::visualization::Visualizer visualizer;
    std::shared_ptr<open3d::geometry::PointCloud> pcd_pointer = std::make_shared<open3d::geometry::PointCloud>(combined_pcd);
    visualizer.CreateVisualizerWindow("Affine Transformation Demo", 1280, 720);
    visualizer.AddGeometry(pcd_pointer); // Add combined point cloud directly
    visualizer.Run();
    visualizer.DestroyVisualizerWindow();
}

void apply_projective_transformation(open3d::geometry::PointCloud& pcd, Eigen::Matrix4d& transformation_matrix) {
    // Apply projective transformation to the original point cloud
    open3d::geometry::PointCloud transformed_pcd;
    transformed_pcd = applyTransformation(pcd, transformation_matrix);
    
    // Merge original and transformed point clouds
    open3d::geometry::PointCloud combined_pcd;
    combined_pcd += pcd;
    combined_pcd += transformed_pcd;
    
    // Visualize the combined point cloud
    open3d::visualization::Visualizer visualizer;
    std::shared_ptr<open3d::geometry::PointCloud> pcd_pointer = std::make_shared<open3d::geometry::PointCloud>(combined_pcd);
    visualizer.CreateVisualizerWindow("Projective Transformation Demo", 1280, 720);
    visualizer.AddGeometry(pcd_pointer); // Add combined point cloud directly
    visualizer.Run();
    visualizer.DestroyVisualizerWindow();
}
