#include "func.h"

int main(int argc ,char* argv[]){
    if(argc < 2){
        std::cerr << "Provide valid video path" << std::endl;
    }
    run_lane_detection(argv[1]);    
    return 0;
}