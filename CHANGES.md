# chomp - Changes <!-- omit in toc -->


## 0.2.0 - 1st September 2026

* Fixed closing of **stdin** / **stdout** when input or output is a pipe;
* Output-write failures are now reported and reflected in the exit code;
* Consume **sistools-common-c** for `--help` / `--version` via **`stcc_show_help()`** / **`stcc_show_version()`**;
* Version output now uses **Diagnosticism** version strings (via **sistools-common-c**);
* Added **`SISTOOL_CHOMP_VER_ALPHABETA`**;


## 0.1.2 - 27th August 2026

* Fixed **cmake/BuildType.cmake** so the default `CMAKE_BUILD_TYPE` is set correctly in the CMake cache (`set(CMAKE_BUILD_TYPE … CACHE …)` instead of `set(CACHE CMAKE_BUILD_TYPE …)`);


## 0.1.1 - 24th August 2026

* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with Linux/macOS/Windows matrix, dependency install, tests, and install verification;
* Added Doxygen API documentation (**Doxyfile**, **doc/mainpage.md**, **generate_doxygen.sh**) and a section-1 man page (**doc/chomp.1**);
* Modernised **CMakeLists.txt** (**CLASP** 0.15 / **STLSoft** 1.11.1 / **Catch2** / **xTests**; **CLASP::core** linkage; MSVC options; `BUILD_TESTING`; man-page installation);
* Added **cmake/BuildType.cmake**;
* Canonicalised CMake helper scripts (**prepare_cmake.sh**, **build_cmake.sh**, **clean_cmake.sh**, **remove_cmake_artefacts.sh**, **run_all_unit_tests.sh**) with **SIS_CMAKE_*** support and MinGW/MSVC flags;
* Added **run_all_unit_tests.cmd**;
* Added **.sis/script_info_lines.txt** and **.sis/project_name.txt**;
* Project boilerplate updates (**.gitattributes**, **.gitignore**, **.vimrc**, **.vscode/settings.json**);
* Added **NEWS.md** and README badge row (incl. CI → **ci.yml**);
* Updated homepage to **https://github.com/sistools/chomp**;
* Updated **LICENSE** copyright years to 2020-2026;


## 0.1.0 - 6th February 2024

* Initial CMake-based release (**CMakeLists.txt**, helper scripts, unit tests, and project documentation);


<!-- ########################### end of file ########################### -->
