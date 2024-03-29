#pragma once

# include <string>

// _type - 1(змея) 2(препятствие) 3(яблоко)

class Piece {
  int   _x;
  int   _y;

public:
  //  Construct
  Piece();
  Piece(int x, int y);
  // Destruct
  ~Piece();
  //  Getters
  int       GetX() const;
  int       GetY() const;
  //  Setters
  void      SetX(int x);
  void      SetY(int y);

private:
  Piece &operator=(Piece const & src) = delete;
  Piece(Piece const & src) = delete;

};

std::ostream& operator<<(std::ostream& os, const Piece& df);
