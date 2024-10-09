#include <stdio.h>
#include <errno.h>

#include <core/file.hpp>
#include <core/array.hpp>

namespace gr
{
    using File_Open_Func = File (Str8 name);

    static const Array<File_Open_Func*> FILE_OPEN_FUNC_ARRAY = (File_Open_Func*[]) {
        &file_find, &file_create, &file_update
    };

    File
    file_find(Str8 name)
    {
        File  self;
        usize descr = (usize) fopen(name.data, "rb");

        if ( descr == 0 ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;

            return self;
        }

        self.descr = descr;
        self.name  = name;

        setbuf((FILE*) self.descr, 0);

        return self;
    }

    File
    file_create(Str8 name)
    {
        File  self;
        usize descr = (usize) fopen(name.data, "wb");

        if ( descr == 0 ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;

            return self;
        }

        self.descr = descr;
        self.name  = name;

        setbuf((FILE*) self.descr, 0);

        return self;
    }

    File
    file_update(Str8 name)
    {
        File  self;
        usize descr = (usize) fopen(name.data, "ab");

        if ( descr == 0 ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;

            return self;
        }

        self.descr = descr;
        self.name  = name;

        setbuf((FILE*) self.descr, 0);

        return self;
    }

    File
    file_close(File* file)
    {
        gr_exec_expect(file != 0, "The file must exist");

        auto& self = *file;

        if ( self.descr != 0 ) {
            isize resl = fclose((FILE*) self.descr);

            gr_exec_expect(resl == 0,
                "The operation must succeed");
        }

        self.descr      = 0;
        self.error      = FILE_ERROR_NONE;
        self.syst_error = 0;

        return self;
    }

    File
    file_delete(File* file)
    {
        gr_exec_expect(file != 0, "The file must exist");

        auto& self = *file;

        if ( self.descr == 0 ) return self;

        isize resl = remove(self.name.data);

        if ( resl != 0 ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;
        }

        return self;
    }

    File
    file_rename(File* file, Str8 name)
    {
        gr_exec_expect(file != 0, "The file must exist");

        auto& self = *file;

        if ( self.descr == 0 ) return self;

        isize resl = rename(self.name.data, name.data);

        if ( resl != 0 ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;

            return self;
        }

        self.name = name;

        return self;
    }

    void
    file_write_string(void* file, Str8 string)
    {
        gr_exec_expect(file != 0, "The file must exist");

        auto& self  = *(File*) file;
        isize bytes = string.items;
        isize resl  = 0;

        resl = fwrite(string.data, bytes, 1,
            (FILE*) self.descr);

        if ( resl != bytes ) {
            self.error      = FILE_ERROR_SYSTEM;
            self.syst_error = errno;
        }
    }

    void
    file_flush(void* file)
    {
        gr_exec_expect(file != 0, "The file must exist");
    }

    /*
    Writer
    file_writer(File* file, Str8 name, File_Mode mode)
    {
        gr_exec_expect(file != 0, "The file must exist");

        auto&  self = *file;
        auto*  func = FILE_OPEN_FUNC_ARRAY[mode];

        gr_exec_expect(self.descr == 0, "The file must not be open");

        Writer writer;

        if ( mode != FILE_MODE_CREATE &&
             mode != FILE_MODE_APPEND )
            return writer;

        self = (*func)(name);

        writer.string_func = &file_write_string;
        writer.flush_func  = &file_flush;
        writer.ctxt        = (byte*) file;

        return writer;
    }
    */
} // namespace gr
