#include "b64e.hpp"
#include <iostream>

int main(){
  
  B64Encoder encoder;
  std::string s1 = "BASE 64 ENCODER!";
  std::string s2 = encoder.Encode(&s1);
  std::string s3 = encoder.Decode(&s2);
  std::cout<<"original string: "<<s1<<std::endl;
  std::cout<<"b64 encoded string: "<<s2<<std::endl;
  std::cout<<"b64 decoded string: "<<s3<<std::endl;
  
  return 0;
}