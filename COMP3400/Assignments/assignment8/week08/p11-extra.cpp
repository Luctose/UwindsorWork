//
// p11.cpp was not presented in class --it has been added after the class.
//
// This program addresses the issue that exceptions can be thrown when 
// performing directory traversals. If you look at the C++ Standard
// Library's filesystem library classes and functions you will notice
// that there are cosntructors, functions, etc. that accept a
// std::error_code object. Those calls will not result in an exception
// being thrown when there are errors open and/or reading directory
// information. :-)
//
// The TPPCL (Josuttis) textbook has a lot more detail on how 
// std::error_code is leveraged. In this program, I simply check
// if the error_code is true (an error occurred) or false (an error
// did not occur). This avoids issues with exceptions.
//
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <exception>
#include <execution>
#include <filesystem>
#include <functional> // std::plus<>
#include <numeric>
#include <queue>
#include <list>
#include <system_error> // for std::error_code
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace std;
  namespace fs = std::filesystem;

  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  try
  {
    uintmax_t total_size{};

    deque<fs::directory_entry> q;
    q.emplace_back( fs::path{argv[1]} );

    while (!q.empty())
    {
      auto const curdir = q.front();
      q.pop_front();

      error_code ec;
      fs::directory_iterator dir_entries{
        curdir, fs::directory_options::skip_permission_denied, ec
      };

      if (ec)
        continue; // curdir cannot be opened, so skip

      //
      // Place [begin(dir_entries),end(dir_entries)) in to a container v. Some notes:
      //
      //   * https://en.cppreference.com/w/cpp/filesystem/directory_iterator 
      //     mentioned that directory_iterator is an INPUT iterator. This 
      //     means that its values once visited cannot be retrieved again.
      //
      //   * Thus, to make two passes over the dir_entries below, we will 
      //     need to copy the directory information in to a container first.
      //
      vector v(begin(dir_entries), end(dir_entries));

      //
      // Since v is a vector, we no longer have to worry about concurrency 
      // issues (e.g., race conditions) that can occur when running things in 
      // parallel if we use execution::par since (i) the data is held in a 
      // container that isn't being modified and (ii) . That said, how much 
      // benefit is there doing this for most directories as most are small?
      // Certainly large directories or director
      //
  
      // First, add all directories to q...
      //   * This is done sequentially since there is not much point in 
      //     doing this in parallel. Also the *inserter() calls are not
      //     thread-safe.
      copy_if(
        begin(v), end(v),
        back_inserter(q),
        [](auto const& an_entry) 
        { 
          error_code ec1, ec2;
          return 
            is_directory(an_entry.path(), ec1) && 
            !is_symlink(an_entry.path(), ec2) && 
            !ec1 && !ec2
          ; 
        }
      );

      // Second, total up all file sizes...
      //   * This is done in parallel using execution::par --but how much
      //     benefit would this yield? On many systems very liitle (this is
      //     why it is important to benchmark things). On systems with 
      //     slow hardware or networked file systems, there is more benefit
      //     provided the load generated by the parallel threads don't
      //     overload things causing them to use significantly more time.
      total_size +=
        transform_reduce(
          execution::par,
          begin(v), end(v),
          uintmax_t{},
          plus<>{},
          [](auto const& entry)
          {
            uintmax_t retval{};

            error_code ec1;
            if (is_regular_file(entry.path(), ec1) && !ec1)
            {
              error_code ec2;
              if (auto sz = file_size(entry.path(), ec2); !ec2)
                retval = sz;
            }
            return retval;
          }
        )
      ;
    }
    cout << "Total size of all files: " << total_size << '\n';
  }
  catch (std::exception const& e)
  {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
  }

  return EXIT_SUCCESS;
}
