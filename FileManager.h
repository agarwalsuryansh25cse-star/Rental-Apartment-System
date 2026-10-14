#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class PropertySystem;

class FileManager {
public:
    static void save(const PropertySystem& system);
    static void load(PropertySystem& system);
};

#endif
