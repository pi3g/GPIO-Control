#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_ROOT "/sys/class/gpio"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/export"

#define LOW 0
#define HIGH 1

int export_pin(int num) {
    FILE* export = fopen(EXPORT, "w");
    if (export == NULL) {
        printf("Failed to open the export file\n");
        exit(-1);
    }
    fprintf(export, "%d", num);
    fclose(export);
    return 0;
}

int unexport_pin(int num) {
    FILE* unexport = fopen(UNEXPORT, "w");
    if (unexport == NULL) {
        printf("Failed to open the unexport file\n");
        exit(-1);
    }
    fprintf(unexport, "%d", num);
    fclose(unexport);
    return 0;
}

int set_direction(char *mode, int num) {
    char direction_file_path[1024];
    snprintf(direction_file_path, sizeof(direction_file_path), "/sys/class/gpio/gpio%d/direction", num);
    FILE* direction = fopen(direction_file_path, "w");
    if (direction == NULL) {
        printf("Failed to open the direction file\n");
        exit(-1);
    }
    fputs(mode, direction);
    fclose(direction);
    return 0;
}

int set_value(int val, int num) {
    char value_file_path[1024];
    snprintf(value_file_path, sizeof(value_file_path), "/sys/class/gpio/gpio%d/value", num);
    FILE* value = fopen(value_file_path, "w");
    if (value == NULL) {
        printf("Failed to open the value file\n");
        exit(-1);
    }
    fprintf(value, "%d", val);
    fclose(value);
    return 0;
}

int main() {

    int rslt;
    int num;
    int num_blinks;

    num = 13;
    num_blinks = 5;

    rslt = export_pin(num);
    sleep(1);
    rslt = set_direction("out", num);
    for (int i = 0; i < num_blinks; i++) {
        rslt = set_value(HIGH, num);
        sleep(1);
        rslt = set_value(LOW, num);
        sleep(1);
    }

    rslt = set_value(LOW, num);
    rslt = set_direction("in", num);
    rslt = unexport_pin(num);

    return EXIT_SUCCESS;
}