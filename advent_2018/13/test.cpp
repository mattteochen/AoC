#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

enum class Dir
{
  up,
  right,
  down,
  left
};

bool is_dir(const char &c)
{
  return c == '<' || c == '>' || c == '^' || c == 'v';
}

struct Cart
{
  int64_t x, y;
  Dir dir;
  int8_t turning_state = -1;
  Cart(const int64_t &X, const int64_t &Y, const char &c) : x(X), y(Y)
  {
    switch(c)
      {
      case '<': dir = Dir::left; break;
      case '>': dir = Dir::right; break;
      case '^': dir = Dir::up; break;
      case 'v': dir = Dir::down; break;
      }
  }
  bool operator<(const Cart &cart) const
  {
    return x < cart.x ? true : (x == cart.x ? y < cart.y : false);
  }
  bool operator==(const Cart &cart) const
  {
    return x == cart.x && y == cart.y;
  }
};

std::ostream &operator<<(std::ostream &os, const Cart &cart)
{
  return os << cart.x << "," << cart.y;
}

Cart move(const Cart &cart, const std::vector<std::string> &lines)
{
  Cart result(cart);
  switch(lines[result.y][result.x])
    {
    case '+':
      result.dir = static_cast<Dir>(
        (static_cast<int>(result.dir) + 4 + result.turning_state) % 4);
      result.turning_state = (result.turning_state + 2) % 3 - 1;
      break;
    case '/':
      switch(result.dir)
        {
        case Dir::up: result.dir = Dir::right; break;
        case Dir::right: result.dir = Dir::up; break;
        case Dir::down: result.dir = Dir::left; break;
        case Dir::left: result.dir = Dir::down; break;
        }
      break;
    case '\\':
      switch(result.dir)
        {
        case Dir::up: result.dir = Dir::left; break;
        case Dir::left: result.dir = Dir::up; break;
        case Dir::down: result.dir = Dir::right; break;
        case Dir::right: result.dir = Dir::down; break;
        }
      break;
    default: break;
    }

  switch(result.dir)
    {
    case Dir::up: --result.y; break;
    case Dir::down: ++result.y; break;
    case Dir::right: ++result.x; break;
    case Dir::left: --result.x; break;
    }

  return result;
}

int main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  std::vector<std::string> lines;
  std::set<Cart> carts;
  size_t y(0);
  std::string line;
  std::getline(infile, line);
  while(infile)
    {
      for(size_t x = 0; x < line.size(); ++x)
        {
          if(is_dir(line[x]))
            {
              carts.emplace(x, y, line[x]);
              line[x] = ((line[x] == '^' || line[x] == 'v') ? '|' : '-');
            }
        }
      lines.push_back(line);
      std::getline(infile, line);
      ++y;
    }

  bool crashed(false);
  while(carts.size() > 1)
    {
      std::set<Cart> moved_carts;
      for(auto cart(carts.begin()); cart != carts.end();)
        {
          Cart moved_cart(move(*cart, lines));
          auto crash_unmoved(carts.find(moved_cart));
          auto crash_moved(moved_carts.find(moved_cart));
          if(crash_unmoved != carts.end())
            {
              if(!crashed)
                {
                  std::cout << "Part 1: " << moved_cart << "\n";
                }
              crashed = true;
              carts.erase(crash_unmoved);
            }
          else if(crash_moved != moved_carts.end())
            {
              if(!crashed)
                {
                  std::cout << "Part 1: " << moved_cart << "\n";
                }
              crashed = true;
              moved_carts.erase(crash_moved);
            }
          else
            {
              moved_carts.insert(moved_cart);
            }
          auto old_cart(cart);
          ++cart;
          carts.erase(old_cart);
        }
      std::swap(carts, moved_carts);
    }
  for(auto &cart : carts)
    std::cout << "Part 2: " << cart << "\n";
}
