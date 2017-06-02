// string constructor
#include <iostream>
#include <string>

struct test_t {
    int i;
    char j = 'c';
};

class Test2 {
public:
    int num;
    Test2(int i);
};

class Test {
public:
    Test(int i);
    void init();
    int num;
    Test2 t;
};

Test::Test(int i) : num(i), t(8)
{

}

void Test::init()
{
    t = Test2(8);
}

int main ()
{
    Test t = Test(3);
    std::cout << t.t.num << std::endl;

  std::string s0 ("Initial string");

  // constructors used in the same order as described above:
  std::string s1;
  std::string s2 (s0);
  std::string s3 (s0, 8, 3);
  std::string s4 ("A character sequence");
  std::string s5 ("Another character sequence", 12);
  std::string s6a (10, 'x');
  std::string s6b (10, 42);      // 42 is the ASCII code for '*'
  std::string s7 (s0.begin(), s0.begin()+7);

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
  std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';

  s2 = std::string("Hey");
  std::cout << s2.size() << std::endl;
  return 0;
}
