file(REMOVE_RECURSE
  "CMakeFiles/docs"
  "doxygen/xml/index.xml"
  "sphinx/index.html"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/docs.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
