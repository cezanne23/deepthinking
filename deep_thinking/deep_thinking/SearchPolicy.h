#pragma once

#include <string>
#include <vector>

using namespace std;

class Search {
 public:
  virtual vector<int> search() const = 0;
};

class SearhByName : public Search {
 private:
  virtual vector<int> search() const override{

  };
};

class SearhByPhoneNumber : public Search {
 private:
  virtual vector<int> search() const override{

  };
};

class SearhByBirth : public Search {
 private:
  virtual vector<int> search() const override{

  };
};
