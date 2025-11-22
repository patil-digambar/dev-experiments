# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-src"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-build"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/digambar/dev-experiments/SkillForge-Project/middlewareframework/middlewareframework/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
