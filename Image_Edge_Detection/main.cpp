#include "func.h"

int main(int argc ,char* argv[]){
    if(argc < 2){
        std::cerr << "Provide valid video path" << std::endl;
    }
    
    run_edge_detection(argv[1] , argv[2]);    
    return 0;
}