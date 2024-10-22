#ifndef B64E_HPP
#define B64E_HPP

#include <string>

  class B64Encoder{
    public:  
    unsigned char B64CT[63];
    unsigned char B64NT[122];

    B64Encoder(void){
      for(int i =  0; i<26; i++) B64CT[i] = i + 65;
      for(int i = 26; i<52; i++) B64CT[i] = i + 71;
      for(int i = 52; i<62; i++) B64CT[i] = i - 4;
      B64CT[62]  = '+';
      B64CT[63]  = '/';
      
      for(int i = 0; i<64; i++) B64NT[B64CT[i]] = i;
      B64NT['='] = 0;
    }

    std::string Encode(std::string *str){
      std::string res;
      unsigned char rem = 0, m1 = 255>>6, m2 = 255>>4, m3 = (char) 255 << 6, m4 = 255>>2, c;
      for(int i = 0; (*str)[i]!='\0'; i++){
        switch(i%3) {
          case 2:  
            c = (*str)[i] & m4;
            res += this->B64CT[c];    
          break;
          case 1:
            c = rem ^ ((*str)[i] >> 4);
            res += this->B64CT[c];
            rem = ((*str)[i] & m2) << 2;
            if((*str)[i+1] != '\0'){
              c = rem ^ (((*str)[i+1] & m3) >> 6);
              res += this->B64CT[c];
              break;
            }
            res+= this->B64CT[rem];
          break;
          default:  
            rem = ((*str)[i] & m1) << 4;
            c = (*str)[i] >> 2;
            res += this->B64CT[c];
            if((*str)[i+1]=='\0') res+= this->B64CT[rem];
          break;
        }  
      }
      while(res.length()&1) res+='=';
      return res;
    }
    
    std::string Decode(std::string *str){
      std::string res; 
      unsigned char c;
      for(int i = 0; (*str)[i]!='=' && (*str)[i]!='\0'; i+=2){
        switch(i%4) {
          case 2: 
          c = (this->B64NT[(*str)[i-1]] << 4) ^ (this->B64NT[(*str)[i]] >> 2);
          if(c<126) res+=c;
          c = (this->B64NT[(*str)[i]] << 6)   ^ this->B64NT[(*str)[i+1]];
          if(c<126) res+=c;
          break;
          default: 
          c = (this->B64NT[(*str)[i]] << 2) ^ (this->B64NT[(*str)[i+1]] >> 4);
          if(c<126) res+=c;
        }
      }
      return res;
    }
  };
#endif 