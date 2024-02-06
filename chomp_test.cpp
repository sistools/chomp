
/* *********************************************************
 * includes
 */

#include "chomp.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <xtests/util/temp_file.hpp>

#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/filesystem/FILE_stream.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

#include <stdio.h>


/* *********************************************************
 * types
 */

using ::xtests::cpp::util::temp_file;


/* *********************************************************
 * compatibility
 */

#if 0
#elif PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_HPP_FILE_STREAM_MAJOR > 2 || \
      (  PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_HPP_FILE_STREAM_MAJOR == 2 && \
         PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_HPP_FILE_STREAM_MINOR >= 2)

# define FILE_stream_HAS_read_all
#endif


/* *********************************************************
 * tests
 */

SCENARIO("empty-input") {

    GIVEN("an empty input file") {

        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose);
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

            int r = sistool_chomp(in, out, 0);

            REQUIRE(0 == r);
        }

        platformstl::file_lines out_lines(tf_out);

        CHECK(0 == out_lines.size());
    }

    GIVEN("an input file with a single line") {

        static char const input[] = "abc";

        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, strlen(input));
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

            int r = sistool_chomp(in, out, 0);

            REQUIRE(0 == r);
        }

        platformstl::file_lines out_lines(tf_out);

        REQUIRE(1 == out_lines.size());
        CHECK("abc" == out_lines[0]);

#if FILE_stream_HAS_read_all

        platformstl::FILE_stream out_stm(tf_out, "r");
        auto const out_contents = out_stm.read_all<std::string>();

        CHECK("abc" == out_contents);
#endif
    }

    GIVEN("an input file with a single line and a trailing EOL") {

        static char const input[] = "abc\n";

        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, strlen(input));
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

            int r = sistool_chomp(in, out, 0);

            REQUIRE(0 == r);
        }

        platformstl::file_lines out_lines(tf_out);

        REQUIRE(1 == out_lines.size());
        CHECK("abc" == out_lines[0]);

#if FILE_stream_HAS_read_all

        platformstl::FILE_stream out_stm(tf_out, "r");
        auto const out_contents = out_stm.read_all<std::string>();

        CHECK("abc" == out_contents);
#endif
    }

    GIVEN("an input file with a single line and 3x trailing EOL") {

        static char const input[] = "abc\n\n\n";

        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, strlen(input));
        temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

        {
            FILE*   in  =   fopen(tf_in.c_str(), "r");
            FILE*   out =   fopen(tf_out.c_str(), "w");

            stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
            stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

            int r = sistool_chomp(in, out, 0);

            REQUIRE(0 == r);
        }

        platformstl::file_lines out_lines(tf_out);

        REQUIRE(1 == out_lines.size());
        CHECK("abc" == out_lines[0]);

#if FILE_stream_HAS_read_all

        platformstl::FILE_stream out_stm(tf_out, "r");
        auto const out_contents = out_stm.read_all<std::string>();

        CHECK("abc" == out_contents);
#endif
    }

    GIVEN("an input file with several lines including a set of empty lines and trailing EOLs") {

        static char const input[] = "\nabc\n\n\ndef\n\n";

        temp_file   tf_in(temp_file::EmptyOnOpen | temp_file::DeleteOnClose, input, strlen(input));

        WHEN("use default flags") {

            int const flags = 0;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(5 == out_lines.size());
            CHECK("" == out_lines[0]);
            CHECK("abc" == out_lines[1]);
            CHECK("" == out_lines[2]);
            CHECK("" == out_lines[3]);
            CHECK("def" == out_lines[4]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("\nabc\n\n\ndef" == out_contents);
#endif
        }

        AND_WHEN("use FLATTEN") {

            int const flags = SISTOOL_CHOMP_F_FLATTEN_N;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(3 == out_lines.size());
            CHECK("" == out_lines[0]);
            CHECK("abc" == out_lines[1]);
            CHECK("def" == out_lines[2]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("\nabc\ndef" == out_contents);
#endif
        }

        AND_WHEN("use CHOMP_FRONT") {

            int const flags = SISTOOL_CHOMP_F_CHOMP_FRONT;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(4 == out_lines.size());
            CHECK("abc" == out_lines[0]);
            CHECK("" == out_lines[1]);
            CHECK("" == out_lines[2]);
            CHECK("def" == out_lines[3]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("abc\n\n\ndef" == out_contents);
#endif
        }

        AND_WHEN("use FLATTEN_N") {

            int const flags = SISTOOL_CHOMP_F_FLATTEN_N;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(3 == out_lines.size());
            CHECK("" == out_lines[0]);
            CHECK("abc" == out_lines[1]);
            CHECK("def" == out_lines[2]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("\nabc\ndef" == out_contents);
#endif
        }

        AND_WHEN("use NO_CHOMP_BACK") {

            int const flags = SISTOOL_CHOMP_F_NO_CHOMP_BACK;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(6 == out_lines.size());
            CHECK("" == out_lines[0]);
            CHECK("abc" == out_lines[1]);
            CHECK("" == out_lines[2]);
            CHECK("" == out_lines[3]);
            CHECK("def" == out_lines[4]);
            CHECK("" == out_lines[5]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("\nabc\n\n\ndef\n\n" == out_contents);
#endif
        }

        AND_WHEN("use all flags") {

            int const flags = 0
                            | SISTOOL_CHOMP_F_NO_CHOMP_BACK
                            | SISTOOL_CHOMP_F_CHOMP_FRONT
                            | SISTOOL_CHOMP_F_FLATTEN_N
                            ;

            temp_file   tf_out(temp_file::EmptyOnOpen | temp_file::DeleteOnClose | temp_file::CloseOnOpen);

            {
                FILE*   in  =   fopen(tf_in.c_str(), "r");
                FILE*   out =   fopen(tf_out.c_str(), "w");

                stlsoft::scoped_handle<FILE*>   scoper_in(in, fclose);
                stlsoft::scoped_handle<FILE*>   scoper_out(out, fclose);

                int r = sistool_chomp(in, out, flags);

                REQUIRE(0 == r);
            }

            platformstl::file_lines out_lines(tf_out);

            REQUIRE(2 == out_lines.size());
            CHECK("abc" == out_lines[0]);
            CHECK("def" == out_lines[1]);

#if FILE_stream_HAS_read_all

            platformstl::FILE_stream out_stm(tf_out, "r");
            auto const out_contents = out_stm.read_all<std::string>();

            CHECK("abc\ndef\n" == out_contents);
#endif
        }

    }
}


/* ///////////////////// end of file //////////////////// */

