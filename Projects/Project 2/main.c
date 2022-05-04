#include "pagingSystem.h"

int main() {
    newInputFile(); // create a new input file with 100 total page references

    //int alg = getAlgChoice(); // get algorithm choice from user input
    int frames = getNumFrames(); // get number of page frames from user input
    int references[100]; // create array to store file contents

    getRefs(references, "PerezA_proj2_input.txt"); // store references from file in an array
    FILE *out;
    
    if(frames == 4)
    {
        out = freopen("PerezA_proj2_output_4_frames.txt", "w", stdout);
    }
    else if(frames == 8)
    {
        out = freopen("PerezA_proj2_output_8_frames.txt", "w", stdout);
    }
    FIFO(frames, references);
    LRU(frames, references);
    secondChance(frames, references);
    
    // Execution of chosen paging-algorithm
    /*if(alg == 1)
    {
        FIFO(frames, references);
    }
    else if(alg == 2)
    {
        LRU(frames, references);
    }
    else if(alg == 3)
    {
        secondChance(frames, references);
    }*/
    fclose(out);
    return EXIT_SUCCESS;
}
