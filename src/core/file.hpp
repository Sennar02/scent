#ifndef GR_CORE_FILE_HPP
#define GR_CORE_FILE_HPP

#include <core/types.hpp>
#include <core/writer.hpp>

namespace gr
{
    enum File_Mode {
        FILE_MODE_NONE   = 0,
        FILE_MODE_READ   = 1,
        FILE_MODE_CREATE = 2,
        FILE_MODE_APPEND = 3,

        FILE_MODE_COUNT = FILE_MODE_APPEND,
    };

    enum File_Error {
        FILE_ERROR_NONE   = 0,
        FILE_ERROR_SYSTEM = 1,

        FILE_ERROR_COUNT = FILE_ERROR_SYSTEM,
    };

    struct File {
        //
        //
        //
        Str8 name;

        //
        //
        //
        usize descr = 0;

        //
        //
        //
        isize error = 0;

        //
        //
        //
        isize syst_error = 0;
    };

    //
    //
    //
    File
    file_find(Str8 name);

    //
    //
    //
    File
    file_create(Str8 name);

    //
    //
    //
    File
    file_update(Str8 name);

    //
    //
    //
    File
    file_close(File* file);

    //
    //
    //
    File
    file_delete(File* file);

    //
    //
    //
    File
    file_rename(File* file, Str8 name);

    /*
    //
    //
    //
    Writer
    file_writer(File* file, Str8 name, File_Mode mode);
    */
} // namespace gr

#endif // GR_CORE_FILE_HPP
