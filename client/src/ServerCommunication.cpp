#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(const char * url){
  this->url = std::string(url);
  curl_global_init(CURL_GLOBAL_WIN32);
}

bool ServerCommunication::checkLogin(const char * username, const char * password, std::string &mesg){
  char hash[41];
  bool login = false;
  this->sha1Hash(password, &hash[0]);

  CURL *curl;
  CURLcode res;

  int datalen = 53 + strlen(username);
  char * data;

  try{
    data = new char[datalen + 1];
  } catch (int e){
    mesg+="Error: Could not allocate memory for request data";
    return login;
  }

  sprintf(data, "a=login&u=%s&p=%s", username, hash);

  curl = curl_easy_init();
  if(curl) {
    std::string resp;
    curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)datalen);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, catch_resp);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      mesg+="Error: request failed";
    }
    else {
      // printf("Resp: %s\n", resp.c_str());
      size_t sep = resp.find('|');
      if (sep == std::string::npos) mesg += resp;
      else if(resp[0] == '-')
        mesg += resp.substr(sep+1);
      else{
        int lvl = resp[0]-'0';
        login = (lvl == 2);
        if (login)
          mesg += "Logged in successfully";
        else
          mesg += "User not allowed to access client";
      }
    }
    curl_easy_cleanup(curl);
  }
  delete[] data;
  return login;
}

size_t catch_resp(void * buffer, size_t size, size_t nmemb, void *userp){
  size_t len = size * nmemb;
  ((std::string *) userp)->append((char *)buffer, len);
  return len;
}

void ServerCommunication::sha1Hash(const char * data, char * hash){
  unsigned char buf[20];
  sha1::calc(data, strlen(data), &buf[0]);
  sha1::toHexString(buf, hash);
}
