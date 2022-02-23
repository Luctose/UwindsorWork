#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
void output(T& object)
{
  cout << "There are " << object.size() << " elements.\n";
  for (int const& i : object)
    cout << i << ' ';
  cout << '\n';
}

int main()
{
  vector<int> v;

  for (int i; cin >> i; )
    v.push_back(i);

  vector<int> v2;
  transform(
    begin(v), end(v), // input "range", i.e., [begin,end)
    back_inserter(v2), // start of the output
    [](int const& value)
    {
      return value*2;
    }
  );

  output(v);
  output(v2);

  cout << "All values from 3 up to but not including 5 are...\n";
  auto pos1 = find(begin(v), end(v), 3);
  auto pos2 = find(pos1, end(v), 5);
  for (auto i=pos1, iEnd=pos2; i != iEnd; ++i)
    cout << *i << ' ';
  cout << '\n';

  transform(
    pos1, pos2,
    pos1,
    [](int const& value)
    {
      return value*-1;
    }
  );
  
  cout << "All values from 3 up to but not including 5 after *-1 are...\n";
  for (auto i=pos1, iEnd=pos2; i != iEnd; ++i)
    cout << *i << ' ';
  cout << '\n';

  output(v);
}
