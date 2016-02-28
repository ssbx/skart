#ifndef FED_UTILS_H
#define FED_UTILS_H

/**
 * @struct FileDump
 * @brief File dump structure.
 * Contain the size of dump and the file dump.
 */
struct t_FileDump {
    int   size;
    char* dump;
};

/**
 * @fn FUtils_dumpFile(const char* file_path)
 * @return FileDump struct
 */
struct t_FileDump FUtils_dumpFile(const char* file_path);

#endif
