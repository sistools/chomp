# **chomp** Changes <!-- omit in toc -->


## 0.1.1 - 3rd August 2026

* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with Linux/macOS/Windows matrix, dependency install, tests, and install verification;
* Modernised **CMakeLists.txt** (**CLASP** 0.15 / **STLSoft** 1.11 / **Catch2** / **xTests**; **CLASP::core** linkage; MSVC options; `BUILD_TESTING`);
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
