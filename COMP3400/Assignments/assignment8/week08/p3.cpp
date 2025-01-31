#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>

int main()
{
  namespace fs = std::filesystem;

  try
  {
    fs::recursive_directory_iterator di("..");
    for (auto const& direntry : di)
    {
      bool isdir = is_directory(direntry);
      bool isfile = is_regular_file(direntry);
      std::cout << isdir << ' ' << isfile << ' ' << direntry.path() << '\n';
    }
  }
  catch (std::exception const& e)
  {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
