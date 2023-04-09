#include "types.h"
#include "user.h"
#include "fcntl.h"

int mean(int nums[], int max){
    int sum = 0;
    for(int i = 0; i < max; i++){
        sum += nums[i];
    }
    return sum / max;
}

int median(int nums[], int max){
    int median;
    if(max % 2 == 0){
        median = (nums[max/2] + nums[max/2 - 1]) / 2;
    }
    else{
        median = nums[max/2];
    }
    return median;
}

int mode(int numbers[], int max){
        int i;
        int j;
        int count = 0;
        int maxCount = 0;
        int mode = numbers[0];
        for(i = 0; i < max; i++){
            for(j = 0; j < max; j++){
                if(numbers[j] == numbers[i]){
                    count++;
                }
            }
            if(count > maxCount){
                maxCount = count;
                mode = numbers[i];
            }
            count = 0;
        }
        return mode;
    }

int main(int argc, char *argv[]){
    int numbers[7];
    int i;
    int max = argc - 1;
    if(max > 7){
        printf(1, "Error: Too many numbers!");
        return 1;
    }
    for(i = 0; i < max; i++){
        numbers[i] = atoi(argv[i+1]);
    }
    
    //sort numbers
    int j;
    for(i = 0; i < max; i++){
        for(j = 0; j < max - 1; j++){
            if(numbers[j] > numbers[j+1]){
                int temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }


    unlink("mmm_result.txt");
    int fd = open("mmm_result.txt", O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf(1, "mmm_result: cannot create mmm_result.txt\n");
        exit();
    }
    printf(fd, "%d %d %d", mean(numbers, max), median(numbers, max), mode(numbers, max));
    write(fd, "\n", 1);
    close(fd);

    exit();
    }
