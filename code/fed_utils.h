#ifndef FED_UTILS_H
#define FED_UTILS_H

/**
 * @struct FileDump
 * @brief File dump structure.
 * Contain the size of dump and the file dump.
 * t_FileDump.dump must be free().
 */
typedef struct FileDump {
    int   size;
    char* dump;
} FileDump;

/**
 * @fn FUtils_dumpFile(const char* file_path)
 * @return FileDump struct
 */
FileDump FUtils_dumpFile(const char* file_path);

#endif
