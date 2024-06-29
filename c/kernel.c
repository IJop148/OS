void kernel_main () {
    // Set the video_memory pointer to the start of the video memory address (0xb8000)
    char* video_memory = (char*) 0xb8000;

    // Write the character 'X' to the video memory
    *video_memory = 'X';
}
